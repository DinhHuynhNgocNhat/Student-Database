/**
 * @file WeeklyCourse.h
 * @brief Defines the WeeklyCourse class, a specialization of the Course class
 * for weekly recurring courses.
 *
 * The WeeklyCourse class represents courses that take place on a specific day
 * of the week and have defined start and end times. It inherits from the Course
 * class and extends its functionality by including additional attributes and
 *  methods specific to weekly courses.
 *
 * @author ngocn
 * @date Jan 11, 2025
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_
#include <Poco/Data/Date.h>
#include <Poco/Data/Time.h>
#include <Poco/DateTime.h>
#include "Course.h"
#include <string>

/**
 * @class WeeklyCourse
 * @brief Represents a course that occurs weekly on a specific day and time.
 *
 * The WeeklyCourse class extends the base Course class by adding attributes
 * for the day of the week and the start and end times of the course.
 */
class WeeklyCourse: public Course
{
private:
	Poco::DateTime::DaysOfWeek dayOfWeek; /**< The day of the week on which the
															course occurs. */
	Poco::Data::Time startTime; /**< The starting time of the course. */
	Poco::Data::Time endTime;  /**< The ending time of the course. */
public:
    /**
     * @brief Constructs a WeeklyCourse object.
     *
     * @param courseKey The unique key for the course.
     * @param title The title of the course.
     * @param major The major associated with the course.
     * @param creditPoints The number of credit points for the course.
     * @param dayOfWeek The day of the week when the course occurs.
     * @param startTime The starting time of the course.
     * @param endTime The ending time of the course.
     */
	WeeklyCourse(unsigned int courrseKey, std::string title, std::string major,
		float creditPoints, Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime, Poco::Data::Time endTime);

    /**
     * @brief Retrieves the day of the week for the course.
     *
     * @return A const reference to the day of the week.
     */
	const Poco::DateTime::DaysOfWeek& getDayOfWeek() const;

    /**
     * @brief Retrieves the start time of the course.
     *
     * @return A const reference to the start time.
     */
	const Poco::Data::Time& getStartTime() const;

    /**
     * @brief Retrieves the end time of the course.
     *
     * @return A const reference to the end time.
     */
	const Poco::Data::Time& getEndTime() const;

    /**
     * @brief Converts an integer to a Poco::DateTime::DaysOfWeek value.
     *
     * @param day The integer representing the day of the week (0 for Sunday, 1
     * for Monday, etc.).
     * @return The corresponding Poco::DateTime::DaysOfWeek value.
     */
	Poco::DateTime::DaysOfWeek getDayFromInt(const int day);

    /**
     * @brief Writes the WeeklyCourse details to an output stream.
     *
     * This method overrides the write method in the Course class.
     *
     * @param out The output stream.
     */
	void write(std::ostream& out) const override;

    /**
     * @brief Reads the WeeklyCourse details from an input stream.
     *
     * This method parse the input stream to extract WeeklyCourse-specific data.
     *
     * @param in The input stream.
     */
	void read(std::istream& in);
};

#endif /* WEEKLYCOURSE_H_ */
