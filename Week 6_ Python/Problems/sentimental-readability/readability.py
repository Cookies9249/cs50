from cs50 import get_string

# Get Input of Text from User
input = get_string("Text: ")

# Count Letters
letters = 0
for c in input:
    if c.isalpha():
        letters += 1

# Count Words
words = input.count(" ") + 1

# Count Sentences
sentences = input.count(".") + input.count("!") + input.count("?")

# Prevent Division by 0

# Calculate L and S in Coleman-Liau Index
l = letters / words * 100.0
s = sentences / words * 100.0

# Calculate Coleman-Liau Index
i = round(0.0588 * l - 0.296 * s - 15.8)

# Print Index to User
if i < 0:
    print("Before Grade 1")
elif i > 16:
    print("Grade 16+")
else:
    print(f"Grade {i}")

print(f"Letters: {letters}")
print(f"Words: {words}")
print(f"Sentences: {sentences}")
print(f"L: {l}")
print(f"S {s}")
print(0.0588 * l - 0.296 * s - 15.8)

# check50 cs50/problems/2022/x/sentimental/readability
# submit50 cs50/problems/2022/x/sentimental/readability