#! /usr/bin/perl -w

use strict;
use warnings;

use lib '.';

use lab08;

my @hashTestSet;

BEGIN {
	@hashTestSet = (
		['wrongemail@gmail.com.ca','2505556789','Warning: invalid email','test1'],
		['sami.qusus@gmail.com','12345','Warning: invalid phone','test2'],
		['sami.qusus@gmail.com','1-250-555-6789','Warning: duplicate email','test3'],
		['sami.qusus@gmail.com','Error: invalid contacts','test4'],
		['tom.jerry@gmail.com','1-250-555-6799','All entries valid','test5'],
	);
}

use Test::More tests => scalar @hashTestSet;

foreach my $testCase (@hashTestSet) {

	my $testname = pop @$testCase;
	my $exp = pop @$testCase;
	my $output = '';
	open ToVariable, '>', \$output or die "nope";
	select ToVariable;
	buildContactHash(\@$testCase);
	select STDOUT;
	like($output, qr/$exp/, $testname);
}

