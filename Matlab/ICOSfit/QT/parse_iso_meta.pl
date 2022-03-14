#! /usr/bin/perl -w
use strict;
my $mol;
my $molname;
my $isonum;
my $isoname;
my $fldno;
my $global;

while (<>) {
  if ( m|^<h4>(\d+): (.*)</h4>|) {
    $mol = $1;
    $molname = $2;
    $molname =~ s/<[^>]*>//g;
  } elsif ($mol) {
    if (m/^<tr>/) {
      $fldno = 1;
    } elsif (m/^<td>/) {
      if (m|^<td>(\d+)</td>|) {
        if ($fldno == 1) {
          $global = $1;
        } elsif ($fldno == 2) {
          $isonum = $1;
        }
      } elsif ($fldno == 3 && m|<td>(.*)</td>|) {
        $isoname = $1;
        $isoname =~ s/<sup>/^/g;
        $isoname =~ s/<[^>]*>//g;
        my $localfile = "QT_$mol$isonum.dat";
        if ( -f $localfile ) {
          print "$mol$isonum $global $molname $isoname\n";
        }
      }
      ++$fldno;
    } elsif (m|^</table>|) {
      $mol = 0;
    }
  }
}
