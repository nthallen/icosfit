#! /bin/bash
function nl_error {
  echo "gen_cppsrc.sh: $*" >&2
  exit 1
}
dir="../cppsrc"
[ -e "$dir" ] && rm -rf $dir
[ -d "$dir" ] && nl_error "Unable to delete cppsrc directory"
mkdir $dir || nl_error mkdir $dir failed
eli "icosfit.specs +(%dflags) :source > $dir" || nl_error eli failed
[ -f $dir/Makefile ] || nl_error Could not locate $dir/Makefile
chmod +w $dir/Makefile
cat Makefile.tail >>$dir/Makefile
cd $dir

cat <<EOF >CMakeLists.txt
cmake_policy(SET CMP0048 NEW)
project(icosfit_src VERSION 4.0.0)

EOF

line="SET(FITSRCS "
curlen=${#line}
for src in *.c; do
  let newlen=curlen+${#src}+1
  if [ $newlen -gt 70 ]; then
    echo "$line" >>CMakeLists.txt
    line="  $src"
    curlen=${#line}
  else
    line="$line $src"
    curlen=$newlen
  fi
done
echo "$line)" >>CMakeLists.txt

cat <<EOF >>CMakeLists.txt    

add_executable(icosfit \${FITSRCS})
set_source_files_properties(\${FITSRCS} PROPERTIES LANGUAGE CXX )
target_link_libraries(icosfit levmar lapack blas)
target_include_directories(icosfit PRIVATE ${icosfit_SOURCE_DIR}/levmar-2.6)
install(icosfit RUNTIME DESTINATION bin)
EOF
