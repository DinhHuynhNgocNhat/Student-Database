/**
 * @file Course.h
 * @brief Defines the Course class, which serves as the base class for various
 * course types.
 *
 * The Course class provides common attributes and methods for courses, such as
 * course key, title, major, and credit points. It also contains virtual methods
 * for reading and writing course details, which can be overridden by derived
 * classes.
 *
 * @author ngocn
 * @date Jan 11, 2025
 */
#include <string>
#include <map>
#ifndef COURSE_H_
#define COURSE_H_

/**
 * @class Course
 * @brief Represents a generic course.
 *
 * The Course class provides attributes and methods common to all courses. It
 * serves as the base class for specialized course types (e.g., BlockCourse,
 * WeeklyCourse).
 * This class is abstract due to its pure virtual destructor.
 */
class Course
{
private:
	static std::map<unsigned char, std::string> majorById; /**< A map to store
						major identifiers and their string representations. */
	unsigned int courseKey; /**< The unique key for the course. */
	std::string title; /**< The title of the course. */
	unsigned char major; /**< The major associated with the course, stored as a
												character for optimization. */
	float creditPoints; /**< The number of credit points assigned to the
																	course. */
public:
    /**
     * @brief Constructs a Course object.
     *
     * @param courseKey The unique key for the course.
     * @param title The title of the course.
     * @param major The major associated with the course.
     * @param creditPoints The number of credit points for the course.
     */
	Course(unsigned int courseKey, std::string title, std::string major,
															float creditPoints);

    /**
     * @brief Pure virtual destructor for the Course class.
     *
     * Declaring the destructor as pure virtual makes this class abstract.
     */
	virtual ~Course() = 0;

    /**
     * @brief Retrieves the unique course key.
     *
     * @return A const reference to the course key.
     */
	const unsigned int& getCourseKey() const;

    /**
     * @brief Retrieves the major of the course.
     *
     * @return A const reference to the major as a string.
     */
	const std::string& getMajor() const;

    /**
     * @brief Retrieves the title of the course.
     *
     * @return A const reference to the course title.
     */
	const std::string& getTitle() const;

    /**
     * @brief Retrieves the credit points of the course.
     *
     * @return A const reference to the credit points.
     */
	const float& getCreditPoints() const;

    /**
     * @brief Retrieves the mapping of major identifiers to their string
     * representations.
     *
     * @return A const reference to the majorById map.
     */
	const std::map<unsigned char, std::string>& getMajorById();

    /**
     * @brief Writes the course details to an output stream.
     *
     * This method can be overridden by derived classes to include additional
     * details.
     *
     * @param out The output stream.
     */
	virtual void write(std::ostream& out) const;

    /**
     * @brief Reads the course details from an input stream.
     *
     * This method can be overridden by derived classes to parse additional
     * details.
     *
     * @param in The input stream.
     */
	virtual void read(std::istream& in);
};

#endif /* COURSE_H_ */
