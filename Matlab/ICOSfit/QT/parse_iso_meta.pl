#! /usr/bin/perl -w
use strict;
my $mol;
my $molname;
#my $isonum;
#my $isoname;
my $fldno;
#my $global;
my %params;
my @cols = qw(global isonum isoname AFGL Abundance Mass);

while (<>) {
  if ( m|^<h4>(\d+): (.*)</h4>|) {
    $mol = $1;
    $molname = $2;
    $molname =~ s/<[^>]*>//g;
  } elsif ($mol) {
    if (m/^<tr>/) {
      $fldno = 0;
    } elsif (m|^<td[^>]*>(.*)</td>|) {
      if ($fldno < @cols) {
        my $val = $1;
        $val =~ s|&nbsp;&times;&nbsp;10<sup>([^<]*)</sup>|E$1|;
        $val =~ s|<sup>([^<]*)</sup>|^{$1}|g;
        $val =~ s|<sub>([^<]*)</sub>|_{$1}|g;
        $params{$cols[$fldno]} = $val;
      }
      ++$fldno;
    } elsif (m|^</tr>| && $fldno >= @cols) {
      my $isoname = $params{isoname};
      $isoname =~ s/<sup>/^/g;
      $isoname =~ s/<[^>]*>//g;
      my $localfile = "QT_$mol$params{isonum}.dat";
      if ( -f $localfile ) {
        print "$mol$params{isonum} $params{global} $molname $isoname $params{Abundance} $params{Mass}\n";
      }
    } elsif (m|^</table>|) {
      $mol = 0;
    }
  }
}
