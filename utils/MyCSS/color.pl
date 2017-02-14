#!/usr/bin/perl -w

BEGIN {
        use FindBin;
        push @INC, $FindBin::Bin. "/../ext/";
};

use utf8;
use strict;

use MyHTML::Base;

my $color_types = {
        "rgb"         => ["rgb", 3, "mycss_values_color_parser_rgb"],
        "rgba"        => ["rgba", 4, "mycss_values_color_parser_rgba"],
        "hsl"         => ["hsl", 3, "mycss_values_color_parser_hsl"],
        "hsla"        => ["hsla", 4, "mycss_values_color_parser_hsla"],
        "hwb"         => ["hwb", 3, "mycss_values_color_parser_hwb"],
        "gray"        => ["gray", 4, "mycss_values_color_parser_gray"],
        "device-cmyk" => ["device-cmyk", length("device-cmyk")],
        "color-mod"   => ["color-mod", length("color-mod")],
        "color"       => ["color", 5],
        "red"         => ["red", 3],
        "green"       => ["green", 5],
        "blue"        => ["blue", 4],
        "alpha"       => ["alpha", 5],
        "a"           => ["a", 1],
        "hue"         => ["hue", 3],
        "saturation"  => ["saturation", length("saturation")],
        "lightness"   => ["lightness", length("lightness")],
        "whiteness"   => ["whiteness", length("whiteness")],
        "blackness"   => ["blackness", length("blackness")],
        "tint"        => ["tint", length("tint")],
        "shade"       => ["shade", length("shade")],
        "blend"       => ["blend", length("blend")],
        "blenda"      => ["blenda", length("blenda")],
        "contrast"    => ["contrast", length("contrast")]
};

# The Code
my $colors = load_from_file("data/color.txt");
my $static_index_size = test_result($colors);
my $static_function_index_size = test_result($color_types);

#
# Create Color Resources
#
my $result = create_result($colors, $static_index_size);
my $result_type = create_result($color_types, $static_function_index_size);

my $utils = MyHTML::Base->new(dirs => {source => "/new/C-git/Modest/source/mycss", template => "tmpl"});
my $data_const = $utils->read_tmpl("color_resources.h");

$utils->save_src("values/color_resources.h", $data_const, {
        BODY => create_static_list_index($result, $static_index_size,
                "mycss_values_color_index_static_entry_t mycss_values_color_name_index_static_for_search", "MyCSS_VALUES_COLOR_ID_",
                sub {
                        return name_to_enum($_[0]->[0], $_[1]). ', '. $_[0]->[3];
                }).
                "\n". mn_index($colors, "mycss_values_color_name_index") ."\n\n".
                
                create_static_list_index($result_type, $static_function_index_size,
                "mycss_values_color_function_index_static_entry_t mycss_values_color_function_index_static_for_search", "MyCSS_VALUES_COLOR_FUNCTION_ID_",
                sub {
                        return name_to_enum($_[0]->[0], $_[1]) .", ". ($_[0]->[2] ? $_[0]->[2] : "mycss_values_color_parser_undef");
                }).
                "\n". mn_index($color_types, "mycss_values_color_function_name_index"),
        
        DEFINED => "#define MyCSS_COLOR_NAME_STATIC_INDEX_FOR_SEARCH_SIZE $static_index_size\n".
                   "#define MyCSS_COLOR_FUNCTION_STATIC_INDEX_FOR_SEARCH_SIZE $static_function_index_size"
});

#
# Create Color Const
#
$utils = MyHTML::Base->new(dirs => {source => "/new/C-git/Modest/source/mycss", template => "tmpl"});
$data_const = $utils->read_tmpl("color_const.h");

$utils->save_src("values/color_const.h", $data_const, {
        BODY => mn_enum($colors, "mycss_values_color_id", "MyCSS_VALUES_COLOR_ID_") ."\n".
                mn_enum($color_types, "mycss_values_color_function_id", "MyCSS_VALUES_COLOR_FUNCTION_ID_")
});

sub create_result {
        my ($colors, $index_length) = @_;
        
        my $result = {};
        
        foreach my $name (keys %$colors) {
                my $id = get_index_id($name, $index_length);
                push @{$result->{$id}}, $colors->{$name};
        }
        
        $result;
}

sub test_result {
        my ($colors) = @_;
        my $op = [0, undef];
        
        foreach my $idx (1..1024) {
                my $result = create_result($colors, $idx);
                my $res_max = test_result_max_value($result, 0);
                
                if(!defined($op->[1]) || $op->[1] > $res_max) {
                        $op->[0] = $idx;
                        $op->[1] = $res_max;
                }
        }
        
        print "Best:\n";
        print $op->[0], ": ", $op->[1], "\n";
        
        $op->[0];
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
        my ($result, $struct, $offset, $enum_prefix, $sub) = @_;
        
        my @list_sorted = sort {$a->[1] <=> $b->[1]} @$result[0..$#$result];
        
        foreach my $i (1..$#list_sorted) {
                my $cur = $offset;
                $offset++;
                push @$struct, "\t{".
                '"'. $list_sorted[$i]->[0] .'", '. $list_sorted[$i]->[1] .', '.
                $sub->($list_sorted[$i], $enum_prefix) .", ".
                ($i < $#list_sorted ? $offset : 0) .", $cur},\n";
        }
        
        $offset;
}

sub create_static_list_index {
        my ($result, $static_list_index_length, $static_name, $enum_prefix, $sub) = @_;
        
        my @res;
        my $struct = [];
        my $offset = $static_list_index_length + 1;
        
        foreach my $i (0..$static_list_index_length)
        {
                if(exists $result->{$i}) {
                        my $id = 0;
                        
                        if(scalar @{$result->{$i}} > 1) {
                                $offset = create_sub_static_list_index($result->{$i}, $struct, $offset, $enum_prefix, $sub);
                                
                                $id = $offset - (@{$result->{$i}} - 1);
                        }
                        
                        my @list_sorted = sort {$a->[1] <=> $b->[1]} @{$result->{$i}}[0..$#{$result->{$i}}];
                        
                        push @res, "\t{".
                        '"'. $list_sorted[0]->[0] .'", '. $list_sorted[0]->[1] .', '.
                        $sub->($list_sorted[0], $enum_prefix) .', ',
                        "$id, $i},\n";
				}
				else {
                        push @res, "\t{NULL, 0, ". $sub->(["undef", 5, 0, 0, 0], $enum_prefix) .", 0, 0},\n";
                }
        }
        
        "static const $static_name\[] = \n{\n". join("", @res, @$struct) ."};\n"
}

sub mn_enum {
        my ($color, $enum_name, $prefix) = @_;
        
        my $idx = 1;
        my (@res, @return);
        
        push @res, [name_to_enum("undef", $prefix), "0x0000"];
        foreach my $name (sort {$a cmp $b} keys %$color) {
                push @res, [name_to_enum($name, $prefix), sprintf("0x%04x", $idx++)];
        }
        push @res, [name_to_enum("last_entry", $prefix), sprintf("0x%04x", ++$idx)];
        
        push @return, "enum $enum_name {";
        push @return, "\t". join(",\n\t", @{MyHTML::Base->format_list_text(\@res, " = ")});
        push @return, "}\ntypedef $enum_name\_t;\n\n";
        
        join("\n", @return);
}

sub mn_index {
        my ($color, $index_name) = @_;
        my $idx = 0;
        
        my (@res, @return);
        
        push @res, "\t\"\"";
        foreach my $name (sort {$a cmp $b} keys %$color)
        {
                push @res, "\t\"$name\"";
        }
        
        push @return, "static const char * $index_name\[". (scalar(keys %$color) + 2) ."] = {";
        push @return, join(",\n", @res). ",";
        push @return, "\tNULL";
        push @return, "};";
        
        join "\n", @return;
}

sub name_to_enum {
        my ($name, $prefix) = @_;
        
        $name =~ s/[-]+/_/g;
        $name = $prefix. uc($name);
        
        $name;
}

sub load_from_file {
        my ($filename) = @_;
        
        my $res = {};
        
        open my $fh, "<", $filename or die "Can't load $filename: $!";
        binmode $fh, ":utf8";
        
        while (my $line = <$fh>) {
			$line =~ s/^\s+//;
            $line =~ s/\s+$//;
            
            my ($name, $hex, $r, $g, $b) = split /\s+/, $line;
            $hex =~ s/^\#//;
            
            $res->{$name} = [$name, length($name), $hex, hex($hex), $r, $g, $b];
		}
		
        close $fh;
        
        $res;
}


