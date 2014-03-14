#!/usr/bin/perl
use v5.10;
use strict;
use warnings;
use JSON::XS qw(decode_json);
use Template;
use Data::Dumper;

sub main {
    my ( $template_path ) = @_;
    my $template = Template->new( { INCLUDE_PATH => '.', ABSOLUTE => 1, PRE_CHOMP   => 1, RELATIVE=>1 } );
    my $data = decode_json( scalar readline STDIN );
    for my $data ( @{ ref($data) eq 'ARRAY' ? $data : [ $data ] } ) {
        $template->process( $template_path, $data  ) or die( $template->error );
    }
    return 0;
}


main( @ARGV ) if not caller;

