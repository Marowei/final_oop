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
	GradTeachAsst gta1("gtaAAA", 311111111, Date(11, 11, 1990), "GTA", FullTime, Engineering, t2, Arts);
	GradTeachAsst gta2("gtaBBB", 311111222, Date(22 , 11, 1990), "GTA", FullTime, Engineering, t1, Engineering);
	gta1.setSalary(2500);
	gta2.setSalary(5500);
	gta1.setRank(Professor);
	t1.print();
	t2.print();
	s1.print();
	s2.print();
	s3.print();
	gs1.print();
	gta1.print();
	gta2.print();
	Course eng("English", 1);
	Course math("Math", 2);
	Course history("History", 3);
	Course cplusplus("C++", 1001);
	Course chinese("Chinese", 1002);
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
	gta1.enrollForCourse(cplusplus);
	gta2.enrollForCourse(chinese);
	eng.listStudentsRegisteredFor();
	math.listStudentsRegisteredFor();
	history.listStudentsRegisteredFor();
	cplusplus.listStudentsRegisteredFor();
	s2.dropFromCourse(history);
	history.listStudentsRegisteredFor();
	t2.dropCourse(history);
	history.listStudentsRegisteredFor();
	t1.assignGrader(gs1.getName());
	t1.assignGrader(gta2.getName());
	t2.assignGrader(gta1.getName());
	t1.listGraders();
	t2.listGraders();
	t1.dropGrader(gs1.getName());
	t1.listGraders();

	system("pause");
}
