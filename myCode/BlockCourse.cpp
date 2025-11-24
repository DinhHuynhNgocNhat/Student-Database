/*
 * BlockCourse.cpp
 *
 *  Created on: Jan 12, 2025
 *      Author: ngocn
 */
#include <iostream>
#include <string>
#include "BlockCourse.h"

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
	std::string major, float creditPoints, Poco::Data::Date startDay,
	Poco::Data::Date endDay, Poco::Data::Time startTime,
	Poco::Data::Time endTime) : Course(courseKey,title,major,creditPoints),
	startDay(startDay), endDay(endDay), startTime(startTime), endTime(endTime)
{
}

const Poco::Data::Date& BlockCourse::getStartDate() const
{
	return startDay;
}

const Poco::Data::Date& BlockCourse::getEndDate() const
{
	return endDay;
}

const Poco::Data::Time& BlockCourse::getStartTime() const
{
	return startTime;
}

const Poco::Data::Time& BlockCourse::getEndTime() const
{
	return endTime;
}

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";
	Course::write(out);
	out << startDay.day()<<"."<<startDay.month()<<startDay.year()<<";"<<
		endDay.day()<<"."<<endDay.month()<<"."<<endDay.year()<<";"<<
		startTime.hour()<<":"<<startTime.minute()<<";"<<endTime.hour()<<":"<<
		endTime.minute()<<std::endl;
}

void BlockCourse::read(std::istream &in)
{
	Course::read(in);

	std::string startDay, startMonth, startYear;
	std::string endDay, endMonth, endYear;
	std::string startHour, startMinute;
	std::string endHour, endMinute;

	//read start date
	std::getline(in, startDay,'.');
	std::getline(in, startMonth,'.');
	std::getline(in, startYear,';');
	this->startDay = Poco::Data::Date{std::stoi(startYear),std::stoi(startMonth)
		,std::stoi(startDay)};

	//read end date
	std::getline(in, endDay,'.');
	std::getline(in, endMonth,'.');
	std::getline(in, endYear,';');
	this->endDay = Poco::Data::Date(std::stoi(endYear),std::stoi(endMonth),
			std::stoi(endDay));

	//read start time
	std::getline(in, startHour,':');
	std::getline(in, startMinute,';');
	this->startTime = Poco::Data::Time(std::stoi(startHour),
			std::stoi(startMinute),0);

	//read end time
	std::getline(in, endHour,':');
	std::getline(in, endMinute);
	this->endTime = Poco::Data::Time(std::stoi(endHour),
			std::stoi(endMinute),0);

}
