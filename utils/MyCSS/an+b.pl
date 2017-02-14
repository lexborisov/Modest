#!/usr/bin/perl -w

BEGIN {
        use FindBin;
        push @INC, $FindBin::Bin. "/../ext/";
};

use bytes;
use strict;
use Encode;

use MyCSS::Grammar;
use MyCSS::Token;
use MyCSS::CFunction;

my $filename = "data/an+b.txt";

my $token = MyCSS::Token->new();
my $grammar = MyCSS::Grammar->new();
my $cfunc = MyCSS::CFunction->new(
	token               => $token,
	grammar             => $grammar,
	func_def            => \&My::Functions::Basic::function_default,
	func_else           => \&My::Functions::Basic::function_else,
	func_last           => \&My::Functions::Basic::function_last,
	func_prefix         => "mycss_an_plus_b_state_",
	func_whitespace     => \&My::Functions::Basic::function_whitespace,
	func_not_whitespace => \&My::Functions::Basic::function_not_whitespace,
	func_string_before  => \&My::Functions::Basic::function_string_before,
	func_string_after   => \&My::Functions::Basic::function_string_after,
	func_proto_args     => "mycss_result_t* result, mycss_an_plus_b_t* anb, mycss_an_plus_b_entry_t* anb_entry, mycss_token_t* token",
	all_chars_for_name  => 1,
	reg_name            => 1,
	func_list           => {}
);

my ($parse_res, $index_res) = $grammar->parser_file($filename);

my $index_list = {};

foreach my $key (@$index_res) {
	my $tree = $grammar->create_tree($parse_res->{$key}, $key);
	my $list = $grammar->parse_tree($tree);
	
	$index_list->{$key} = $list;
}

my $hash_full = {};
my $hash_origin = {};

foreach my $key (@$index_res) {
	my ($work_full, $work_origin) = $grammar->decomposite($index_list, [$key]);
	
	$hash_origin->{$key} = $work_origin->{$key};
}

my $key = "<anb>";

my $ghash = {};
my $attr = $grammar->make_combine_hash_from_decomposing_list($hash_origin->{$key}, $hash_origin, sub{ $_[1]->entry->name }, $ghash);

my $func_result = {};
my $first_result = $cfunc->create($key, $attr);
$cfunc->print_result_names($first_result);

foreach my $gkey (keys %$ghash) {
	$func_result->{ $gkey } = $cfunc->create($gkey, $ghash->{$gkey}, "shared")
		if %{$ghash->{$gkey}};
}

foreach my $key (keys %$func_result) {
	$cfunc->print_result_names($func_result->{$key});
}

print "\n";
$cfunc->print_result_data($first_result);
foreach my $key (keys %$func_result) {
	$cfunc->print_result_data($func_result->{$key});
}

package My::Functions;

package My::Functions::Basic;

sub function_whitespace {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	[
		"if(result->parser != mycss_an_plus_b_state_token_skip_whitespace)",
		"\t"."result->parser = mycss_an_plus_b_state_token_skip_whitespace;"
	];
}

sub function_not_whitespace {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	[
		"if(result->parser != mycss_an_plus_b_state_token_all)",
		"\t"."result->parser = mycss_an_plus_b_state_token_all;"
	];
}

sub function_string_before {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	[
		"myhtml_string_t str;",
		"mycss_token_data_to_string(result->entry, token, &str, true);"
	];
}

sub function_string_after {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	["myhtml_string_destroy(&str, false);"];
}

sub function_default {
	my ($creater, $cfunc, $fname, $type) = @_;
	
	return ["result->state = $fname;"];
}

sub function_else {
	my ($creater, $cfunc, $fname) = @_;
	
	[
		"mycss_an_plus_b_parser_expectations_error(result, anb, anb_entry, token);",
		"result->parser = result->parser_switch;",
		"return false;"
	];
}

sub function_last {
	my ($creater, $cfunc, $fname, $type, $find_next) = @_;
	
	if($find_next) {
		return [
			"MyCSS_DEBUG_MESSAGE(\"$fname\")"
		];
	}
	
	[
		"MyCSS_DEBUG_MESSAGE(\"$fname\")",
		"result->parser = result->parser_switch;"
	];
}




