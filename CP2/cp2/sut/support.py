# -*- coding: utf-8 -*-

#
# Because python, there's an f.readall(), but only for binary files,
# and we have a text file.
#
def readall(f):
    lines = []
    while True:
        line = f.readline()
        if line is None or line == "":
            break
        lines.append(line)
    return "".join(lines)

def trynumber(s):
    if len(s) > 10:
        return None
    try:
        x = int(s)
    except Exception as e:
        return None
    return x

def readfile(path):
    try:
        f = open(path, 'r')
    except Exception as e:
        return None
    contents = readall(f)
    f.close()
    return contents
    
def mightbefile(contents, pathfmt):
    val = trynumber(contents)
    if val is None:
        # not a test number, so it must be the test program itself
        return (contents, None)
    path = pathfmt.format(val)
    return (readfile(path), val)
