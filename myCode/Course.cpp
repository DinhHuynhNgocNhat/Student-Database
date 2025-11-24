/*
 * Course.cpp
 *
 *  Created on: Jan 11, 2025
 *      Author: ngocn
 */
#include <iostream>
#include "Course.h"
#include <string>
#include <map>

std::map<unsigned char, std::string> Course::majorById=
{
	{'A',"Automation"},
	{'E',"Embedded"},
	{'C',"Communication"},
	{'P',"Power"}
};

Course::Course(unsigned int courseKey, std::string title, std::string major,
		float creditPoints) : courseKey(courseKey), title(title),
		creditPoints(creditPoints)
{
	//Have major
	std::map<unsigned char,std::string>::iterator majorId = majorById.begin();
	for(; majorId !=majorById.end();majorId++){
		if (majorId->second == major){
			this->major = majorId->first;
			return;
		}
	}
}

Course::~Course(){

}

const std::string& Course::getMajor() const
{
	return majorById.at(this->major);
}

const std::string& Course::getTitle() const
{
	return title;
}

const float& Course::getCreditPoints() const
{
	return creditPoints;
}

const unsigned int& Course::getCourseKey() const
{
	return courseKey;
}

void Course::write(std::ostream &out) const
{
	out << courseKey << ";" << title << ";" << getMajor() << ";" <<
			creditPoints << ";";
}

void Course::read(std::istream &in)
{
	in >> courseKey;
	in.ignore(1,';'); // skip until ';'

	std::getline(in, title, ';');

	std::string majorIn;
	std::getline(in, majorIn, ';');
	for (auto majorId : majorById){
		if(majorId.second == majorIn){
			major = majorId.first;
		}
	}

	in >> creditPoints;
	in.ignore(1,';');
}
