SELECT m.title
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
JOIN ratings r ON m.id = r.movie_id
WHERE p.name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;