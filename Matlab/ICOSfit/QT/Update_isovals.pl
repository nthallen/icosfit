#! /usr/bin/perl -w
use strict;

my %V;
my @isonum;

while (<>) {
  my ($isonum, $global, $molname, $isoname, $abundance, $molwt) = split;
  $V{"I$isonum"} = { molname => $molname, isoname => $isoname,
                     abundance => $abundance, molwt => $molwt,
                     in_isovals => 0, isonum => $isonum };
  push(@isonum, $isonum);
}

my $fname = "../isovals.m";
open(IFP, "<", $fname) || die "Cannot locate $fname\n";
open(OFP, ">", "$fname.new") || die "Cannot write to $fname.new\n";
while ( my $line = <IFP> ) {
  if ( $line =~ m/^ *add_iso\(([^\)]*)\);/ ) {
    my @args = split(',', $1);
    my $isonum = $args[0]+0;
    if (defined($V{"I$isonum"})) {
      my $P = $V{"I$isonum"};
      $P->{in_isovals} = 1;
      print OFP
        "  add_iso( $isonum,$args[1],$args[2], $P->{abundance}," .
        " $P->{molwt},$args[5],$args[6],$args[7]);\n";
    } else {
      if ($isonum % 10) {
        warn "No QT file for Isotopologue $isonum\n";
      } elsif ($args[4] != 0) {
        warn "Molecule $isonum has non-zero weight\n";
      }
      print OFP $line;
    }
  } else {
    print OFP $line;
  }
}
close(IFP);
close(OFP);
unlink($fname);
rename("$fname.new", $fname);

for my $key ( keys %V ) {
  my $P = $V{$key};
  if (! $P->{in_isovals}) {
    warn "Isotopologue $P->{isonum} $P->{isoname} missing from isovals.m\n";
  }
}

$fname = "../../../icosfit/elisrc/molwt.c";
open(IFP, "<", $fname) || die "Cannot locate $fname\n";
open(OFP, ">", "$fname.new") || die "Cannot write to $fname.new\n";

my $generated = 0;

while ( my $line = <IFP> ) {
  if ( $line =~ m/^ *case / ) {
    if (!$generated) {
      for my $isonum (@isonum) {
        my $P = $V{"I$isonum"};
        print OFP
          "    case $isonum: return $P->{molwt}; // $P->{isoname}\n";
      }
      $generated = 1;
    }
  } else {
    print OFP $line;
  }
}

close(IFP);
close(OFP);
unlink($fname);
rename("$fname.new", $fname);
