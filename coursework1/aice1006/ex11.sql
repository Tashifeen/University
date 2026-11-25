-- Find each Year 1 Computer Science Student (by id and name) and their average exam mark (sorted in descending order of marks)
SELECT s.student_id, s.student_name, AVG(e.exam_mark) AS avg_exam_mark
FROM STUDENT s
JOIN ENROLMENT e ON s.student_id = e.student_id -- Help: https://www.w3schools.com/sql/sql_join.asp
WHERE s.year = 1
AND s.programme = 'Computer Science'
GROUP BY s.student_id, s.student_name
ORDER BY avg_exam_mark DESC;
