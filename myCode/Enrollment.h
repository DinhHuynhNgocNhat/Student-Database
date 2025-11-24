/**
 * @file Enrollment.h
 * @brief Defines the Enrollment class representing a student's enrollment in a
 * course.
 *
 * The Enrollment class contains information about the course, the semester in
 * which the enrollment took place, and the grade received by the student. It
 * provides methods for accessing and modifying the enrollment data and supports
 * reading from and writing to streams.
 *
 * @author ngocn
 * @date Jan 11, 2025
 */
#include <string>
#include "Course.h"
#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

class Enrollment
{
private:
	std::string semester; /**< The semester in which the course is taken. */
	float grade; /**< The grade received for the course. */
	const Course* course; /**< Pointer to the course associated with this
                               enrollment. */
public:
    /**
     * @brief Constructs an Enrollment object.
     *
     * @param semester The semester in which the course is taken.
     * @param course Pointer to the associated course.
     */
	Enrollment(std::string semester,const Course* course);

    /**
     * @brief Retrieves the associated course.
     *
     * @return A const pointer to the associated course.
     */
	const Course* getCourse() const;

    /**
     * @brief Retrieves the semester of the enrollment.
     *
     * @return A const reference to the semester string.
     */
	const std::string& getSemester() const;

    /**
     * @brief Retrieves the grade received for the course.
     *
     * @return A const reference to the grade.
     */
	const float& getGrade() const;

    /**
     * @brief Sets the grade for the course.
     *
     * @param grade The new grade to assign to the enrollment.
     */
	void setGrade(float& grade);

    /**
     * @brief Compares two Enrollment objects for equality.
     *
     * Checks if the enrollments belong to the same semester and course.
     *
     * @param enroll The Enrollment object to compare with.
     * @return True if the enrollments are equal, false otherwise.
     */
    bool operator==(const Enrollment& enroll) const;

    /**
     * @brief Writes the enrollment details to an output stream.
     *
     * Outputs the semester, grade, and course key to the stream.
     *
     * @param out The output stream.
     */
    void write(std::ostream& out) const;

    /**
     * @brief Reads the enrollment details from an input stream.
     *
     * Reads and parses the semester, grade, and course key from the stream.
     *
     * @param in The input stream.
     */
    void read(std::istream& in);
};

#endif /* ENROLLMENT_H_ */
