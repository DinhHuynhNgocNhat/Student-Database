/**
 * @file Address.h
 * @brief Defines the Address class, which represents a student's address.
 *
 * This class encapsulates information about a student's address, including
 * street, postal code, city name, and additional information.
 *
 * @author ngocn
 * @date Jan 11, 2025
 */
#include <string>

#ifndef ADDRESS_H_
#define ADDRESS_H_

/**
 * @class Address
 * @brief Represents a student's address.
 *
 * This class holds details about the address of a student, including the street
 * , postal code, city name, and any additional information.
 */
class Address
{
private:
	std::string street; /**< The street name of the address. */
	unsigned short postalCode; /**< The postal code of the address. */
	std::string cityName; /**< The city name of the address. */
	std::string additionalInfo;  /**< Any additional information about
																the address. */
public:
    /**
     * @brief Constructs an Address object.
     *
     * @param street The street name.
     * @param postalCode The postal code.
     * @param cityName The city name.
     * @param additionalInfo Any additional information.
     */
	Address(std::string street, unsigned short postalCode, std::string cityName,
												std::string additionalInfo);

    /**
     * @brief Retrieves the street name.
     *
     * @return A const reference to the street name.
     */
	const std::string& getStreet() const;

    /**
     * @brief Retrieves the postal code.
     *
     * @return A const reference to the postal code.
     */
	const unsigned short& getPostalCode() const;

    /**
     * @brief Retrieves the city name.
     *
     * @return A const reference to the city name.
     */
	const std::string& getCityName() const;

    /**
     * @brief Retrieves additional information about the address.
     *
     * @return A const reference to the additional information.
     */
	const std::string& getAdditionalInfo() const;

    /**
     * @brief Writes the address details to an output stream.
     *
     * @param out The output stream.
     */
	void write(std::ostream& out) const;

    /**
     * @brief Reads the address details from an input stream.
     *
     * @param in The input stream.
     */
	void read(std::istream& in);
};

#endif /* ADDRESS_H_ */
