/**
 * @file SimpleUI.h
 * @brief Defines the SimpleUI class, which provides a user interface
 *        for managing the student database.
 *
 * The SimpleUI class serves as the interface for interacting with the
 * StudentDb. It provides methods to add, list, update, and search
 * students and courses, as well as to read and write data to and from
 * external sources. It also supports fetching student data from a server.
 *
 * @author ngocn
 * @date Jan 11, 2025
 */
#include "StudentDb.h"
#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

/**
 * @class SimpleUI
 * @brief Provides a user interface for managing the student database.
 *
 * The SimpleUI class acts as the controller and view in the MVC pattern.
 * It facilitates communication between the user and the StudentDb by
 * implementing interactive commands for database management.
 */
class SimpleUI
{
private:
	StudentDb& studentDb; /**< A reference to the StudentDb instance. */

    /**
     * @brief Adds a new course to the database.
     */
	void addNewCourse();

    /**
     * @brief Lists all courses in the database.
     */
	void listCourses() const;

    /**
     * @brief Displays details of a specific course.
     *
     * @param course A pointer to the Course object to display.
     */
	void listSpecificCourses(const Course* course) const;

    /**
     * @brief Adds a new student to the database.
     */
	void addStudent();

    /**
     * @brief Adds a new enrollment for a student.
     */
	void addEnrollment();

    /**
     * @brief Prints all students in the database with their details.
     */
	void printStudent();

    /**
     * @brief Searches for students by name.
     */
	void searchStudent();

    /**
     * @brief Updates the details of a specific student.
     */
	void updateStudent();

    /**
     * @brief Writes the database to an external file.
     */
	void writeData();

    /**
     * @brief Reads the database from an external file.
     */
	void readData();

    /**
     * @brief Fetches student data from a remote server.
     */
	void getStudentFromServer() const;
public:
	SimpleUI(StudentDb& studentDb);
	void run();
};

#endif /* SIMPLEUI_H_ */
