/*
 * Enrollment.cpp
 *
 *  Created on: Jan 11, 2025
 *      Author: ngocn
 */
#include <iostream>
#include "Enrollment.h"

Enrollment::Enrollment(std::string semester,const Course *course):
	semester(semester), course(course)
{
	this->grade = 0;
}

const std::string& Enrollment::getSemester() const
{
	return semester;
}

const Course* Enrollment::getCourse() const
{
	return course;
}

void Enrollment::setGrade(float& grade)
{
	this->grade=grade;
}

const float& Enrollment::getGrade() const
{
	return grade;
}

bool Enrollment::operator ==(const Enrollment &enroll) const
{
	if (course == enroll.getCourse() && semester == enroll.getSemester()){
		return true;
	}
	return false;
}

void Enrollment::write(std::ostream &out) const
{
	out << course->getCourseKey() << ";" << semester <<";"<< grade <<std::endl;
}

void Enrollment::read(std::istream &in)
{
	std::getline(in, semester, ';');
	in >> grade;
	in.ignore(1,';');
}
