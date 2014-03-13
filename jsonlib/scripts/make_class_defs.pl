use strict;
use warnings;
use JSON::XS qw( decode_json );

my $defs = decode_json( join '', <STDIN> );

print_definitions($defs);



sub print_definitions {
  my ( $defs ) = shift;
  my @classes = @{ $defs->{'classes'} };


  foreach my $class ( @classes ) {
    my $namespace = $class->{"namespace"};
    my @nscomponents = split /::/, $namespace;
    foreach my $nscomponent ( @nscomponents ) {
        print "namespace $nscomponent {\n";
    }
    my $id = $class->{"id"};
    my @members = @{ $class->{'members'} };

    print "class $id {\n";

    foreach my $member ( @members ) {
        my $id = $member->{"id"};
        my $type = $member->{"type"};
        
        print "    $type    _$id;\n";
    }

    #ctor
    print "  public:\n";
    print "    template < class MapT >\n";
    print "    $id ( MapT& args ) :\n";

    print join ",\n", map {
            my $id = $_->{"id"};
            my $key = $_->{"key"} // $id;
            "     _$id( args[\"$key\"] )"
        } @members;
    print "\n";
    print "     { }\n";

    print "}/*$id*/;\n";


    foreach my $nscomponent ( @nscomponents ) {
        print "}/*$nscomponent*/\n";
    }


  }

}
