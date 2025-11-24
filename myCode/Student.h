/**
 * @file Student.h
 * @brief Defines the Student class representing a student in the database.
 *
 * The Student class stores information about a student, including personal
 * details, date of birth, address, and enrollments in courses. It provides
 * methods for accessing and modifying student data and supports reading from
 * and writing to streams.
 *
 * @author ngocn
 * @date Jan 11, 2025
 */
#include <Poco/Data/Date.h>
#include <string>
#include <vector>
#include "Address.h"
#include "Enrollment.h"
#ifndef STUDENT_H_
#define STUDENT_H_

/**
 * @class Student
 * @brief Represents a student and their associated data.
 *
 * The Student class manages a student's personal information, enrollments in
 * courses, and other related data.
 */
class Student
{
private:
	static unsigned int nextMatrikelNumber; /**< Static counter for the next
                                                 	 	 	 matrikel number. */
	unsigned int matrikelNumber; /**< Unique identifier for the student. */
	std::string firstName; /**< The first name of the student. */
	std::string lastName; /**< The last name of the student. */
	Poco::Data::Date dateOfBirth; /**< The date of birth of the student. */
	std::vector<Enrollment> enrollments; /**< List of courses the student is
                                              enrolled in. */
	Address address; /**< The address of the student. */
public:
    /**
     * @brief Constructs a Student object.
     *
     * @param firstName The first name of the student.
     * @param lastName The last name of the student.
     * @param dateOfBirth The date of birth of the student.
     * @param address The address of the student.
     */
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, Address address);

    /**
     * @brief Retrieves the matrikel number of the student.
     *
     * @return The matrikel number.
     */
	unsigned int getMatrikelNumber() const;

    /**
     * @brief Retrieves the next available matrikel number.
     *
     * @return The next matrikel number.
     */
	unsigned int getNextMatrikelNumber() const;

    /**
     * @brief Retrieves the first name of the student.
     *
     * @return A const reference to the first name.
     */
	const std::string& getFirstName() const;

    /**
     * @brief Retrieves the last name of the student.
     *
     * @return A const reference to the last name.
     */
	const std::string& getLastName() const;

    /**
     * @brief Retrieves the address of the student.
     *
     * @return A const reference to the Address object.
     */
	const Address& getAddress() const;

    /**
     * @brief Retrieves the date of birth of the student.
     *
     * @return A const reference to the Poco::Data::Date object.
     */
	const Poco::Data::Date& getDateOfBirth() const;

    /**
     * @brief Retrieves the list of enrollments for the student.
     *
     * @return A const reference to the vector of Enrollment objects.
     */
	const std::vector<Enrollment>& getEnrollment() const;

    /**
     * @brief Updates the address of the student.
     *
     * @param address The new Address object.
     */
	void setAddress(Address& address);

    /**
     * @brief Updates the date of birth of the student.
     *
     * @param dateOfBirth The new Poco::Data::Date object.
     */
	void setDateOfBirth(Poco::Data::Date& dateOfBirth);

    /**
     * @brief Updates the first name of the student.
     *
     * @param firstName The new first name.
     */
	void setFirstName(std::string& firstName);

    /**
     * @brief Updates the last name of the student.
     *
     * @param lastName The new last name.
     */
	void setLastName(std::string& lastName);

    /**
     * @brief Adds a new enrollment for the student.
     *
     * @param enrollment The Enrollment object to add.
     * @return True if the enrollment is added successfully, false otherwise.
     */
	bool addEnrollment(Enrollment& enrollment);

    /**
     * @brief Checks if an enrollment already exists.
     *
     * @param enrollment The Enrollment object to check.
     * @return True if the enrollment already exists, false otherwise.
     */
	bool repeatEnrollment(Enrollment& enrollments) const;

    /**
     * @brief Updates the grade for a specific course.
     *
     * @param courseKey The key of the course to update.
     * @param newGrade The new grade for the course.
     * @return True if the grade is updated successfully, false otherwise.
     */
	bool setGrade(unsigned int courseKey, float newGrade);

    /**
     * @brief Removes an enrollment for a specific course.
     *
     * @param courseKey The key of the course to remove.
     * @return True if the enrollment is removed successfully, false otherwise.
     */
	bool removeEnrollment(unsigned int courseKey);

    /**
     * @brief Writes the student data to an output stream.
     *
     * Outputs the personal details, address, and enrollments.
     *
     * @param out The output stream.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the student data from an input stream.
     *
     * Reads and parses the personal details, address, and enrollments.
     *
     * @param in The input stream.
     */
	void read(std::istream& in);
};

#endif /* STUDENT_H_ */
