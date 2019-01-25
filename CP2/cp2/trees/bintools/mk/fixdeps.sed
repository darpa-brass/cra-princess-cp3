#
# Assume anything beginning with "target" came from arch/$CPU.
#

/^target[^: ]*\.o:/s,^,arch/$(CPU)/,
