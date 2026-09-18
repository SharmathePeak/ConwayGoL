import sys

gen = 1
print(gen)
# Read line by line from standard input
for line in sys.stdin:
    clean_line = line.strip()
    print(clean_line)
    if clean_line != "---":
        pass
    else:
        gen += 1
        print(gen)
