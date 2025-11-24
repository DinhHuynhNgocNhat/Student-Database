/**
 * @file StudentDb.h
 * @brief Defines the StudentDb class that manages the student database.
 *
 * The StudentDb class is responsible for maintaining and managing the student
 * and course data. It provides functionalities to add, retrieve, and modify
 * students, courses, and enrollments, as well as to persist data to and
 * retrieve data from streams.
 *
 * @author ngocn
 * @date Jan 11, 2025
 */

#include "Student.h"
#include "Course.h"
#include <map>
#include <memory>
#ifndef STUDENTDB_H_
#define STUDENTDB_H_

/**
 * @class StudentDb
 * @brief Represents the student database and manages its content.
 *
 * The StudentDb class provides operations for adding students and courses,
 * managing enrollments, and storing and retrieving data from external sources.
 */
class StudentDb
{
private:
	std::map<int,Student> students; /**< A map of students, keyed by their
                                          matrikel number. */
	std::map<int, std::unique_ptr<const Course>> courses; /**< A map of
                                                                courses, keyed
                                                                by course ID. */
public:
    /**
     * @brief Constructs an empty StudentDb object.
     */
	StudentDb();

    /**
     * @brief Retrieves the map of students.
     *
     * @return A const reference to the map of students.
     */
	const std::map<int,Student> getStudent() const;

    /**
     * @brief Retrieves the map of courses.
     *
     * @return A const reference to the map of courses.
     */
	const std::map<int,std::unique_ptr<const Course>>& getCourse() const;

    /**
     * @brief Adds a new course to the database.
     *
     * @param course A unique pointer to the Course object to add.
     */
	void addCourse(std::unique_ptr<Course>& course);

    /**
     * @brief Adds a new student to the database.
     *
     * @param student The Student object to add.
     */
	void addNewStudent(Student& student);

    /**
     * @brief Adds a new enrollment for a student in a course.
     *
     * @param matrikelNummer The matrikel number of the student.
     * @param courseKey The key of the course.
     * @param semester The semester in which the student enrolls.
     * @return True if the enrollment is successful, false otherwise.
     */
	bool addEnrollment(unsigned int matrikelNummer, unsigned int courseKey,
														std::string semester);

    /**
     * @brief Validates if a student exists in the database.
     *
     * @param matrikelNummer The matrikel number of the student.
     * @return True if the student exists, false otherwise.
     */
	bool validStudent(unsigned int matrikelNummer);

    /**
     * @brief Searches for students by name.
     *
     * @param name The name or part of the name to search for.
     * @return A vector of Student objects matching the search criteria.
     */
	std::vector<Student> getStudentByName(const std::string& name) const;

    /**
     * @brief Retrieves a student by their matrikel number.
     *
     * @param matrikelNummer The matrikel number of the student.
     * @return A reference to the Student object.
     */
	Student& getStudentByMatrikelNummer(unsigned int matrikelNummer);

    /**
     * @brief Retrieves a course by its key.
     *
     * @param courseKey The key of the course.
     * @return A const reference to the Course object.
     */
	const Course& getCourseByCourseKey(unsigned int courseKey) const;

    /**
     * @brief Clears all data from the student database.
     */
	void clearStudentDatabase();

    /**
     * @brief Writes the student database to an output stream.
     *
     * Outputs the data for courses, students, and enrollments.
     *
     * @param out The output stream.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the student database from an input stream.
     *
     * Reads and parses the data for courses, students, and enrollments.
     *
     * @param in The input stream.
     */
	void read(std::istream& in);
};

#endif /* STUDENTDB_H_ */
