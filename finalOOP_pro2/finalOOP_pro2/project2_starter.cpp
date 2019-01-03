#include "project2_starter.h"
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
static string qualificationName[] = { "NoSchooling",
                                      "HighSchool",
	                                  "Undergraduate",
	                                  "Graduate",
	                                  "Doctorate" };
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
}
// no-arg constructor
Course::Course(const string str, long id) :courseName(str), courseId(id), ownerCounter(0) {
}
// constructor
Course::Course(const Course& other): ownerCounter(0) {
	courseName = other.courseName;
	courseId = other.courseId;
}
// copy constructor
Course& Course::operator=(const Course& other) {
	if (this != &other) {
		courseName = other.courseName;
		courseId = other.courseId;
	}
	return *this;
}
// copy assignment op  
Course::~Course() {
	removeAllOwnerStudent();
}
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
}
void Course::setCourseName(const string CourseName) {
	courseName = CourseName;
}
long Course::getCourseId() const {
	return courseId;
}
void Course::setCourseId(long CourseId) {
	courseId = CourseId;
}
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
Student::Student() :Person(), status(sUnknown), department(dUnknown), numCourses(0), qualification(HighSchool) {
}
// constructor:
Student::Student(const string theName,
	unsigned long theSSN,
	const Date  theBirthDate,
	const string theAddress,
	StudentStatus theStatus,
	Department theDepartment,
	Qualification theQualification
	)
	: Person(theName, theSSN, theBirthDate, theAddress), status(theStatus), department(theDepartment), numCourses(0), qualification(theQualification){
}


// copy constructor, assignment operator, destructor:
Student::Student(const Student& other) :Person(other), numCourses(0) {
	status = other.status;
	department = other.department;
	qualification = other.qualification;
}
Student& Student::operator=(const Student& other) {
	if (this != &other) {
		Person::operator=(other);
		status = other.status;
		department = other.department;
		qualification = other.qualification;
	}
	return *this;
}
Student::~Student() {
	dropAllCourse();
}

void Student::setStatus(StudentStatus aStatus) {
	status = aStatus;
}
StudentStatus Student::getStatus() const {
	return status;
}
void Student::setQualification(Qualification quli) {
	qualification = quli;
}
Qualification Student::getQualification()const {
	return qualification;
}
void Student::setDepartment(Department dept) {
	department = dept;
}
Department Student::getDepartment() const {
	return department;
}

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
Qualification Student::getStudentQualification() const {
	return qualification;
}

void Student::print() const {
	Person::print();
	cout << "status = " << statusLabels[status] << endl
		 << "department = " << departmentNames[department] << endl
	     << "Education = " << qualificationName[qualification] << endl;
}
//////////// derived class Teacher /////////////
Teacher::Teacher() :Person(), rank(rUnknown), department(dUnknown), salary(0), numCourses(0), numGraders(0), yearOfExperience(0), qualification(Doctorate){};
Teacher::Teacher(const string& theName, long theSSN, const Date theBirthDate,
	const string& theAddress, Rank theRank, Department theDepartment, double theSalary, double theYearOfExperience, Qualification theQualification) :
	Person(theName, theSSN, theBirthDate, theAddress), rank(theRank),
	department(theDepartment),
	salary(theSalary),
	numCourses(0),
	numGraders(0),
	yearOfExperience(theYearOfExperience),
	qualification(theQualification) {
}
Teacher::Teacher(const Teacher& other) :Person(other), numCourses(0), numGraders(0) {
	rank = other.rank;
	department = other.department;
	yearOfExperience = other.yearOfExperience;
	qualification = other.qualification;
	salary = other.salary;
}
Teacher& Teacher::operator=(const Teacher& other) {
	if (this != &other) {
		Person::operator=(other);
		rank = other.rank;
		department = other.department;
		yearOfExperience = other.yearOfExperience;
		qualification = other.qualification;
		salary = other.salary;
	}
	return *this;
}
Teacher::~Teacher() {
	dropTeachAllCourse();
}

void Teacher::setDepartment(Department dept) {
	department = dept;
}
Department Teacher::getDepartment() const {
	return department;
}

// change rank when the teacher is promoted
bool Teacher::setRank(Rank newRank) {
	rank = newRank;
	return true;
}
Rank Teacher::getRank() const {
	return rank;
}
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
void Teacher::dropTeachAllCourse() {
	for (int i = 0; i < numCourses; i++) {
			coursesOffered[i]->removeAllOwnerStudent();
	}
	numCourses=0;
}
void Teacher::listCoursesQuailfuedToTeach() const {
	cout << getName() << "'s courses quailfue list" << endl;
	for (int i = 0; i < numCourses; i++) {
		if (coursesOffered[i]->getCourseId() > 1000) {
			cout << "course : " << coursesOffered[i]->getCourseName() << "quailfued is " << qualificationName[Graduate] << endl;
		}
		else {
			cout << "course : " << coursesOffered[i]->getCourseName() << "quailfued is " << qualificationName[Undergraduate] << endl;
		}
	}
}
double Teacher::getYearOfExperience() const {
	return yearOfExperience;
}
void Teacher::setYearOfExperience(double year){
	yearOfExperience = year;
}
Qualification Teacher::getHighestDegree() const {
	return qualification;
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
void Teacher::setSalary(double sal)  {
	salary = sal;
}
double Teacher::getSalary() const {
	return salary;
}

void Teacher::print() const {
	Person::print();
	cout << "rank = " << rankNames[rank] << endl
		<< "salary = " << salary << endl
		<< "department = " << departmentNames[department] << endl
		<< "year of experience = " << yearOfExperience << endl
		<< "qualification = " << qualificationName[qualification] << endl;
}
////////// derived class GraduateStudent /////////////
GraduateStudent::GraduateStudent() : Student(), advisor(nullptr){
	setQualification(Undergraduate);
}
GraduateStudent::GraduateStudent(const string& theName,
	unsigned long theSSN,
	const Date theBirthDate,
	const string& theAddress,
	StudentStatus theStatus,
	Department theDepartment,
	Teacher& theAdvisor,
	Qualification theQualification)
	: Student(theName, theSSN, theBirthDate, theAddress, theStatus, theDepartment, theQualification),
	  advisor(&theAdvisor) {
}

GraduateStudent::GraduateStudent(const GraduateStudent& other) : Student(other) {
	advisor = other.advisor;
	setQualification(other.getQualification());
}
GraduateStudent&  GraduateStudent::operator=(const GraduateStudent& other) {
	if (this != &other) {
		Student::operator=(other);
		advisor = other.advisor;
		setQualification(other.getQualification());
	}
	return *this;
}
GraduateStudent::~GraduateStudent() {
	dropAllCourse();
}
//need to override the following method inherited from 
//Student class because a grad students cannot enroll in 
//low-level courses
bool GraduateStudent::enrollForCourse(Course& aCourse) {
	if (aCourse.getCourseId() < 1000){ // low-level courses
		cout << aCourse.getCourseName() << " is low-level course." << endl;
		return false;
	}
	else {
		return Student::enrollForCourse(aCourse);
	}
}

void GraduateStudent::changeAdvisor(Teacher& newAdvisor) {
	advisor = &newAdvisor;
}
void GraduateStudent::setDepartment(Department dept) {
	Student::setDepartment(dept);
}
Department GraduateStudent::getDepartment() const {
	return Student::getDepartment();
}

bool GraduateStudent::dropFromCourse(Course& theCourse) {
	return Student::dropFromCourse(theCourse);
}
void GraduateStudent::dropAllCourse() {
	return Student::dropAllCourse();
}
void GraduateStudent::listCoursesRegisteredFor() const {
	Student::listCoursesRegisteredFor();
}
Qualification GraduateStudent::getStudentQualification() const {
	return getQualification();
}
Teacher& GraduateStudent::getAdvisor() const {
	if (advisor == nullptr) {
		throw runtime_error("teacher is null");
	}
	return *advisor;
}

void GraduateStudent::print() const {
	Student::print();
	cout << "advisor = " << advisor->getName() << endl;
}
//////////// derived class GradTeachAsst ///////////////
GradTeachAsst::GradTeachAsst() :GraduateStudent(),
	salary(0),
	rank(GradTeachingAsst),
	yearOfExperience(0),
	numCourses(0){
	setQualification(Undergraduate);
}
GradTeachAsst::GradTeachAsst(const string& theName,
	unsigned long theSSN,
	const Date theBirthDate,
	const string& theAddress,
	StudentStatus theStatus,
	Department studentDepartment,    // (A)
	Teacher& theAdvisor,
	Department teachingDepartment,    // compare to A
	double theSalary,
	Qualification theQualification,
	double theYearOfExperience,
	Rank theRank):GraduateStudent(theName,theSSN,theBirthDate,theAddress,theStatus, studentDepartment,theAdvisor, theQualification),
	salary(theSalary),
	rank(theRank),
	yearOfExperience(theYearOfExperience),
	numCourses(0) {
}

GradTeachAsst::GradTeachAsst(const GradTeachAsst& other) :  GraduateStudent(other),
															salary(other.salary),
															rank(other.rank),
															yearOfExperience(other.yearOfExperience),
															numCourses(0) {
	setQualification(other.getQualification());
}
GradTeachAsst& GradTeachAsst::operator=(const GradTeachAsst& other) {
	if (this != &other) {
		GraduateStudent::operator=(other);
		salary = other.salary;
		rank = other.rank;
		setQualification(other.getQualification());
		yearOfExperience = other.yearOfExperience;
	}
	return *this;
}
GradTeachAsst::~GradTeachAsst() {
	dropAllCourse();
	dropTeachAllCourse();
}
Rank GradTeachAsst::getRank()const {
	return rank;
}
void GradTeachAsst::setDepartment(Department dept) {
	GraduateStudent::setDepartment(dept);
}
Department GradTeachAsst::getDepartment() const {
	return GraduateStudent::getDepartment();
}
bool GradTeachAsst::enrollForCourse(Course& aCourse) {
	return GraduateStudent::enrollForCourse(aCourse);
}
bool GradTeachAsst::dropFromCourse(Course& theCourse) {
	return GraduateStudent::dropFromCourse(theCourse);
}
void GradTeachAsst::dropAllCourse() {
	return GraduateStudent::dropAllCourse();
}
void GradTeachAsst::listCoursesRegisteredFor() const {
	GraduateStudent::listCoursesRegisteredFor();
}
Qualification GradTeachAsst::getStudentQualification()const {
	return getQualification();
}
void GradTeachAsst::listCoursesQuailfuedToTeach() const {
	cout << getName() << "'s courses quailfue list" << endl;
	for (int i = 0; i < numCourses; i++) {
		if (coursesOffered[i]->getCourseId() > 1000) {
			cout << "course : " << coursesOffered[i]->getCourseName() << "quailfued is " << qualificationName[Graduate] << endl;
		}
		else {
			cout << "course : " << coursesOffered[i]->getCourseName() << "quailfued is " << qualificationName[Undergraduate] << endl;
		}
	}
}
void GradTeachAsst::setYearOfExperience(double year) {
	yearOfExperience = year;
}
double GradTeachAsst::getYearOfExperience() const {
	return yearOfExperience;
}
Qualification GradTeachAsst::getHighestDegree() const {
	return getStudentQualification();
}
void GradTeachAsst::setSalary(double theSalary) {
	salary = theSalary;
}
double GradTeachAsst::getSalary() const {
	return salary;
}
bool GradTeachAsst::offerCourse(Course& aCourse) {
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
bool GradTeachAsst::dropCourse(Course& theCourse) {
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
void GradTeachAsst::dropTeachAllCourse() {
	for (int i = 0; i < numCourses; i++) {
		coursesOffered[i]->removeAllOwnerStudent();
	}
	numCourses = 0;
}
void GradTeachAsst::print() const {
	GraduateStudent::print();
	cout << "salary = " << getSalary() << endl
		<< "yearOfExperience = " << yearOfExperience << endl
		<< "rank = " << rankNames[rank] << endl;
}
