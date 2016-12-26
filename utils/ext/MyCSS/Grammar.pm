package MyCSS::Grammar;

use utf8;
use strict;
use Encode;

use MyCSS::Token;

my $GRAMMAR_SUB_INDEX = {
	'['  => \&GRAMMAR_LEFT_SQUARE_BRACKET,
	']'  => \&GRAMMAR_RIGHT_SQUARE_BRACKET,
	'<'  => \&GRAMMAR_BEGIN_LESS_THAN_SIGN,
	'|'  => \&GRAMMAR_VERTICAL_LINE,
};

my $GRAMMAR_MOD_INDEX = {
	'*'  => \&GRAMMAR_PARSE_MOD_ASTERISK,
	'?'  => \&GRAMMAR_PARSE_MOD_QUESTION_MARK,
	'|'  => \&GRAMMAR_PARSE_MOD_VERTICAL_LINE, # fake
	'['  => \&GRAMMAR_PARSE_MOD_SQUARE_BRACKET,
	'#'  => \&GRAMMAR_PARSE_MOD_DEFAULT,
	'+'  => \&GRAMMAR_PARSE_MOD_DEFAULT,
	''   => \&GRAMMAR_PARSE_MOD_DEFAULT
};

my $GRAMMAR_SYS_MAP = {
	'['  => 1,
	'|'  => 1
};

sub new {
	bless {}, $_[0];
}

sub parser {
	my $grammar = shift;
	
	my ($result, $index) = ({}, []);
	my ($key, $value);
	
	my @current;
	foreach my $line (split /\n/, $_[0])
	{
		$line =~ s/^\s+//;
		$line =~ s/\s+$//;
		next unless $line;
		
		if ($line =~ /^[^'"]+\s*=/) {
			($key, $value) = split /\s*=\s*/, $line, 2;
			
			push @$index, $key;
			
			$result->{ $key } = [] unless $result->{ $key };
			$grammar->parse_line($result->{ $key }, $value);
		}
		else {
			$grammar->parse_line($result->{ $key }, $line);
		}
	}
	
	($result, $index);
}

sub parse_line {
	my $grammar = shift;
	my $current = shift;
	
	my @line = split //, $_[0];
	my $tmp  = 0;
	my $i    = 0;
	
	for ($i = 0; $i < @line; ++$i) {
		if ($line[$i] eq '<') {
			my $res;
			($res, $i) = $grammar->parse_line_entry(\@line, $i);
			push @$current, join "", @$res;
			
			$tmp = $i;
		}
		elsif($line[$i] =~ /\s/) {
			push @$current, join "", @line[($tmp + 1)..($i - 1)] if ($tmp + 1) < $i;
			$tmp = $i;
		}
	}
	
	push @$current, join "", @line[($tmp + 1)..($i - 1)] if ($tmp + 1) < $i;
}

sub parse_line_entry {
	my ($grammar, $line, $i) = @_;
	
	my $is_the_end = 0;
	my $is = 0;
	my @res;
	
	for ($i = $i; $i < @$line; ++$i) {
		if ($line->[$i] eq '\\') {
			$is++;
			
			if (($is % 2) == 0) {
				push @res, $line->[$i];
			}
		}
		elsif($line->[$i] eq '\'') {
			my $cur_res;
			($cur_res, $i) = $grammar->parse_line_text($line, ($i + 1), "'");
			push @res, join "", "'", @$cur_res;
		}
		elsif($line->[$i] eq '"') {
			my $cur_res;
			($cur_res, $i) = $grammar->parse_line_text($line, ($i + 1), '"');
			push @res, join "", '"', @$cur_res;
		}
		elsif ($line->[$i] eq '>') {
			push @res, $line->[$i];
			
			if (($is % 2) == 0)
			{
				while(1) {
					++$i;
					
					if($i < @$line) {
						if($line->[$i] =~ /\s/) {
							--$i;
							last;
						}
						
						push @res, $line->[$i];
					}
					else {
						last;
					}
				}
				
				last;
			}
		}
		else {
			$is = 0 if $is;
			
			push @res, $line->[$i];
		}
	}
	
	(\@res, $i);
}

sub parse_line_text {
	my ($grammar, $line, $i, $qo) = @_;
	
	my $is_the_end = 0;
	my $is = 0;
	my @res;
	
	for ($i = $i; $i < @$line; $i++) {
		if ($line->[$i] eq '\\') {
			$is++;
			
			if (($is % 2) == 0) {
				push @res, $line->[$i];
			}
		}
		elsif ($line->[$i] eq $qo) {
			push @res, $line->[$i];
			
			if (($is % 2) == 0)
			{
				last;
			}
		}
		else {
			$is = 0 if $is;
			
			push @res, $line->[$i];
		}
	}
	
	(\@res, $i);
}

sub parse_line_other {
	my ($grammar, $line, $i) = @_;
	
	for ($i = $i; $i < @$line; ++$i) {
		if ($line->[$i] eq '>' && ($i < @$line || $line->[$i] =~ /\s/)) {
			return $i;
		}
	}
}


sub parser_file {
	my ($grammar, $filename) = @_;
	
	open my $fh, "<", $filename or die "Can't open file: $!";
	my @data = <$fh>;
	close $fh;
	
	$grammar->parser(join("", @data));
}

sub GRAMMAR_LEFT_SQUARE_BRACKET { # ([)
	my ($name, $rules, $idx, $tree, $open, $mod, $attr) = @_;
	
	my $entry = $tree->new({name => $name, mod => "[", attr => $attr});
	$open->[-1]->append_child($entry);
	
	push @$open, $entry;
}

sub GRAMMAR_RIGHT_SQUARE_BRACKET { # (])
	my ($name, $rules, $idx, $tree, $open, $mod, $attr) = @_;
	
	if(@$open <= 1) {
		warn "RIGHT SQUARE BRACKET: try delete ROOT of tree! WRONG!\n";
		exit(1);
	}
	
	my $entry = grammar_open_delete_vertical_line($open, 1);
	
	$entry->mod($mod) if $mod;
}

sub GRAMMAR_BEGIN_LESS_THAN_SIGN { # (<)
	my ($name, $rules, $idx, $tree, $open, $mod, $attr) = @_;
	
	my $entry = $tree->new({name => $name, mod => $mod, attr => $attr});
	$open->[-1]->append_child($entry);
}

sub GRAMMAR_VERTICAL_LINE { # (|)
	my ($name, $rules, $idx, $tree, $open, $mod, $attr) = @_;
	
	my $idx_find = grammar_open_find_in_scope_entry_by_name($open, "|");
	
	if ($idx_find) {
		grammar_open_delete_remove_from_end($open, $open->[$idx_find], 1);
	}
	
	my $entry = $tree->new({name => $name, mod => "|", attr => $attr});
	$open->[-1]->append_child($entry);
	
	push @$open, $entry;
}

sub grammar_open_delete_vertical_line {
	my ($open, $include) = @_;
	
	my $i = @$open;
	while ($i) {
		--$i;
		
		if($open->[$i]->name eq "[") {
			if($include) {
				return delete $open->[$i];
			}
			
			last;
		}
		
		delete $open->[$i];
	}
}

sub grammar_open_delete_remove_from_end {
	my ($open, $entry, $include) = @_;
	
	my $i = @$open;
	while ($i) {
		--$i;
		
		if($open->[$i] eq $entry) {
			delete $open->[$i] if $include;
			last;
		}
		
		delete $open->[$i];
	}
}

sub grammar_open_find_in_scope_entry_by_name {
	my ($open, $name) = @_;
	
	my $i = @$open;
	while ($i) {
		--$i;
		
		if($open->[$i]->{name} eq "[") {
			last;
		}
		elsif ($open->[$i]->{name} eq $name) {
			return $i;
		}
	}
	
	undef;
}

sub create_tree {
	my ($grammar, $rules, $name) = @_;
	
	my $root = MyCSS::Grammar::MyTree->new({name => $name});
	
	my $open = [$root];
	my $idx = 0;
	
	while($idx < @$rules)
	{
		my $name = $rules->[$idx];
		my $original_name = $name;
		my $mod = parser_delete_postmod($name);
		my $attr = parser_delete_attr($name);
		
		if($name =~ /^(.)/)
		{
			unless(exists $GRAMMAR_SUB_INDEX->{$1}) {
				warn "Not find in index: $name ($original_name)";
				$idx++;
				next;
			}
			
			if (exists $attr->{value}) {
				$name =~ s/^<//;
				$name =~ s/>$//;
				$name = "<$name ". $attr->{value} .">";
			}
			
			$GRAMMAR_SUB_INDEX->{$1}->($name, $rules, $idx, $root, $open, $mod, $attr);
		}
		
		$idx++;
	}
	
	$root;
}

sub grammar_delete_empty {
	my ($list) = @_;
	
	my $i = @$list;
	while ($i) {
		--$i;
		delete $list->[$i] unless @{$list->[$i]};
	}
}

sub parse_append {
	my ($grammar, $entry) = @_;
	
	my $end = [[]];
	if ($entry->name eq "[" || $entry->name eq "|")
	{
		my $new_start = [];
		
		if($entry->child) {
			_grammar_parse_tree($grammar, $entry->child, $new_start, $end);
		}
		
		grammar_delete_empty($end);
	}
	else
	{
		$end->[-1] = [$entry];
	}
	
	$end;
}

sub GRAMMAR_PARSE_MOD_ASTERISK { # (*)
	my ($entry, $start, $ends, $curent_ends) = @_;
	
	my $end_len = $#$ends;
	
	foreach my $cend (@$curent_ends) {
		foreach my $i (0..$end_len) {
			my $end = $ends->[$i];
			
			my @new_end = @$end;
			push @$start, \@new_end;
			
			push @new_end, @$cend;
			push @$ends, \@new_end;
		}
	}
}

sub GRAMMAR_PARSE_MOD_QUESTION_MARK { # (?)
	my ($entry, $start, $ends, $curent_ends) = @_;
	
	my $end_len = $#$ends;
	
	foreach my $cend (@$curent_ends) {
		foreach my $i (0..$end_len) {
			my $end = $ends->[$i];
			
			my @new_end = @$end;
			push @$start, \@new_end;
			
			push @new_end, @$cend;
			push @$ends, \@new_end;
		}
	}
}

sub GRAMMAR_PARSE_MOD_VERTICAL_LINE { # (|)
	my ($entry, $start, $ends, $curent_ends) = @_;
	
	foreach my $cend (@$curent_ends) {
		push @$ends, \@$cend;
		push @$start, $ends->[-1];
	}
}

sub GRAMMAR_PARSE_MOD_SQUARE_BRACKET { # ([)
	my ($entry, $start, $ends, $curent_ends) = @_;
	
	my $end_len = $#$ends;
	
	foreach my $i (0..$end_len) {
		my $end = $ends->[$i];
		
		my @tmp = @{$curent_ends->[0]};
		
		foreach my $t (1..$#$curent_ends) {
			my $cend = $curent_ends->[$t];
			
			my @new_end = (@$end, @$cend);
			push @$start, \@new_end;
			
			push @$ends, \@new_end;
		}
		
		push @$end, @tmp;
	}
}

sub GRAMMAR_PARSE_MOD_DEFAULT {
	my ($entry, $start, $ends, $curent_ends) = @_;
	
	my $end_len = $#$ends;
	
	foreach my $cend (@$curent_ends) {
		foreach my $i (0..$end_len) {
			push @{$ends->[$i]}, @$cend;
		}
	}
}

# <compound-selector> [ <t1> | <t2> ] <lalalal>
sub _grammar_parse_tree {
	my ($grammar, $entry, $start, $ends) = @_;
	
	push @$start, $ends->[-1] unless exists $ends->[-1] && @{$ends->[-1]};
	
	while ($entry) {
		my $curent_ends = parse_append($grammar, $entry);
		
		$GRAMMAR_MOD_INDEX->{ ($entry->mod || "") }->($entry, $start, $ends, $curent_ends);
		
		$entry = $entry->next;
	}
}

sub parse_tree {
	my ($grammar, $entry) = @_;
	
	my $ends  = [[]];
	my $start = [];
	
	_grammar_parse_tree($grammar, $entry->child, $start, $ends);
	grammar_delete_empty($start);
	
	$start;
}

sub decomposite {
	my ($grammar, $index_of_list, $keys, $sub_for_bless_entry) = @_;
	
	my $save_index = {};
	my $work_full = {};
	my $work_origin = {};
	
	$grammar->{sub_for_bless_entry} = $sub_for_bless_entry;
	
	foreach my $key (@$keys) {
		my $parents = [];
		my ($full_list, $origin_list) = $grammar->decomposite_list($index_of_list->{$key}, $index_of_list, $save_index, $parents);
		
		$work_full->{$key} = $full_list;
		$work_origin->{$key} = $origin_list;
	}
	
	($work_full, $work_origin);
}

sub decomposite_list {
	my ($grammar, $list, $index_of_list, $save_index, $parents) = @_;
	
	my $work_full = [];
	my $work_origin = [];
	
	foreach my $entries (@$list) {
		my ($full_list, $origin_list) = $grammar->decomposite_list_entries($entries, $index_of_list, $save_index, $parents);
		push @{$work_full}, @$full_list;
		push @{$work_origin}, @$origin_list;
	}
	
	($work_full, $work_origin);
}

sub decomposite_list_entries {
	my ($grammar, $entries, $index_of_list, $save_index, $parents) = @_;
	
	my $work_full = [[]];
	my $work_origin = [[]];
	
	foreach my $entry (@$entries)
	{
		my @next_parrents = @$parents;
		
		my ($full_list, $origin_list) = $grammar->decomposite_list_entry($entry, $index_of_list, $save_index, \@next_parrents);
		
		my $new_work_full;
		my $new_work_origin;
		
		foreach my $res_entries (@$full_list) {
			foreach my $work_entry (@$work_full) {
				push @{$new_work_full}, [@$work_entry, @$res_entries];
			}
		}
		
		foreach my $res_entries (@$origin_list) {
			foreach my $work_entry (@$work_origin) {
				push @{$new_work_origin}, [@$work_entry, @$res_entries];
			}
		}
		
		$work_full = $new_work_full;
		$work_origin = $new_work_origin;
	}
	
	($work_full, $work_origin);
}

sub decomposite_list_entry {
	my ($grammar, $entry, $index_of_list, $save_index, $parents) = @_;
	
	my $full_list = [];
	my $origin_list = [];
	
	if ($index_of_list->{ $entry->name }) {
		push @$parents, $entry;
		$grammar->decomposite_push_to_list($origin_list, $entry, $parents);
		
		if ($save_index->{$entry->name}) {
			$full_list = $save_index->{$entry->name};
		}
		else {
			$full_list = $grammar->decomposite_list($index_of_list->{ $entry->name }, $index_of_list, $save_index, $parents);
			$save_index->{$entry->name} = $full_list;
		}
	}
	else {
		$grammar->decomposite_push_to_list($origin_list, $entry, $parents);
		$grammar->decomposite_push_to_list($full_list, $entry, $parents);
	}
	
	($full_list, $origin_list);
}

sub decomposite_push_to_list {
	my ($grammar, $list, $entry, $parents) = @_;
	
	unless(ref $grammar->{sub_for_bless_entry}) {
		push @{$list}, [ MyCSS::Token->new($entry, $parents) ];
	}
	else {
		push @{$list}, [
			$grammar->{sub_for_bless_entry}->($grammar, $entry, $parents)
		];
	}
}

sub make_combine_hash_from_decomposing_list {
	my ($grammar, $list, $list_full, $sub, $glob_hash, $glob_next, $to_fix) = @_;
	
	$sub ||= sub{ $_[1]->name };
	$to_fix ||= [];
	
	my $hash = {};
	my $tmp_hash = $hash;
	
	foreach my $entries (@$list)
	{
		foreach my $i (0..$#$entries)
		{
			my $entry = $entries->[$i]->clone( $entries->[$i]->entry->clone );
			my $key = $sub->($grammar, $entry);
			
			if ($list_full->{ $entry->entry->name }) {
				my $loc_next = {};
				my $name = MyCSS::CFunction->create_func_name($entry->entry->name, "after", 0);
				
				$loc_next->{ref} = $name if ($i + 1) <= $#$entries;
				
				my $res = $grammar->make_combine_hash_from_decomposing_list($list_full->{$entry->entry->name}, $list_full, $sub, $glob_hash, $loc_next, $to_fix);
				
				foreach my $sn_ney (keys %$res) {
					$tmp_hash->{$sn_ney} = $res->{$sn_ney};
				}
				
				$glob_hash->{$name} = {} unless $glob_hash->{$name};
				$tmp_hash = $glob_hash->{$name};
				next;
			}
			
			$tmp_hash->{$key} = {} unless exists $tmp_hash->{$key};
			
			my $nr = $tmp_hash->{$key};
			
			if($glob_next) {
				if($glob_next->{ref}) {
					if($i == $#$entries) {
						$entry->{entry}->{is_last} = 0;
						$entry->{entry}->{is_next} = 1;
						
						$entry->{entry}->{is_glob} = 1;
					}
					else {
						$entry->{entry}->{is_next} = 1;
					}
					
					$entry->{entry}->{is_ref} = $glob_next->{ref};
				}
				else {
					if($i == $#$entries) {
						$entry->{entry}->{is_last} = 1;
					}
					else {
						$entry->{entry}->{is_next} = 1;
					}
				}
			}
			else {
				if($i == $#$entries) {
					$entry->{entry}->{is_last} = 1;
					$entry->{entry}->{is_next} = 0;
					$entry->{entry}->{is_glob} = 0;
				}
				else {
					$entry->{entry}->{is_last} = 0;
					$entry->{entry}->{is_next} = 1;
					$entry->{entry}->{is_glob} = 0;
				}
			}
			
			my @exists = grep {$_->{entry}->{name} eq $entry->{entry}->{name}} @{$nr->{val}};
			
			if (@exists) {
				my $current_attr = $exists[0]->{entry}->{attr};
				my $attr = $entry->{entry}->{attr};
				
				foreach my $key (keys %$attr) {
					next if $current_attr->{$key};
					$current_attr->{$key} = $attr->{$key};
				}
				
				$exists[0]->{entry}->{is_next} = 1
					if $entry->{entry}->{is_next} && !$exists[0]->{entry}->{is_next};
				
				$exists[0]->{entry}->{is_last} = 1
					if $entry->{entry}->{is_last} && !$exists[0]->{entry}->{is_last};
			}
			else {
				push @{$nr->{val}},  $entry;
			}
			
			if ($i == $#$entries) {
				unless( exists $nr->{next} ) {
					$nr->{next} = $glob_next || {};
				}
				else {
					if ($glob_next && %$glob_next) {
						foreach my $key (keys %$glob_next) {
							$nr->{next}->{$key} = $glob_next->{$key};
						}
					}
					
					if (keys %{$nr->{next}} > 1 && $nr->{next}->{ref}) {
						push @$to_fix, $nr;
					}
				}
			}
			else {
				$nr->{next} = {} unless exists $nr->{next};
				$tmp_hash = $nr->{next};
			}
		}
		
		undef $tmp_hash;
		$tmp_hash = $hash;
	}
	
	unless($glob_next) {
		foreach my $entry (@$to_fix) {
			my $ref_name = delete $entry->{next}->{ref};
			
			foreach my $name (keys %{$glob_hash->{$ref_name}}) {
				die "Oh God, dupl!!! $name; Change config" if exists $entry->{next}->{$name};
				
				$entry->{next}->{$name} = $glob_hash->{$ref_name}->{$name};
			}
		}
	}
	
	$hash;
}

sub print_list {
	my ($grammar, $result, $tab_count) = @_;
	
	foreach my $res (@$result) {
		print "\t" for 1..$tab_count || 0;
		
		print join " -> ", map {ref $_ ne "HASH" ? $_->entry->{name} : $_->{name}} @$res;
		
		print "\n";
	}
}

sub parser_delete_postmod {
	if($_[0] =~ s/^(<.*?>)([^>]+)$/$1/) {
		return $2;
	}
	elsif($_[0] =~ s/^(.*?\])([^\]+])$/$1/) {
		return $2;
	}
	
	"";
}

sub parser_delete_attr {
	my $attr = {};
	
	if($_[0] =~ s/^(<.*?)\s+(.*?)>$/$1>/) {
		my @data = split /\s+/, $2;
		
		foreach my $dt (@data) {
			my ($key, $value) = split /=/, $dt, 2;
			if(defined $value && $value =~ s/^"//) {
				$value =~ s/"$//;
			}
			
			$attr->{$key} = $value;
		}
	}
	
	$attr;
}


1;

package MyCSS::Grammar::MyTree;

sub new {
	my ($class, $args) = @_;
	
	$class = ref $class if ref $class;
	
	bless $args, $class;
}

sub append_child {
	my ($to, $entry) = @_;
	
	if ($to->{last_child}) {
		$to->{last_child}->{next} = $entry;
		$entry->{prev} = $to->{last_child};
	}
	else {
		$to->{child} = $entry;
	}
	
	$entry->{next} = undef;
	$entry->{parent} = $to;
	
	$to->{last_child} = $entry;
}

sub parent {
	$_[0]->{parent} = $_[1] if @_ > 1;
	$_[0]->{parent};
}

sub child {
	$_[0]->{child} = $_[1] if @_ > 1;
	$_[0]->{child};
}

sub next {
	$_[0]->{next} = $_[1] if @_ > 1;
	$_[0]->{next};
}

sub prev {
	$_[0]->{prev} = $_[1] if @_ > 1;
	$_[0]->{prev};
}

sub name {
	$_[0]->{name} = $_[1] if @_ > 1;
	$_[0]->{name};
}

sub mod {
	$_[0]->{mod} = $_[1] if @_ > 1;
	$_[0]->{mod};
}

sub clone {
	my %new_hash = %{$_[0]};
	$_[0]->new(\%new_hash);
}

1;
