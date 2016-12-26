package MyCSS::Token;

use utf8;
use strict;
use Encode;

use base qw( Exporter );

my ($TOKEN_TYPE_UNDEF, $TOKEN_INDEX_ENUM, $TOKEN_INDEX_ENUM_REV, $TOKEN_INDEX, $TOKEN_INDEX_REV);
use vars qw($AUTOLOAD $VERSION $ABSTRACT @ISA @EXPORT);

BEGIN {
	$TOKEN_TYPE_UNDEF = "MyCSS_TOKEN_TYPE_UNDEF";
	
	$TOKEN_INDEX = {
		'<ident-token>'           => "MyCSS_TOKEN_TYPE_IDENT",
		'<function-token>'        => "MyCSS_TOKEN_TYPE_FUNCTION",
		'<at-keyword-token>'      => "MyCSS_TOKEN_TYPE_AT_KEYWORD",
		'<hash-token>'            => "MyCSS_TOKEN_TYPE_HASH",
		'<string-token>'          => "MyCSS_TOKEN_TYPE_STRING",
		'<bad-string-token>'      => "MyCSS_TOKEN_TYPE_BAD_STRING",
		'<url-token>'             => "MyCSS_TOKEN_TYPE_URL",
		'<bad-url-token>'         => "MyCSS_TOKEN_TYPE_BAD_URL",
		'<delim-token>'           => "MyCSS_TOKEN_TYPE_DELIM",
		'<number-token>'          => "MyCSS_TOKEN_TYPE_NUMBER",
		'<percentage-token>'      => "MyCSS_TOKEN_TYPE_PERCENTAGE",
		'<dimension-token>'       => "MyCSS_TOKEN_TYPE_DIMENSION",
		'<unicode-range-token>'   => "MyCSS_TOKEN_TYPE_UNICODE_RANGE",
		'<include-match-token>'   => "MyCSS_TOKEN_TYPE_INCLUDE_MATCH",
		'<dash-match-token>'      => "MyCSS_TOKEN_TYPE_DASH_MATCH",
		'<prefix-match-token>'    => "MyCSS_TOKEN_TYPE_PREFIX_MATCH",
		'<suffix-match-token>'    => "MyCSS_TOKEN_TYPE_SUFFIX_MATCH",
		'<substring-match-token>' => "MyCSS_TOKEN_TYPE_SUBSTRING_MATCH",
		'<column-token>'          => "MyCSS_TOKEN_TYPE_COLUMN",
		'<whitespace-token>'      => "MyCSS_TOKEN_TYPE_WHITESPACE",
		'<CDO-token>'             => "MyCSS_TOKEN_TYPE_CDO",
		'<CDC-token>'             => "MyCSS_TOKEN_TYPE_CDC",
		'<colon-token>'           => "MyCSS_TOKEN_TYPE_COLON",
		'<semicolon-token>'       => "MyCSS_TOKEN_TYPE_SEMICOLON",
		'<comma-token>'           => "MyCSS_TOKEN_TYPE_COMMA",
		'<[-token>'               => "MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET",
		'<]-token>'               => "MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET",
		'<(-token>'               => "MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS",
		'<)-token>'               => "MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS",
		'<{-token>'               => "MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET",
		'<}-token>'               => "MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET",
		# and comment
		'<comment-token>'         => "MyCSS_TOKEN_TYPE_COMMENT"
	};
	
	$TOKEN_INDEX_ENUM = {
		MyCSS_TOKEN_TYPE_UNDEF                => 0x0000,
		MyCSS_TOKEN_TYPE_WHITESPACE           => 0x0001,
		MyCSS_TOKEN_TYPE_IDENT                => 0x0002,
		MyCSS_TOKEN_TYPE_FUNCTION             => 0x0003,
		MyCSS_TOKEN_TYPE_AT_KEYWORD           => 0x0004,
		MyCSS_TOKEN_TYPE_HASH                 => 0x0005,
		MyCSS_TOKEN_TYPE_STRING               => 0x0006,
		MyCSS_TOKEN_TYPE_URL                  => 0x0007,
		MyCSS_TOKEN_TYPE_NUMBER               => 0x0008,
		MyCSS_TOKEN_TYPE_DIMENSION            => 0x0009,
		MyCSS_TOKEN_TYPE_PERCENTAGE           => 0x000a,
		MyCSS_TOKEN_TYPE_INCLUDE_MATCH        => 0x000b,
		MyCSS_TOKEN_TYPE_DASH_MATCH           => 0x000c,
		MyCSS_TOKEN_TYPE_PREFIX_MATCH         => 0x000d,
		MyCSS_TOKEN_TYPE_SUFFIX_MATCH         => 0x000e,
		MyCSS_TOKEN_TYPE_SUBSTRING_MATCH      => 0x000f,
		MyCSS_TOKEN_TYPE_COLUMN               => 0x0010,
		MyCSS_TOKEN_TYPE_CDO                  => 0x0011,
		MyCSS_TOKEN_TYPE_CDC                  => 0x0012,
		MyCSS_TOKEN_TYPE_BAD_STRING           => 0x0013,
		MyCSS_TOKEN_TYPE_DELIM                => 0x0014,
		MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS     => 0x0015,
		MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS    => 0x0016,
		MyCSS_TOKEN_TYPE_COMMA                => 0x0017,
		MyCSS_TOKEN_TYPE_COLON                => 0x0018,
		MyCSS_TOKEN_TYPE_SEMICOLON            => 0x0019,
		MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET  => 0x001a,
		MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET => 0x001b,
		MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET   => 0x001c,
		MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET  => 0x001d,
		MyCSS_TOKEN_TYPE_BAD_URL              => 0x001e,
		MyCSS_TOKEN_TYPE_COMMENT              => 0x001f,
		MyCSS_TOKEN_TYPE_UNICODE_RANGE        => 0x0020,
		MyCSS_TOKEN_TYPE_LAST_ENTRY           => 0x0021
	};
	
	$TOKEN_INDEX_ENUM_REV = {};
	$TOKEN_INDEX_ENUM_REV->{ $TOKEN_INDEX_ENUM->{$_} } = $_ foreach keys %$TOKEN_INDEX_ENUM;
	
	$TOKEN_INDEX_REV = {};
	$TOKEN_INDEX_REV->{ $TOKEN_INDEX->{$_} } = $_ foreach keys %$TOKEN_INDEX;
	
	@ISA = qw(Exporter);
	
	{
		no strict 'refs';
		
		foreach (keys %$TOKEN_INDEX_ENUM) {
			*{ 'MyCSS::Token::'. $_ } = eval "sub{ \$TOKEN_INDEX_ENUM->{$_} }";
			push @EXPORT, $_;
		}
	}
}

sub new {
	my $token = bless {entry => $_[1], parents => $_[2], type => 0, type_name => ""}, $_[0];
	
	if(ref $token->entry) {
		my $type = $token->convert_name_to_type_like();
		$token->type( $token->type_to_num( $token->type_name( $type ) ) ) if $type;
	}
	
	$token;
}

sub clone {
	my $class = ref $_[0];
	$class->new($_[1] || $_[0]->{entry},  $_[2] || $_[0]->{parents});
}

sub entry {
	unless(ref $_[0]) {
	print "";
	}
	$_[0]->{entry};
}

sub convert_name_to_type_strict {
	my ($self, $name) = @_;
	
	$name ||= $self->entry->name;
	
	exists $TOKEN_INDEX->{$name} ? $TOKEN_INDEX->{$name} : undef;
}

sub convert_name_to_type_like {
	my ($self, $name) = @_;
	
	$name ||= $self->entry->name;
	
	$name =~ s/ .*?>$/>/;
	
	foreach my $key (keys %$TOKEN_INDEX) {
		if ($name =~ /^\s*\Q$key\E\s*$/i) {
			return $TOKEN_INDEX->{$key};
		}
	}
	
	if ($name =~ /^<'.*?'>$/) {
		return "MyCSS_TOKEN_TYPE_DELIM";
	}
	
	undef;
}

sub text_to_token {
	my ($self, $text, $return_current_if_fail) = @_;
	
	$text ||= $self->entry->name;
	
	if($text =~ /^'.*?'$/) {
		return "<delim-token>";
	}
	elsif($text =~ /^".*?"$/) {
		return "<string-token>";
	}
	elsif($text =~ /^[0-9\.\-+E]+$/) {
		return "<number-token>";
	}
	
	$return_current_if_fail ? $text : undef;
}

sub type_to_num {
	return $TOKEN_INDEX_ENUM->{$_[1]} if @_ > 1;
	$TOKEN_INDEX_ENUM->{$_[0]};
}

sub num_to_type {
	return $TOKEN_INDEX_ENUM_REV->{$_[1]} if @_ > 1;
	$TOKEN_INDEX_ENUM_REV->{$_[0]};
}

sub type_to_name {
	return $TOKEN_INDEX_REV->{$_[1]} if @_ > 1;
	$TOKEN_INDEX_REV->{$_[0]};
}

sub get_type_undef { $TOKEN_TYPE_UNDEF }

sub type {
	$_[0]->{type} = $_[1] if @_ > 1;
	$_[0]->{type};
}

sub type_name {
	$_[0]->{type_name} = $_[1] if @_ > 1;
	$_[0]->{type_name};
}

sub entry_clean_name {
	my $name = $_[1];
	$name ||= $_[0]->entry->name;
	
	return $name if $name =~ s/^<'(.*?)'>$/$1/;
	$name =~ s/^\<(.*?)\>$/$1/;
	
	$name;
}

sub join_clean_name {
	my $name = $_[1];
	$name ||= $_[0]->entry_clean_name();
	
	$name =~ s/\s+//g;
	$name;
}

1;


