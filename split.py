#!/usr/bin/python

# Simple program to split a text file into smaller files with a fixed number of lines
# Usage: split.py -i <inputfile> -l <desired number of lines per file>

import sys, getopt

def main(argv):
   inputfile = ''
   outputfile = ''
   try:
      opts, args = getopt.getopt(argv,"hi:l:",["inputfile=","lines="])
   except getopt.GetoptError:
      print 'split.py -i <inputfile> -l <desired number of lines per file>'
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         print 'split.py -i <inputfile> -l <desired number of lines per file>'
         sys.exit()
      elif opt in ("-i", "--inputfile"):
         inputfile = arg
      elif opt in ("-l", "--lines"):
         lines_per_file = arg

   lines = []  # stores lines prior to writing
   lines_counter = 0  
   files_counter = 0
   desired_lines = int(lines_per_file)

   with open(inputfile) as original:
      for line in original:  # iterate through initial file
         lines.append(line)
         lines_counter += 1
         if lines_counter == desired_lines:
            i = desired_lines * (files_counter + 1)
            with open('splitoutput_example_%s.txt' % i, 'w') as small_file:
               small_file.write(''.join(lines)) # dump content of lines to a small output file
            lines = []  # reset lines
            lines_counter = 0
            files_counter += 1  # keep count of created files
      if lines_counter:  # if there are some remaining lines not yet written
         i = desired_lines * (files_counter + 1)
         with open('splitoutput_example_%s.txt' % i, 'w') as small_file:
               small_file.write(''.join(lines)) # dump content of lines to a small output file
         files_counter += 1

   print '%s output files (each with %s lines) created.' % (files_counter, desired_lines)

if __name__ == "__main__":
   main(sys.argv[1:])
