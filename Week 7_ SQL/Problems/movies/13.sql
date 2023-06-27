SELECT DISTINCT(name)
  FROM people AS p
  JOIN stars AS s
    ON s.person_id = p.id
 WHERE NOT name = "Kevin Bacon"
   AND s.movie_id IN (

SELECT s.movie_id
  FROM stars AS s
  JOIN people AS p
    ON s.person_id = p.id
 WHERE p.name = "Kevin Bacon"
   AND p.birth = 1958);