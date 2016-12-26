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

my $filename = "data/namespace.txt";

my $token = MyCSS::Token->new();
my $grammar = MyCSS::Grammar->new();
my $cfunc = MyCSS::CFunction->new(
	token               => $token,
	grammar             => $grammar,
	func_def            => \&My::Functions::Basic::function_default,
	func_else           => \&My::Functions::Basic::function_else,
	func_last           => \&My::Functions::Basic::function_last,
	func_whitespace     => \&My::Functions::Basic::function_whitespace,
	func_not_whitespace => \&My::Functions::Basic::function_not_whitespace,
	func_string_before  => \&My::Functions::Basic::function_string_before,
	func_string_after   => \&My::Functions::Basic::function_string_after,
	func_prefix         => "mycss_namespace_state_",
	func_proto_args     => "mycss_result_t* result, mycss_namespace_t* ns, mycss_namespace_entry_t* ns_entry, mycss_token_t* token",
	func_list           => {
		namespace_begin   => \&My::Functions::namespace_begin,
		namespace_url     => \&My::Functions::namespace_url,
		namespace_name    => \&My::Functions::namespace_name,
		namespace_end     => \&My::Functions::namespace_end
	}
);

my ($parse_res, $index_res) = $grammar->parser_file($filename);

my $index_list = {};
foreach my $key (@$index_res) {
	my $tree = $grammar->create_tree($parse_res->{$key}, $key);
	my $list = $grammar->parse_tree($tree);
	
	$index_list->{$key} = $list;
}

my $key = "<namespace>";

my $work = $grammar->decomposite($index_list, [$key], sub {
	return MyCSS::Token->new($_[1]);
});

print "Work data for $key:\n";
my $hash = $grammar->make_combine_hash_from_decomposing_list($work->{$key}, sub{ $_[1]->entry->name });

my $func_result = $cfunc->create($key, $hash);
$cfunc->print_result_names($func_result);
$cfunc->print_result_data($func_result);

package My::Functions;

sub namespace_begin {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_namespace_parser_begin(result, ns, ns_entry, token);"]
}

sub namespace_name {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_namespace_parser_name(result, ns, ns_entry, token);"]
}

sub namespace_url {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_namespace_parser_url(result, ns, ns_entry, token);"]
}

sub namespace_end {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_namespace_parser_end(result, ns, ns_entry, token);"]
}

package My::Functions::Basic;

sub function_whitespace {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	[
		" if(result->parser != mycss_namespace_state_token_skip_whitespace)",
		"\t"."result->parser = mycss_namespace_state_token_skip_whitespace;"
	];
}

sub function_not_whitespace {
	my ($creater, $cfunc, $exists_delim) = @_;
	
	[
		"if(result->parser != mycss_namespace_state_token_all)",
		"\t"."result->parser = mycss_namespace_state_token_all;"
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

sub function_last {
	my ($creater, $cfunc, $fname, $type, $find_next) = @_;
	
	if($find_next) {
		return [
			"printf(\"$fname\\n\");  /* End of selector */"
		];
	}
	
	[
		"printf(\"$fname\\n\");  /* End of selector */",
		"result->parser = result->parser_switch;"
	];
}

sub function_default {
	my ($creater, $cfunc, $fname, $type) = @_;
	
	["ns->state = $fname;"];
}

sub function_else {
	["mycss_namespace_parser_expectations_error(result, ns, ns_entry, token);",
	 "result->parser = result->parser_switch;"];
}


