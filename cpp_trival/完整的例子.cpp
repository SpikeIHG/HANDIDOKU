
# include "Student.h"
#include <iostream>
#include<cstring>
using namespace std;

int main()
{
	Student xu("xuxy123456789012", 21, 90, "very good student");
	Student zhang("zhang", 22, 95, 0);
	Student yang;
	Student li("lishi", 20, 85, "good");
	Student ma(li);
	xu.displayName();
	cout << "zhang . score = " << zhang.getScore() << endl;
	int  x = zhang.getAge();
	cout << "zhang . age = " << x << endl;
	xu.setScore(95);

	xu.compareAgeWithOther(zhang);
	xu.compareAgeWithOther(&zhang);


	return 0;
}


Student::Student(const char* name, short age, float score, const char* remark)
{
	cout << "general construct" << endl;
	int len;

	if (name) {
		len = strlen(name);
		if (len <= 9)
			strcpy(this->name, name);
		else {
			cout << "name is too long;  cut  string" << endl;
			memcpy(this->name, name, 9);
			this->name[9] = 0;
		}
	}
	else  this->name[0] = 0;
	(*this).age = age;
	Student::score = score;
	if (remark) {
		len = strlen(remark)+1;
		this->remark = (char*)malloc(len);
		strncpy(this->remark, remark,len);
	}
	else this->remark = NULL;
}


Student::Student()
{
	cout << "no parameter construct" << endl;
	strcpy(name, "noname");
	age = 0;
	score = 0;
	remark = NULL;
}

Student::~Student()
{
	cout << "deconstruct :" << name << endl;
	if (remark) {
		free(remark);
		remark = NULL;
	}
}

void Student::displayRemark()
{
	cout << "remark : " << remark << endl;
}

void Student::displayName()
{
	cout << "name : " << name << endl;
}
int Student::getAge()
{
	return age;
}

float Student::getScore()
{
	return score;
}

void Student::setScore(float score)
{
	this->score = score;
}

Student::Student(const Student& s)
{
	cout << "construct : object parameter" << endl;
	strcpy(name, s.name);
	age = s.age;
	score = s.score;
	if(s.remark){
	int len = strlen(s.remark) + 1;
	remark = (char*)malloc(len);
	strncpy(remark, s.remark,len);}
	else
	remark=nullptr;
}

