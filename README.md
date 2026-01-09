Student Result Management System (C++)
📌 Project Overview

This project is a console-based Student Result Management System developed in C++.
It allows the user to manage student academic records, calculate results, assign grades, and generate class reports.
The system also supports file handling to save and load data permanently.

🎯 Features

Add new student records

Display all students in sorted order

Search student by roll number

Update student details

Delete student records

Calculate percentage and grade automatically

Generate class report (average, highest, lowest)

Subject-wise statistics

Save data to file

Load data from file at program start

🧱 Concepts Used

This project is built using core C++ concepts:

Structures (struct)

Arrays

Functions

Conditional statements

Loops

File handling (ifstream, ofstream)

Sorting (Bubble Sort)

Input validation

C-style strings

📂 File Handling

File Name: students.txt

Student data is saved when the program exits.

Student data is loaded automatically when the program starts.

This ensures data persistence.

🧮 Result Calculation Criteria
Component	Weightage
Quizzes	10%
Assignments	10%
Midterm	30%
Final Exam	50%
🏷️ Grade System
Percentage	Grade
≥ 85	A
≥ 75	B
≥ 65	C
≥ 50	D
< 50	F
🔍 Roll Number Format

The roll number must follow this format:

25X-1234


First 2 characters → digits

3rd character → uppercase alphabet

4th character → hyphen (-)

Last 4 characters → digits

▶️ How to Run the Project

Compile the program using a C++ compiler:

g++ main.cpp -o studentSystem


Run the executable:

./studentSystem


Follow the on-screen menu options.

📊 Menus Available
Main Menu

Student Operations

File Operations

Class Report

Exit

Student Operations

Add Student

Display All Students

Search Student

Update Student

Delete Student

⚠️ Limitations

Maximum 100 students

Uses arrays instead of dynamic containers

Console-based (no GUI)

🛠️ Future Improvements

Use vector instead of arrays

Use string instead of C-style strings

Add GUI support

Improve file format (CSV or binary)

👨‍🎓 Author

Project Type: Academic / Viva Project

Language: C++

Paradigm: Procedural Programming

✅ Conclusion

This project demonstrates effective use of basic C++ programming concepts, file handling, and data management techniques to build a functional student result management system.
