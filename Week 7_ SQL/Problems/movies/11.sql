SELECT m.title
  FROM movies AS m
  JOIN stars AS s
    ON m.id = s.movie_id
  JOIN ratings AS r
    ON r.movie_id = m.id
  JOIN people AS p
    ON p.id = s.person_id
 WHERE p.name = "Chadwick Boseman"
 ORDER BY r.rating DESC
 LIMIT 5;