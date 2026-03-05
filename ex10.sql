-- Find each building in the university and the total capacity of all rooms it contains
	-- 'GROUP BY' operation ensures each room capacity sum is calaculated in diffrent buildings (as multiple rooms can be in 1 building)
	  
SELECT building, SUM(capacity) AS total_capacity -- Source for 'SUM' operation: https://www.w3schools.com/sql/sql_sum.asp
FROM ROOM
GROUP BY building; -- 'GROUP BY vs ORDER BY': https://www.geeksforgeeks.org/sql/difference-between-order-by-and-group-by-clause-in-sql/
