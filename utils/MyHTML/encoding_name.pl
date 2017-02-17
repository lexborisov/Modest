#!/usr/bin/perl -w

BEGIN {
        use FindBin;
        push @INC, $FindBin::Bin. "/../ext/";
};

use utf8;
use strict;
use MyHTML::Base;
use JSON::XS;

my $static_list_index_length = 419;

my $utils = MyHTML::Base->new(dirs => {source => "../../source/myhtml", template => "tmpl"});
my $raw_data = $utils->read_tmpl_raw("encoding/encodings.json");
my $encodings = decode_json(join("", @$raw_data));
#test_result();

my ($result, $index) = create_result($encodings, $static_list_index_length);
print_enum($index);
#print_for_test_meta($result);

#my $static_list = create_static_list_index($result);
#print $static_list, "\n";

print "";

sub print_for_test_meta {
        my ($result) = @_;
        
        foreach my $key (sort {$a cmp $b} keys %$result) {
                foreach my $encode_entry (sort {$a cmp $b} @{$result->{$key}})
                {
                        print $encode_entry->[0], "\n";
                        print '<meta http-equiv="Content-Type" Content="text/html; charset=', $encode_entry->[1], '">', "\n\n";
                }
        }
}

sub create_result {
        my ($encodings, $static_list_index_length) = @_;
        my $result = {};
        my $index = {};
        
        foreach my $entry (@$encodings) {
                foreach my $encoding (@{$entry->{encodings}}) {
                        next if $encoding->{name} =~ /replacement/i;
                        
                        $index->{ $encoding->{name} } = 1;
                        
                        foreach my $label (sort {$a cmp $b} @{$encoding->{labels}}) {
                                my $id = get_index_id($label, $static_list_index_length);
                                
                                push @{$result->{$id}}, [$encoding->{name}, $label, length($label), length($encoding->{name})];
                        }
                }
        }
        
        ($result, $index);
}

sub test_result {
        my $op = [0, undef];
        
        foreach my $idx (1..2048) {
                my $result = create_result($encodings, $idx);
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
        
        my @list_sorted = sort {$a->[2] <=> $b->[2]} @$result[0..$#$result];
        
        foreach my $i (1..$#list_sorted) {
                my $cur = $offset;
                $offset++;
                
                push @$struct, "\t{".
                '"'. $list_sorted[$i]->[0] .'", '. $list_sorted[$i]->[3] .', '.
                '"'. $list_sorted[$i]->[1] .'", '. $list_sorted[$i]->[2] .', '.
                name_to_myhtml_encoding($list_sorted[$i]->[0]), ', '.
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
                        
                        my @list_sorted = sort {$a->[2] <=> $b->[2]} @{$result->{$i}}[0..$#{$result->{$i}}];
                        
                        push @res, "\t{".
                        '"'. $list_sorted[0]->[0] .'", '. $list_sorted[0]->[3] .', '.
                        '"'. $list_sorted[0]->[1] .'", '. $list_sorted[0]->[2] .', '.
                        name_to_myhtml_encoding($list_sorted[0]->[0]), ', '.
                        "$id, $i},\n";
				}
				else {
                        push @res, "\t{NULL, 0, NULL, 0, 0, 0, 0},\n";
                }
        }
        
        "static const myhtml_encoding_detect_name_entry_t myhtml_encoding_detect_name_entry_static_list_index[] = \n{\n". join("", @res, @$struct) ."};\n"
}

sub name_to_myhtml_encoding {
        my ($name) = @_;
        
        $name =~ s/[-]+/_/g;
        $name = "MyHTML_ENCODING_". uc($name);
        
        $name;
}

sub print_enum {
        my ($index) = @_;
	
	print "enum myhtml_encoding_list {\n\t";
        
        my @vals;
        push @vals, ["MyHTML_ENCODING_DEFAULT", "0x00", "utf_8"];
	push @vals, ["MyHTML_ENCODING_AUTO", "0x01", "NULL"];
	push @vals, ["MyHTML_ENCODING_NOT_DETERMINED", "0x02", "NULL"];
        push @vals, ["MyHTML_ENCODING_UTF_8", "0x00", "utf_8"];
	push @vals, ["MyHTML_ENCODING_UTF_16LE", "0x04", "utf_16le"];
	push @vals, ["MyHTML_ENCODING_UTF_16BE", "0x05", , "utf_16be"];
	push @vals, ["MyHTML_ENCODING_X_USER_DEFINED", "0x06", "x_user_defined"];
	
	my $i = 7; 
	foreach my $id (sort {$a cmp $b} keys %$index) {
                $id =~ s/[-\s]+/_/g;
                next if $id =~ /UTF_8$/i;
                next if $id =~ /UTF_16LE$/i;
                next if $id =~ /UTF_16BE$/i;
                next if $id =~ /X_USER_DEFINED$/i;
                
                push @vals, ["MyHTML_ENCODING_". uc($id), sprintf("0x%02x", $i), lc($id)];
                
		$i++;
	}
	
        push @vals, ["MyHTML_ENCODING_LAST_ENTRY", sprintf("0x%02x", $i), "NULL"];
        
        print join(",\n\t", @{MyHTML::Base->format_list_text(\@vals, "= ")}), "\n";
        
	print "}\ntypedef myhtml_encoding_t;\n\n";
        
        print "static const myhtml_encoding_custom_f myhtml_encoding_function_index[] = \n{\n";
        foreach my $entry (@vals) {
                if($entry->[2] eq "NULL") {
                        print "\t",  $entry->[2], ",\n";
                } else {
                        print "\t",  "myhtml_encoding_decode_", $entry->[2], ",\t// ", $entry->[0], "\n";
                }
        }
        
        print "};\n";
        
        print "static const myhtml_encoding_entry_name_index_t myhtml_encoding_entry_name_index_static_list_index[(MyHTML_ENCODING_LAST_ENTRY + 1)] =\n{\n";
        
        foreach my $entry (sort {hex($a->[1]) <=> hex($b->[1])} @vals) {
                $entry->[0] =~ s/MyHTML_ENCODING_//;
                
                if($entry->[0] ne "SHIFT_JIS") {
                        $entry->[0] =~ s/_/-/g;
                }
                
                if($entry->[0] eq "LAST-ENTRY") {
                        $entry->[0] = "";
                }
                
                #if($entry->[0] eq "AUTO") {
                #        $entry->[0] = "";
                #}
                
                print "\t", '{"', $entry->[0], '", ', length($entry->[0]), "}", ",\n";
        }
        
        print "};\n";
}




