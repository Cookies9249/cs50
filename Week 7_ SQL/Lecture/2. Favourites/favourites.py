import cs50
import csv

# Opens db file into SQL
db = cs50.SQL("sqlite:///favourites.db")

title = input("Title: ").strip()

# Executes sqlite command, title = variable used in command, returns list
# Selects # of items in favourites where title like ?
rows = db.execute("SELECT COUNT(*) AS counter FROM favourites WHERE title LIKE ?", title)

row = rows[0]

print(row["counter"])


""" SQL (Relational Database)
    sqlite3 favourites.db
    .mode csv
    .import favourites.csv favourites
    .schema

    CREATE TABLE table_name (column_name DATA_TYPE, ...);
    CREATE INDEX index_name ON table_name (column_name, ...);

    SELECT columns FROM table;
    - SELECT * FROM favourites; (* = all items)
    - SELECT title FROM favourites;
    - SELECT title, genre FROM favourites;
    - SELECT DISTINCT(UPPER(title)) FROM favourites;
    - SELECT title FROM favourites WHERE title LIKE "%office%";

    - DELETE FROM favourites WHERE title LIKE "%friends%";
    - UPDATE favourites SET title = "THE OFFICE" WHERE title LIKE "office";
    - UPDATE favourites SET genre = "Adventure, Action, Comedy" WHERE title LIKE "avatar";

FIND FROM LIST

import cs50
import csv

db = cs50.SQL("sqlite:///favorites8.db") # URI: opens up library

open("favorites.db", "w").close()

# Primary Key = Key used across tables, defined in this table
# Foreign Key = Key used across tables, defined in another table
db.execute("CREATE TABLE shows (id INTEGER, title TEXT NOT NULL, PRIMARY KEY(id));")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT NOT NULL, FOREIGN KEY(show_id) REFERENCES (id));")

with open("favorites.db", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        # for every row, access "title"
        title = row["title"].strip().upper()
        # insert ???
        show_id = db.execute("INSERT INTO shows (title) VALUES(?)", title)
        for genre in row["genres"].split(", "):
            db.execute("INSERT INTO genres (show_id, genre) VALUES (?, ?)", show_id, title)

# show = SELECT show_id FROM genres WHERE genre = "Comedy";
# SELECT title FROM shows WHERE id = (show);
#   creates...
# SELECT DISTINCT(title) FROM shows WHERE id IN (SELECT show_id FROM genres WHERE genre = "Comedy") ORDER BY title;

# INSERT INTO shows (title) VALUES("Seinfeld");
# INSERT INTO genres (show_id, genre) VALUES(159, "Comedy");
# UPDATE shows SET title = "SEINFELD" WHERE title = "Seinfeld";

# SELECT title FROM shows WHERE id IN (SELECT show_id FROM stars WHERE person_id IN (SELECT person_id FROM people WHERE name = "Steve Carell")) ORDER BY title;
# CREATE INDEX name_index ON people (name);
# CREATE INDEX show_index_index ON stars (name_id);
# CREATE INDEX star_index ON stars (person_id);

# SELECT title FROM people JOIN stars ON people.id = stars.person_id JOIN shows ON stars.show_id = shows.id WHERE name = "Steve Carell" ORDER BY title;
"""