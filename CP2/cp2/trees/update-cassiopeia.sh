#!/bin/sh
# update-cassiopeia.sh - update the cassiopeia tree here
# usage: ./update-cassiopeia.sh
#
# You must have cloned the cassiopeia tree in parallel to this tree,
# and done a git checkout of the version you want, so that
# ../../../cassiopeia is the tree to copy.
#
# The copy should skip build products, but for best results you should
# (a) clean the tree before copying it, and
# (b) examine the changes git sees after you do the copy, and fix
#     as/if needed.
#
# You should do "git addremove" afterwards so you can commit the
# changes without missing stuff.
#
# Don't run this without thinking - this tree should be updated as
# needed, but not arbitrarily, so that everything continues to work.


# again, don't run without thinking. comment this out after you've thought,
# and put it back afterwards.
echo nope
exit 5

set -x
rsync -av --delete --delete-excluded \
      --exclude='.git*' --exclude='.circleci' \
      --exclude='_build' --exclude='cassiopeia' \
      ../../../cassiopeia/ cassiopeia/
set +x

echo "This commit is:"
(
    cd ../../../cassiopeia &&
	git log | head -1 | awk '{ print $2 }'
)
