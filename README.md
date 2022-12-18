# Library-Management
A **Library-Management-System** designed with the **QT C++ framework** that provides libraries with a useful software to perform essential tasks using a GUI. The software comprises of a menu-driven GUI interface styled with the **Windows Fluent Design** as its base. Its backend comprises a **SQLite database** containing 4 tables: *books*, *users*, *issued_books* and *classification_numbers (for the books)*. The application offers the following functionalities:
- Add, edit, search and delete a book in the *books* table
- Add, edit, search and delete a user in the *users* table
- Issue and return a book
- Print the list of books, users, issued books and overdue books
- Export the list of books, users, issued_books and overdue books as a csv file

<img src="https://github.com/Jishnu8/Library-Management/blob/main/data/library_management.png" width="700" height="Auto">

## Build
#### 1. Clone Repository
```
git clone https://github.com/Jishnu8/Library-Management
```
#### 2. Create build directory
```
mkdir build
```
#### 3. Configure and Build

a) Using CMake
```
cmake ..
make
```
b) Using qmake
```
qmake $path_to_LibraryManagement.pro
make
```
#### 4. Run Executable
```
./LibraryManagement
```
