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

//another enum type for project 2
enum Qualification { NoSchooling, HighSchool, Undergraduate, Graduate, Doctorate };

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
/////////////     base class M_QualifiedToTeach      ///////////////
class M_QualifiedToTeach
{
public:

	virtual void setDepartment(Department dept) = 0;
	virtual Department getDepartment() const = 0;

	virtual void listCoursesQuailfuedToTeach() const = 0;
	virtual double getYearOfExperience() const = 0;

	virtual Qualification getHighestDegree() const = 0;
	virtual double getSalary() const = 0;
	// offer this course
	virtual bool offerCourse(Course& aCourse) = 0;
	// cancel this course
	virtual bool dropCourse(Course& theCourse) = 0;
	virtual void dropTeachAllCourse() = 0;
};

/////////////     base class M_CanBecomestudent      ///////////////
class M_CanBecomestudent
{
public:
	virtual void setDepartment(Department dept) = 0;
	virtual Department getDepartment() const = 0;

	virtual bool enrollForCourse(Course& aCourse) = 0;
	virtual bool dropFromCourse(Course& theCourse) = 0;
	virtual void listCoursesRegisteredFor() const = 0;
	virtual void dropAllCourse() = 0;
	virtual Qualification getStudentQualification() const = 0;
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


class Student : public Person,public M_CanBecomestudent{

  StudentStatus status;
  Department    department;
  Course*       enrolled[MaxCoursesForStudent];
  int           numCourses;
  Qualification qualification;
  
public:

	Student();

  // constructor:
	Student(const string theName,
		unsigned long theSSN,
		const Date  theBirthDate,
		const string theAddress,
		StudentStatus theStatus,
		Department theDepartment,
		Qualification theQualification = HighSchool);


  // copy constructor, assignment operator, destructor:
	Student(const Student& other);
	Student& operator=(const Student& other);
	 ~Student();

	 void setStatus(StudentStatus aStatus);
	 StudentStatus getStatus() const;
	 void setQualification(Qualification quli);
	 Qualification getQualification()const;
	 virtual void setDepartment(Department dept);
	 virtual Department getDepartment() const;
	 virtual bool enrollForCourse(Course& aCourse);
	 virtual bool dropFromCourse(Course& theCourse);
	 virtual void dropAllCourse();
	 virtual void listCoursesRegisteredFor() const;
	 virtual Qualification getStudentQualification()const;
	 virtual void print() const;
};

constexpr int MaxCoursesForTeacher = 2;
constexpr int MaxGraders = 2;

//////////// derived class Teacher /////////////


class Teacher : public Person , public M_QualifiedToTeach{
  
  Rank             rank;
  double           salary;
  Department       department;
  int              numCourses;   // num of courses taught currently
  int              numGraders;
  Course*          coursesOffered[ MaxCoursesForTeacher ];
  string           graders[ MaxGraders ]; 
  double           yearOfExperience;
  Qualification    qualification;
public:

	Teacher();
	Teacher(const string& theName, long theSSN, const Date theBirthDate,
		const string& theAddress, Rank theRank, Department theDepartment, double theSalary, double theYearOfExperience, Qualification theQualification = Doctorate);
	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);
	~Teacher();

	virtual void setDepartment(Department dept);
	virtual Department getDepartment() const;

  // change rank when the teacher is promoted
	bool setRank(Rank newRank);
	Rank getRank() const;
	void listCoursesTaught() const;
  // offer this course
	virtual bool offerCourse(Course& aCourse);
  // cancel this course
	virtual bool dropCourse(Course& theCourse);
	virtual void dropTeachAllCourse();

	virtual void listCoursesQuailfuedToTeach() const;
	virtual void setYearOfExperience(double year);
	virtual double getYearOfExperience() const;

	virtual Qualification getHighestDegree() const;
	virtual void setSalary(double sal);
	virtual double getSalary() const;

	bool assignGrader(const string& newGrader);
	bool dropGrader(const string& grader);
	void listGraders() const;
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
		Teacher& theAdvisor,
		Qualification theQualification = Undergraduate);
	GraduateStudent(const GraduateStudent& other);
	GraduateStudent&  operator=(const GraduateStudent& other);
	~GraduateStudent();
	//need to override the following method inherited from 
	//Student class because a grad students cannot enroll in 
	//low-level courses
	void changeAdvisor(Teacher& newAdvisor);
	virtual void setDepartment(Department dept);
	virtual Department getDepartment() const;
	virtual bool enrollForCourse(Course& aCourse);
	virtual bool dropFromCourse(Course& theCourse);
	virtual void dropAllCourse();
	virtual void listCoursesRegisteredFor() const;
	virtual Qualification getStudentQualification()const;
	virtual void print() const;
	Teacher& getAdvisor() const;
};



//////////// derived class GradTeachAsst ///////////////


class GradTeachAsst : public GraduateStudent, public M_QualifiedToTeach {
	double        salary;
	double        yearOfExperience;
	Rank          rank;
	Course*       coursesOffered[MaxCoursesForTeacher];
	int           numCourses;
public:

  //constructor:
  GradTeachAsst();
  GradTeachAsst(const string& theName,
                 unsigned long theSSN,
                 const Date theBirthDate,
                 const string& theAddress,
                 StudentStatus theStatus,
                 Department studentDepartment,
                 Teacher& theAdvisor,
                 Department teachingDepartment, 
	             double theSalary,
	             Qualification theQualification = Undergraduate,
	             double theYearOfExperience = 0,
	             Rank theRank = GradTeachingAsst);


  GradTeachAsst( const GradTeachAsst& other );
  GradTeachAsst& operator=( const GradTeachAsst& other );
  ~GradTeachAsst();

  Rank getRank()const;
  virtual void setDepartment(Department dept);
  virtual Department getDepartment() const;
  virtual bool enrollForCourse(Course& aCourse);
  virtual bool dropFromCourse(Course& theCourse);
  virtual void dropAllCourse();
  virtual void listCoursesRegisteredFor() const;
  virtual Qualification getStudentQualification()const;
  virtual void listCoursesQuailfuedToTeach() const;
  virtual void setYearOfExperience(double);
  virtual double getYearOfExperience() const;
  virtual Qualification getHighestDegree() const;
  virtual void setSalary(double theSalary);
  virtual double getSalary() const;
  virtual bool offerCourse(Course& aCourse);
  virtual bool dropCourse(Course& theCourse);
  virtual void dropTeachAllCourse();
  virtual void print() const;
};
