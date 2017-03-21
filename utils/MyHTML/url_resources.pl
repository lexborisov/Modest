#!/usr/bin/perl -w

BEGIN {
        use FindBin;
        push @INC, $FindBin::Bin. "/../ext/";
};

use utf8;
use strict;
use MyHTML::Base;

my $simple_encode = {
	# A C0 control is a code point in the range U+0000 to U+001F, inclusive
	# The simple encode set are C0 controls and all code points greater than U+007
};

my $default_encode = {
	" " => '',
	'"' => '',
	"#" => '',
	"<" => '',
	">" => '',
	"?" => '',
	"`" => '',
	"{" => '',
	"}" => ''
};

my $userinfo_encode = {
	"/" => '',
	":" => '',
	";" => '',
	"=" => '',
	"@" => '',
	"[" => '',
	"\\" => '',
	"]" => '',
	"^" => '',
	"|" => ''
};

my $forbidden_host_code_point = {
	"\x00" => '',
	"\x09" => '',
	"\x0A" => '',
	"\x0D" => '',
	"\x20" => '',
	"#"       => '',
	"\%"      => '',
	"/"       => '',
	":"       => '',
	"?"       => '',
        "\@"      => '',
        "["       => '',
        "\\"      => '',
        "]"       => ''
};

my $utils = MyHTML::Base->new(dirs => {source => "../../source/myhtml/url", template => "tmpl"});

my $utils_data = $utils->read_tmpl("url_resources.h");
$utils->save_src("resources.h", $utils_data,
	{
		BODY =>
                        get_text_data(creare_for_query(), "myhtml_url_resources_static_map_query_charset") .
                        get_text_data(creare_for_forbidden_host_code_point(), "myhtml_url_resources_static_map_forbidden_host_code_point") .
                        "/* A C0 control is a code point in the range U+0000 to U+001F, inclusive. The C0 control percent-encode set are C0 controls and all code points greater than U+007E. */\n".
                        get_text_data(creare_for_simple(), "myhtml_url_resources_static_map_C0") .
                        '/* The path percent-encode set is the myhtml_url_resources_static_map_path and code points U+0020, \'"\', "#", "<", ">", "?", "`", "{", and "}". */'."\n".
			get_text_data(creare_for_default(), "myhtml_url_resources_static_map_path") .
                        '/* The userinfo percent-encode set is the myhtml_url_resources_static_map_path and code points "/", ":", ";", "=", "@", "[", "\", "]", "^", and "|". */'."\n".
			get_text_data(creare_for_userinfo(), "myhtml_url_resources_static_map_userinfo")
	}
);

sub creare_for_query {
	my @data;
	
	for my $codepoint (0..255) {
		my $char = chr($codepoint);
		
                # less than 0x21, greater than 0x7E, or is 0x22, 0x23, 0x3C, or 0x3E
		if ($codepoint < 33 || $codepoint > 126 || $codepoint == 0x22 ||
                    $codepoint == 0x23 || $codepoint == 0x3C || $codepoint == 0x3E) 
		{
                        push @data, "0x00";
		}
		else {
                        push @data, sprintf("0x%02x", $codepoint);
		}
	}
	
	return \@data;
}

sub creare_for_forbidden_host_code_point {
	my @data;
	
	for my $codepoint (0..255) {
		my $char = chr($codepoint);
		
		if (exists $default_encode->{$char} || $char eq chr(0))
		{
                        push @data, sprintf("0x%02x", $codepoint);
		}
		else {
			push @data, "0xff";
		}
	}
	
	return \@data;
}

sub creare_for_default {
	my @data;
	
	for my $codepoint (0..255) {
		my $char = chr($codepoint);
		
		if (exists $default_encode->{$char} ||
			$codepoint <= 0x1F || $codepoint > 0x7E)
		{
			push @data, "0x00"
		}
		else {
			push @data, sprintf("0x%02x", $codepoint);
		}
	}
	
	return \@data;
}

sub creare_for_simple {
	my @data;
	
	for my $codepoint (0..255) {
		my $char = chr($codepoint);
		
		if ($codepoint <= 0x1F || $codepoint > 0x7E)
		{
			push @data, "0x00"
		}
		else {
			push @data, sprintf("0x%02x", $codepoint);
		}
	}
	
	return \@data;
}

sub creare_for_userinfo {
	my @data;
	
	for my $codepoint (0..255) {
		my $char = chr($codepoint);
		
		if (exists $default_encode->{$char} ||
			exists $userinfo_encode->{$char} ||
			$codepoint <= 0x1F || $codepoint > 0x7E)
		{
			push @data, "0x00"
		}
		else {
			push @data, sprintf("0x%02x", $codepoint);
		}
	}
	
	return \@data;
}

sub get_text_data {
	my ($data, $name) = @_;
	
	my @return;
	
	push @return, "static const unsigned char $name\[] =\n{";
	
	my $max = $#$data;
	foreach my $num (0..$max) {
		push @return, "\n\t" unless $num % 10;
		push @return, $data->[$num]. ($num != $max ? ", " : "");
	}
	
	push @return, "\n};\n\n";
	
	join "", @return;
}
