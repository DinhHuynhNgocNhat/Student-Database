/*
 * WeeklyCourse.cpp
 *
 *  Created on: Jan 11, 2025
 *      Author: ngocn
 */
#include <iostream>
#include <string>
#include "WeeklyCourse.h"

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek dayOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime):Course(courseKey, title, major, creditPoints),
		dayOfWeek(dayOfWeek), startTime(startTime), endTime(endTime)
{


}

const Poco::DateTime::DaysOfWeek& WeeklyCourse::getDayOfWeek() const
{
	return dayOfWeek;
}

const Poco::Data::Time& WeeklyCourse::getStartTime() const
{
	return startTime;
}

const Poco::Data::Time& WeeklyCourse::getEndTime() const
{
	return endTime;
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";
	Course::write(out);
	out << dayOfWeek << ";" << startTime.hour() << ":" << startTime.minute() <<
		";" << endTime.hour() << ":" << endTime.minute()<< std::endl;
}

void WeeklyCourse::read(std::istream &in)
{
	Course::read(in);
	int day;
	in >> day;

	this->dayOfWeek = this->getDayFromInt(day);
	in.ignore(1,';');

	std::string hour,minute;

	std::getline(in, hour,':');
	std::getline(in, minute,';');
	this->startTime = Poco::Data::Time(std::stoi(hour),std::stoi(minute),0);

	std::getline(in, hour,':');
	std::getline(in, minute,';');
	this->endTime = Poco::Data::Time(std::stoi(hour),std::stoi(minute),0);
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDayFromInt(const int day)
{
	switch (day){
	case 0:
		return Poco::DateTime::DaysOfWeek::SUNDAY;
	case 1:
		return Poco::DateTime::DaysOfWeek::MONDAY;
	case 2:
		return Poco::DateTime::DaysOfWeek::TUESDAY;
	case 3:
		return Poco::DateTime::DaysOfWeek::WEDNESDAY;
	case 4:
		return Poco::DateTime::DaysOfWeek::THURSDAY;
	case 5:
		return Poco::DateTime::DaysOfWeek::FRIDAY;
	case 6:
		return Poco::DateTime::DaysOfWeek::SATURDAY;
	default:
		return Poco::DateTime::DaysOfWeek::SUNDAY;
	}
}
