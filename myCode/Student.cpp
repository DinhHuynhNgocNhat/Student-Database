/*
 * Student.cpp
 *
 *  Created on: Jan 11, 2025
 *      Author: ngocn
 */

#include "Student.h"
#include <iostream>
#include <algorithm>
unsigned int Student::nextMatrikelNumber =100000;

Student::Student(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, Address address) : firstName(firstName),
		lastName(lastName), dateOfBirth(dateOfBirth), address(address)
{
	this->matrikelNumber = this->nextMatrikelNumber;
	this->nextMatrikelNumber++;
}

unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

unsigned int Student::getNextMatrikelNumber() const
{
	return nextMatrikelNumber;
}

const std::string& Student::getFirstName() const
{
	return firstName;
}

const std::string& Student::getLastName() const
{
	return lastName;
}

const Address& Student::getAddress() const
{
	return address;
}

const Poco::Data::Date& Student::getDateOfBirth() const
{
	return dateOfBirth;
}

const std::vector<Enrollment>& Student::getEnrollment() const
{
	return enrollments;
}

void Student::setAddress(Address &address)
{
	this->address=address;
}

void Student::setDateOfBirth(Poco::Data::Date &dateOfBirth)
{
	this->dateOfBirth = dateOfBirth;
}

void Student::setFirstName(std::string &firstName)
{
	this->firstName = firstName;
}

void Student::setLastName(std::string &lastName)
{
	this->lastName = lastName;
}

bool Student::addEnrollment(Enrollment &enrollment)
{
	if (repeatEnrollment(enrollment)){
		return false;
	}
	else{
		enrollments.push_back(enrollment);
		return true;
	}
}

bool Student::repeatEnrollment(Enrollment &enrollment) const
{
	if(std::find(enrollments.begin(), enrollments.end(), enrollment)
			!= enrollments.end()){
		return true;
	}
	return false;
}

bool Student::setGrade(unsigned int courseKey, float newGrade)
{
	for (auto& enrollment : enrollments){
		if(enrollment.getCourse()->getCourseKey() == courseKey){
			enrollment.setGrade(newGrade);
			return true;
		}
	}
	return false;
}

bool Student::removeEnrollment(unsigned int courseKey)
{
	for(auto removeEnroll = enrollments.begin(); removeEnroll !=
											enrollments.end(); removeEnroll++){
		if(removeEnroll->getCourse()->getCourseKey()==courseKey)
		{
			removeEnroll = enrollments.erase(removeEnroll);
			return true;
		}
	}
	return false;
}

void Student::write(std::ostream &out) const
{
	out<<matrikelNumber<<";"<<firstName<<";"<<lastName<<";"<<dateOfBirth.day()<<
		"."<<dateOfBirth.month()<<"."<<dateOfBirth.year()<<";";
	address.write(out);
	out << std::endl;
}

void Student::read(std::istream &in)
{
	in >> matrikelNumber;
	if(matrikelNumber > nextMatrikelNumber){
		nextMatrikelNumber = matrikelNumber++;
	}
	in.ignore(256,';');

	std::getline(in, firstName,';');

	std::getline(in, lastName, ';');

	std::string birthDay, birthMonth, birthYear;
	std::getline(in, birthDay,'.');
	std::getline(in, birthMonth,'.');
	std::getline(in, birthYear,';');
	this->dateOfBirth = Poco::Data::Date(std::stoi(birthYear),
			std::stoi(birthMonth),std::stoi(birthDay));

	//this->address=address.read(in);
	this->address.read(in);
}
