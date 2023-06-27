import sys

numbers = [4, 6, 8, 2, 7, 5, 0]

# numbers.py
if 0 in numbers:
    print("Number found!")
else:
    print("Number not found.")

# names.py
names = ["Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"]

if "Ron" in names:
    print("Person found!")
else:
    print("Person not found.")

# phonebook.py
from cs50 import get_string

people = { # Structs in Python
    "Carter": "+1-617-495-1000",
    "David": "+1-949-468-2750"
}

name = get_string("Name: ")
if name in people:
    print(f"Number: {people[name]}")

# phonebook2.py
import csv

name = get_string("Name: ")
number = get_string("Number: ")

# With opening csv with name file...
with open("phonebook.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow([name, number])

# Alternate Method:
#file = open("phonebook.csv", "a") # Create file
#writer = csv.writer(file) # Initiate writer
#writer.writerow([name, number]) # Write into file
#file.close()

# hogwarts.py
import csv

houses = {
    "Gryffindor": 0,
    "Slytherin": 0,
    "Hufflepuff": 0,
    "Ravenclaw": 0
}

with open("hogwarts.csv", "r") as hfile:
    # DictReader uses first row as keys
    reader = csv.DictReader(hfile)
    for row in reader:
        house = row["House"]
        houses[house] += 1

for house in houses:
    count = houses[house]
    print(f"{house}: {count}")