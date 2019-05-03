#! /usr/bin/perl -w
use strict;

require './lab08.pl';

# create a couple of test cases
my @contactList = (
       [ 'me@nowhere.ca', '1234567890' ],
       [ 'you@some.where.else', '2505551111' ],
       [ 'nobody.I.know@here.com', '1234567890' ] );

my %contactHash = (
       'me@nowhere.ca' => '1234567890' ,
       'you@some.where.else' => '2505551111' ,
       'nobody.I.know@here.com' => '1234567890' );

# function to display the contents of a hash table
sub displayHash(%)
{
   my $href = $_[0];
   my %hash = %$href;
   foreach my $k (keys %hash) {
      print "   key $k has value $hash{$k}\n";
   }
}

# function to run a couple of test cases
sub runTests()
{
   # test a call to buildContactHash
   print "\nTesting buildContactHash\n";
   my $hashRef = buildContactHash(\@contactList);
   if ($hashRef == 0) {
      print "build returned 0, there must have been a problem\n";
   } else {
      print "The contents of the contact list are:\n";
      displayHash($hashRef);
   }

   # test a call to buildReverseHash
   print "\nTesting buildReverseHash\n";
   $hashRef = buildReverseHash(\%contactHash);
   print "The contents of the reverse list are:\n";
   displayHash($hashRef);
}

# call the runTests
runTests();

# --------------------------------
#   Sample output from a test run
#
# Testing buildContactHash
# The contents of the contact list are:
#    key you@some.where.else has value 2505551111
#    key nobody.I.know@here.com has value 1234567890
#    key me@nowhere.ca has value 1234567890
#
# Testing buildReverseHash
# Warning: duplicate phone number 1234567890
#    replacing me@nowhere.ca with nobody.I.know@here.com
# The contents of the reverse list are:
#    key 2505551111 has value you@some.where.else
#    key 1234567890 has value nobody.I.know@here.com
# --------------------------------

