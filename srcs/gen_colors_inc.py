
from __future__ import print_function

fmt = "\"\\033[48;5;%03dm\\0\""

print("//go:generate python print_colors_tab.py > colors.inc")
print("#define COLORSTRIDE 12")

lst = [fmt % n for n in xrange(16, 232)]
print("#define COLORTAB", ' '.join(lst))
