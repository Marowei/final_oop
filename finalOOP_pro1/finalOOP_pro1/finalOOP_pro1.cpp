#include "project1_starter.h"
int main()
{
	Person p0;
	Date d1(28, 12, 2018);
	Person p1("Marowei", 123456789, d1, "NTUST");
	p0.print();
	cout << "--------------------"<< endl;
	p1.print();

	printf("test update\n");
	system("pause");
}
