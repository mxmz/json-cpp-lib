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
        if ( $txt =~ /^[\"\{\},\w\:\-]{1,60}$/ ) {
                $txt =~ tr/:,\{\}\"-/__/d;
                return "j".$txt;
        } else {
            return sha1_hex($txt);
        }
}


sub flatten_subschema {
    my ( $schema, $cache ) = @_;
    if ( my $ref = delete $schema->{'$ref'} ) {
                return sha1_hex($ref);
    }
    my $desc = delete $schema->{'description'};
    my $id = id_from_json($schema);
    if ( $cache->{$id} ) {
        warn ("this schema is already cached: ", encode_json($schema), "\n" );
        $cache->{$id}->{'used'}++;
        return $id;
    }

    my @checks ;
    my %check_map_value = (
                        type => "has_type",
                        format => "has_format",
                        required => "must_have"
                    );

    foreach my $k ( keys %check_map_value ) {
            if ( $schema->{$k}  ) {
                    push @checks, {
                            type  => $check_map_value{$k},
                            value =>   $schema->{$k}
                    }
            }
    }

    my %check_map_subschema = (
                        anyOf => "satisfies_any",
                        allOf => "satisfies_all",
                        oneOf => "satisfies_one",
                        items => "is_array_of"
                    );

    foreach my $k ( keys %check_map_subschema ) {
            if ( $schema->{$k}  ) {
                    push @checks, {
                            type  => $check_map_subschema{$k},
                            value =>  ref($schema->{$k}) eq 'HASH' ?
                                        flatten_subschema( $schema->{$k}  , $cache ) :
                                         [  map { flatten_subschema($_,$cache)  }  @{ $schema->{$k} } ]
                    }
            }
    }


    if ( $schema->{'properties'} ) {
        foreach my $key ( keys %{$schema->{'properties'}} ) {
                my $value = $schema->{'properties'}->{$key} ;
                my $schema_id = flatten_subschema($value, $cache ) ;
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
    my %files = ();
    foreach my $f ( @files ) {
        my $schema = decode_json( scalar slurp($f) );
        $files{$f} = flatten_subschema($schema, \%cache);
    }
    use Data::Dumper;
    print encode_json( {
                    files => \%files,
                    schemas => \%cache,
                    } );

    return 0;
}



exit(main(@ARGV)) if not caller;










