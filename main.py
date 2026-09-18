import sys

# Read line by line from standard input
for line in sys.stdin:
    clean_line = line.strip()
    print(clean_line)
    i = 0
    while i < len(clean_line):
        print(f"Damn {clean_line[i]}")
        i += 1
