#include "project1_starter.h"
using namespace std;
/////////////     base class Person      ///////////////
	/*		Person_private
	string name;
	string address;
	unsigned long ssn;
	Date birthdate;
	*/
	// constructor:
Person::Person() {
	
}
Person::Person(const string theName, unsigned long theSSN, Date theBday, const string theAddress) {
}

// copy constructor:
Person::Person(const Person&) {
}

// copy assignment operator:
Person& Person::operator=(const Person&) {
}

// destructor:
Person::~Person() {
}

void Person::setName(const string theName) {
}
string Person::getName() const {
}
void Person::setAddress(const string theAddress) {
}
string Person::getAddress() const {
}
Date Person::getBirthDate() const {
}
unsigned long Person::getIdentification() const {
}
void Person::setIdentification(unsigned long newID) {
}

void Person::print() const {
}

///////////////// derived class Student //////////////
/*			student private
  StudentStatus status;
  Department    department;
  Course*       enrolled[ MaxCoursesForStudent ];
  int           numCourses;
*/
//constructor:
Student::Student() {
}
Student::Student(const string theName,
	unsigned long theSSN,
	const Date  theBirthDate,
	const string theAddress,
	StudentStatus theStatus,
	Department theDepartment) {
}
// copy constructor, assignment operator, destructor:
Student::Student(const Student&) {
}
Student& Student::operator=(const Student&) {
}
Student::~Student() {
}
void Student::setStatus(StudentStatus aStatus) {
}
StudentStatus Student::getStatus() const {
}
void Student::setDepartment(Department dept) {
}
Department Student::getDepartment() const {
}

bool Student::enrollForCourse(const Course& aCourse) {
}
bool Student::dropFromCourse(const Course& theCourse) {
}
void Student::listCoursesRegisteredFor() const {
}

void Student::print() const {
}