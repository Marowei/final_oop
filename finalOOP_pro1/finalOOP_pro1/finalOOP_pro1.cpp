#include "project1_starter.h"
int main()
{
	
	/*Person p0;
	Date d1(28, 12, 2018);
	Person p1("Marowei", 123456789, d1, "NTUST");
	p0.print();
	cout << "--------------------"<< endl;
	p1.print();*/
	Teacher t1("tAAA", 100000000, Date(28, 12, 2018), "AAA", Professor, Engineering,100000);
	Teacher t2("tBBB", 200000000, Date(20, 1, 2018), "AAA2", Professor, Engineering,60000);
	Student s1("sAAA", 111111111, Date(27, 11, 2000), "ZZZ", FullTime, Engineering);
	Student s2("sBBB", 111111222, Date(28, 11, 2000), "ZZZ", FullTime, Engineering);
	Student s3("sCCC", 111111333, Date(29, 11, 2000), "ZZZ", PartTime, Arts);
	
	GraduateStudent gs1("gsAAA", 211111222, Date(25, 11, 2000), "CCC", FullTime, Engineering, t1);
	
	t1.print();
	t2.print();
	s1.print();
	s2.print();
	s3.print();
	gs1.print();
	Course eng("English", 1);
	Course math("Math", 2);
	Course history("History", 3);
	Course cplusplus("C++", 1001);
	t1.offerCourse(eng);
	t1.offerCourse(math);
	t2.offerCourse(history);
	s1.enrollForCourse(eng);
	s1.enrollForCourse(math);
	s1.enrollForCourse(history);
	s2.enrollForCourse(math);
	s2.enrollForCourse(history);
	s3.enrollForCourse(eng);
	s3.enrollForCourse(history);
	gs1.enrollForCourse(math);
	gs1.enrollForCourse(cplusplus);
	eng.listStudentsRegisteredFor();
	math.listStudentsRegisteredFor();
	history.listStudentsRegisteredFor();
	cplusplus.listStudentsRegisteredFor();
	s2.dropFromCourse(history);
	history.listStudentsRegisteredFor();
	t2.dropCourse(history);
	history.listStudentsRegisteredFor();
	t1.assignGrader(gs1.getName());
	t1.listGraders();
	t1.dropGrader(gs1.getName());
	t1.listGraders();
	system("pause");
}
