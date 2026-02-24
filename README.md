# **STUDENT DATABASE (StudentDB)**
## 📌 Overview

**This project implements a complete object-oriented student database system including:**

- Course management

- Student management

- Enrollment handling

- File persistence (CSV-like format)

- Network-based test data generation

The architecture follows the Model–View–Controller pattern:

- Model: StudentDb and domain classes

- View + Controller: SimpleUI

All user interaction is strictly handled inside SimpleUI.

## 🎯 Objectives

- Design immutable domain classes where possible

- Automatically generate matriculation numbers

- Hide internal storage optimizations

- Maintain strict separation between model and UI

## 🏗 System Architecture
### 1️. Course (Base Class)

**Represents a university course.**

Derived classes:

- WeeklyCourse

- BlockCourse

Storage Optimization

The property major is internally stored as a char and mapped to a string via the static lookup table majorById.

This optimization is completely hidden from users of the class.

### 2️. Student

**Automatically assigned matriculation number**

- First name / last name

- Date of birth

- Address

- Enrollments

- The static member nextMatrikelNumber ensures unique IDs.

### 3️. Address (Immutable)

If any address field changes, a new object must be created.

### 4️. Enrollment

A student enrolled in a course

- Semester

- Optional grade

### 5️ StudentDb (Model)

- All courses

- All students

- All enrollments

Provides methods for:

- Adding courses

- Adding students

- Managing enrollments

- Searching students

- Updating student data

❗ No input/output operations are allowed in this class.

### 6️. SimpleUI (View + Controller)

Handles:

- All user input

- Output formatting

- Command dispatching

Only this class may use cin and cout.

## 📐 UML Diagrams
🔹 Overall Class Diagram

<img width="1039" height="624" alt="image" src="https://github.com/user-attachments/assets/ca8fce1c-755d-414a-8859-3ec1fab978da" />

## 💾 Persisting the Database
### 🎯 Goal

- Store and restore the database using a custom
- Comma-separated values-inspired format.

### File Structure:

- Number of courses

- Course entries

- Number of students

- Student entries

- Number of enrollments

- Enrollment entries

- Values are separated using ;.

### 📝 Writing Data

- Each relevant class implements: virtual void write(std::ostream& out);

Responsibilities:

- Course::write → writes base class data

- Derived classes → write type indicator + derived data

- Student::write

- Enrollment::write

- StudentDb::write → orchestrates writing

SimpleUI only triggers file operations.

## 📥 Reading Data

StudentDb::read(std::istream& in):

- Clears database

- Restores content

- Delegates parsing to domain classes

- Updates nextMatrikelNumber

- Parsing logic is not implemented inside SimpleUI.

## 🌐 Obtaining Test Data (POCO Version)
### 🎯 Goal

Automatically generate students by retrieving sample data from:

- Host: www.hhs.users.h-da.cloud
- Port: 4242

Server commands:

- generate

- quit

### 🛠 Implementation with POCO

- Network communication is implemented using the
- POCO C++ Libraries.

Used components:

- Poco::Net::StreamSocket

- Poco::Net::SocketAddress

- Poco::Net::SocketStream

- Poco::JSON::Parser

- Poco::JSON::Object

### 🔁 Workflow

- Establish TCP connection

- Send generate command

- Flush stream

- Receive JSON data

- Parse JSON using Poco::JSON::Parser

- Extract:

  - Name

  - Date of birth

  - Address

- Create new Student object

- Repeat if multiple students requested

- Send quit command

### ⚠ Important Notes

- Network streams are buffered → call flush()

- Server timeout: 5 seconds

- Always terminate session properly using quit

- No network logic inside StudentDb (handled via command in SimpleUI)

## 🧪 Testing

- Functional testing via SimpleUI

- Persistence tested via write → read → compare

- Enrollment and search functionality verified

- Network feature tested manually

## 📚 Documentation

- Complete Doxygen documentation

- Documentation includes:

- Class responsibilities

- Design decisions

- File format explanation

- Network communication approach

## 🎯 Learning Objectives

- Advanced OOP design

- MVC architecture

- Immutable objects

- Polymorphism and delegation

- Stream-based file I/O

- Network programming with POCO

- JSON parsing

- Clean architectural separation
