#include <iostream>
#include <string>
using namespace std;
//starter for project 1



//////// enumerations for symbolic data members //////////


enum StudentStatus{FullTime, PartTime, Exchange, sUnknown};

static const string statusLabels[] = {"full-time","part-time",
                                      "exchange","unknown"};


enum Department{Accounting, Business, Engineering, Mathematics,
                Physics, Arts, Chemistry, dUnknown};

static const string departmentNames[] = {"Accounting",
                                         "Business",
                                         "Engineering",
                                         "Mathematics",
                                         "Physics",
                                         "Arts",
                                         "Chemistry",
                                         "Unknown"};

enum Rank {Instructor,GradTeachingAsst,AsstProf,
           AssocProf,Professor,ResScientist,Dean,rUnknown};


static string rankNames[] = {"Instructor",
                             "GradTeachingAsst",
                             "AsstProf",
                             "AssocProf",
                             "Professor",
                             "ResScientist",
                             "Dean"
                             "Unknown"};





///////////////   utility class Date   ////////////////


class Date {
public:
  int d, m, y;
  static Date today;
  Date( int dd=0, int mm=0, int yy=0 )
  {
	checkDate(dd,mm,yy);
    dd ? d = dd : today.d;
    mm ? m = mm : today.m;
    yy ? y = yy : today.y;
  }
  void checkDate(int &d, int &m, int &y)
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
  friend ostream& operator<<( ostream&, Date );
};

ostream& operator<<( ostream& os, Date dt )
{
  os << dt.m << "-" << dt.d << "-" << dt.y << endl;
  return os;
}


Date Date::today( 1, 1, 2000 );



/////////////     utility class Course      ///////////////


class Course{

  string courseName;
  long   courseId;

public:

	Course(): courseName("null"), courseId(0){
	};                                  
	// no-arg constructor
	Course(const string, long):courseName(courseName), courseId(courseId){
	};              
	// constructor
	Course(const Course& other) {
		courseName = other.courseName;
		courseId = other.courseId;
	};                   
	// copy constructor
	Course& operator=(const Course& other) {
		if (this!=&other) {
			courseName = other.courseName;
			courseId = other.courseId;
		}
		return *this;
	};  
	// copy assignment op  
	~Course() {
	};                                 
	// destructor

  // comparison operators:
  bool operator==( const Course& );
  bool operator!=( const Course& );

  string getCourseName() const {
	  return courseName;
  };
  void setCourseName(const string CourseName) {
	  courseName = CourseName;
  };
  long getCourseId() const {
	  return courseId;
  };
  void setCourseId(long CourseId) {
	  courseId = CourseId;
  };

  friend ostream& operator<<( ostream& os, Course aCourse )
  {
    os << aCourse.courseName << "  "  << aCourse.courseId << endl;
    return os;
  }
};


/////////////     base class Person      ///////////////

class Person{

  string name;
  string address;
  unsigned long ssn;
  Date birthdate;
  
public:
    
  Person():name("Person"), address("No.43,Section 4, Keelung Rd, Da'an District, Taipei City,106"), ssn(123456789), birthdate(Date::today) 
  {
  }
  // constructor:
  Person(const string theName, unsigned long theSSN, Date theBday, const string theAddress):name(theName), address(theAddress), ssn(theSSN), birthdate(theBday) {
  }
  // copy constructor:
  Person(const Person& obj) {
	  name = obj.name;
	  address = obj.address;
	  ssn = obj.ssn;
	  birthdate = obj.birthdate;
  }
  
  // copy assignment operator:
  Person& operator=(const Person& obj) {
	  name = obj.name;
	  address = obj.address;
	  ssn = obj.ssn;
	  birthdate = obj.birthdate;
	  return *this;
  }
  // destructor:
  ~Person() {
  
  }
  void setName(const string theName) {
	  name = theName;
  }
  string getName() const {
	  return name;
  }
  void setAddress(const string theAddress) {
	  address = theAddress;
  }
  string getAddress() const {
	  return address;
  }
  Date getBirthDate() const {
	  return birthdate;
  }
  unsigned long getIdentification() const {
	  return ssn;
  }
  void setIdentification(unsigned long newID) {
	  ssn = newID;
  }
  virtual void print() const {
	  cout << "name = " << name << endl
		  << "address = " << address << endl
		  << "Identification = " << ssn << endl
		  << "BirthDate = " << birthdate << endl;
  }
};


const int MaxCoursesForStudent = 4;


///////////////// derived class Student //////////////


class Student : virtual public Person {

  StudentStatus status;
  Department    department;
  Course*       enrolled[ MaxCoursesForStudent ];
  int           numCourses; 
  
public:

	Student() :Person(), status(sUnknown), department(dUnknown) {
	}

  // constructor:
	Student(const string theName,
		unsigned long theSSN,
		const Date  theBirthDate,
		const string theAddress,
		StudentStatus theStatus,
		Department theDepartment)
		: Person(theName, theSSN, theBirthDate, theAddress), status(theStatus), department(theDepartment) {
	};


  // copy constructor, assignment operator, destructor:
	 Student(const Student& other):Person(other) {
		status = other.status;
		department = other.department;
	};
	 Student& operator=(const Student& other){
		 if (this!=&other) {
			 Person::operator=(other);
			 status = other.status;
			 department = other.department;
		 }
		 return *this;
	 };
	 ~Student() {};

	 void setStatus(StudentStatus aStatus) {
		 status = aStatus;
	 };
	 StudentStatus getStatus() const {
		 return status;
	 };
	 void setDepartment(Department dept) {
		 department = dept;
	 };
	 Department getDepartment() const {
		 return department;
	 };

  bool enrollForCourse(const Course& aCourse);
  bool dropFromCourse(const Course& theCourse);
  void listCoursesRegisteredFor() const;

  void print() const {
	  Person::print();
	  cout << "status = " << status << endl
		  << "department = " << department << endl;
  };
};




const int MaxCoursesForTeacher = 2;
const int MaxGraders = 2;

//////////// derived class Teacher /////////////


class Teacher : virtual public Person {
  
  Rank             rank;
  double           salary;
  Department       department;
  int              numCourses;   // num of courses taught currently
  int              numGraders;
  Course*          coursesOffered[ MaxCoursesForTeacher ];
  string*          graders[ MaxGraders ]; 
  
public:

	Teacher() :Person(), rank(rUnknown), department(dUnknown) {};
	Teacher(const string theName, long theSSN, const Date theBirthDate,
		const string theAddress, Rank theRank, Department theDepartment)
		: Person(theName, theSSN, theBirthDate, theAddress), rank(theRank), department(theDepartment) {
	};
	Teacher(const Teacher& other):Person(other) {
		rank = other.rank;
		department = other.department;
	};
	Teacher& operator=(const Teacher& other) {
		if (this != &other) {
			Person::operator=(other);
			rank = other.rank;
			department = other.department;
		}
		return *this;
	};
	~Teacher() {};

	void setDepartment(Department dept) {
		department = dept;
	};
	Department getDepartment() const {
		return department;
	};

  // change rank when the teacher is promoted
	void setRank(Rank newRank) {
		rank = newRank;
	};
	Rank getRank() const {
		return rank;
	};

  void listCoursesTaught() const;
  // offer this course
  bool offerCourse( const Course& aCourse );
  // cancel this course
  bool dropCourse( const Course& theCourse);

  bool assignGrader( const string newGrader );
  bool dropGrader( const string grader );
  void listGraders() const;

  double getSalary() const {
	  return salary;
  };
  void setSalary(double theSalary) {
	  salary = theSalary;
  };

  void print() const {
	  Person::print();
	  cout << "rank = " << rank << endl
		  << "salary = "<< salary <<endl
		  << "department = " << department << endl;
  };
};




const unsigned GradCourseLevel = 400;

const unsigned MaxCoursesForGradStudent = 4;


////////// derived class GraduateStudent /////////////


class GraduateStudent : public Student {
  
  Teacher advisor;
  unsigned short numCourses;

public:
  
  //constructor:
  GraduateStudent();
  GraduateStudent( const string theName,
                   unsigned long theSSN,
                   const Date theBirthDate,
                   const string theAddress,
                   StudentStatus theStatus,
                   Department theDepartment,
                   const Teacher& theAdvisor);
  
  GraduateStudent( const GraduateStudent& other );
  GraduateStudent&  operator=( const GraduateStudent& other );
  ~GraduateStudent(){}


  //need to override the following method inherited from 
  //Student class because a grad students cannot enroll in 
  //low-level courses
  bool enrollForCourse( const Course& aCourse );

  void changeAdvisor( const Teacher& newAdvisor );

  Teacher getAdvisor() const;

  void print() const;
};



//////////// derived class GradTeachAsst ///////////////


class GradTeachAsst : public GraduateStudent, public Teacher {

public:

  //constructor:
  GradTeachAsst();
  GradTeachAsst( const string theName,
                 unsigned long theSSN,
                 const Date theBirthDate,
                 const string theAddress,
                 StudentStatus theStatus,
                 Department studentDepartment,    // (A)
                 const Teacher& theAdvisor,
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
  bool setRank( Rank newRank );

  // this method must be overridden because of name conflict
  // from two different bases  
  void print() const;   
};
