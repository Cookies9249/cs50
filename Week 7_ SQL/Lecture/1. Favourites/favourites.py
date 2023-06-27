import csv

titles = {}

with open("favourites.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row["title"].upper().strip()
        if not title in titles:
            titles[title] = 0
        titles[title] += 1

for title in sorted(titles, key=lambda title: titles[title], reverse=True):
    print(title, titles[title])

print()

#################################################################
# . = char              .* = 0+ chars               .+ = 1+ chars
# ? = optional          ^ = input start             $ = input end
#################################################################

import csv
import re

counter = 0

with open("favourites.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row["title"].upper().strip()
        if re.search("^(OFFICE|THE.OFFICE|)$", title):
            counter += 1

print(f"Number of people who like The Office: {counter}")

print()

#################################################################

import csv

title = input("Title: ").upper().strip()
counter = 0

with open("favourites.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        if row["title"].upper().strip() == title:
            counter += 1

print(f"Count: {counter}")

print()