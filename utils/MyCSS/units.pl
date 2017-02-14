#!/usr/bin/perl -w

BEGIN {
        use FindBin;
        push @INC, $FindBin::Bin. "/../ext/";
};

use utf8;
use strict;

# The Init
my $static_list_index_length = 199;
my $MAX_LEN_UNIT_NAME = 0;
my $COUNT_UNITS = 0;

my $ENUM_NAME   = "mycss_units_type";
my $ENUM_PREFIX = "MyCSS_UNIT_TYPE_";

my $INDEX_NAME  = "mycss_units_index_name";
my $STATIC_NAME = "mycss_units_index_static_for_search";

my $DEFINE_INDEX_LEN_NAME = "MyCSS_UNITS_STATIC_INDEX_FOR_SEARCH_SIZE";

# The Code
my $units = load_units("data/units.txt");

print_units_enum_and_periods($units);
#print_units_index($units);
#print_ubnit_index_entries_count();

my $result = create_result($units, $static_list_index_length);
#test_result($units);

#my $static_list = create_static_list_index($result);
#print $static_list, "\n";

sub create_result {
        my ($units, $index_length) = @_;
        
        my $result = {};
        
        foreach my $prefix (keys %$units) {
                foreach my $unit (@{$units->{$prefix}}) {
                        my $id = get_index_id($unit, $index_length);
                        push @{$result->{$id}}, [$unit, length($unit), $prefix];
                        
                        $MAX_LEN_UNIT_NAME = length($unit) if $MAX_LEN_UNIT_NAME < length($unit);
                        
                        $COUNT_UNITS++;
                }
        }
        
        $result;
}

sub test_result {
        my ($units) = @_;
        my $op = [0, undef];
        
        foreach my $idx (1..1024) {
                my $result = create_result($units, $idx);
                my $res_max = test_result_max_value($result, 0);
                
                if(!defined($op->[1]) || $op->[1] > $res_max) {
                        $op->[0] = $idx;
                        $op->[1] = $res_max;
                }
        }
        
        print "Best:\n";
        print $op->[0], ": ", $op->[1], "\n";
}

sub test_result_max_value {
        my ($res, $is_print) = @_;
        
        my $max = 0;
        foreach my $id (sort {scalar(@{$res->{$a}}) <=> scalar(@{$res->{$b}})} keys %$res) {
                print "$id: ", scalar(@{$res->{$id}}), "\n" if $is_print;
                
                $max = scalar(@{$res->{$id}}) if $max < scalar(@{$res->{$id}});
        }
        
        $max;
}

sub get_index_id {
        use bytes;
        
        my @chars = split //, $_[0];
        my $f = ord(lc($chars[0]));
        my $l = ord(lc($chars[-1]));
        
        ((($f * $l * scalar(@chars))) % $_[1]) + 1;
}

sub create_sub_static_list_index {
        my ($result, $struct, $offset) = @_;
        
        my @list_sorted = sort {$a->[1] <=> $b->[1]} @$result[0..$#$result];
        
        foreach my $i (1..$#list_sorted) {
                my $cur = $offset;
                $offset++;
                push @$struct, "\t{".
                '"'. $list_sorted[$i]->[0] .'", '. $list_sorted[$i]->[1] .', '.
                name_to_enum($list_sorted[$i]->[2]). "_" . uc($list_sorted[$i]->[0]), ', '.
                ($i < $#list_sorted ? $offset : 0) .", $cur},\n";
        }
        
        $offset;
}

sub create_static_list_index {
        my ($result) = @_;
        
        my @res;
        my $struct = [];
        my $offset = $static_list_index_length + 1;
        
        foreach my $i (0..$static_list_index_length)
        {
                if(exists $result->{$i}) {
                        my $id = 0;
                        
                        if(scalar @{$result->{$i}} > 1) {
                                $offset = create_sub_static_list_index($result->{$i}, $struct, $offset);
                                
                                $id = $offset - (@{$result->{$i}} - 1);
                        }
                        
                        my @list_sorted = sort {$a->[1] <=> $b->[1]} @{$result->{$i}}[0..$#{$result->{$i}}];
                        
                        push @res, "\t{".
                        '"'. $list_sorted[0]->[0] .'", '. $list_sorted[0]->[1] .', '.
                        name_to_enum(uc($list_sorted[0]->[0])), ', '.
                        "$id, $i},\n";
				}
				else {
                        push @res, "\t{NULL, 0, MyCSS_UNIT_TYPE_UNDEF, 0, 0},\n";
                }
        }
        
        "static const mycss_units_index_static_entry_t $STATIC_NAME\[] = \n{\n". join("", @res, @$struct) ."};\n"
}

sub print_units_enum_and_periods {
        my ($units) = @_;
        
        my $idx = 1;
        my $periods = {};
        
        print "enum $ENUM_NAME {\n";
        print "\t", name_to_enum("undef"), " = 0x00,\n";
        
        foreach my $prefix (sort {$a cmp $b} keys %$units)
        {
                if ($prefix =~ /^length/) {
                        $periods->{length}->{min} = $idx unless exists $periods->{length};
				}
                
                $periods->{$prefix}->{min} = $idx;
                
                foreach my $unit (sort {$a cmp $b} @{$units->{$prefix}}) {
                        print "\t", name_to_enum($unit), " = ", sprintf("0x%02x", $idx++), ",\n";
                }
                
                if ($prefix =~ /^length/) {
                        $periods->{length}->{max} = ($idx - 1);
				}
                
                $periods->{$prefix}->{max} = ($idx - 1);
        }
        
        print "\t", name_to_enum("last_entry"), " = ", sprintf("0x%02x", ++$idx), ",\n";
        print "}\ntypedef $ENUM_NAME\_t;\n\n";
        
        foreach my $prefix (sort {$a cmp $b} keys %$periods) {
                my $strict_name = $prefix;
                $strict_name =~ s/-/_/g;
                
                print "#define mycss_units_is_$strict_name\_type(type) (type >= ", $periods->{$prefix}->{min}, " && type <= ", $periods->{$prefix}->{max}, ")\n";
        }
}

sub print_units_index {
        my ($units) = @_;
        my $idx = 0;
        
        print "static const char * $INDEX_NAME\[", ($COUNT_UNITS + 2) ,"] = {\n";
        print '"", ';
        
        foreach my $prefix (sort {$a cmp $b} keys %$units)
        {
                foreach my $unit (sort {$a cmp $b} @{$units->{$prefix}}) {
                        print qq~"$unit", ~;
                        print "\n" unless ++$idx % 10;
                }
        }
        
        print "NULL,\n";
        print "}\n";
}

sub print_ubnit_index_entries_count {
        print "#define $DEFINE_INDEX_LEN_NAME ", $static_list_index_length, "\n";
}

sub name_to_enum {
        my ($name) = @_;
        
        $name =~ s/[-]+/_/g;
        $name = $ENUM_PREFIX. uc($name);
        
        $name;
}

sub load_units {
        my ($filename) = @_;
        
        my $res = {};
        
        open my $fh, "<", $filename or die "Can't load $filename: $!";
        binmode $fh, ":utf8";
        
        while (my $line = <$fh>) {
			$line =~ s/^\s+//;
            $line =~ s/\s+$//;
            
            my ($key, $val) = split /\s*:\s*/, $line, 2;
            
            $res->{$key} = [split /\s*,\s*/, $val];
		}
		
        close $fh;
        
        $res;
}


