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

# !WARNING! Work! Draft version!

my $filename = "data/rules.txt";

my $token = MyCSS::Token->new();
my $grammar = MyCSS::Grammar->new();
my $cfunc = MyCSS::CFunction->new(
	token => $token,
	grammar => $grammar,
	func_def  => \&function_default,
	func_else => \&function_else,
	func_last => \&function_last,
	func_prefix => "mycss_rules_state_",
	func_whitespace => \&function_whitespace,
	func_string_before => \&function_string_before,
	func_string_after  => \&function_string_after,
	func_proto_args    => "mycss_result_t* result, mycss_rules_t* rules, mycss_token_t* token"
);

my ($parse_res, $index_res) = $grammar->parser_file($filename);
#my ($parse_res, $index_res) = $grammar->parser('<namespace> = <string-token value="i"> <string-token ws> | <delim-token value="s"> | <delim-token value="s"> <hash-token>');

sub function_whitespace {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	[
		" if(result->parser != mycss_rules_state_token_skip_whitespace)",
		"\t"."result->parser = mycss_rules_state_token_skip_whitespace;"
	];
}

sub function_string_before {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	[
		"myhtml_string_t str;",
		"mycss_token_data_to_string(result->entry, token, &str);"
	];
}

sub function_string_after {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	["myhtml_string_destroy(&str, false);"];
}

sub function_default {
	my ($creater, $cfunc, $fname, $type) = @_;
	
	["ns->state = $fname;"];
}

sub function_else {
	["result->parser = result->parser_switch;"];
}

sub function_last {
	my ($creater, $cfunc, $fname, $type) = @_;
	
	[
		"printf(\"$fname\\n\");  /* End of rules */",
		"result->parser = result->parser_switch;"
	];
}

my $index_list = {};
foreach my $key (@$index_res) {
	my $tree = $grammar->create_tree($parse_res->{$key}, $key);
	my $list = $grammar->parse_tree($tree);
	
	$index_list->{$key} = $list;
}

my $key = "<body>";

my $workd = $grammar->decomposite($index_list, [$key]);
$grammar->print_list($workd->{$key}, 1);

print "\n\n";

my $work = $grammar->decomposite($index_list, [$key], sub {
	return MyCSS::Token->new($_[1]);
});

print "Work data for $key:\n";
my $hash = $grammar->make_combine_hash_from_decomposing_list($work->{$key}, sub{ $_[1]->entry->name });
print "Combine hash count: ", scalar(keys %$hash), "\n";

my $func_result = $cfunc->create($key, $hash);
$cfunc->print_result_names($func_result);
print "\n";
$cfunc->print_result_data($func_result);


