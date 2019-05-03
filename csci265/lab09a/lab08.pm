#! /usr/bin/perl
use strict;
use warnings;
use Email::Valid;

package lab08;

require Exporter;
use vars qw(@ISA @EXPORT @EXPORT_OK);
@ISA = qw(Exporter);
@EXPORT = qw(buildContactHash);
@EXPORT_OK = qw(validEmail validPhone);

# lab08.pm
# --------
# provides function buildContactHash, which can be used in other perl
#    scripts by imcluding the line:
#       use lab08;
# also provided are functions validEmail and validPhone, which can be
#    used to test the validity of strings containing email addresses
#    and phone numbers


# Data type definitions
# ---------------------
# a contact list is an array of pairs, where each pair has two strings:
#   one containing an email address, the other containing a phone number
# e.g.
#    my contactList = (
#         [ "me@nowhere.ca", "1234567890" ],
#         [ "you@some.where.else", "2505551111" ],
#         [ "nobody.I.know@here.com", "1234567890" ] );
#
# a contact hash contains the email/phone information in a hash table form,
#   where the email address is the key and the phone number is the value
# e.g.
#    my contactHash = (
#         "me@nowhere.ca" => "1234567890" ,
#         "you@some.where.else" => "2505551111" ,
#         "nobody.I.know@here.com" => "1234567890" );
#


# buildContactHash
# ----------------
# buildContactHash takes a (reference to) a contact list as its parameter,
#    fills in a contact hash, and returns a reference to the contact hash.
# if no warnings or error messages are generated (see below), then just before
#       returning the function displays the message 'All entries valid'
# Error handling:
#    if the passed contact list is in a structurally invalid format
#       the function displays an informative error message beginning
#       with 'Error: invalid contacts', and returns 0
#       (structurally valid meaning a list of lists, where the inner lists
#        each contain exactly two strings)
#    if any entry contains an invalid email address and/or phone number
#       the function displays a warning message beginning with the string
#       'Warning: invalid email' or 'Warning: invalid phone' and ignores
#       that email/phone entry (i.e. does not add it to the hash)
#       - the validity of email addresses and phone numbers are checked
#         using the validEmail and validPhone functions
#    if a duplicate email address is encountered the function displays
#       a warning message beginning with 'Warning: duplicate email'
#       and replaces the old associated phone number with the new one
# Sample call:
#    my $hashRef = buildContactHash(\@contactList);
sub buildContactHash(@)
{
   my $aRef = $_[0];
   my @cList = @$aRef;
   my %cHash;
   my $AllOK = 1; # see if any invalid entries are detected
   # process each entry in the contact list
   for my $entry (@cList) {
       # the entry should be a reference to a list of two strings, i.e. [ email, phone ]
       if ((ref $entry) ne "ARRAY") {
          print "Error: invalid contacts found (non-lists)\n";
          return 0;
       }
       my @pList = @$entry;
       if ((scalar @pList) != 2) {
          print "Error: invalid contacts found (number of fields != 2): @pList\n";
          return 0;
       }
       # get the email address string
       my $email = $pList[0];
       # get the phone number string
       my $phone = $pList[1];
       # check for duplicate email addresses
       if (exists $cHash{$email}) {
          my $oldPhone = $cHash{$email};
          print "Warning: duplicate email address: $email\n";
          print "   replacing $oldPhone with $phone\n";
          $AllOK = 0;
       }
       # add the new hash table entry
       my $valid = 1;
       if (not validEmail($email)) {
          print "Warning: invalid email address ignored: $email\n";
          $valid = 0;
          $AllOK = 0;
       }
       if (not validPhone($phone)) {
          print "Warning: invalid phone number ignored: $phone\n";
          $valid = 0;
          $AllOK = 0;
       }
       # set the new value if valid
       if ($valid) {
          $cHash{$email} = $phone;
       }
   }
   if ($AllOK) {
      print "All entries valid\n";
   }
   return \%cHash;
}


# validEmail
# ==========
# check the validity of a passed email address (e.g. "me.too@some.place")
sub validEmail($)
{
   return Email::Valid->address($_[0]);
}


# validPhone
# ==========
# check the validity of a passed phone number (e.g. "1-250-555-6789")
sub validPhone($)
{
   my $regex = qr/^[0-9]+([-]?[0-9]+)*$/;
   return ($_[0] =~ m/$regex/);
}

1;
