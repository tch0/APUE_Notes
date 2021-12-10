#!/usr/bin/env python3
# format the output of errno -l command
# usage : errno -l | ./FormatErrnoListInfo.py
s = input()
while len(s) > 0:
    l = s.split(' ')
    print(l[0] + " "*(15 - len(l[0]) + 1), end = "")
    print(l[1] + " "*(3 - len(l[1]) + 1), end = "")
    print(" ".join(l[2:]))
    try:
        s = input()
    except:
        break