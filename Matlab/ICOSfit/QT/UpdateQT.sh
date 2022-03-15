#! /bin/bash
# UpdateQT.sh
rm -f index.html
wget https://hitran.org/docs/iso-meta/
./parse_iso_meta.pl index.html >iso-map.txt
cat iso-map.txt |
  while read lcl glbl molname isoname abundance molwt; do
    qfile=q$glbl.txt
    QTfile=QT_$lcl.dat
    isonum=`echo $lcl | sed -e 's/^.*\(.\)$/\1/'`
    [ -f $qfile ] || wget https://hitran.org/data/Q/$qfile
    if [ -f $qfile ]; then
      d2u $qfile

cat >$QTfile <<EOF
# Partition Function for $molname isotopologue $isonum: $isoname
# Temperature range: 160-320 K
#T,K     Q(T)
EOF

      inrange=no
      cat $qfile | while read line; do
        temp=${line#* }
        temp=${line%% *}
        case $temp in
          "160") inrange=yes;;
          "321") inrange=no;;
        esac
        [ "$inrange" = "yes" ] && echo $line
      done >>$QTfile
      rm $qfile
    fi
  done
./Update_isovals.pl iso-map.txt
rm -f iso-map.txt index.html
