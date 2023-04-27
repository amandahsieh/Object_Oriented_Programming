//
// Instructor: Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/03/24
//
#include "mySystemApp.h"

using namespace std;

#define STUDENT_INFO "Name:Sai-Keung Wong   ID:0123456789"

void MY_SYSTEM_APP::showMyStudentInfo( ) const
{
	cout << "*******************************" << endl;
    cout << "Date:2022/03/24" << endl;
	cout << "Student ID:\t" << endl;
	cout << "Student Name:\t" << endl;
	cout << "Student Email:\t" << endl;
	cout << "*******************************" << endl;
}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
	mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE;
    //string title = STUDENT_INFO;
    //glutSetWindowTitle(title.data( ));
	updateMonteCarloTitle();
}

const char* MY_SYSTEM_APP::getStudentInfo() const {
	return STUDENT_INFO;
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = true;
}

void MY_SYSTEM_APP::update( )
{

}
// CODE: 2022/03/24. Do not delete this line.



