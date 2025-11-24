/**
 * @file BlockCourse.h
 * @brief Defines the BlockCourse class, which represents a course conducted in
 * a block schedule.
 *
 * The BlockCourse class is derived from the Course class and provides
 * additional details about courses conducted in a block format, including start
 * and end dates, and start and end times.
 *
 * @author ngocn
 * @date Jan 12, 2025
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_
#include <Poco/Data/Date.h>
#include <Poco/DateTime.h>
#include <Poco/Data/Time.h>
#include <string>
#include "Course.h"

/**
 * @class BlockCourse
 * @brief Represents a course conducted in a block schedule.
 *
 * This class provides specific details about block courses, such as start and
 * end dates, and start and end times. It extends the Course class.
 */
class BlockCourse: public Course
{
private:
	Poco::Data::Date startDay; /**< The start date of the block course. */
	Poco::Data::Date endDay;   /**< The end date of the block course. */
	Poco::Data::Time startTime;/**< The start time of the block course each
																		day. */
	Poco::Data::Time endTime; /**< The end time of the block course each day. */
public:

    /**
     * @brief Constructs a BlockCourse object.
     *
     * @param courseKey The unique key for the course.
     * @param title The title of the course.
     * @param major The major associated with the course.
     * @param creditPoints The number of credit points for the course.
     * @param startDay The start date of the block course.
     * @param endDay The end date of the block course.
     * @param startTime The start time of the block course each day.
     * @param endTime The end time of the block course each day.
     */
	BlockCourse(unsigned int courrseKey, std::string title, std::string major,
		float creditPoints, Poco::Data::Date startDay, Poco::Data::Date endDay,
		Poco::Data::Time startTime, Poco::Data::Time endTime);

    /**
     * @brief Retrieves the start date of the block course.
     *
     * @return A const reference to the start date.
     */
	const Poco::Data::Date& getStartDate() const;

    /**
     * @brief Retrieves the end date of the block course.
     *
     * @return A const reference to the end date.
     */
	const Poco::Data::Date& getEndDate() const;

    /**
     * @brief Retrieves the start time of the block course each day.
     *
     * @return A const reference to the start time.
     */
	const Poco::Data::Time& getStartTime() const;

    /**
     * @brief Retrieves the end time of the block course each day.
     *
     * @return A const reference to the end time.
     */
	const Poco::Data::Time& getEndTime() const;

    /**
     * @brief Writes the details of the block course to an output stream.
     *
     * @param out The output stream.
     */
	void write(std::ostream& out) const override;

    /**
     * @brief Reads the details of the block course from an input stream.
     *
     * @param in The input stream.
     */
	void read(std::istream& in);
};

#endif /* BLOCKCOURSE_H_ */
