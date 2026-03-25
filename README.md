# Code publication repository for lab 4
# "Fishing flotilla management system"

--- 
## Description
This is a C++ app for automating work with an sqlite3 database through a command line interface.<br>
The program allows for automatic database creation (for testing purposes) and manual. The databases can be automatically cleaned up after testing is finishied.

---

## Documentation repository
The repository meant for documenting this project as well as individual project for lab 4 is below:
<a href="https://github.com/fpmi-tpmp2026/tpmp-gr13b-lab4-bestest-team">Fishing flotilla managemenet system documentation</a>

---

## Usage
All interactions with the program are built inside the makefile:

`make run` - run the application without creating a database

`make db` - create a seeded database from test data

`make clean` - clean compiled program and database files

`make test` - run built-in unit tests on the application, development purposes only

---

## Contents
| Folder     | Files            | Purpose                                                                     |   |   |
|------------|------------------|-----------------------------------------------------------------------------|---|---|
| /workflows | ci.yml           | Automated testing through github actions to ensure compilation and running. |   |   |
| /database  | schema.sql       | Defines the basic structure for creating databases with the app.            |   |   |
|            | seed.sql         | Contains a predefined database for testing purposes.                        |   |   |
| /include   | auth.h           | Contains classes for authorization in the database.                         |   |   |
|            | database.h       | Contains a wrapper class for working with sqlite3 databases.                |   |   |
|            | queries.h        | Functions for working with a database defined in our variant of the lab.    |   |   |
| /src       | main.cpp         | Main program loop                                                           |   |   |
|            | database.cpp     | Definitions for database.h                                                  |   |   |
|            | auth.cpp         | Definitions for auth.h                                                      |   |   |
|            | queries.cpp      | Definitions for queries.h                                                   |   |   |
| /tests     | main_test.cpp    | Runs tests using CUnit interface for all basic interactions with the app.   |   |   |
|            | test_auth.cpp    | Definitions for authorization test functions used by main_test.cpp          |   |   |
|            | test_queries.cpp | Definitions for database interactions test functions used by main_test.cpp  |   |   |
| /          | Makefile         | Makefile for interacting with the program.                                  |   |   |

---

## Testing
As per the task in the lab, the program has built-in automatic testing both through github actions (`/workflows/ci.yml`)<br>
and regular unit testing (`/tests/*` and `make test`).

---

## Contributing

<a href="https://github.com/iliaamakarov">Ilia Makarov</a>

<a href="https://github.com/VHursevich">Vadim Hursevich</a>
