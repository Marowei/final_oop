#include "project1_starter.h"
static const string statusLabels[] = { "full-time","part-time",
									  "exchange","unknown" };

static const string departmentNames[] = { "Accounting",
										 "Business",
										 "Engineering",
										 "Mathematics",
										 "Physics",
										 "Arts",
										 "Chemistry",
										 "Unknown" };

static string rankNames[] = { "Instructor",
							 "GradTeachingAsst",
							 "AsstProf",
							 "AssocProf",
							 "Professor",
							 "ResScientist",
							 "Dean"
							 "Unknown" };
Date::Date(int dd, int mm, int yy)
{
	checkDate(dd, mm, yy);
	dd ? d = dd : today.d;
	mm ? m = mm : today.m;
	yy ? y = yy : today.y;
}
void Date::checkDate(int &d, int &m, int &y)
{
	if (d > 31 || d < 0)
	{
		cout << "set day is error." << endl << "auto set to " << today.d << endl;
		d = today.d;
	}
	if (m > 12 || m < 0)
	{
		cout << "set month is error." << endl << "auto set to " << today.m << endl;
		m = today.m;
	}
	if (y > 2019 || y < 0)
	{
		cout << "set day is error." << endl << "auto set to " << today.y << endl;
		y = today.y;
	}
}
ostream& operator<<(ostream& os, Date dt)
{
	os << dt.m << "-" << dt.d << "-" << dt.y;
	return os;
}
Date Date::today(1, 1, 2000);

Course::Course() : courseName("null"), courseId(0), ownerCounter(0) {
};
// no-arg constructor
Course::Course(const string str, long id) :courseName(str), courseId(id), ownerCounter(0) {
};
// constructor
Course::Course(const Course& other): ownerCounter(0) {
	courseName = other.courseName;
	courseId = other.courseId;
};
// copy constructor
Course& Course::operator=(const Course& other) {
	if (this != &other) {
		courseName = other.courseName;
		courseId = other.courseId;
	}
	return *this;
};
// copy assignment op  
Course::~Course() {
	removeAllOwnerStudent();
};
// destructor
bool Course::addOwnerStudent(Student& student) {
	if (ownerCounter >= MaxStudentForCourses) {
		cout << courseName << "'s students is full." << endl;
		return false;
	}
	else {
		courseOwner[ownerCounter] = &student;
		ownerCounter++;
		return true;
	}
}
void Course::listStudentsRegisteredFor() {
	cout << courseName << "'s students number is " << ownerCounter << endl;
	for (int i = 0; i < ownerCounter; i++) {
		cout << "student : " << courseOwner[i]->getName() << endl;
	}
}
// comparison operators:
bool Course::operator==(const Course& other) const {
	return courseId == other.courseId;
}
bool Course::operator!=(const Course& other) const {
	return courseId != other.courseId;
}

string Course::getCourseName() const {
	return courseName;
};
void Course::setCourseName(const string CourseName) {
	courseName = CourseName;
};
long Course::getCourseId() const {
	return courseId;
};
void Course::setCourseId(long CourseId) {
	courseId = CourseId;
};
bool Course::removeOwnerStudent(Student& student) {
	for (int i = 0; i < ownerCounter; i++) {
		if (*courseOwner[i] == student) {  //swap i and last
			ownerCounter--;
			courseOwner[i] = courseOwner[ownerCounter];
			
			return true;
		}
	}
	return false;
}
void Course::removeAllOwnerStudent() {
	for (int i = 0; i < ownerCounter;i++) {
		courseOwner[i]->dropFromCourse(*this);
	}
	ownerCounter = 0;
}
ostream& operator<<(ostream& os, Course aCourse)
{
	os << aCourse.courseName << "  " << aCourse.courseId << endl;
	return os;
}
/////////////     base class Person      ///////////////
Person::Person() :name("Person"), address("No.43,Section 4, Keelung Rd, Da'an District, Taipei City,106"),
                  ssn(123456789), birthdate(Date::today) {
}
// constructor:
Person::Person(const string theName, unsigned long theSSN, Date theBday, const string theAddress) :name(theName), address(theAddress), ssn(theSSN), birthdate(theBday) {
}
// copy constructor:
Person::Person(const Person& obj) {
	name = obj.name;
	address = obj.address;
	ssn = obj.ssn;
	birthdate = obj.birthdate;
}

// copy assignment operator:
Person& Person::operator=(const Person& obj) {
	name = obj.name;
	address = obj.address;
	ssn = obj.ssn;
	birthdate = obj.birthdate;
	return *this;
}
bool Person::operator==(const Person& obj) const {
	return ssn == obj.ssn;
}
bool Person::operator!=(const Person& obj) const {
	return ssn != obj.ssn;
}
// destructor:
Person::~Person() {

}
void Person::setName(const string theName) {
	name = theName;
}
string Person::getName() const {
	return name;
}
void Person::setAddress(const string theAddress) {
	address = theAddress;
}
string Person::getAddress() const {
	return address;
}
Date Person::getBirthDate() const {
	return birthdate;
}
unsigned long Person::getIdentification() const {
	return ssn;
}
void Person::setIdentification(unsigned long newID) {
	ssn = newID;
}
void Person::print() const {
	cout << endl
		<< "name = " << name << endl
		<< "address = " << address << endl
		<< "Identification = " << ssn << endl
		<< "BirthDate = " << birthdate << endl;
}
///////////////// derived class Student //////////////
Student::Student() :Person(), status(sUnknown), department(dUnknown), numCourses(0){
}

// constructor:
Student::Student(const string theName,
	unsigned long theSSN,
	const Date  theBirthDate,
	const string theAddress,
	StudentStatus theStatus,
	Department theDepartment)
	: Person(theName, theSSN, theBirthDate, theAddress), status(theStatus), department(theDepartment), numCourses(0){
};


// copy constructor, assignment operator, destructor:
Student::Student(const Student& other) :Person(other), numCourses(0) {
	status = other.status;
	department = other.department;
};
Student& Student::operator=(const Student& other) {
	if (this != &other) {
		Person::operator=(other);
		status = other.status;
		department = other.department;
	}
	return *this;
};
Student::~Student() {
	dropAllCourse();
};

void Student::setStatus(StudentStatus aStatus) {
	status = aStatus;
};
StudentStatus Student::getStatus() const {
	return status;
};
void Student::setDepartment(Department dept) {
	department = dept;
};
Department Student::getDepartment() const {
	return department;
};

bool Student::enrollForCourse(Course& aCourse) {
	if (numCourses >= MaxCoursesForStudent) {
		cout << getName() << " course number is full." << endl;
		return false;
	}
	else {
		if (aCourse.addOwnerStudent(*this)) {
			enrolled[numCourses] = &aCourse;
			numCourses++;
			return true;
		}
		else {
			cout << "course : " << aCourse << "'s student is full" << endl;
			return false;
		}
	}
}
bool Student::dropFromCourse(Course& theCourse) {
	for (int i = 0; i < numCourses; i++) {
		if (*enrolled[i] == theCourse) {  //swap i and last
			enrolled[i]->removeOwnerStudent(*this);
			numCourses--;
			enrolled[i] = enrolled[numCourses];
			return true;
		}
	}
	return false;
}
void Student::dropAllCourse() {
	for (int i = 0; i < numCourses; i++) {
		enrolled[i]->removeOwnerStudent(*this);
	}
	numCourses = 0;
}
void Student::listCoursesRegisteredFor() const {
	cout << getName() << "'s Courses" << endl;
	for (int i = 0; i < numCourses;i++) {
		cout << "course : " << enrolled[i]->getCourseName() << endl;
	}
}

void Student::print() const {
	Person::print();
	cout << "status = " << statusLabels[status] << endl
		<< "department = " << departmentNames[department] << endl;
};
//////////// derived class Teacher /////////////
Teacher::Teacher() :Person(), rank(rUnknown), department(dUnknown), salary(0), numCourses(0), numGraders(0) {};
Teacher::Teacher(const string theName, long theSSN, const Date theBirthDate,
	const string theAddress, Rank theRank, Department theDepartment, double theSalary): 
	Person(theName, theSSN, theBirthDate, theAddress), rank(theRank),
	department(theDepartment),
	salary(theSalary),
	numCourses(0),
	numGraders(0){
};
Teacher::Teacher(const Teacher& other) :Person(other), numCourses(0), numGraders(0) {
	rank = other.rank;
	department = other.department;
};
Teacher& Teacher::operator=(const Teacher& other) {
	if (this != &other) {
		Person::operator=(other);
		rank = other.rank;
		department = other.department;
	}
	return *this;
};
Teacher::~Teacher() {
	dropAllCourse();
};

void Teacher::setDepartment(Department dept) {
	department = dept;
};
Department Teacher::getDepartment() const {
	return department;
};

// change rank when the teacher is promoted
void Teacher::setRank(Rank newRank) {
	rank = newRank;
};
Rank Teacher::getRank() const {
	return rank;
};
void Teacher::listCoursesTaught() const {
	cout << getName() << "'s course list:" << endl;
	for (int i = 0; i < numCourses;i++){
		cout << "course : " << coursesOffered[i]->getCourseName() << endl;
	}
}
// offer this course
bool Teacher::offerCourse(Course& aCourse) {
	if (numCourses >= MaxCoursesForTeacher) {
		cout << getName() << "'s course number is full." << endl;
		return false;
	}
	else {
		coursesOffered[numCourses] = &aCourse;
		numCourses++;
		return true;
	}
}
// cancel this course
bool Teacher::dropCourse(Course& theCourse) {
	for (int i = 0; i < numCourses; i++) {
		if (*coursesOffered[i] == theCourse) {  //swap i and last
			coursesOffered[i]->removeAllOwnerStudent();
			numCourses--;
			coursesOffered[i] = coursesOffered[numCourses];
			
			return true;
		}
	}
	return false;
}
void Teacher::dropAllCourse() {
	for (int i = 0; i < numCourses; i++) {
			coursesOffered[i]->removeAllOwnerStudent();
	}
	numCourses=0;
}
bool Teacher::assignGrader(const string& newGrader) {
	if (numGraders >= MaxGraders) {
		cout << "grader is full" << endl;
		return false;
	}
	else {
		graders[numGraders] = newGrader;
		numGraders++;
		return true;
	}
}
bool Teacher::dropGrader(const string& grader) {
	for (int i = 0; i < numGraders; i++) {
		if (graders[i] == grader) {
			numGraders--;
			graders[i] = graders[numGraders];
			return true;
		}
	}
	return false;
}
void Teacher::listGraders() const {
	cout << getName() << "'s Graders list("<< numGraders <<")" << endl;
	for (int i = 0; i < numGraders; i++) {
		cout << "graders : " << graders[i] << endl;
	}
}

double Teacher::getSalary() const {
	return salary;
};
void Teacher::setSalary(double theSalary) {
	salary = theSalary;
};

void Teacher::print() const {
	Person::print();
	cout << "rank = " << rankNames[rank] << endl
		<< "salary = " << salary << endl
		<< "department = " << departmentNames[department] << endl;
};
////////// derived class GraduateStudent /////////////
GraduateStudent::GraduateStudent() : Student(), Person(), advisor(nullptr) {
};
GraduateStudent::GraduateStudent(const string& theName,
	unsigned long theSSN,
	const Date theBirthDate,
	const string& theAddress,
	StudentStatus theStatus,
	Department theDepartment,
	Teacher& theAdvisor)
	: Student(theName, theSSN, theBirthDate, theAddress, theStatus, theDepartment),
	  Person(theName, theSSN, theBirthDate, theAddress),
	  advisor(&theAdvisor) {
};

GraduateStudent::GraduateStudent(const GraduateStudent& other) : Student(other),Person(other) {
	advisor = other.advisor;
};
GraduateStudent&  GraduateStudent::operator=(const GraduateStudent& other) {
	if (this != &other) {
		Student::operator=(other);
		advisor = other.advisor;
	}
	return *this;
};
GraduateStudent::~GraduateStudent() {
}
//need to override the following method inherited from 
//Student class because a grad students cannot enroll in 
//low-level courses
bool GraduateStudent::enrollForCourse(Course& aCourse) {
	if (aCourse.getCourseId() < 1000){// low-level courses
		cout << aCourse.getCourseName() << " is low-level course." << endl;
		return false;
	}
	else {
		return Student::enrollForCourse(aCourse);
	}
}

void GraduateStudent::changeAdvisor(Teacher& newAdvisor) {
	advisor = &newAdvisor;
};

Teacher& GraduateStudent::getAdvisor() const {
	if (advisor == nullptr) {
		throw runtime_error("teacher is null");
	}
	return *advisor;
};

void GraduateStudent::print() const {
	Student::print();
	cout << "advisor = " << advisor->getName() << endl;
};