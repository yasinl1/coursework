Library Management System
CST2550 Coursework 1
This project implements a simple library management system for a small library to track book details and member information.
Features

Add new library members
Issue books to members
Return books from members
Display books borrowed by a specific member
Calculate fines for overdue books

Requirements

C++ compiler with C++11 support or later

Make build system

Catch2 for unit testing

Project Structure

src/ - Source code files
include/ - Header files
tests/ - Catch2 test files
Makefile - Build configuration

Building the Project
To build the project, run:
Copymake
To clean the build files:
Copymake clean
Running the Program
After building, run the program with:
Copy./library_system
Running Tests
To run the Catch2 tests:
Copy./run_tests
Design
The system is designed using object-oriented principles, following the provided UML class diagram. Key classes include:

Book
Member
Library

Implementation Notes

The system reads book data from a CSV file (not hardcoded, configurable at runtime)
Input validation is implemented to ensure data integrity
The system uses a console-based menu for user interaction

Version Control
This project uses Git for version control. Commit messages follow clear and descriptive conventions.
Testing
Unit tests are implemented using the Catch2 framework to ensure the correctness of class implementations and key functionalities.
Limitations and Future Improvements
[To be filled in after project completion]
Author

Yasin Lester

License
This project is submitted as coursework for CST2550 and is subject to university academic policies.
