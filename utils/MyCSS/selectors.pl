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

my $filename = "data/selectors_grammar_work.txt";

my $token = MyCSS::Token->new();
my $grammar = MyCSS::Grammar->new();
my $cfunc = MyCSS::CFunction->new(
	token               => $token,
	grammar             => $grammar,
	func_def            => \&My::Functions::Basic::function_default,
	func_else           => \&My::Functions::Basic::function_else,
	func_last           => \&My::Functions::Basic::function_last,
	func_prefix         => "mycss_selectors_state_",
	func_whitespace     => \&My::Functions::Basic::function_whitespace,
	func_not_whitespace => \&My::Functions::Basic::function_not_whitespace,
	func_string_before  => \&My::Functions::Basic::function_string_before,
	func_string_after   => \&My::Functions::Basic::function_string_after,
	func_proto_args     => "mycss_result_t* result, mycss_selectors_t* selectors, mycss_selectors_entry_t* selector, mycss_token_t* token",
	func_list           => {
		selector_ident_type              => \&My::Functions::selector_ident_type,
		selector_ident_attr              => \&My::Functions::selector_ident_attr,
		selector_namespace               => \&My::Functions::selector_namespace,
		selector_after_namespace         => \&My::Functions::selector_after_namespace,
		selector_id                      => \&My::Functions::selector_id,
		selector_class                   => \&My::Functions::selector_class,
		selector_matcher_eq              => \&My::Functions::selector_matcher_eq,
		selector_matcher_include         => \&My::Functions::selector_matcher_include,
		selector_matcher_dash            => \&My::Functions::selector_matcher_dash,
		selector_matcher_prefix          => \&My::Functions::selector_matcher_prefix,
		selector_matcher_suffix          => \&My::Functions::selector_matcher_suffix,
		selector_matcher_substring       => \&My::Functions::selector_matcher_substring,
		selector_value                   => \&My::Functions::selector_value,
		selector_modifier                => \&My::Functions::selector_modifier,
		selector_end                     => \&My::Functions::selector_end,
		selector_pseudo_class            => \&My::Functions::selector_pseudo_class,
		selector_function                => \&My::Functions::selector_function,
		selector_function_end            => \&My::Functions::selector_function_end,
		selector_combinator_greater_than => \&My::Functions::selector_combinator_greater_than,
		selector_combinator_plus         => \&My::Functions::selector_combinator_plus,
		selector_combinator_tilde        => \&My::Functions::selector_combinator_tilde,
		selector_combinator_column       => \&My::Functions::selector_combinator_column
	}
);

my ($parse_res, $index_res) = $grammar->parser_file($filename);
#my ($parse_res, $index_res) = $grammar->parser('<attribute-selector> = <[-token ws> <wq-name-attr> <]-token ws func=selector_end>
#<wq-name-attr> = <ident-token>? <delim-token value="|" func=selector_namespace> | <ident-token func=selector_ident_attr>');

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
	
	#$hash_full->{$key} = $grammar->make_combine_hash_from_decomposing_list($work_full->{$key}, sub{ $_[1]->entry->name });
}

#my $key = "<combinator>";
my $key = "<simple-selector>";
#my $key = "<pseudo-element-selector>";
#my $key = "<attribute-selector>";

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

sub selector_combinator_greater_than {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_combinator_greater_than(result, selectors, selector, token);"]
}

sub selector_combinator_plus {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_combinator_plus(result, selectors, selector, token);"]
}

sub selector_combinator_tilde {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_combinator_tilde(result, selectors, selector, token);"]
}

sub selector_combinator_column {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_combinator_column(result, selectors, selector, token);"]
}

sub selector_ident_type {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_ident_type(result, selectors, selector, token);"]
}

sub selector_ident_attr {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_ident_attr(result, selectors, selector, token);"]
}

sub selector_namespace {
	my ($creater, $cfunc, $fname, $type) = @_;
	
	if ($fname eq "mycss_selectors_state_simple_selector_left_bracket_vertical_bar") {
		return ["mycss_selectors_parser_selector_ident_attr(result, selectors, selector, token);",
				"mycss_selectors_parser_selector_namespace(result, selectors, result->result_entry->selector, token);"];
	}
	
	["mycss_selectors_parser_selector_namespace(result, selectors, selector, token);"]
}

sub selector_after_namespace {
	my ($creater, $cfunc, $fname, $type) = @_;
	
	if ($fname eq "mycss_selectors_state_simple_selector_ident_vertical_bar_ident" ||
		$fname eq "mycss_selectors_state_simple_selector_ident_vertical_bar_asterisk" ||
		$fname eq "mycss_selectors_state_simple_selector_vertical_bar_ident" ||
		$fname eq "mycss_selectors_state_simple_selector_vertical_bar_asterisk")
	{
		return ["mycss_selectors_parser_selector_after_namespace(result, selectors, selector, token);",
				"mycss_selectors_parser_selector_end(result, selectors, selector, token);"];
	}
	
	["mycss_selectors_parser_selector_after_namespace(result, selectors, selector, token);"]
}

sub selector_id {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_id(result, selectors, selector, token);"]
}

sub selector_class {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_class(result, selectors, selector, token);"]
}

sub selector_matcher_eq {
	my ($creater, $cfunc, $fname, $type) = @_;
	["if(selector->value == NULL)",
	 "\tselector->value = mycss_selectors_value_attribute_create(result, true);", "",
	 "mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_EQUAL;"]
}

sub selector_matcher_include {
	my ($creater, $cfunc, $fname, $type) = @_;
	["if(selector->value == NULL)",
	 "\tselector->value = mycss_selectors_value_attribute_create(result, true);", "",
	 "mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_INCLUDE;"]
}

sub selector_matcher_dash {
	my ($creater, $cfunc, $fname, $type) = @_;
	["if(selector->value == NULL)",
	 "\tselector->value = mycss_selectors_value_attribute_create(result, true);", "",
	 "mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_DASH;"]
}

sub selector_matcher_prefix {
	my ($creater, $cfunc, $fname, $type) = @_;
	["if(selector->value == NULL)",
	 "\tselector->value = mycss_selectors_value_attribute_create(result, true);", "",
	 "mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_PREFIX;"]
}

sub selector_matcher_suffix {
	my ($creater, $cfunc, $fname, $type) = @_;
	["if(selector->value == NULL)",
	 "\tselector->value = mycss_selectors_value_attribute_create(result, true);", "",
	 "mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_SUFFIX;"]
}

sub selector_matcher_substring {
	my ($creater, $cfunc, $fname, $type) = @_;
	["if(selector->value == NULL)",
	 "\tselector->value = mycss_selectors_value_attribute_create(result, true);", "",
	 "mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_SUBSTRING;"]
}

sub selector_value {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_value(result, selectors, selector, token);"]
}

sub selector_modifier {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_modifier(result, selectors, selector, token);"]
}

sub selector_end {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_end(result, selectors, selector, token);"]
}

sub selector_pseudo_class {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_pseudo_class(result, selectors, selector, token);"]
}

sub selector_function {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_function(result, selectors, selector, token);"]
}

sub selector_function_end {
	my ($creater, $cfunc, $fname, $type) = @_;
	["mycss_selectors_parser_selector_function_end(result, selectors, selector, token);"]
}


package My::Functions::Basic;

sub function_whitespace {
	my ($creater, $cfunc, $fname, $type_name) = @_;
	
	if (($fname ne "mycss_selectors_state_simple_selector_colon_colon" && $type_name eq "MyCSS_TOKEN_TYPE_FUNCTION") ||
		($fname ne "mycss_selectors_state_simple_selector_colon" && $type_name eq "MyCSS_TOKEN_TYPE_FUNCTION"))
	{
		return [];
	}
	
	[
		"if(result->parser != mycss_selectors_state_token_skip_whitespace)",
		"\t"."result->parser = mycss_selectors_state_token_skip_whitespace;"
	];
}

sub function_not_whitespace {
	my ($creater, $cfunc, $fname, $type_name) = @_;
	
	if (($fname ne "mycss_selectors_state_simple_selector_colon_colon" && $type_name eq "MyCSS_TOKEN_TYPE_FUNCTION") ||
		($fname ne "mycss_selectors_state_simple_selector_colon" && $type_name eq "MyCSS_TOKEN_TYPE_FUNCTION"))
	{
		return [];
	}
	
	[
		"if(result->parser != mycss_selectors_state_token_all)",
		"\t"."result->parser = mycss_selectors_state_token_all;"
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
	
	if ($fname ne "mycss_selectors_state_simple_selector_colon_colon_function" &&
		$fname ne "mycss_selectors_state_simple_selector_colon_function") {
		return ["result->state = $fname;"];
	}
	
	[];
}

sub function_else {
	my ($creater, $cfunc, $fname) = @_;
	
	# exception for begin selectors <ident-token>
	# if next token is whitespace or something else do not call expectations error
	# it is normally situation
	if($fname eq "mycss_selectors_state_simple_selector_ident") {
		return [
			"mycss_selectors_parser_selector_end(result, selectors, selector, token);",
			"result->parser = result->parser_switch;",
			"return false;"
		];
	}
	elsif($fname eq "mycss_selectors_state_simple_selector" ||
		  $fname eq "mycss_selectors_state_simple_selector_delim" ||
		  $fname eq "mycss_selectors_state_combinator_greater_than")
	{
		return [
			"result->parser = result->parser_switch;",
			"return false;"
		];
	}
	
	[
		"mycss_selectors_parser_expectations_error(result, selectors, selector, token);",
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




