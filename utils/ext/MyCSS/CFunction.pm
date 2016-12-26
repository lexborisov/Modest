package MyCSS::CFunction;

use utf8;
use strict;
use Encode;

use MyCSS::Token;

my $MyCSS_CFUNCTION_CHAR_NAME = {
	'0' => "Null",
	'1' => "Start of Heading",
	'2' => "Start of Text",
	'3' => "End of Text",
	'4' => "End of Transmission",
	'5' => "Enquiry",
	'6' => "Acknowledgment",
	'7' => "Bell",
	'8' => "Back Space",
	'9' => "Horizontal Tab",
	'10' => "Line Feed",
	'11' => "Vertical Tab",
	'12' => "Form Feed",
	'13' => "Carriage Return",
	'14' => "Shift Out",
	'15' => "Shift In",
	'16' => "Data Line Escape",
	'17' => "Device Control 1",
	'18' => "Device Control 2",
	'19' => "Device Control 3",
	'20' => "Device Control 4",
	'21' => "Negative Acknowledgement",
	'22' => "Synchronous Idle",
	'23' => "End of Transmit Block",
	'24' => "Cancel",
	'25' => "End of Medium",
	'26' => "Substitute",
	'27' => "Escape",
	'28' => "File Separator",
	'29' => "Group Separator",
	'30' => "Record Separator",
	'31' => "Unit Separator",
	'32' => "Space",
	'33' => "Exclamation mark",
	'34' => "Double quotes",
	'35' => "Number",
	'36' => "Dollar",
	'37' => "Procent",
	'38' => "Ampersand",
	'39' => "Single quote",
	'40' => "Left parenthesis",
	'41' => "Right parenthesis",
	'42' => "Asterisk",
	'43' => "Plus",
	'44' => "Comma",
	'45' => "Hyphen",
	'46' => "Full stop",
	'47' => "Slash or divide",
	'48' => "Zero",
	'49' => "One",
	'50' => "Two",
	'51' => "Three",
	'52' => "Four",
	'53' => "Five",
	'54' => "Six",
	'55' => "Seven",
	'56' => "Eight",
	'57' => "Nine",
	'58' => "Colon",
	'59' => "Semicolon",
	'60' => "Less than",
	'61' => "Equals",
	'62' => "Greater than",
	'63' => "Question mark",
	'64' => "At symbol",
	'65' => "A",
	'66' => "B",
	'67' => "C",
	'68' => "D",
	'69' => "E",
	'70' => "F",
	'71' => "G",
	'72' => "H",
	'73' => "I",
	'74' => "J",
	'75' => "K",
	'76' => "L",
	'77' => "M",
	'78' => "N",
	'79' => "O",
	'80' => "P",
	'81' => "Q",
	'82' => "R",
	'83' => "S",
	'84' => "T",
	'85' => "U",
	'86' => "V",
	'87' => "W",
	'88' => "X",
	'89' => "Y",
	'90' => "Z",
	'91' => "Left bracket",
	'92' => "Backslash",
	'93' => "Right bracket",
	'94' => "CircumFlex",
	'95' => "Underscore",
	'96' => "Grave accent",
	'97' => "a",
	'98' => "b",
	'99' => "c",
	'100' => "d",
	'101' => "e",
	'102' => "f",
	'103' => "g",
	'104' => "h",
	'105' => "i",
	'106' => "j",
	'107' => "k",
	'108' => "l",
	'109' => "m",
	'110' => "n",
	'111' => "o",
	'112' => "p",
	'113' => "q",
	'114' => "r",
	'115' => "s",
	'116' => "t",
	'117' => "u",
	'118' => "v",
	'119' => "w",
	'120' => "x",
	'121' => "y",
	'122' => "z",
	'123' => "Opening brace",
	'124' => "Vertical bar",
	'125' => "Closing brace",
	'126' => "Tilde",
	'127' => "Delete"
};

# temp
sub temp_delim_data_state {
	"data";
}

sub temp_token_type_state {
	"token->type";
}

sub temp_get_data_state {
	("myhtml_incoming_buffer_t *buffer = mycss_token_buffer_first(selectors->entry, token);",
    "const char data = buffer->data[ (token->begin - buffer->offset) ];");
}

sub temp_set_state {
	"selectors->state = $_[0];";
}

sub temp_function_state {
	"bool $_[0](mycss_selectors_t* selectors, mycss_token_t* token)";
}

sub temp_function_return_state {
	"return true;";
}

sub temp_check_parser_state {
	("if(selectors->parser != $_[0])",
	"\tselectors->parser = $_[0];");
}

sub new {
	my $class = shift;
	my %args = (
		grammar             => undef,
		token               => undef,
		func_list           => {},
		func_def            => \&MyCSS::CFunction::Creater::default_def,
		func_else           => \&MyCSS::CFunction::Creater::default_else,
		func_last           => \&MyCSS::CFunction::Creater::default_last,
		func_whitespace     => \&MyCSS::CFunction::Creater::default_whitespace,
		func_not_whitespace => \&MyCSS::CFunction::Creater::default_not_whitespace,
		func_prefix         => "",
		func_delim_before   => \&MyCSS::CFunction::Creater::default_delim_before,
		func_delim_after    => \&MyCSS::CFunction::Creater::default_delim_after,
		func_string_before  => \&MyCSS::CFunction::Creater::default_string_before,
		func_string_after   => \&MyCSS::CFunction::Creater::default_string_after,
		data_string         => "str.data",
		data_delim          => "*token->data",
		func_proto_args     => "mycss_entry_t* entry, mycss_token_t* token",
		all_chars_for_name  => 0,
		reg_name            => 0,
		@_
	);
	
	bless \%args, $class;
}

sub create {
	my ($cfunc, $name, $hash, $prefix) = @_;
	
	my $result = {names => [], data => []};
	$cfunc->_create($hash, $name, $prefix || "", $result);
	
	$result;
}

sub _create {
	my ($cfunc, $hash, $name, $prefix, $result) = @_;
	
	my $by_types = {};
	$name = $cfunc->create_func_name($name, "", 0);
	
	foreach my $key (sort {$a cmp $b} keys %$hash)
	{
		my $type = $cfunc->token_type_by_name($key);
		
		foreach my $val (@{$hash->{$key}->{val}}) {
			if (exists $val->entry->{attr}->{value}) {
				push @{$by_types->{$type}->{by}}, $val;
			}
			else {
				push @{$by_types->{$type}->{all}}, $val;
			}
		}
	}
	
	my $count = scalar keys %$hash;
	my $is_switcher = $count > 2 ? 1 : 0;
	my $creater = "MyCSS::CFunction::Creater";
	my $next_prefix = $prefix ? "$prefix\_$name" : $name;
	my $func_name = $cfunc->create_func_name($name, $prefix, 1);
	
	my @data;
	my $pos = 0;
	foreach my $type_num (sort {$a cmp $b} keys %$by_types) {
		my $type_name = MyCSS::Token->num_to_type($type_num);
		
		push @data, @{$creater->default($cfunc, $func_name, $next_prefix, $type_num,
						  $by_types->{ $type_num }->{all},
						  $by_types->{ $type_num }->{by},
						  $is_switcher,
						  $pos)};
		
		$pos++;
	}
	
	push @data, @{$creater->default_type_else($cfunc, $func_name, $by_types, $is_switcher)};
	
	my @inside;
	my $tabs = "";
	
	push @inside, $creater->function_prototype($cfunc, $func_name), "{";
	if ($is_switcher) {
		push @inside, "\t"."switch (token->type) {";
		$tabs = "\t";
	}
	push @inside, map {"\t$tabs$_"} @data;
	if ($is_switcher) {
		push @inside, "\t"."}";
	}
	push @inside, "\t", "\t"."return true;";
	push @inside, "}", "";
	
	push @{$result->{data}}, \@inside;
	push @{$result->{names}}, $creater->function_prototype($cfunc, $func_name).";";
	
	foreach my $key (sort {$a cmp $b} keys %$hash) {
		my $hash_nm = $hash->{$key};
		next if $hash_nm->{next}->{ref};
		
		if(keys %{$hash_nm->{next}}) {
			$cfunc->_create($hash_nm->{next}, $key, $next_prefix, $result);
		}
	}
}

sub print_result_names {
	my ($cfunc, $result) = @_;
	
	foreach my $proto (@{$result->{names}}) {
		print $proto, "\n";
	}
}

sub print_result_data {
	my ($cfunc, $result) = @_;
	
	foreach my $entries (@{$result->{data}}) {
		print join("\n", @$entries), "\n";
	}
}

sub token     { $_[0]->{token} }
sub grammar   { $_[0]->{grammar} }
sub func_list { $_[0]->{func_list} }
sub func_def  { $_[0]->{func_def} }
sub func_else { $_[0]->{func_else} }
sub func_last { $_[0]->{func_last} }
sub all_chars_for_name { $_[0]->{all_chars_for_name} }
sub reg_name { $_[0]->{reg_name} }

sub token_type_by_name {
	my $type_name = MyCSS::Token->convert_name_to_type_like($_[1]) || MyCSS::Token->get_type_undef();
	MyCSS::Token->type_to_num($type_name);
}

sub token_type_name_by_name {
	my $type_name = MyCSS::Token->convert_name_to_type_like($_[1]) || MyCSS::Token->get_type_undef();
	$type_name;
}

sub create_func_name {
	my ($cfunc, $name, $prefix, $full) = @_;
	
	my $func_name = "";
	
	if (defined $name && $name ne "") {
		my $c_name = MyCSS::Token->entry_clean_name($name);
		my ($only_name, $value) = split / /, $c_name, 2;
		
		if(defined $value) {
			if($cfunc->all_chars_for_name) {
				my @nname;
				
				foreach my $char (split //, $value) {
					if($cfunc->reg_name) {
						if($char eq "^") {
							push @nname, "begin";
						}
						elsif($char eq "\$") {
							push @nname, "end";
						}
						else {
							push @nname, lc($MyCSS_CFUNCTION_CHAR_NAME->{ ord(lc($char)) });
						}
					}
					else {
						push @nname, lc($MyCSS_CFUNCTION_CHAR_NAME->{ ord(lc($char)) });
					}
				}
				
				$func_name = join "_", @nname;
			}
			elsif(length($value) == 1 && exists $MyCSS_CFUNCTION_CHAR_NAME->{ ord(lc($value)) }) {
				$func_name = lc($MyCSS_CFUNCTION_CHAR_NAME->{ ord(lc($value)) });
			}
			else {
				$func_name = lc($value);
			}
		}
		else {
			$func_name = lc($c_name);
			
			$func_name =~ s/\-token$//;
			
			if (length($func_name) == 1 && exists $MyCSS_CFUNCTION_CHAR_NAME->{ ord(lc($func_name)) }) {
				$func_name = lc($MyCSS_CFUNCTION_CHAR_NAME->{ ord(lc($func_name)) });
			}
		}
	}
	
	$func_name =~ s/\s+|\||-/_/g;
	$func_name =~ s/_+/_/g;
	
	my $end_name = ($prefix ? $prefix."_" : "") .$func_name;
	
	if ($full) {
		return $cfunc->{"func_prefix"}. $end_name;
	}
	
	$end_name;
}


package MyCSS::CFunction::Creater;

sub default_type_begin {
	my ($self, $cfunc, $type, $all, $by, $is_switcher, $pos) = @_;
	
	my @data;
	my $type_name = $cfunc->token->num_to_type($type);
	
	if ($is_switcher) {
		push @data, $self->cont_case_token_type($type_name);
	}
	else {
		push @data, $self->cont_if_token_type($type_name, $pos);
	}
	
	\@data;
}

sub default_type_end {
	my ($self, $cfunc, $type, $all, $by, $is_switcher, $pos) = @_;
	
	my @data;
	my $type_name = $cfunc->token->num_to_type($type);
	
	if ($is_switcher) {
		push @data, $self->cont_case_token_type_end($type_name);
	}
	else {
		push @data, $self->cont_if_token_type_end($type_name);
	}
	
	\@data;
}

sub get_func {
	my ($self, $val) = @_;
	return $val->entry->{attr}->{func} if $val->entry->{attr}->{func};
	
	my $parents = $val->{parents};
	my $i = @$parents;
	
	while ($i) {
		$i--;
		
		my $entry = $parents->[$i];
		return $entry->{attr}->{func} if $entry->{attr}->{func};
	}
	
	undef;
}

sub get_func_last {
	my ($self, $val) = @_;
	return $val->entry->{attr}->{func_last} if $val->entry->{attr}->{func_last};
	
	my $parents = $val->{parents};
	my $i = @$parents;
	
	while ($i) {
		$i--;
		
		my $entry = $parents->[$i];
		return $entry->{attr}->{func_last} if $entry->{attr}->{func_last};
	}
	
	undef;
}

sub default_function {
	my ($self, $cfunc, $prefix, $type, $val, $all, $by, $is_switcher) = @_;
	
	my @data;
	my $attr = $val->entry->{attr};
	my $function_name = $cfunc->create_func_name($val->entry->name, "$prefix", 1);
	
	my $func = $self->get_func($val);
	if ($func) {
		push @data, @{$cfunc->func_list->{$func}->($self, $cfunc, $function_name, $type, $val->entry->{is_last})};
	}
	
	if ($val->entry->{is_last})
	{
		my $func_last = $self->get_func_last($val);
		
		if ($func_last) {
			push @data, @{$cfunc->func_list->{ $func_last }->($self, $cfunc, $function_name, $type, $val->entry->{is_next})};
		}
		else {
			push @data, @{$cfunc->func_last->($self, $cfunc, $function_name, $type, $val->entry->{is_next})};
		}
	}
	
	if ($val->entry->{is_next}) {
		if ($val->entry->{is_glob}) {
			$function_name = $cfunc->create_func_name($val->entry->{is_ref}, "shared", 1);
		}
		
		push @data, @{$cfunc->func_def->($self, $cfunc, $function_name, $type, $val->entry->{is_last})};
	}
	
	\@data;
}

sub default_function_for_all {
	my ($self, $cfunc, $prefix, $type, $all, $by) = @_;
	
	my @data;
	my (@next, @empty, @glob);
	
	my $type_name = $cfunc->token->num_to_type($type);
	my $function_name = $cfunc->create_func_name($cfunc->token->type_to_name($type_name), "$prefix", 1);
	
	foreach my $val (@$all) {
		if ($val->entry->{is_next}) {
			push @next, $val;
		}
		
		if($val->entry->{is_last}) {
			push @empty, $val;
		}
		
		if($val->entry->{is_glob}) {
			push @glob, $val;
		}
	}
	
	my @vals;
	foreach (@next, @empty) {
		my $func = $self->get_func($_);
		push @vals, $func if $func;
	}
	
	if (@vals) {
		push @data, @{$cfunc->func_list->{ $vals[0] }->($self, $cfunc, $function_name, $type, scalar(@empty))};
	}
	
	if (@empty) {
		my @vals;
		foreach (@empty) {
			my $func = $self->get_func_last($_);
			push @vals, $func if $func;
		}
		
		if (@vals) {
			push @data, @{$cfunc->func_list->{ $vals[0] }->($self, $cfunc, $function_name, $type, scalar(@next))};
		}
		else {
			push @data, @{$cfunc->func_last->($self, $cfunc, $function_name, $type, scalar(@next))};
		}
		
		push @data, "" if @next;
	}
	
	if (@next) {
		if (@glob) {
			$function_name = $cfunc->create_func_name($glob[0]->entry->{is_ref}, "shared", 1);
		}
		
		push @data, @{$cfunc->func_def->($self, $cfunc, $function_name, $type, scalar(@empty))};
	}
	
	\@data;
}

sub default_type_values {
	my ($self, $cfunc, $prefix, $type, $all, $by, $is_switcher) = @_;
	
	my $type_name = $cfunc->token->num_to_type($type);
	my $function_name = $cfunc->create_func_name($cfunc->token->type_to_name($type_name), "$prefix", 1);
	
	my @delim  = grep {$_->{type_name} eq "MyCSS_TOKEN_TYPE_DELIM"} @$by;
	my @string = grep {$_->{type_name} eq "MyCSS_TOKEN_TYPE_STRING" ||
					   $_->{type_name} eq  "MyCSS_TOKEN_TYPE_AT_KEYWORD" ||
					   $_->{type_name} eq  "MyCSS_TOKEN_TYPE_IDENT" ||
					   $_->{type_name} eq  "MyCSS_TOKEN_TYPE_DIMENSION"
					   } @$by;
	
	my $max = 0;
	foreach my $entry (@string) {
		$max = length($entry->entry->{attr}->{value})
			if $max < length($entry->entry->{attr}->{value});
	}
	
	if ($max == 1) {
		@delim = @string;
		@string = ();
	}
	
	my @data;
	my $npos = 0;
	foreach my $npos (0..$#$by) {
		my $val = $by->[$npos];
		my $attr = $val->entry->{attr};
		
		if($val->{type_name} eq "MyCSS_TOKEN_TYPE_DELIM") {
			push @data, map {"\t$_"} $self->cont_if_char($attr->{value}, $npos);
		}
		elsif(length($attr->{value}) == 0) {
			die "Length Value is 0\n";
		}
		elsif(@string == 0) {
			push @data, map {"\t$_"} $self->cont_if_char($attr->{value}, $npos);
		}
		else {
			push @data, map {"\t$_"} $self->cont_if_string($attr->{value}, $npos);
		}
		
		push @data, map {"\t\t$_"} @{$self->default_function($cfunc, $prefix, $type, $val, $all, $by, $is_switcher)};
		
		if (exists $val->entry->{attr}->{ws} && $val->entry->{is_next}) {
			my @after = @{$cfunc->{func_whitespace}->($self, $cfunc, $function_name, $type_name)};
			push @data, "\t\t", (map {"\t\t$_"} @after) if @after;
		}
		elsif($val->entry->{is_next}) {
			my @after = @{$cfunc->{func_not_whitespace}->($self, $cfunc, $function_name, $type_name)};
			push @data, "\t\t", (map {"\t\t$_"} @after) if @after;
		}
		
		push @data, "\t}";
	}
	
	\@data;
}

sub default_type_else {
	my ($self, $cfunc, $fname, $by_types, $is_switcher) = @_;
	
	my @data;
	
	if ($is_switcher) {
		push @data, $self->cont_case_token_type_default();
	}
	else {
		push @data, $self->cont_if_token_type_default();
	}
	
	push @data, map {"\t$_"} @{$cfunc->func_else->($self, $cfunc, $fname)};
	
	if ($is_switcher) {
		if ($data[-1] !~ /return/) {
			push @data, $self->cont_case_token_type_default_end();
		}
		else {
			push @data, "}";
		}
	}
	else {
		push @data, $self->cont_if_token_type_default_end();
	}
	
	\@data;
}

sub default {
	my ($self, $cfunc, $function_name, $prefix, $type, $all, $by, $is_switcher, $pos) = @_;
	
	my @data = @{$self->default_type_begin($cfunc, $type, $all, $by, $is_switcher, $pos)};
	
	my $data_len = @data;
	push @data, map {"\t$_"} @{$self->default_function_for_all($cfunc, $prefix, $type, $all, $by)};
	
	if($by && @$by)
	{
		my @delim  = grep {$_->{type_name} eq "MyCSS_TOKEN_TYPE_DELIM"} @$by;
		my @string = grep {$_->{type_name} eq "MyCSS_TOKEN_TYPE_STRING" ||
						   $_->{type_name} eq  "MyCSS_TOKEN_TYPE_AT_KEYWORD" ||
						   $_->{type_name} eq  "MyCSS_TOKEN_TYPE_IDENT" ||
						   $_->{type_name} eq  "MyCSS_TOKEN_TYPE_DIMENSION"
						   } @$by;
		
		my $max = 0;
		foreach my $entry (@string) {
			$max = length($entry->entry->{attr}->{value})
				if $max < length($entry->entry->{attr}->{value});
		}
		
		if ($max == 1) {
			@delim = @string;
			@string = ();
		}
		
		if (@delim) {
			push @data, map {"\t$_"} @{$cfunc->{func_delim_before}->($self, $cfunc, scalar(@string))};
		}
		if (@string) {
			push @data, map {"\t$_"} @{$cfunc->{func_string_before}->($self, $cfunc, scalar(@delim))};
		}
		
		push @data, "\t" if $data_len < @data;
		push @data, @{$self->default_type_values($cfunc, $prefix, $type, $all, $by, $is_switcher, $pos)};
		
		my @not_vals = grep {not exists $_->entry->{attr}->{value}} @$by;
		if (@not_vals) {
			my @val_func = grep {exists $_->entry->{attr}->{func}} @not_vals;
			
			if (@val_func > 1) {
				die "To many call functions from one type in current level\n";
			}
			
			if (@val_func) {
				push @data, map {"\t\t$_"} @{$self->default_function($cfunc, $prefix, $type, $val_func[0], $all, $by, $is_switcher)};
			}
			else {
				push @data, map {"\t\t$_"} @{$self->default_function($cfunc, $prefix, $type, $not_vals[0], $all, $by, $is_switcher)};
			}
		}
		else {
			push @data, map {"\t$_"} @{$self->default_type_else($cfunc, $function_name, undef, 0)};
		}
		
		if (@delim) {
			my @delim_after = @{$cfunc->{func_delim_after}->($self, $cfunc, scalar(@string))};
			push @data, map {"\t$_"} @delim_after if @delim_after;
		}
		if (@string) {
			my @string_after = @{$cfunc->{func_string_after}->($self, $cfunc, scalar(@delim))};
			push @data, "\t", (map {"\t$_"} @string_after) if @string_after;
		}
	}
	
	my @ws = grep {exists $_->entry->{attr}->{ws}} @$all;
	my @is_next = grep {$_->entry->{is_next}} @$all;
	
	my $type_name = $cfunc->token->num_to_type($type);
	
	if (@ws && @is_next) {
		my @after = @{$cfunc->{func_whitespace}->($self, $cfunc, $function_name, $type_name)};
		push @data, "\t", (map {"\t$_"} @after) if @after;
	}
	elsif(@is_next) {
		my @after = @{$cfunc->{func_not_whitespace}->($self, $cfunc, $function_name, $type_name)};
		push @data, "\t", (map {"\t$_"} @after) if @after;
	}
	
	push @data, @{$self->default_type_end($cfunc, $type, $all, $by, $is_switcher, $pos)};
	
	\@data;
}

sub cont_case_token_type_default_end {
	"\tbreak;",
	"}";
}

sub cont_if_token_type_default_end {
	"}";
}

sub cont_case_token_type_default {
	"default: {";
}

sub cont_if_token_type_default {
	"else {";
}

sub cont_case_token_type_end {
	"\tbreak;",
	"}";
}

sub cont_if_token_type_end {
	"}";
}

sub cont_case_token_type {
	"case $_[1]: {";
}

sub cont_if_token_type {
	($_[2] ? "else " : "") . "if(token->type == $_[1]) {";
}

sub cont_if_char {
	($_[2] ? "else " : "") . "if(*token->data == '$_[1]') {";
}

sub cont_if_string {
	($_[2] ? "else " : "") . "if(myhtml_strncasecmp(str.data, \"$_[1]\", ". length($_[1]) .") == 0) {";
}

sub default_else {
	[""];
}

sub default_def {
	[""];
}

sub default_last {
	[""];
}

sub default_string_before {
	[];
}

sub default_string_after {
	[];
}

sub default_delim_before {
	[];
}

sub default_delim_after {
	[];
}

sub default_whitespace {
	[];
}

sub default_not_whitespace {
	[];
}

sub function_prototype {
	"bool $_[2](". $_[1]->{func_proto_args} .")";
}

1;