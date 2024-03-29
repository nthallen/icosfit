#! /bin/bash
# ./cygwin_release.sh <VERSION> [<branch>]
# VERSION is always required
# branch defaults to master, which is appropriate for
# a formal release. branch can be specified for a beta
# release.
function nl_error {
  echo "cygwin_release.sh: $*" >&2
  exit 1
}
VERSION=$1
branch=master
[ -n "$2" ] && branch=$2
[ -n "$VERSION" ] ||
  nl_error "Must specify VERSION as first argument"

#archive=../icosfit-$VERSION.tar.xz
#git archive $branch --prefix=icosfit-$VERSION/ --format=tar |
#  xz  >$archive

cur_dir=/usr/src/icosfit-$VERSION

if [ -d $cur_dir ]; then
  echo "$cur_dir already exists"
else
  prev_dir=''
  cv=$VERSION
  while [ -z "$prev_dir" ]; do
    ncv=${cv%.*}
    [ "$ncv" = "$cv" ] && break
    cv=$ncv
    prev_dir=`ls -d /usr/src/icosfit-${cv}.* 2>/dev/null | tail -n1`
  done
  mkdir $cur_dir
  if [ -n "$prev_dir" -a -d $prev_dir ]; then
    cp $prev_dir/icosfit.cygport $cur_dir
  else
    echo "No obvious earlier version of icosfit.cygport found"
  fi
fi
#cp $archive $cur_dir/
