#!/usr/bin/perl

use warnings;
use diagnostics;
use strict;

open INFILE1, "nickie_accept_prex_I.dat" ;
my @lines1 = <INFILE1>;
close INFILE1;

open INFILE2, "nickie_accept_prex_II.dat";
my @lines2 = <INFILE2>;
close INFILE2;

my $nlines1 = @lines1;
my $nlines2 = @lines2;
chomp @lines1;
chomp @lines2;
print "$nlines1 $nlines2\n";

if( $nlines1 = $nlines2 ){
    for ( my $i = 0; $i < $nlines1; $i++ ) {
	if( $lines1[$i] =~ /(\S+)\s(\S+)/ ){
	    #print "$2\n";
	    my $line1 = $2;
	    if( $lines2[$i] =~ /(\S+)\s(\S+)/ ){
		#print "$2\n";
		my $line2 = $2;
		if( $line2 < $line1 ){
		    #print $line2 - $line1;
		    #print "\n";
		}
		#print "$lines1[$i] $lines2[$i]\n";
	    }
	}
    }
}

my $sum1 = 0.;
my $sum2 = 0.;

for ( @lines1 ){
    if( /\S+\s(\S+)/ ){
	$sum1 = $sum1 + $1;
    }
}

for ( @lines2 ){
    if( /\S+\s(\S+)/ ){
	$sum2 = $sum2 + $1;
    }
}

print "$sum1 $sum2\n";
