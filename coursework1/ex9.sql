-- Comments in .sql fies: https://www.w3schools.com/sql/sql_comments.asp

-- BUILDING
CREATE TABLE BUILDING (
	building TEXT PRIMARY KEY,
  	name     TEXT NOT NULL -- All buildings have a name!
);
INSERT INTO BUILDING (building, name)
SELECT DISTINCT building, faculty -- https://www.geeksforgeeks.org/sql/sql-distinct-clause/
FROM faculty;

-- ROOM
CREATE TABLE ROOM (
	building  TEXT NOT NULL,
  	room      TEXT NOT NULL,
  	capacity  INTEGER,
  	PRIMARY KEY (building, room),
  	FOREIGN KEY (building) REFERENCES BUILDING(building) -- https://www.w3schools.com/SQL/sql_ref_foreign_key.asp
);
INSERT INTO ROOM (building, room, capacity)
SELECT DISTINCT building, room, capacity
FROM faculty;

-- STUDENT
CREATE TABLE STUDENT (
	student_id    INTEGER PRIMARY KEY,
  	student_name  TEXT,
  	student_email TEXT,
  	programme     TEXT,
  	year          INTEGER,
  	address       TEXT,
  	contact       TEXT
);
INSERT INTO STUDENT (student_id, student_name, student_email, programme, year, address, contact)
SELECT DISTINCT student_id, student_name, student_email, programme, year, address, contact
FROM students;

-- MODULE
CREATE TABLE MODULE (
	module_id     TEXT PRIMARY KEY,
  	module_name   TEXT,
  	module_leader TEXT,
  	lecturer1     TEXT,
  	lecturer2     TEXT,
  	building      TEXT,
  	room          TEXT,
  FOREIGN KEY (building, room) REFERENCES ROOM(building, room)
);
INSERT INTO MODULE (module_id, module_name, module_leader, lecturer1, lecturer2, building, room)
SELECT DISTINCT module_id, module_name, module_leader, "lecturer1/", "lecturer2/", building, room
FROM students;

-- ENROLMENT
CREATE TABLE ENROLMENT (
	-- Primary Key cannot be null by definition (Source: https://www.dbvis.com/thetable/can-a-primary-key-be-null-in-an-sql-table/)
		-- but we're including the 'NOT NULL' just to be safe
	student_id  INTEGER NOT NULL,
  	module_id   TEXT NOT NULL,
  	exam_mark   INTEGER,
  	coursework1 INTEGER,
  	coursework2 INTEGER,
  	coursework3 INTEGER,
  	PRIMARY KEY (student_id, module_id),
  	FOREIGN KEY (student_id) REFERENCES STUDENT(student_id),
  	FOREIGN KEY (module_id)  REFERENCES MODULE(module_id)
);
INSERT INTO ENROLMENT (student_id, module_id, exam_mark, coursework1, coursework2, coursework3)
SELECT DISTINCT student_id, module_id, "exam_mark/", coursework1, coursework2, coursework3
FROM students;
