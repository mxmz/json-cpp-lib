use strict;
use JSON::XS qw(decode_json encode_json);
use File::Slurp qw(slurp);
use Digest::SHA1 qw(sha1_hex);

sub id_from_json{
        my ($json) = @_;
        if (my $id = $json->{'id'}) {
                return sha1_hex($id);
        }
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
    my $id = id_from_json($schema);
    if ( $cache->{$id} ) {
        warn ("this schema is already cached: ", encode_json($schema), "\n" );
        $cache->{$id}->{'used'}++;
        return $id;
    }

    my @checks ;

    if ( $schema->{'type'}  ) {
            push @checks, {
                    type  => 'has_type',
                    value =>   $schema->{'type'}
            }
    }
    if ( $schema->{'format'}  ) {
            push @checks, {
                    type  => 'has_format',
                    value =>   $schema->{'format'}
            }
    }

    if ( $schema->{'properties'} ) {
        foreach my $key ( keys %{$schema->{'properties'}} ) {
                my $value = $schema->{'properties'}->{$key} ;
                my $schema_id = $value->{'$ref'} ? sha1_hex($value->{'$ref'} ) : flatten_subschema($value, $cache ) ;
                    push @checks, {
                        type => "has_attribute",
                        value => {
                                name  => $key,
                                schema => $schema_id,
                        }

                }
        
        }
    }
        $cache->{$id} = {
            checks => \@checks,
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
    print encode_json(\%cache);

    return 0;
}



exit(main(@ARGV)) if not caller;










