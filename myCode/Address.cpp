/*
 * Address.cpp
 *
 *  Created on: Jan 11, 2025
 *      Author: ngocn
 */
#include <iostream>
#include "Address.h"

Address::Address(std::string street, unsigned short postalCode,
	std::string cityName, std::string additionalInfo) : street(street),
	postalCode(postalCode), cityName(cityName), additionalInfo(additionalInfo)
{
}

const std::string& Address::getStreet() const
{
	return street;
}

const unsigned short& Address::getPostalCode() const
{
	return postalCode;
}

const std::string& Address::getCityName() const
{
	return cityName;
}

const std::string& Address::getAdditionalInfo() const
{
	return additionalInfo;
}

void Address::write(std::ostream &out) const
{
	out<<street<<";"<<postalCode<<";"<<cityName<<";"<<additionalInfo;
}

void Address::read(std::istream &in)
{
	//Address adr("",0,"","");
	std::getline(in,street,';');

	in >> postalCode;
	in.ignore(1,';');

	std::getline(in,cityName,';');

	std::getline(in, additionalInfo,'\n');
}
