#!/usr/bin/env perl
#author:Zelin Li
#date:2020.02.13
#utility:count each characters number from a file (normally is sequence file)

use strict;

my %tmp;
open (HD,"/PATH/TO/sequence.fa") or die "$!";

map { $tmp{$_}++; $tmp{sum}++ } 
  map { chomp; split //,$_ } <HD>;

close HD;

print "$_: $tmp{$_}\n"
   foreach (sort { $tmp{$b} <=> $tmp{$a} } keys %tmp);
