# Simple program to split a text file into smaller files with a fixed number of lines

lines_per_file = 100  # desired line length of output files
lines = []  # stores lines prior to writing
lines_counter = 0  
files_counter = 0

with open('example.txt') as original:
    for line in original:  # iterate through initial file
        lines.append(line)
        lines_counter += 1
        if lines_counter == lines_per_file:
            i = lines_per_file * (files_counter + 1)
            with open('split_example_%s.txt' % i, 'w') as small_file:
                small_file.write(''.join(lines)) # dump content of lines to a small output file
            lines = []  # reset lines
            lines_counter = 0
            files_counter += 1  # keep count of created files
    if lines_counter:  # if there are some remaining lines not yet written
        i = lines_per_file * (files_counter + 1)
        with open('split_example_%s.txt' % i, 'w') as small_file:
            small_file.write(''.join(lines)) # dump content of lines to a small output file
        files_counter += 1

print '%s output files (each with %s lines) created.' % (files_counter, lines_per_file)

