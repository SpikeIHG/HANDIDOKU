class Student {
private:	
	char  name[10];
    short age;
	float score;
	char* remark;
public:
	Student(const char* name, short age, float score, const char* remark);
	Student();
	Student(const Student& s);
	void displayRemark();
	void displayName();
	float getScore();
	void  setScore(float score);
	int getAge();
	Student& operator =(const  Student& s);
	~Student();
	bool compareAgeWithOther(const Student rhs)const{return age>rhs.age;}
	bool compareAgeWithOther(const Student*rhs)const{return age>rhs->age;}
};
