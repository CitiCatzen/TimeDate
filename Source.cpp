#include <iostream>
#include "Time_date.h"
using namespace std;


vector<myStack<Time_date>> sortStack(myStack<Time_date> imStack);
int weekday(Time_date Some);
enum weekday
{
	mondays,
	tuesdays, 
	wednesdays, 
	thursdays, fridays,
	saturdays, 
	sundays
};

int main()
{
	Time_date b;
	b = Time_date::parse("10:27 pm  22-05-2019", "IE-12h");
	cout << b << endl;
	system("PAUSE");
	return 0;
}

vector<myStack<Time_date>> sortStack(myStack<Time_date> imStack)
{
	myStack<Time_date>  mondays, tuesdays, wednesdays, thursdays, fridays, saturdays, sundays;
	vector< myStack<Time_date> >  noName;
	while (!imStack.empty())
	{
		switch (weekday(imStack.top()))
		{
		case 0:
			saturdays.push(imStack.top());
			break;
		case 1:
			sundays.push(imStack.top());
			break;
		case 2:
			mondays.push(imStack.top());
			break;
		case 3:
			tuesdays.push(imStack.top());
			break;
		case 4:
			wednesdays.push(imStack.top());
			break;
		case 5:
			thursdays.push(imStack.top());
			break;
		case 6:
			fridays.push(imStack.top());
			break;
		}

		imStack.pop();
	}
	noName.push_back(mondays);
	noName.push_back(tuesdays);
	noName.push_back(wednesdays);
	noName.push_back(thursdays);
	noName.push_back(fridays);
	noName.push_back(saturdays);
	noName.push_back(sundays);
	return noName;
}

int weekday(Time_date Some)
{
	int one = 0;
	switch (Some.Month())
	{
		case 1:
		case 10:
			one = 1;
			break;
		case 5:
			one = 2;
			break;
		case 8:
			one = 3;
			break;
		case 2:
		case 11:
		case 3:
			one = 4;
			break;
		case 6:
			one = 5;
			break;
		case 9:
		case 12:
			one = 6;
			break;
		case 4:
		case 7:
			one = 0;
	}
	int two = (6 + Some.Year() % 100 + (Some.Year() % 100) / 4) % 7;
	int sum = (Some.Day() + one + two) % 7;
	return sum;
}
