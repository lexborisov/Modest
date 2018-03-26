#!/usr/bin/perl -w

BEGIN {
        use FindBin;
        push @INC, $FindBin::Bin. "/../ext/";
};

use utf8;
use strict;

my $static_list_index_length = 57;
my $func_map = {
        not => "",
        matches => "",
        has => "",
        dir => "",
        lang => "",
        current => "",
        drop => "",
        'nth-child' => "",
        'nth-last-child' => "",
        'nth-of-type' => "",
        'nth-last-of-type' => "",
        'nth-column' => "",
        'nth-last-column' => "",
        'contains' => ""
};

my $INDEX_OF_NAMES = print_functions();

my $result = create_result($static_list_index_length);
my $static_list = create_static_list_index($result);

print $static_list, "\n";

sub create_result {
        my ($static_list_index_length) = @_;
        my $result = {};
        
        foreach my $ns (sort {$a cmp $b} keys %$func_map)
        {
                my $id = get_index_id($ns, $static_list_index_length);
                
                push @{$result->{$id}}, [$ns, length($ns)];
        }
        
        my $count = 0;
        my @res = (["MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_UNDEF", sprintf("0x%02x", $count++)],
                   ["MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_UNKNOWN", sprintf("0x%02x", $count++)]);
        
        foreach my $name (sort {$a cmp $b} keys %$func_map) {
                push @res, ["MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_".uc(name_to_correct_name($name)), sprintf("0x%02x", $count++)];
        }
        
        push @res, ["MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LAST_ENTRY", sprintf("0x%02x", $count++)];
        
        print "enum mycss_selectors_sub_type_pseudo_class_function {\n\t";
        print join(",\n\t", @{format_list_text(\@res, "= ")}), "\n";
        print "}\ntypedef mycss_selectors_sub_type_pseudo_class_function_t;\n\n";
        
        print "Max number: $count\n";
        
        foreach my $name (sort {$a cmp $b} keys %$func_map) {
                print "void * mycss_selectors_value_pseudo_class_function_", lc(name_to_correct_name($name)), "_create(mycss_result_t* result, bool set_clean);\n";
        }
        print "\n";
        
        foreach my $name (sort {$a cmp $b} keys %$func_map) {
                print "void * mycss_selectors_value_pseudo_class_function_", lc(name_to_correct_name($name)), "_create(mycss_result_t* result, bool set_clean)\n{\n";
                print "\treturn NULL;\n";
                print "}\n\n";
        }
        
        foreach my $name (sort {$a cmp $b} keys %$func_map) {
                print "void * mycss_selectors_value_pseudo_class_function_", lc(name_to_correct_name($name)), "_destroy(mycss_result_t* result, void* value, bool self_destroy);\n";
        }
        print "\n";
        
        foreach my $name (sort {$a cmp $b} keys %$func_map) {
                print "void * mycss_selectors_value_pseudo_class_function_", lc(name_to_correct_name($name)), "_destroy(mycss_result_t* result, void* value, bool self_destroy)\n{\n";
                print "\tif(self_destroy) {\n";
                print "\t\treturn NULL;\n";
                print "\t}\n\n";
                print "\treturn value;";
                print "\n}\n\n";
        }
        
        print "static const mycss_selectors_value_function_destroy_f mycss_selectors_value_function_destroy_map[MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LAST_ENTRY] = {\n";
        print "\tmycss_selectors_value_pseudo_class_function_undef_destroy,\n";
        print "\tmycss_selectors_value_pseudo_class_function_undef_destroy,\n";
        foreach my $name (sort {$a cmp $b} keys %$func_map) {
                print "\tmycss_selectors_value_pseudo_class_function_", lc(name_to_correct_name($name)), "_destroy,\n";
        }
        print "};\n\n";
        
        $result;
}

sub format_list_text {
        my ($list, $join_val) = @_;
        
        my ($max, $len) = (0, 0);
        foreach my $struct (@$list) {
                $len = length($struct->[0]);
                $max = $len if $len > $max;
        }
        
        my @res;
        foreach my $struct (@$list) {
                $len = $max - length($struct->[0]);
                push @res, sprintf("%s%$len"."s %s%s", $struct->[0], ($len ? " " : ""), $join_val, $struct->[1]);
        }
        
        \@res;
}

sub test_result {
        my $op = [0, undef];
        
        foreach my $idx (1..1024) {
                my $result = create_result($idx);
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
                $INDEX_OF_NAMES->{$list_sorted[$i]->[0]}, ', '.
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
                        $INDEX_OF_NAMES->{$list_sorted[0]->[0]}, ', '.
                        "$id, $i},\n";
				}
				else {
                        push @res, "\t{NULL, 0, NULL, 0, 0},\n";
                }
        }
        
        "static const mycss_selectots_function_begin_entry_t mycss_selectors_function_begin_map_index[] = \n{\n". join("", @res, @$struct) ."};\n"
}

sub print_functions {
        my $headers;
        foreach my $name (keys %$func_map) {
                my $corect_name = name_to_correct_name($name);
                $headers->{$name} = "mycss_selectors_function_begin_$corect_name";
        }
        
        print join( "\n", map {"void ". $headers->{$_} ."(mycss_result_t* result, mycss_selectors_entry_t* selector);"} keys %$headers), "\n\n";
        
        foreach my $key (keys %$headers) {
                print "void ". $headers->{$key} ."(mycss_result_t* result, mycss_selectors_entry_t* selector)\n{\n\t\n}\n\n";
        }
        
        $headers;
}

sub name_to_correct_name {
        my ($name) = @_;
        $name =~ s/[-]+/_/g;
        $name;
}

