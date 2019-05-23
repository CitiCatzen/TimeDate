#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
#pragma once
#ifndef Date_time
#define Date_time
//////////////////////////
enum  Part_time_date {
	Minutes = 0,
	Hour,
	Day,
	Mounth,
	Year 
};
//////////////////////////
struct Time_date_dif {
	int Minutes_count, Hour_count, Days_count, Mounth_count, Year_count;
};
//////////////////////////
template<class T>
class myStack
{
public:
	myStack() : head(nullptr), Size(0)
	{};
	bool empty();
	void push(T);
	void pop();
	T& top();
	int size() { return Size; }
	template<class T>
	class Node
	{
	public:
		Node* pNext;
		T data;

		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}

	};

	Node<T>* head;
	int Size;
};
//////////////////////////
class Time_date {

	bool Check() {
		for (int i = 0; i < 5; i++) {
			int Top[5]{ 24, 60, 31, 12, 2099 };	int Lower[5]{ 0, 0, 1, 1, 2000 };
			return !((TD[i] <= Top[i]) && (Lower[i] <= TD[i]));
		};
	}

	int TD[5] {0, 0, 0, 0, 0};
	int a {5};
	char signDate = '.';
	

public:
	Time_date()
	{
		TD[0] = 0;
		TD[1] = 0;
		TD[2] = 0;
		TD[3] = 0;
		TD[4] = 0;
	}

	Time_date(int Minutes, int Hour, int Day, int Mounth, int Year) {
		TD[0] = Minutes;
		TD[1] = Hour;
		TD[2] = Day;
		TD[3] = Mounth;
		TD[4] = Year;
		Check();
	};
	 
	Time_date Sum_time_date(Time_date Second);
	Time_date_dif Dif_time_date(Time_date Second);
	void toString(string Time_Date, string Format);
	void Sum(Part_time_date i, int Digit);
	static Time_date parse(string Time_Date, string Format);

	int Minutes()const {
		return TD[0];
	}
	int Hour()const {
		return TD[1];
	}
	int Day()const {
		return TD[2];
	}
	int Month()const {
		return TD[3];
	}
	int Year()const {
		return TD[4];
	}

	Time_date operator+=(Time_date Second);
	Time_date operator=(Time_date Second);
	Time_date operator+(Time_date Second);
	Time_date_dif operator-(Time_date Second);
	bool operator<(Time_date);
	bool operator>(Time_date);
	bool operator>=(Time_date);
	bool operator<=(Time_date);
	friend ostream& operator<<(ostream& out, Time_date& First);
	int operator[](Part_time_date First);
	operator int();



};
//////////////////////////

Time_date Time_date::parse(string Time_Date, string Format)
{
	Time_date forReturn;
	string sText = "";
	if ((Format.find("12h") != string::npos) and (Time_Date.find("pm") != string::npos)) forReturn.TD[1] += 12;
	if (Format.find("GB") != string::npos) forReturn.toString(Time_Date, sText = "GB");
	else if (Format.find("IE") != string::npos) forReturn.toString(Time_Date, sText = "IE");
	else forReturn.toString(Time_Date, sText = "RUS");
	return forReturn;
}

void Time_date::toString(string Time_Date, string Format)
{
	if (Format == "IE") signDate = '-';
	else if (Format == "GB") signDate = '/';
	char* ptr = &Time_Date.at(0);
	string sText = "";
	int countPoints = 0;
	while (*ptr != '\0') {
		while ((*ptr != signDate) && (*ptr != ' ') &&(*ptr != '\0') && *ptr != ':')
		{
			sText = sText + *ptr;
			ptr++;
		}
		countPoints++;
		if ((*ptr == ' ') and (countPoints == 3)) {
			countPoints--;
			goto there;
		}
		switch (countPoints)
		{
		case 1:
			TD[1] += stoul(sText);
			break;
		case 2:
			TD[0] += stoul(sText);
			break;
		case 3:
			TD[2] += stoul(sText);
			break;
		case 4:
			TD[3] += stoul(sText);
			break;
		case 5:
			TD[4] += stoul(sText);
			break;
		}
		there:
			sText.clear();
			if (*ptr != '\0') ptr++;

	};
}

Time_date::operator int() {
	int Sum = 0;
	Time_date Test = *this;
	while (Test.TD[4] != 0) {
		if ((Test.TD[4] % 400 == 0) or ((Test.TD[4] % 4 == 0) and !(Test.TD[4] % 100 == 100))) Sum += 366;
		else Sum += 365;
		(Test.TD[4])--;
	}
	while (Test.TD[3] != 0) {
		if (Test.TD[3] == 2) {
			if ((TD[4] % 400 == 0) or ((TD[4] % 4 == 0) and !(TD[4] % 100 == 100))) {
				Sum += 29;
			}
			else Sum += 28;
		};
		if ((TD[3] == 5) or (TD[3] == 7) or (TD[3] == 10)) {
			Sum += 30;
		}
		else Sum += 31;
		(Test.TD[3])--;
	}
	Sum += Test.TD[2];
	return Sum;
}

int Time_date::operator[](Part_time_date First) {
	int i = 0;
	while (i < 5) {
		if (First == i) return TD[i];
		i++;
	}
}

ostream& operator<<(ostream& out, Time_date& First) {
	out << First.Hour() << ":" << First.Minutes() << endl << First.Day() << First.signDate << First.Month() << First.signDate << First.Year() << endl;
	return out;
}

bool Time_date::operator<(Time_date Second) {
	int i = 4;
	while (i >= 0) {
		if (TD[i] < Second.TD[i]) {
			return true;
		}
		if (TD[i] > Second.TD[i]) {
			return false;
		}
		if (i == 0) return false;
		else i--;
	}
}

bool Time_date::operator>(Time_date Second) {
	int i = 4;
	while (i >= 0) {
		if (TD[i] > Second.TD[i]) {
			return true;
		}
		if (TD[i] < Second.TD[i]) {
			return false;
		}
		if (i == 0) return false;
		else i--;
	}
}

bool Time_date::operator>=(Time_date Second) {
	int i = 4;
	while (i >= 0) {
		if (TD[i] > Second.TD[i]) {
			return true;
		}
		if (TD[i] < Second.TD[i]) {
			return false;
		}
		if (i == 0) return true;
		else i--;
	}
}

bool Time_date::operator<=(Time_date Second) {
	int i = 4;
	while (i == 0) {
		if (TD[i] < Second.TD[i]) {
			return true;
		}
		if (TD[i] > Second.TD[i]) {
			return false;
		}
		if (i == 0) return true;
		else i--;
	}
}

Time_date_dif Time_date::operator-(Time_date Second) {
	int Difference[8]{ 60, 24, 28, 12, 10000, 29, 30, 31 };
	for (int i = 0; i < 5; i++) {
		int j = i;
		if (i == 2) { //������� ���� � ������?
			if (TD[3] == 3) {//�������� ���� �� �������������
				if ((TD[4] % 400 == 0) or ((TD[4] % 4 == 0) and !(TD[4] % 100 == 100))) {
					j = 5;
				}
				else j = 2;
			};
			if ((TD[3] == 5) or (TD[3] == 7) or (TD[3] == 10)) {
				j = 6;
			}
			else j = 7;
		};
		if ((TD[i] - Second.TD[i]) >= 0) TD[i] -= Second.TD[i];
		else {
			TD[i] = (TD[i] - Second.TD[i]) + Difference[j];
			(TD[i + 1])--;
		};
	};
	Time_date_dif a;
	a.Minutes_count = TD[0];
	a.Hour_count = TD[1];
	a.Days_count = TD[2];
	a.Mounth_count = TD[3];
	a.Year_count = TD[4];
	return a;
}

Time_date Time_date::operator+(Time_date Second) {
	int Roole[8]{ 60, 24, 28, 12, 10000, 29, 30, 31 };
	for (int i = 0; i < 5; i++) {
		int j = i;
		if (i == 2) { //������� ���� � ������?
			if (TD[3] == 2) {//�������� ���� �� �������������
				if ((TD[4] % 400 == 0) or ((TD[4] % 4 == 0) and !(TD[4] % 100 == 100))) {
					j = 5;
				}
				else j = 2;
			};
			if ((TD[3] == 4) or (TD[3] == 6) or (TD[3] == 9)) {
				j = 6;
			}
			else j = 7;
		};
		if ((TD[i] + Second.TD[i]) < Roole[j]) TD[i] += Second.TD[i];
		else {
			TD[i] = (TD[i] + Second.TD[i]) - Roole[j];
			(TD[i + 1])++;
		};
	};
	return *this;
}

Time_date Time_date::operator=(Time_date Second) {
	TD[0] = Second.TD[0];
	TD[1] = Second.TD[1];
	TD[2] = Second.TD[2];
	TD[3] = Second.TD[3];
	TD[4] = Second.TD[4];
	signDate = Second.signDate;
	return Second;
}

Time_date Time_date::operator+=(Time_date Second) {
	int Roole[8]{ 60, 24, 28, 12, 10000, 29, 30, 31 };
	for (int i = 0; i < 5; i++) {
		int j = i;
		if (i == 2) { //������� ���� � ������?
			if (TD[3] == 2) {//�������� ���� �� �������������
				if ((TD[4] % 400 == 0) or ((TD[4] % 4 == 0) and !(TD[4] % 100 == 100))) {
					j = 5;
				}
				else j = 2;
			};
			if ((TD[3] == 4) or (TD[3] == 6) or (TD[3] == 9)) {
				j = 6;
			}
			else j = 7;
		};
		if ((TD[i] + Second.TD[i]) < Roole[j]) TD[i] += Second.TD[i];
		else {
			TD[i] = (TD[i] + Second.TD[i]) - Roole[j];
			(TD[i + 1])++;
		};
	};
	return *this;
}

void Time_date::Sum(Part_time_date i, int Digit) {
	int Roole[8]{ 60, 24, 28, 12, 10000, 29, 30, 31 };
	int j = i;
	if (i == 2) { //������� ���� � ������?
		if (TD[3] == 2) {//�������� ���� �� �������������
			if ((TD[4] % 400 == 0) or ((TD[4] % 4 == 0) and !(TD[4] % 100 == 100))) {
				j = 5;
			}
			else j = 2;
		};
		if ((TD[3] == 4) or (TD[3] == 6) or (TD[3] == 9)) {
			j = 6;
		}
		else j = 7;
	};
	if ((TD[i] + Digit) < Roole[j]) TD[i] += Digit;
	else {
		TD[i] += (TD[i] + Digit) - Roole[j];
		(TD[i + 1])++;
	};
}

Time_date_dif Time_date::Dif_time_date(Time_date Second) {
	Time_date Dif(0, 0, 0, 0, 0);
	int Difference[8]{ 60, 24, 28, 12, 10000, 29, 30, 31 };
	for (int i = 0; i < 5; i++) {
		int j = i;
		if (i == 2) { //������� ���� � ������?
			if (TD[3] == 2) {//�������� ���� �� �������������
				if ((TD[4] % 400 == 0) or ((TD[4] % 4 == 0) and !(TD[4] % 100 == 100))) {
					j = 5;
				}
				else j = 2;
			};
			if ((TD[3] == 5) or (TD[3] == 7) or (TD[3] == 10)) {
				j = 6;
			}
			else j = 7;
		};
		if ((TD[i] - Second.TD[i]) >= 0) Dif.TD[i] += TD[i] - Second.TD[i];
		if ((TD[i] - Second.TD[i]) < 0) {
			Dif.TD[i] += (TD[i] - Second.TD[i]) + Difference[j];
			(Dif.TD[i + 1])--;
		};
	};
	Time_date_dif a;
	a.Minutes_count = Dif.TD[0];
	a.Hour_count = Dif.TD[1];
	a.Days_count = Dif.TD[2];
	a.Mounth_count = Dif.TD[3];
	a.Year_count = Dif.TD[4];
	return a;

}

Time_date Time_date::Sum_time_date(Time_date Second) {
	Time_date Sum(0, 0, 0, 0, 0);
	int Roole[8]{ 60, 24, 28, 12, 10000, 29, 30, 31 };
	for (int i = 0; i < 5; i++) {
		int j = i;
		if (i == 2) { //������� ���� � ������?
			if (TD[3] == 2) {//�������� ���� �� �������������
				if ((TD[4] % 400 == 0) or ((TD[4] % 4 == 0) and !(TD[4] % 100 == 100))) {
					j = 5;
				}
				else j = 2;
			};
			if ((TD[3] == 4) or (TD[3] == 6) or (TD[3] == 9)) {
				j = 6;
			}
			else j = 7;
		};
		if ((TD[i] + Second.TD[i]) < Roole[j]) Sum.TD[i] += TD[i] + Second.TD[i];
		else {
			Sum.TD[i] += (TD[i] + Second.TD[i]) - Roole[j];
			(Sum.TD[i + 1])++;
		};
	};
	return Sum;
}

#endif 

template<class T>
inline bool myStack<T>::empty()
{
	if (Size == 0) return true;
	else return false;
}

template<class T>
inline void myStack<T>::push(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<class T>
inline void myStack<T>::pop()
{
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

template<class T>
inline T& myStack<T>::top()
{
	return head->data;
}



