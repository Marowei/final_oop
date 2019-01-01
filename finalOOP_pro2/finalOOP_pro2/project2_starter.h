#include <iostream>
#include <string>
using namespace std;
//starter for project 1



//////// enumerations for symbolic data members //////////


enum StudentStatus{FullTime, PartTime, Exchange, sUnknown};


enum Department{Accounting, Business, Engineering, Mathematics,
                Physics, Arts, Chemistry, dUnknown};

enum Rank {Instructor,GradTeachingAsst,AsstProf,
           AssocProf,Professor,ResScientist,Dean,rUnknown};

class Person;
class Student;
///////////////   utility class Date   ////////////////

class Date {
public:
	int d, m, y;
	static Date today;
	Date(int dd = 0, int mm = 0, int yy = 0);
	void checkDate(int &d, int &m, int &y);
	friend ostream& operator<<( ostream&, Date );
};
/////////////     utility class Course      ///////////////

constexpr int MaxStudentForCourses = 50;
class Course{

  string courseName;
  long   courseId;
  Student* courseOwner[MaxStudentForCourses];
  int ownerCounter;

public:

	Course();                                  
	// no-arg constructor
	Course(const string, long);              
	// constructor
	Course(const Course& other);                   
	// copy constructor
	Course& operator=(const Course& other);
	// copy assignment op  
	~Course();
	// destructor
	bool addOwnerStudent(Student& student);
	bool removeOwnerStudent(Student& student);
	void removeAllOwnerStudent();

	void listStudentsRegisteredFor();
  // comparison operators:
	bool operator==(const Course& other) const;
	bool operator!=(const Course& other) const;
	
	string getCourseName() const;
	void setCourseName(const string CourseName);
	long getCourseId() const;
	void setCourseId(long CourseId);

	friend ostream& operator<<(ostream& os, Course aCourse);
};


/////////////     base class Person      ///////////////

class Person{

  string name;
  string address;
  unsigned long ssn;
  Date birthdate;
  
public:
    
	Person();
	// constructor:
	Person(const string theName, unsigned long theSSN, Date theBday, const string theAddress);
	// copy constructor:
	Person(const Person& obj);
  
	// copy assignment operator:
	Person& operator=(const Person& obj);
	bool operator==(const Person& obj) const;
	bool operator!=(const Person& obj) const;
	// destructor:
	~Person();
	void setName(const string theName);
	string getName() const;
	void setAddress(const string theAddress);
	string getAddress() const;
	Date getBirthDate() const;
	unsigned long getIdentification() const;
	void setIdentification(unsigned long newID);
	virtual void print() const;
};
constexpr int MaxCoursesForStudent = 4;


///////////////// derived class Student //////////////


class Student : virtual public Person {

  StudentStatus status;
  Department    department;
  Course*       enrolled[MaxCoursesForStudent];
  int           numCourses; 
  
public:

	Student();

  // constructor:
	Student(const string theName,
		unsigned long theSSN,
		const Date  theBirthDate,
		const string theAddress,
		StudentStatus theStatus,
		Department theDepartment);


  // copy constructor, assignment operator, destructor:
	Student(const Student& other);
	Student& operator=(const Student& other);
	 ~Student();

	 void setStatus(StudentStatus aStatus);
	 StudentStatus getStatus() const;
	 void setDepartment(Department dept);
	 Department getDepartment() const;

	 virtual bool enrollForCourse(Course& aCourse);
	 bool dropFromCourse(Course& theCourse);
	 void dropAllCourse();
	 void listCoursesRegisteredFor() const;

	 virtual void print() const;
};

constexpr int MaxCoursesForTeacher = 2;
constexpr int MaxGraders = 2;

//////////// derived class Teacher /////////////


class Teacher : virtual public Person {
  
  Rank             rank;
  double           salary;
  Department       department;
  int              numCourses;   // num of courses taught currently
  int              numGraders;
  Course*          coursesOffered[ MaxCoursesForTeacher ];
  string           graders[ MaxGraders ]; 
  
public:

	Teacher();
	Teacher(const string& theName, long theSSN, const Date theBirthDate,
		const string& theAddress, Rank theRank, Department theDepartment, double theSalary);
	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	~Teacher();

	void setDepartment(Department dept);
	Department getDepartment() const;

  // change rank when the teacher is promoted
	virtual bool setRank(Rank newRank);
	Rank getRank() const;
	void listCoursesTaught() const;
  // offer this course
	bool offerCourse(Course& aCourse);
  // cancel this course
	bool dropCourse(Course& theCourse);
	void dropAllCourse();

	bool assignGrader(const string& newGrader);
	bool dropGrader(const string& grader);
	void listGraders() const;

	double getSalary() const;
	void setSalary(double theSalary);

	virtual void print() const;
};

constexpr unsigned GradCourseLevel = 400;
constexpr unsigned MaxCoursesForGradStudent = 4;


////////// derived class GraduateStudent /////////////


class GraduateStudent : public Student {
  
  Teacher* advisor;
  unsigned short numCourses; 

public:
  
  //constructor:
	GraduateStudent();
	GraduateStudent(const string& theName,
		unsigned long theSSN,
		const Date theBirthDate,
		const string& theAddress,
		StudentStatus theStatus,
		Department theDepartment,
		Teacher& theAdvisor);
	GraduateStudent(const GraduateStudent& other);
	GraduateStudent&  operator=(const GraduateStudent& other);
	~GraduateStudent();
	//need to override the following method inherited from 
	//Student class because a grad students cannot enroll in 
	//low-level courses
	bool enrollForCourse(Course& aCourse );

	void changeAdvisor(Teacher& newAdvisor);

	Teacher& getAdvisor() const;
	virtual void print() const;
};



//////////// derived class GradTeachAsst ///////////////


class GradTeachAsst : public GraduateStudent, public Teacher {

public:

  //constructor:
  GradTeachAsst();
  GradTeachAsst(const string& theName,
                 unsigned long theSSN,
                 const Date theBirthDate,
                 const string& theAddress,
                 StudentStatus theStatus,
                 Department studentDepartment,    // (A)
                 Teacher& theAdvisor,
                 Department teachingDepartment,    // compare to A
				 Rank theRank = GradTeachingAsst);


  GradTeachAsst( const GradTeachAsst& other );
  GradTeachAsst& operator=( const GradTeachAsst& other );
  ~GradTeachAsst();

  void setStudentDepartment( Department dept );
  Department getStudentDepartment() const;
  
  void setTeachingDepartment( Department dept );
  Department getTeachingDepartment() const;
  
  // this method must be overridden because for a GradTeachAsst
  // the rank cannot be changed
  bool setRank(Rank newRank);

  // this method must be overridden because of name conflict
  // from two different bases  
  virtual void print() const;   
};
