#! /usr/bin/perl -w
use strict;
use Email::Valid;

# lab08.pl
# --------
# provides functions buildContactHash and buildReverseHash, which
#    can be used in other perl scripts by imcluding the line:
#       require "lab08.pl";
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
# a reverse contact hash also stores the information in a hash table form,
#   but with the phone numbers as keys, and email addresses as values
# e.g.
#   my reverseHash = (
#         "1234567890" => "nobody.I.know@here.com",
#         "2505551111" => "you@some.where.else" );


# buildContactHash
# ----------------
# buildContactHash takes a (reference to) a contact list as its parameter,
#    fills in a contact hash, and returns a reference to the contact hash.
# Error handling:
#    if the passed contact list is in a structurally invalid format
#       the function displays an informative error message and returns 0
#       (structurally valid meaning a list of lists, where the inner lists
#        each contain exactly two strings)
#    if any entry contains an invalid email address and/or phone number
#       the function displays a warning and ignores that email/phone entry
#       - the validity of email addresses and phone numbers are checked
#         using the validEmail and validPhone functions
#    if a duplicate email address is encountered the function displays
#       a warning and replaces the old associated phone number with
#       the new one
# Sample call:
#    my $hashRef = buildContactHash(\@contactList);
sub buildContactHash(@)
{
}


# buildReverseHash
# ----------------
# buildReverseHash takes a (reference to) a contact hash as its parameter,
#    fills in a reverse contact hash, and returns a reference to the reverse hash.
# Error handling:
#    if any entry contains an invalid email address and/or phone number
#       the function displays a warning and ignores that email/phone entry
#       - the validity of email addresses and phone numbers are checked
#         using the validEmail and validPhone functions
#    if a duplicate phone number is encountered the function displays
#       a warning and replaces the old associated email address with
#       the new one
# Sample call:
#    my $revHashRef = buildReverseHash(\%contactHash);
sub buildReverseHash(%)
{
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
