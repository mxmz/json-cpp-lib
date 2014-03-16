use strict;
use JSON::XS qw(decode_json encode_json);
use File::Slurp qw(slurp);
use Digest::MD5 qw(md5_hex);

sub id_from_json{
        my ($json) = @_;
        if (my $id = $json->{'id'}) {
                return md5_hex($id);
        }
        my $txt = encode_json($json);
        if ( $txt =~ /^[\"\{\},\w\:\-]{1,60}$/ ) {
                $txt =~ tr/:,\{\}\"-/__/d;
                return "j".$txt;
        } else {
            return md5_hex($txt);
        }
}


sub flatten_subschema {
    my ( $schema, $cache ) = @_;
    if ( my $ref = delete $schema->{'$ref'} ) {
                return md5_hex($ref);
    }
    my $desc = delete $schema->{'description'};
    my $id = id_from_json($schema);
    if ( $cache->{$id} ) {
        warn ("schema already in cache: ", encode_json($schema), "\n" );
        $cache->{$id}->{'used'}++;
        return $id;
    }

    my @checks ;
    my %defs;

    my %subschema_defs = qw( anyOf allOf oneOf items );

    foreach my $k ( keys %subschema_defs ) {
            if ( $schema->{$k}  ) {
                 $schema->{$k} = ref($schema->{$k}) eq 'HASH' ?
                                        flatten_subschema( $schema->{$k}  , $cache ) :
                                         [  map { flatten_subschema($_,$cache)  }  @{ $schema->{$k} } ]
            }
    }


    if ( $schema->{'properties'} ) {
        my %properties;
        foreach my $key ( keys %{$schema->{'properties'}} ) {
                my $value = $schema->{'properties'}->{$key} ;
                my $schema_id = flatten_subschema($value, $cache ) ;
                    push @checks, {
                        type => "property_satisfies",
                        value => {
                                name  => $key,
                                schema => $schema_id,
                        }
                };
                $properties{$key} = $schema_id;
        }
        $schema->{'properties'} = \%properties;
    }
        $cache->{$id} = {
            defs   => $schema,
            used => 1,
            desc => $desc || substr( encode_json($schema), 0, 40 )
            };
    return $id;

}

sub main {
    my (@files) = @_;
    my %cache;
    my %files = ();
    foreach my $f ( @files ) {
        my $source = decode_json( scalar slurp($f) );
        my @schemas = ref($source) eq 'ARRAY' ? @{$source} : $source;
        my $count = 1;
        foreach my $schema (@schemas ) {
            my $id = $f;
            $id =~ tr#/.-#___#;
            $id .= $count++;
            $files{$id} = {
                id => $id,
                schema => flatten_subschema( $schema, \%cache )
            };
        }
    }
    use Data::Dumper;
    print encode_json( {
                    sources => \%files,
                    schemas => \%cache,
                    } );

    return 0;
}



exit(main(@ARGV)) if not caller;










