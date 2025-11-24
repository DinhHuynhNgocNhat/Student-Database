/*
 * StudentDb.cpp
 *
 *  Created on: Jan 11, 2025
 *      Author: ngocn
 */
#include <iostream>
#include <sstream>
#include "StudentDb.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"

StudentDb::StudentDb()
{
}

const std::map<int, Student> StudentDb::getStudent() const
{
	return students;
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourse()const
{
	return courses;
}

void StudentDb::addNewStudent(Student& student)
{
	students.insert(std::make_pair(student.getMatrikelNumber(),student));
}

void StudentDb::addCourse(std::unique_ptr<Course>& course)
{
    courses.insert(std::make_pair(course->getCourseKey(),std::move(course)));
}

std::vector<Student> StudentDb::getStudentByName(const std::string &name) const
{
	std::vector<Student> studentResult;
	for(const std::pair<int,Student> student : students){
		const std::string fullName = student.second.getFirstName() +
				student.second.getLastName();

        if (fullName.find(name) != std::string::npos) {
            studentResult.push_back(student.second);
        }
	}
	return studentResult;
}

bool StudentDb::addEnrollment(unsigned int matrikelNummer,
		unsigned int courseKey, std::string semester)
{
	Student& student = getStudentByMatrikelNummer(matrikelNummer);

	auto findCourse = courses.find(courseKey);
	if (findCourse == courses.end()){
		return false;
	}
	const Course* course = findCourse->second.get();

	Enrollment enrollment(semester,course);
	return student.addEnrollment(enrollment);
}

Student& StudentDb::getStudentByMatrikelNummer (unsigned int matrikelNummer)
{
	return students.at(matrikelNummer);
}

const Course& StudentDb::getCourseByCourseKey(unsigned int courseKey) const
{
    auto it = this->courses.find(courseKey);
    const Course* enrollCourse = it->second.get();

    return *enrollCourse;
}

bool StudentDb::validStudent(unsigned int matrikelNummer)
{
	auto it = students.find(matrikelNummer);
	if(it == students.end()){
		return false;
	}
	return true;
}

void StudentDb::write(std::ostream &out) const
{
	//print courses
	out << courses.size() << std::endl;
	for (auto& course : courses){
		course.second->write(out);
	}

	//print students
	out << students.size() << std::endl;
	for (auto& student : students){
		student.second.write(out);
	}

	//print enrollment
	for (auto& student : students){
		if (student.second.getEnrollment().size() != 0){
			out << student.second.getEnrollment().size() << std::endl;
		}
		for (auto& enrollment : student.second.getEnrollment()){
			out << student.first <<";";
			enrollment.write(out);
		}
	}
}

void StudentDb::clearStudentDatabase()
{
	this->courses.clear();
	this->students.clear();
}

void StudentDb::read(std::istream &in)
{
	this->clearStudentDatabase();

	//read courses
	int totalCourses;
	in >> totalCourses;
	in.ignore();

	for (int order = 0; order < totalCourses; order++){
		std::string courseLine;
		std::getline(in, courseLine, '\n');

		std::stringstream strm(courseLine);

		//example: W;5387;APT;Automation;5;3;17:45;19:15
		//type is the first token
		std::string type;
		std::getline(strm, type,';');

		//read weekly courses
		if (type == "W"){
			std::unique_ptr<Course> pCourse(new WeeklyCourse(0,"","Automation",
				0,Poco::DateTime::DaysOfWeek::MONDAY, Poco::Data::Time(0,0,0),
				Poco::Data::Time(0,0,0)));
			pCourse->read(strm);
			addCourse(pCourse);
		}

		//read blocked courses
		else if (type == "B"){
			std::unique_ptr<Course> pCourse(new BlockCourse(0,"","Automation",0,
				Poco::Data::Date{1,1,1},Poco::Data::Date{1,1,1},
				Poco::Data::Time{0,0,0}, Poco::Data::Time{0,0,0}));
			pCourse->read(strm);
			addCourse(pCourse);
		}
	}

	//read students
	int totalStudents;
	in >> totalStudents;
	in.ignore();

	for (int order = 0; order < totalStudents; order++){
		Student student("","",Poco::Data::Date(1,1,1),Address("",0,"",""));
		std::string studentLine;
		std::getline(in, studentLine, '\n');

		std::stringstream strm(studentLine);

		student.read(strm);
		addNewStudent(student);
	}

	//read enrollments
	int totalEnrollments;
	in >> totalEnrollments;
	in.ignore();

	for(int order=0; order<totalEnrollments; order++){
		//stringstream for each enrollment
		std::string enrollmentLine;
		std::getline(in, enrollmentLine, '\n');
		std::stringstream strm(enrollmentLine);

		//read matrikel nummer
		unsigned int matrikelNummer;
		strm >> matrikelNummer;
		strm.ignore(1,';');

		//read course key
		unsigned int courseKey;
		strm >> courseKey;
		strm.ignore(1,';');

		//read enrollment
		const Course* enrollCourse = &(this->getCourseByCourseKey(courseKey));
		Enrollment enrollment{"",enrollCourse};
		enrollment.read(strm);
		getStudentByMatrikelNummer(matrikelNummer).addEnrollment(enrollment);
		strm.ignore();
	}
}
