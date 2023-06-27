SELECT m.title
  FROM movies AS m
  JOIN stars AS s
    ON m.id = s.movie_id
  JOIN people AS p
    ON s.person_id = p.id
 WHERE p.name = "Johnny Depp"
   AND m.id IN (

SELECT s.movie_id
  FROM movies AS m
  JOIN stars AS s
    ON m.id = s.movie_id
  JOIN people AS p
    ON p.id = s.person_id
 WHERE p.name = "Helena Bonham Carter");