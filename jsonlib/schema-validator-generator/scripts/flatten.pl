use strict;
use JSON::XS qw(decode_json encode_json);
use File::Slurp qw(slurp);
use Digest::SHA1 qw(sha1_hex);

sub id_from_json{
        my ($json) = @_;
        my $txt = encode_json($json);
        if ( $txt =~ /^[\"\{\},\w\:\-]{1,40}$/ ) {
                $txt =~ tr/:,\{\}\"-/__/d;
                return $txt;
        } else {
            return sha1_hex($txt);
        }
}


sub flatten_subschema {
    my ( $schema, $cache ) = @_;
    my $desc = delete $schema->{'description'};
    my $id = $schema->{"id"} || id_from_json($schema);
    if ( $cache->{$id} ) {
        warn ("this schema is already cached: ", encode_json($schema), "\n" );
        $cache->{$id}->{'used'}++;
        return $id;
    }

    my @constraints ;

    if ( $schema->{'properties'} ) {
        foreach my $key ( keys %{$schema->{'properties'}} ) {
                my $value = $schema->{'properties'}->{$key} ;
                my $schema_id = $value->{'$ref'} || flatten_subschema($value, $cache ) ;
                    push @constraints, {
                        type => "has_attribute",
                        value => {
                                name  => $key,
                                schema => $schema_id,
                        }

                }
        
        }
    }
    if ( $schema->{'type'}  ) {
            push @constraints, {
                    type  => 'has_type',
                    value =>   $schema->{'type'}
            }
    }
    if ( $schema->{'format'}  ) {
            push @constraints, {
                    type  => 'has_format',
                    value =>   $schema->{'format'}
            }
    }
    $cache->{$id} = {
            constraints => \@constraints,
            used => 1,
            desc => $desc || encode_json($schema)
            };
    return $id;

}

sub main {
    my (@files) = @_;
    my %cache;
    foreach my $f ( @files ) {
        my $schema = decode_json( scalar slurp($f) );
        flatten_subschema($schema, \%cache);
    }
    use Data::Dumper;
    print Dumper(\%cache);

    return 0;
}



exit(main(@ARGV)) if not caller;










