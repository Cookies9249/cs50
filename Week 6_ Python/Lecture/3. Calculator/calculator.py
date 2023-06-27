try:
    # input() can be used to obtain an input
    # int() converts input into int
    x = int(input("x: "))
# except is performed if any above functions fail
except:
    print("That is not an int!")
    exit()

try:
    y = int(input("y: "))
except:
    print("That is not an int!")
    exit()

print(f"Sum: {x + y}")

# '/' automatically converts result into float
# '//' can be used to prevent that
print(f"Quotient: {x / y}")
print()

# parity.py
if x % 2 == 0:
    print("x is even")
else:
    print("x is odd")

if y % 2 == 0:
    print("y is even")
else:
    print("y is odd")
print()

# agree.py
from cs50 import get_string

s = get_string("Do you agree? ").lower()

if s in ["y", "yes"]:
    print("Agreed.")
elif s in ["n", "no"]:
    print("Not agreed.")
print()

# meow.c
def main(): # define main
    meow(3)

def meow(n): # define functions
    for i in range(n):
        print("meow")

main() # call main once everything is defined
print()

# scores.c
from cs50 import get_int

scores1 = []
scores2 = []
for i in range(3):
    score = get_int("Score: ")
    scores1.append(score) # add score to scores
    scores2 += [score] # both work

average1 = sum(scores1) / len(scores1)
average2 = sum(scores2) / len(scores2)

print(f"Average: {average1}")
print(f"Average: {average2}")
print()

# uppercase.py
before = get_string("Before: ")

after = before.upper() # Method 1
print(f"After: {after}")

print("After: ", end="") # Method 2
for c in before: # For every char
    print(c.upper(), end="")
print()
print()

# argv.py
from sys import argv, exit

for arg in argv[1:]: # For every arg in list
    print("hello " + arg)

print()

# exit.py
if len(argv) != 2:
    print("Missing command-line argument")
    #sys.exit(1)
else:
    print(f"hello, {argv[1]}")

print()