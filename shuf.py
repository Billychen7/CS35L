#!/usr/bin/python

import random, sys, string, argparse
from optparse import OptionParser

class shuf:
    def __init__(self, filename, x):
        if(filename == "null" or filename == "-"):
            self.lines = sys.stdin.readlines()
            if(len(self.lines) <= 0):
                return 0
        elif(x == "Null"):
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()
    def chooseline(self, i, n, r, input):
        output = []
        if n is int and n < 0:
            parser.error("error negative count: {0}".
                         format(n))
        if(i != "Null"):
            if(input != "null"):
                parser = OptionParser()
                parser.error("extra operand " + input)
            min = int(i.split('-')[0])
            max = int(i.split('-')[1])
            arr = [y for y in range(min,max+1)]
            if(r and n == "null"):
                while(True):
                    sys.stdout.write(str(random.choice(range(min, max + 1))) + '\n')
            else:
                if(n == "null"):
                    while(len(arr) >= 1):
                        a = random.choice(range(len(arr)))
                        output.append(str(arr[a]) + '\n')
                        del(arr[a])
                    return output
                else:
                    for c in range(n):
                        if(len(arr) == 0):
                            return output
                        elif(not r):
                            a = random.choice(range(len(arr)))
                            output.append(str(arr[a]) + '\n')
                            del(arr[a])
                        else:
                            a = random.choice(range(len(arr)))
                            output.append(str(arr[a]) + '\n')
                    return output
        lines = self.lines[:]
        if(r and n == "null"):
            while(True):
                sys.stdout.write(lines[random.choice(range(len(lines)))])
        else:
            if(n == "null"):
                n = len(self.lines)
            for c in range(n):
                if(r):
                    output.append(lines[random.choice(range(len(lines)))])
                else:
                    a = random.choice(range(len(lines)))
                    output.append(lines[a])
                    del lines[a]
                    if(len(lines) == 0):
                        return output
        return output
def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog {OPTION]... FILE
Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-n", "--head-count",
                      action="store", dest="n",
                      help="Output at most HEADCOUNT lines. By default, all input lines are output")
    parser.add_option("-i", "--input-range",
                      action="store", dest="i", default="Null",
                      help="Act as if input came from a file containing the range of unsigned decimal integers LO-HI, one per line.")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="r", default=False,
                      help="Output lines can be repeated")
    options, args = parser.parse_args(sys.argv[1:])
    try:
        n = int(options.n)
    except:
        n = "null"
    if n is int and n < 0:
        parser.error("negative count: {0}".
                     format(n))
    r = bool(options.r)
    i = str(options.i)
    try:
        input = args[0]
    except:
        input = "null"
    try:
        generator = shuf(input, i)
        result = generator.chooseline(i, n, r, input)
        for obj in result:
            sys.stdout.write(obj)
    except IOError as err:
        parser.error("I/0 error({0}): {1}".
                     format(errno, strerror))
if __name__ == "__main__":
    main()
