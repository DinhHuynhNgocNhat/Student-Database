/*
 * SimpleUI.cpp
 *
 *  Created on: Jan 11, 2025
 *      Author: ngocn
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include "SimpleUI.h"
#include "WeeklyCourse.h"
#include "BlockCourse.h"
#include <map>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"

#include "Poco/Net/DNS.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"

using namespace std;

SimpleUI::SimpleUI(StudentDb& studentDb) : studentDb(studentDb)
{

}

Poco::DateTime::DaysOfWeek getDayFromInt(const int day)
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

string getDayToString(const Poco::DateTime::DaysOfWeek& DayOfWeek)
{
	switch (DayOfWeek){
	case Poco::DateTime::DaysOfWeek::SUNDAY:
		return "Sunday";
	case Poco::DateTime::DaysOfWeek::MONDAY:
		return "Monday";
	case Poco::DateTime::DaysOfWeek::TUESDAY:
		return "Tuesday";
	case Poco::DateTime::DaysOfWeek::WEDNESDAY:
		return "Wednesday";
	case Poco::DateTime::DaysOfWeek::THURSDAY:
		return "Thursday";
	case Poco::DateTime::DaysOfWeek::FRIDAY:
		return "Friday";
	case Poco::DateTime::DaysOfWeek::SATURDAY:
		return "Saturday";
	default:
		return "Invalid day";
	}
}

void SimpleUI::addNewCourse()
{
	cout << "----------------------------------------" << endl;
	cout<<endl;
	cout<<"--Add new course--"<<endl;

	//Enter course key
	cout<<"Enter the course key: ";
	unsigned int courseKey;
	cin>>courseKey;

	//Enter title
	cout<<"Enter the title of the course: ";
	string title;
	cin.ignore();

	//manipulator to ignore initial whitespace characters before reading data.
	getline(cin>>ws,title);

	//enter major
	cout<<"Enter the major of the course: ";
	string major;
	cin>>major;

	//Enter credit points
	cout<<"Enter the number of credit points: ";
	float creditPoints;
	cin >> creditPoints;

	//Enter type of course
	cout<<"Enter the type of the course (0. Weekly Course or 1. Block Course):";
	int typeOfCourse;
	cin>> typeOfCourse;

	//Weekly course
	if (typeOfCourse == 0){
		cout<<"Enter the course day per week: "<<endl;
		cout<<"0. Sunday"<<endl;
		cout<<"1. Monday"<<endl;
		cout<<"2. Tuesday"<<endl;
		cout<<"3. Wednesday"<<endl;
		cout<<"4. Thursday"<<endl;
		cout<<"5. Friday"<<endl;
		cout<<"6. Saturday"<<endl;
		int dayPerWeek;
		cin >> dayPerWeek;
		Poco::DateTime::DaysOfWeek dayOfWeek = getDayFromInt(dayPerWeek);

		//Enter start time
		cout<<"Enter the staring time of the class in 24h format (hh:mm:ss): ";
		int hour, minute, second;
		char iconColon;
		cin >> hour >> iconColon >> minute >> iconColon >> second;
		Poco::Data::Time startTime(hour,minute,second);

		//Enter end time
		cout<<"Enter the ending time of the class in 24h format (hh:mm:ss): ";
		cin >> hour >> iconColon >> minute >> iconColon >> second;
		Poco::Data::Time endTime(hour,minute,second);

		//Add Weekly course
		std::unique_ptr<Course> weeklyCourse (new WeeklyCourse(courseKey,title,
			major, creditPoints, dayOfWeek, startTime, endTime));

		studentDb.addCourse(weeklyCourse);
		cout<<"New weekly course is added successfully. "<<endl;
	}

	//Block course
	else if (typeOfCourse == 1){
		//Enter start time
		cout<<"Enter the beginning date of the course (dd/mm/yyyy): ";
		int day,month,year;
		char iconSlash;
		cin >> day >> iconSlash >> month >> iconSlash >> year;
		Poco::Data::Date startDate(year,month,day);

		//Enter end time
		cout<<"Enter the ending date of the course (dd/mm/yyyy): ";
		cin >> day >> iconSlash >> month >> iconSlash >> year;
		Poco::Data::Date endDate(year,month,day);

		//Enter start time
		cout<<"Enter the beginning time in 24h format (hh:mm:ss): ";
		int hour,minute,second;
		char iconColon;
		cin >> hour >> iconColon >> minute >> iconColon >> second;
		Poco::Data::Time startTime(hour,minute,second);

		//Enter end time
		cout<<"Enter the ending time in 24h format (hh:mm:ss): ";
		cin >> hour >> iconColon >> minute >> iconColon >> second;
		Poco::Data::Time endTime(hour,minute,second);

		//Add Block course
		std::unique_ptr<Course> blockCourse(new BlockCourse(courseKey,title,
	    		major, creditPoints, startDate, endDate, startTime, endTime));

		this->studentDb.addCourse(blockCourse);
		cout<<"The new block course is added successfully."<<endl;
	}
	cout << "----------------------------------------" << endl;
}

void SimpleUI::listCourses() const
{
	cout << "----------------------------------------" << endl;
	cout<<endl;
	cout<<"--List courses--"<<endl;
	const map<int,unique_ptr<const Course>>& courses = studentDb.getCourse();
	//If no course in list
	if (courses.empty()){
		cout<<"The list is empty. Please add new course!!!"<<endl;
		return;
	}

	//print all course
	for (const auto& course : courses)
	{
	    const Course* pCourse = course.second.get();
	    listSpecificCourses(pCourse);
	}
	cout << "----------------------------------------" << endl;
}

void SimpleUI::listSpecificCourses(const Course* course) const
{
	cout<<"    --------------    "<<endl;
	cout << "Course key: " << course->getCourseKey() <<endl;
	cout << "Course title: " << course->getTitle() << endl;
	cout << "Major: " << course->getMajor() <<endl;
	cout << "Number of credit points: "
			<< course->getCreditPoints() <<endl;

	if (auto weeklyCourse=dynamic_cast<const WeeklyCourse*>(course)){
		cout<<"Type of course: Weekly Course, ";
		const Poco::Data::Time& startTime = weeklyCourse->getStartTime();
		const Poco::Data::Time& endTime = weeklyCourse->getEndTime();

		cout<<"on "<<getDayToString(weeklyCourse->getDayOfWeek())<<" per week"<<
			", from "<<startTime.hour()<<":"<<(startTime.minute()<10 ? "0" : "")
			<<startTime.minute()<<" to "<<endTime.hour()<<":"<<
			(endTime.minute()<10 ? "0" : "")<<endTime.minute()<<endl;
	}

	if(auto blockCourse=dynamic_cast<const BlockCourse*>(course)){
		cout<<"Type of course: Block Course, ";
		const Poco::Data::Date& startDate = blockCourse->getStartDate();
		const Poco::Data::Date& endDate = blockCourse->getEndDate();
		const Poco::Data::Time& startTime = blockCourse->getStartTime();
		const Poco::Data::Time& endTime = blockCourse->getEndTime();

		cout<<" starts on "<<startDate.day()<<"/"<<startDate.month()<<"/"<<
			startDate.year()<<" ends on "<<endDate.day()<<"/"<<endDate.month()<<
			"/"<<endDate.year()<<". Time: "<<startTime.hour()<<":"<<
			(startTime.minute()< 10 ? "0" : "")<<startTime.minute()<<" - "<<
			endTime.hour()<<":"<<(endTime.minute()< 10 ? "0" : "")<<
			endTime.minute()<<endl;
	}
}

void SimpleUI::addStudent()
{
	cout << "----------------------------------------" << endl;
	cout<<endl;
	cout<<"--Add student--"<<endl;

	cout<<"Enter first name: ";
	string firstName;
	getline(cin>>ws, firstName);

	cout<<"Enter last name: ";
	string lastName;
	getline(cin>>ws, lastName);

	cout<<"Enter date of birth (dd/mm/yyyy): ";
	int day,month,year;
	char iconSlash;
	cin >> day >> iconSlash >> month >> iconSlash >> year;
	Poco::Data::Date birthDay(year,month,day);

	cout<<"Enter the student address:"<<endl;
	cout<<"Street: ";
	string street;
	getline(cin>>ws, street);

	cout<<"Postal code:";
	unsigned short postalCode;
	cin >> postalCode;

	cout<<"City: ";
	string city;
	getline(cin>>ws, city);

	cout << "Additional Information (enter 0 if no additional information): ";
	string additionalInfo;
	getline(cin >> ws, additionalInfo);

	if (additionalInfo=="0") {
	    additionalInfo = "";
	}

	Address address(street,postalCode,city,additionalInfo);
	Student student(firstName,lastName,birthDay,address);

	studentDb.addNewStudent(student);
	cout<<"New student is added successfully."<<endl;
	cout << "----------------------------------------" << endl;
}

void SimpleUI::addEnrollment()
{
	cout << "----------------------------------------" << endl;
	cout<<endl;
	cout<<"--Add enrollment--"<<endl;
	unsigned int matrikelNummer;
	unsigned int courseKey;
	while(true){
		cout<<"Enter student matrikel nummer: ";
		cin >> matrikelNummer;

		if(studentDb.validStudent(matrikelNummer)){
			break;
		}
		cout<<"Not found student!!!"<<endl;
	}

	while(true){
		cout<<"Enter the course key: ";
		cin >> courseKey;

		if(studentDb.getCourse().find(courseKey) !=studentDb.getCourse().end()){
			break;
		}
		cout<<"Invalid course key!!!"<<endl;
	}

	cout<<"Enter the semester: ";
	string semester;
	cin >> semester;

	if (studentDb.addEnrollment(matrikelNummer,courseKey,semester)){
		cout<<"Add enrollment successfully."<<endl;
		return;
	}
	else{
		cout<<"Student has already enrolled this course!!!"<<endl;
		return;
	}
	cout << "----------------------------------------" << endl;
}

void SimpleUI::printStudent()
{
	cout << "----------------------------------------" << endl;
	cout<<"--Print student--"<<endl;
	const map<int,Student>& students = studentDb.getStudent();
	//If no student in list
	if (students.empty()){
		cout<<"The list is empty. Please add student"<<endl;
		return;
	}

	//print all students
	for (const auto& student : students)
	{
		cout<<"  ------------------------  "<<endl;
	    cout<<"Matrikel Nummer: "<<student.first<<endl;
	    cout<<"Full name: "<<student.second.getFirstName()<<" "<<
	    		 student.second.getLastName()<<endl;
	    cout<<"Date of Birth: "<<student.second.getDateOfBirth().day()<<"/"<<
	    	student.second.getDateOfBirth().month()<<"/"<<
			student.second.getDateOfBirth().year()<<endl;
	    cout<<"Address: "<<student.second.getAddress().getStreet()<<", "<<
	    	student.second.getAddress().getPostalCode()<<", "<<
			student.second.getAddress().getCityName()<<";"<<
			student.second.getAddress().getAdditionalInfo()<<endl<<endl;

	    cout<<"Student enroll courses: "<<endl;
	    vector<Enrollment> enrollments = student.second.getEnrollment();

	    if(enrollments.empty()){
	    	cout<<"This student have not enrolled any course."<<endl;
	    }
	    else{
	    	for(Enrollment enrollment : enrollments){
	    		const Course* enrollCourse = enrollment.getCourse();
	    		listSpecificCourses(enrollCourse);
	    		cout<<"On "<<enrollment.getSemester()<<" semester"<<endl;
	    		cout<<"Grade: "<<enrollment.getGrade()<<endl;
	    	}
	    }
	}
	cout << "----------------------------------------" << endl;
}

void SimpleUI::searchStudent()
{
	cout << "----------------------------------------" << endl;
	cout<<"--Search student--"<<endl;
	cout<<"Enter the name of student: ";
	string name;
	getline(cin>>ws, name);

	const vector<Student> students = studentDb.getStudentByName(name);

	if(students.empty()){
		cout<<"Not found!!!"<<endl;
	}
	else{
		cout<<"Result:"<<endl;
		for(const Student& student : students){
			cout<<". Matrikel nummer: "<<student.getMatrikelNumber()<<" - "
				" Full name: "<<student.getFirstName()<<" "<<
				student.getLastName()<<endl;
		}
	}
	cout << "----------------------------------------" << endl;
}

void SimpleUI::updateStudent()
{
	cout << "----------------------------------------" << endl;
	cout<<"--Update student data--"<<endl;
	cout<<"Enter matrikel nummmer of student: ";
	unsigned int matrikelNummer;
	cin >> matrikelNummer;

	Student& student = studentDb.getStudentByMatrikelNummer(matrikelNummer);

	cout<<"Student data: "<<endl;
	cout<<" . Matrikel nummer: "<<student.getMatrikelNumber()<<endl;
	cout<<" . Full name: "<<student.getFirstName()<<" "<<student.getLastName()
			<<endl;
	cout<<" . Date of birth: "<<student.getDateOfBirth().day()<<"/"<<
		student.getDateOfBirth().month()<<"/"<<student.getDateOfBirth().year()
		<<endl;
	cout<<" . Address: "<<student.getAddress().getStreet()<<", "<<
			student.getAddress().getPostalCode()<<" "<<
			student.getAddress().getCityName()<<"; "<<
			student.getAddress().getAdditionalInfo()<<endl<<endl;

    cout<<"Student enroll courses: "<<endl;
    vector<Enrollment> enrollments = student.getEnrollment();
    if(enrollments.empty()){
    	cout<<"This student have not enrolled any course."<<endl;
    }
    else{
    	for(Enrollment& enrollment : enrollments){
    		const Course* enrollCourse = enrollment.getCourse();
    		listSpecificCourses(enrollCourse);
    		cout<<"On "<<enrollment.getSemester()<<" semester"<<endl;
    		cout<<"Grade: "<<enrollment.getGrade()<<endl;
    	}
    }

	while(true){
		cout<<"Choose the data to edit: "<<endl;
		cout<<"0. Exit"<<endl;
		cout<<"1. First name"<<endl;
		cout<<"2. Last name"<<endl;
		cout<<"3. Date of birth"<<endl;
		cout<<"4. Address"<<endl;
		cout<<"5. Enrollment"<<endl;

		int choice;
		cin >> choice;

		switch (choice){
		case 1:{
			cout<<"Enter the new first name: ";
			string firstName;
			getline(cin>>ws, firstName);
			student.setFirstName(firstName);
			cout<<"Change first name successfully."<<endl;
			break;
		}
		case 2:{
			cout<<"Enter the new last name: ";
			string lastName;
			getline(cin>>ws, lastName);
			student.setLastName(lastName);
			cout<<"Change last name successfully."<<endl;
			break;
		}
		case 3:{
			cout<<"Enter the new birthday (dd/mm/yyyy): ";
			int day,month,year;
			char iconSlash;
			cin >> day >> iconSlash >> month >> iconSlash >> year;
			Poco::Data::Date birthDay(year,month,day);
			student.setDateOfBirth(birthDay);
			cout<<"Change date of birth successfully."<<endl;
			break;
		}
		case 4:{
			cout<<"Enter new student address:"<<endl;
			cout<<"Street: ";
			string street;
			getline(cin>>ws, street);

			cout<<"Postal code: ";
			unsigned short postalCode;
			cin>>postalCode;

			cout<<"City: ";
			string cityName;
			getline(cin>>ws, cityName);

			cout<<"Additional information (enter '0' if no additional"
					" information): ";
			string additionalInfo;
			getline(cin>>ws, additionalInfo);
			if (additionalInfo=="0") {
			    additionalInfo = "";
			}

			Address address(street,postalCode,cityName,additionalInfo);
			student.setAddress(address);
			cout<<"Change new address successfully."<<endl;
			break;
		}
		case 5:{
			cout<<"Edit enrollment:"<<endl;
			cout<<"0. Enter a mark for the enrollment"<<endl;
			cout<<"1, Remove the enrollment"<<endl;
			int select;
			cin>>select;

			if (select == 0 ){
				cout<<"Enter the course key: ";
				unsigned int courseKey;
				cin>>courseKey;

				cout<<"Enter the grade of this course: ";
				float grade;
				cin >> grade;

				if(student.setGrade(courseKey,grade)==false){
					cout<<"Invalid course key. Please try again."<<endl;
					break;
				}
				else{
					cout<<"Set a mark successfully."<<endl;
					break;
				}
			}
			else if(select == 1){
				if(student.getEnrollment().empty()){
			    	cout<<"This student have not enrolled any course."<<endl;
			    }
			    else{
			    	for(const Enrollment& enrollment : student.getEnrollment()){
			    		const Course* enrollCourse = enrollment.getCourse();
			    		listSpecificCourses(enrollCourse);
			    		cout<<"On "<<enrollment.getSemester()<<" semester"<<
			    														endl;
			    		cout<<"Grade: "<<enrollment.getGrade()<<endl;
			    	}
			    	cout<<"Enter the course key of the removing course: "<<endl;
					unsigned int courseKey;
					cin>>courseKey;

					if (student.removeEnrollment(courseKey)==false){
						cout<<"Invalid course key: Please try again."<<endl;
						break;
					}
					cout<<"Remove the enrollment successfully."<<endl;
			    }
			}
			else{
				cout<<"Invalid!!!"<<endl;
			}
			break;
		}
		case 0: std::cout<<"Quit Command"<<std::endl; return;
		default:
			cout<<"Invalid choice. Please enter again"<<endl; break;
		}
	}
    cout << "----------------------------------------" << endl;
}

void SimpleUI::writeData()
{
	cout << "----------------------------------------" << endl;
	cout<<"Write the database to an external file"<<endl;
	cout<<"Enter the file name: ";
	string fileName;
	cin >> fileName;

	//opens a file in write mode. If the file does not exist, it is created.
	//If the file already exists, its contents may be overwritten
	ofstream file; //Output File Stream
	file.open(fileName);

	studentDb.write(file);
	file.close();
	cout<<"Write to an external file completely."<<endl;
	cout << "----------------------------------------" << endl;
}

void SimpleUI::readData()
{
	cout << "----------------------------------------" << endl;
	cout<<"Read the database from an external file"<<endl;
	cout<<"Enter the file name: ";
	string fileName;
	cin >> fileName;

	//Open the file in read mode. If the file does not exist or cannot be opened
	ifstream file; //Input File Stream
	file.open(fileName);

	studentDb.read(file);
	file.close();
	cout<<"Read an external file completely."<<endl;
	cout << "----------------------------------------" << endl;
}

void SimpleUI::getStudentFromServer() const
{
	cout << "----------------------------------------" << endl;
	cout<<"--Get Student data from server--"<<endl;
	int numberInput;
	cout<<"Enter the number of generating student from server: ";
	cin >> numberInput;
	if(numberInput <=0){
		cout<<"Invalid input!!!"<<endl;
		return;
	}

	try{
        //Poco::Net::SocketAddress address(address,port);
        Poco::Net::SocketAddress address("www.hhs.users.h-da.cloud",4242);

        // Connect to the server
        Poco::Net::StreamSocket socket;
        socket.connect(address, 5000); // 5s timeout

        // Create a buffered stream and send message to server
        Poco::Net::SocketStream stream(socket);
        string response;
        stream << "generate" << endl;
        stream.flush();

        // Read the first line response from the stream
        getline(stream, response);

        while(true){
        	if(response.find("100 Generating") != string::npos){
        		//get next line - json format
        		getline(stream,response);
        	}
        	//"cell" response has student data
        	if(response.find("cell") != string::npos){
        		Poco::JSON::Parser parser;
        		Poco::Dynamic::Var result = parser.parse(response);

        		if(!result.isEmpty()){
        			Poco::JSON::Object::Ptr obj =
        					result.extract<Poco::JSON::Object::Ptr>();
        			Poco::DynamicStruct dynamicStruct = *obj;

        			//get name
        			string firstName = dynamicStruct["name"]["firstName"];
        			string lastName = dynamicStruct["name"]["lastName"];

        			//get address
        			string street = dynamicStruct["location"]["street"];
        			string cityName = dynamicStruct["location"]["city"];
        			string additionalInfo = dynamicStruct["location"]["state"];
        			unsigned short postalCode =
        						dynamicStruct["location"]["postCode"];
        			Address studentAddress(street,postalCode,
        									cityName,additionalInfo);

        			//get date of birth
        			int year = dynamicStruct["dateOfBirth"]["year"] + 1900;

        			//month cannot equal 0
        			int month = dynamicStruct["dateOfBirth"]["month"] + 1;
        			int day = dynamicStruct["dateOfBirth"]["day"];
        			Poco::Data::Date dateOfBirth(year,month,day);

        			Student newStudentFromServer(firstName,lastName,
        										dateOfBirth,studentAddress);
        			studentDb.addNewStudent(newStudentFromServer);
        		}
        		numberInput--;

        		//get the next line
        		getline(stream,response);
        		if (response.find("200 Data generated.") != string::npos){
        			//if add fully number of students
        			if(numberInput == 0){
        				cout << "Added new students successfully. Quit command."
        						<<endl;

        				//Send quit
        				stream << "quit" <<endl;
        				stream.flush();

        				//receive response
        				getline(stream,response);
        				cout << response << endl << endl;
        				return;
        			}

        			//not enough number of input- repeat send generate to server
        			else {
        				stream << "generate" << endl;
        				stream.flush();

        				getline(stream,response);
        			}
        		}
        	}
        }
	}
	catch(Poco::Exception& ex){
		cerr  << "Poco Exception: " << ex.displayText() << endl;
		return;
	}
}

void SimpleUI::run()
{
	while(true){
		std::cout<<"---Student Database Management---"<<std::endl;
		std::cout<<"0. Exit"<<std::endl;
		std::cout<<"1. Add new Course"<<std::endl;
		std::cout<<"2. List courses"<<std::endl;
		std::cout<<"3. Add new student"<<std::endl;
		std::cout<<"4. Add enrollment"<<std::endl;
		std::cout<<"5. Print student"<<std::endl;
		std::cout<<"6. Search student"<<std::endl;
		std::cout<<"7. Update student"<<std::endl;
		std::cout<<"8. Write the database to an external file"<<std::endl;
		std::cout<<"9. Read the database from an external file"<<std::endl;
		std::cout<<"10. Get students from server"<<std::endl;
		std::cout<<"Enter your choice: ";

		int choice;
		std::cin>>choice;

		switch (choice){
			case 1: addNewCourse(); break;
			case 2: listCourses(); break;
			case 3: addStudent(); break;
			case 4: addEnrollment(); break;
			case 5: printStudent(); break;
			case 6: searchStudent(); break;
			case 7: updateStudent(); break;
			case 8: writeData(); break;
			case 9: readData(); break;
			case 10: getStudentFromServer(); break;
			case 0: std::cout<<"Quit Command"<<std::endl; return;
			default: std::cout<<"Invalid choice!!!"<<std::endl; break;
		}
	}
}
