#include<iostream>
#include<iomanip>
#include<conio.h>
#include<fstream>
#include<algorithm>
#include<vector>
#pragma warning(disable:4996)
#define Maxlen 20 //名字数组长度上限
#define IDlen 19 //身份证数组长度上限
#define CourseIDlen 10 //课程号数组长度上限
#define CourseNamelen 20 //课程名数组长度上限
#define StudentIDlen 15 //学号数组长度上限
#define TeacherIDlen 15 //教职工号数组长度上限
#define StudentKeylen 20 //学生密码数组长度上限
#define StudentClassNamelen 10 //学生班级数组长度上限
#define Dutylen 20 //教师职务数组长度上限
#define Departmentlen 20 //学生院系数组长度上限
#define MaxCourse 100 //课程总数上限
#define Accountlen 40 //账号总长度上限
#define Keylen 20 //密码总长度上限
#define Emaillen 40 //邮箱总长度上限
#define MaxStu 10000 //学生总数量上限
#define MaxTea 1000 //学生总数量上限
using namespace std;
int flag_student_modify = 0, flag_teacher_modify = 0;


//日期类定义
class Date {
protected:
	int year;//年
	int month;//月
	int day;//日
public:
	Date(int y = 0, int m = 0, int d = 0) :year(y), month(m), day(d) {};
	Date(const Date& p) { year = p.year; month = p.month; day = p.day; }
	friend ostream& operator << (ostream& out, const Date& p);
	friend istream& operator >> (istream& in, Date& p);
	Date& operator = (const Date& p) { year = p.year; month = p.month; day = p.day; return *this; }
	void SetDate(int y, int m, int d) { year = y; month = m; day = d; }
	void ShowDate() { cout << year << '/' << month << '/' << day << endl; }
	void GetDate(int& y, int& m, int& d) { y = year; m = month; d = day; }
};

ostream& operator << (ostream& out, const Date& p) {
	out << p.year << '/' << p.month << '/' << p.day;
	return out;
}

istream& operator >> (istream& in, Date& p) {
	char ch; int num = 0;
	while (in.get(ch) && !isdigit(ch)) continue;
	while (isdigit(ch)) {
		num = (num << 3) + (num << 1) + (ch - '0');
		in.get(ch);
	}
	p.year = num;
	num = 0;
	while (in.get(ch) && !isdigit(ch)) continue;
	while (isdigit(ch)) {
		num = (num << 3) + (num << 1) + (ch - '0');
		in.get(ch);
	}
	p.month = num;
	num = 0;
	while (in.get(ch) && !isdigit(ch)) continue;
	while (isdigit(ch)) {
		num = (num << 3) + (num << 1) + (ch - '0');
		in.get(ch);
	}
	p.day = num;
	while (ch != '\n') in.get(ch);
	return in;
}


//抽象类，学生和老师类由此继承
class Person {
protected:
	char name[Maxlen];//姓名
	char sex;//性别：M—男，F—女
	char ID[IDlen];//身份证号
	Date date;
public:
	Person() {
		name[0] = '\0';
		sex = '\0';
		ID[0] = '\0';
		date.SetDate(0, 0, 0);
	}
	Person(char* n, char s, char* id, Date _date) {
		strcpy(name, n);
		sex = s;
		strcpy(ID, id);
		date = _date;
	}
	Person(const char* n, const char s, const char* id, const Date _date) {
		strcpy(name, n);
		sex = s;
		strcpy(ID, id);
		date = _date;
	}
	Person(const Person& p) {
		strcpy(name, p.name);
		sex = p.sex;
		strcpy(ID, p.ID);
		date = p.date;
	}
	void SetName(char* n) { strcpy(name, n); }
	void SetSex(char s) { sex = s; }
	void SetID(char* id) { strcpy(ID, id); }
	void SetDate(Date _date) { date = _date; }
	void GetName(char*& n) {
		strcpy(n, name);
	}
	void GetSex(char& s) {
		s = sex;
	}
	void GetID(char*& id) {
		strcpy(id, ID);
	}
	void GetDate(int& y, int& m, int& d) {
		date.GetDate(y, m, d);
	}
	virtual void Show() const = 0; //纯虚函数
};

//账号信息类,学生和老师类由此继承
class AccountInfo {
protected:
	char Account[Accountlen];
	char Key[Keylen];
	char Email[Emaillen];
public:
	AccountInfo() {
		Account[0] = '\0';
		Key[0] = '\0';
		Email[0] = '\0';
	}
	AccountInfo(char* ac, char* key, char* email) {
		strcpy(Account, ac);
		strcpy(Key, key);
		strcpy(Email, email);
	}
	AccountInfo(const char* ac, const char* key, const char* email) {
		strcpy(Account, ac);
		strcpy(Key, key);
		strcpy(Email, email);
	}
	AccountInfo(const AccountInfo& p) {
		strcpy(Account, p.Account);
		strcpy(Key, p.Key);
		strcpy(Email, p.Email);
	}
	bool SetAccount(char* ac) {
		strcpy(Account, ac);
		if (strcmp(Account, ac) == 0)return true;
		return false;
	}
	bool SetKey(char* key) {
		strcpy(Key, key);
		if (strcmp(Key, key) == 0)return true;
		return false;
	}
	void GetKey(char* k) {
		strcpy(k, Key);
	}
	bool SetEmail(char* email) {
		strcpy(Email, email);
		if (strcmp(Email, email) == 0)return true;
		return false;
	}
	bool JudgeKey(char* key) {
		if (strcmp(Key, key) == 0)return true;
		return false;
	}
};

//课程类
class Course {
protected:
	char CourseID[CourseIDlen]; //课程号
	char CourseName[CourseNamelen]; //课程名
	int Credits; //学分
	int ClassHours; //学时
public:
	friend Course* GetCourseInfoFromTXT();
	friend int RewriteCourseInfoIntoTXT(Course* pCor, int n);
	friend Course* SearchCourseInfoInArr(Course* pCor, char* cid);
	friend void ShowSingleCourse(char* cid);
	friend void ShowCourses();
	Course() {
		CourseID[0] = '\0';
		CourseName[0] = '\0';
		Credits = 0;
		ClassHours = 0;
	}
	Course(char* id, char* name, int c, int h) {
		strcpy(CourseID, id);
		strcpy(CourseName, name);
		Credits = c;
		ClassHours = h;
	}
	Course(const Course& p) {
		strcpy(CourseID, p.CourseID);
		strcpy(CourseName, p.CourseName);
		Credits = p.Credits;
		ClassHours = p.ClassHours;
	}
	void ShowCourse() {
		cout << "课程号：" << CourseID << "  课程名：" << CourseName << "  学分：" << Credits << "  学时：" << ClassHours;
	}
	void SetCourse(char* id, char* name, int c, int h) {
		strcpy(CourseID, id);
		strcpy(CourseName, name);
		Credits = c;
		ClassHours = h;
	}

	void GetCourse(char*& id, char*& n, int &c, int &h) const {
		strcpy(id, CourseID);
		strcpy(n, CourseName);
		c = Credits;
		h = ClassHours;
	}
	void getID(char*& id) {
		strcpy(id, CourseID);
	}
	bool judge_ID(char* id) {
		if (strcmp(CourseID, id) == 0)return true;
		return false;
	}
};

//课程成绩类
class CourseScore {
protected:
	char CourseID[CourseIDlen]; //课程号
	double score; //分数
	char grade; //等第
	double gradepoint; //绩点
public:
	CourseScore() {
		CourseID[0] = '\0';
		score = 0;
		grade = 0;
		gradepoint = 0;
	}
	CourseScore(char* id, double s, char g, double gp) {
		strcpy(CourseID, id);
		score = s;
		grade = g;
		gradepoint = gp;
	}
	CourseScore(const CourseScore& p) {
		strcpy(CourseID, p.CourseID);
		score = p.score;
		grade = p.grade;
		gradepoint = p.gradepoint;
	}
	void Set(char* id, double s, char g, double gp) {
		strcpy(CourseID, id);
		score = s;
		grade = g;
		gradepoint = gp;
	}
	void Get(char*& id, double& s, char& g, double& gp) const {
		strcpy(id, CourseID);
		s = score;
		g = grade;
		gp = gradepoint;
	}
	void GetCourse(char*& id) {
		strcpy(id, CourseID);
	}
	bool judge_ID(char* id) {
		if (strcmp(CourseID, id) == 0)return true;
		return false;
	}
};



bool GPA_cal(double s, char& g, double& gp) {
	if (s >= 90) {
		g = 'A';
		gp = 4.0;
	}
	if (s < 90 && s >= 78) {
		g = 'B';
		gp = 3.0;
	}
	if (s < 78 && s >= 68) {
		g = 'C';
		gp = 2.0;
	}
	if (s < 68 && s >= 60) {
		g = 'D';
		gp = 1.0;
	}
	if (s < 60 && s >= 0) {
		g = 'F';
		gp = 0;
	}
	return true;
}


//学生类
class Student :public Person, public AccountInfo{
protected:
	char StuID[StudentIDlen];//学号
	char StuClass[StudentClassNamelen];//班级
	char Department[Departmentlen];//院系
	int CourseNum;//选课门数
	CourseScore Scores[MaxCourse];//选课成绩
public:
	friend class Teacher;
	static int TotalNum; //学生总人数
	Student() {
		StuID[0] = '\0';
		StuClass[0] = '\0';
		Department[0] = '\0';
		CourseNum = 0;
	}
	Student(char* name, char s, char* id, const Date& date, char* stuid, char* stuclass, char* depart, char* stukey) :Person(name, s, id, date) {
		strcpy(StuID, stuid);
		strcpy(StuClass, stuclass);
		strcpy(Department, depart);
		strcpy(Key, stukey);
		SetAccount(StuID);
		CourseNum = 0;
	}
	Student(const Student& p) :Person(p.name, p.sex, p.ID, p.date), AccountInfo(p.Account, p.Key, p.Email) {
		strcpy(StuID, p.StuID);
		strcpy(StuClass, p.StuClass);
		strcpy(Department, p.Department);
		CourseNum = p.CourseNum;
		for (int i = 0; i < CourseNum; i++) {
			char* tmp_id = new char[10];
			double tmp_s, tmp_gp;
			char tmp_g;
			p.Scores[i].Get(tmp_id, tmp_s, tmp_g, tmp_gp);
			Scores[i].Set(tmp_id, tmp_s, tmp_g, tmp_gp);
			delete[] tmp_id;
		}
	}
	void GetStuID(char* id) {
		strcpy(id, StuID);
	}
	void GetDepart(char*& d) {
		strcpy(d, Department);
	}
	void GetClass(char*& c) {
		strcpy(c, StuClass);
	}
	int GetCourseNum() {
		return CourseNum;
	}
	bool compare_ID(char* id) {
		if (strcmp(StuID, id) == 0)return true;
		return false;
	}
	bool SetStuID(char* id) {
		strcpy(StuID, id);
		strcpy(Account, id);
		if (strcmp(StuID, id) == 0)return true;
		return false;
	}
	bool SetStuClass(char* c) {
		strcpy(StuClass, c);
		if (strcmp(StuClass, c) == 0)return true;
		return false;
	}
	bool SetStuDepartment(char* depart) {
		strcpy(Department, depart);
		if (strcmp(Department, depart) == 0)return true;
		return false;
	}
	bool SetCouserNum(int n) {
		CourseNum = n;
		return true;
	}
	bool AddCourse(char* tmp_id, double tmp_s, double tmp_gp, char tmp_g) {
		GPA_cal(tmp_s, tmp_g, tmp_gp);
		Scores[CourseNum++].Set(tmp_id, tmp_s, tmp_g, tmp_gp);
		if (CourseNum <= MaxCourse)return true;
	}
	void ShowScores() const {
		if (CourseNum == 0) {
			cout << "尚未录入选课信息" << endl;
			return;
		}
		int i;
		for (i = 0; i < CourseNum; i++) {
			char* tmp_id = new char[10];
			double tmp_s, tmp_gp;
			char tmp_g;
			Scores[i].Get(tmp_id, tmp_s, tmp_g, tmp_gp);
			cout << "========第" << i + 1 << "门========\n";
			cout << "课程号： " << tmp_id <<  endl;
			if (tmp_s > 0)cout << "成绩： " << tmp_s << "  等第： " << tmp_g << "  绩点： " << tmp_gp << endl;
			else cout << "该门课程成绩还未给出" << endl;
		}
	}
	void Show() const {
		cout << "姓名：" << name << "   ";
		cout << "学号：" << StuID << "   ";
		cout << "院系：" << Department << "   ";
		cout << "班级：" << StuClass << endl;
		if (sex == 'M' || sex == 'm') cout << "性别：男" << "   ";
		else if (sex == 'F' || sex == 'f') cout << "性别：女" << "   ";
		else cout << "性别：未知" << "   ";
		cout << "生日：" << date << "   ";
		cout << "身份证号：" << ID << endl;
		cout << endl;
	}
	void GetCourseID(int i,char*& courseid) {
		Scores[i].GetCourse(courseid);
	}
	bool search_course(char* course_id, double& s, char& g, double& gp) {
		int i = 0;
		char* tmp = new char[20];
		for (i = 0; i < CourseNum; i++) {
			if (Scores[i].judge_ID(course_id)) {
				Scores[i].Get(tmp, s, g, gp);
				break;
			}
		}
		delete[] tmp;
		if (i == CourseNum)return false;
		return true;
	}
	bool set_course(char* course_id, double s, char g, double gp) {
		int i = 0;
		for (i = 0; i < CourseNum; i++) {
			if (Scores[i].judge_ID(course_id)) {
				Scores[i].Set(course_id, s, g, gp);
				break;
			}
		}
		if (i == CourseNum)return false;
		return true;
	}
}stu[MaxStu];


//老师类
class Teacher :public Person, public AccountInfo {
protected:
	char TeacherID[TeacherIDlen];//教职工号
	char Department[Departmentlen];//院系
	char duty[Dutylen];//职位
	int CourseNum;//任课门数
	Course courses[MaxCourse];//任课信息
public:
	static int TotalNum; //教师总人数
	Teacher() {
		TeacherID[0] = '\0';
		Department[0] = '\0';
		duty[0] = '\0';
		Key[0] = '\0';
		Account[0] = '\0';
		Email[0] = '\0';
		CourseNum = 0;
	}
	Teacher(char* name, char s, char* id, const Date& date, char* teaid, char* dut, char* depart, char* teakey) :Person(name, s, id, date) {
		strcpy(TeacherID, teaid);
		strcpy(duty, dut);
		strcpy(Department, depart);
		strcpy(Key, teakey);
		SetAccount(TeacherID);
		CourseNum = 0;
	}
	Teacher(const Teacher& p) :Person(p.name, p.sex, p.ID, p.date), AccountInfo(p.Account, p.Key, p.Email) {
		strcpy(TeacherID, p.TeacherID);
		strcpy(duty, p.duty);
		strcpy(Department, p.Department);
		CourseNum = p.CourseNum;
		for (int i = 0; i < CourseNum; i++) {
			char* tmp_id = new char[10];
			char* tmp_name = new char[20];
			int tmp_c, tmp_h;
			p.courses[i].GetCourse(tmp_id, tmp_name, tmp_c, tmp_h);
			courses[i].SetCourse(tmp_id, tmp_name, tmp_c, tmp_h);
			delete[] tmp_id;
			delete[] tmp_name;
		}
	}
	void GetTeaID(char* id) {
		strcpy(id, TeacherID);
	}
	void GetDepart(char*& d) {
		strcpy(d, Department);
	}
	void GetDuty(char*& d) {
		strcpy(d, duty);
	}
	int GetCourseNum() {
		return CourseNum;
	}
	bool compare_ID(char* id) {
		if (strcmp(TeacherID, id) == 0)return true;
		return false;
	}
	bool SetTeaID(char* id) {
		strcpy(TeacherID, id);
		strcpy(Account, id);
		if (strcmp(TeacherID, id) == 0)return true;
		return false;
	}
	bool SetTeaDepartment(char* d) {
		strcpy(Department, d);
		if (strcmp(Department, d) == 0)return true;
		return false;
	}
	bool SetDuty(char* d) {
		strcpy(duty, d);
		if (strcmp(duty, d) == 0)return true;
		return false;
	}
	bool SetCouserNum(int n) {
		CourseNum = n;
		return true;
	}
	int get_coursenum() {
		return CourseNum;
	}
	bool AddCourse(char* tmp_id, char* tmp_name, int tmp_c, int tmp_h) {
		courses[CourseNum++].SetCourse(tmp_id, tmp_name, tmp_c, tmp_h);
		if (CourseNum <= MaxCourse)return true;
	}
	bool search_course(char* course_id) {
		int i = 0;
		for (i = 0; i < CourseNum; i++) {
			if (courses[i].judge_ID(course_id)) {
				return true;
			}
		}
		if (i == CourseNum)return false;
		return true;
	}
	void ShowClasses() const {
		if (CourseNum == 0) {
			cout << "尚未录入课程信息" << endl;
			return;
		}
		int i;
		for (i = 0; i < CourseNum; i++) {
			char* tmp_id = new char[10];
			char* tmp_name = new char[20];
			int tmp_c, tmp_h;
			courses[i].GetCourse(tmp_id, tmp_name, tmp_c, tmp_h);
			cout << "========第" << i + 1 << "门========\n";
			cout << "课程号： " << tmp_id << endl;
			cout << "课程名： " << tmp_name << endl;
			cout << "学分： " << tmp_c << endl;
			cout << "学时： " << tmp_h << endl;
			delete[] tmp_id;
			delete[] tmp_name;
		}
		cout << endl;
	}
	void Show() const {
		cout << "姓名：" << name << "   ";
		cout << "教职工号：" << TeacherID << "   ";
		cout << "院系：" << Department << "   ";
		cout << "职位：" << duty << endl;
		if (sex == 'M' || sex == 'm') cout << "性别：男" << "   ";
		else if (sex == 'F' || sex == 'f') cout << "性别：女" << "   ";
		else cout << "性别：未知" << "   ";
		cout << "生日：" << date << "   ";
		cout << "身份证号：" << ID << endl;
		cout << endl;
	}
	void get_couseid(int i, char*& id) {
		courses[i].getID(id);
	}
	bool Get_course(char* id, char*& n, int& c, int& h) {
		int i = 0;
		for (i = 0; i < CourseNum; i++) {
			if (courses[i].judge_ID(id)) {
				courses[i].GetCourse(id, n, c, h);
				return true;
			}
		}
		if (i == CourseNum)return false;
		return true;
	}
}tea[MaxTea];


//排序辅助结构体
class sort_score {
public:
	string name;
	double score;
	sort_score(string n, double s) {
		name = n;
		score = s;
	}
};

bool comp(const sort_score& a, const sort_score& b) {
	return a.score > b.score;
}


int Teacher::TotalNum = 0;
int Student::TotalNum = 0;



void Student_Module()
{
	char ch;
	while (true) {
		cout << endl;
		cout << "================学生================" << endl;
		cout << "a.创建学生账号" << endl;
		cout << "b.登录学生账号" << endl;
		cout << "q.返回主菜单" << endl;
		cin.get(ch);
		while (ch != 'a' && ch != 'b' && ch != 'q')cin.get(ch);
		if (ch == 'a') {
			flag_student_modify = 1;
			cout << "==============创建学生账号==============\n";
			cout << "从文件读入中……\n";
			ifstream input("StudentInfo.txt");
			string tmp;
			char str[1000];
			int i = 0;
			if (!input.is_open()) {
				cout << "未能成功打开文件，请重试！" << endl;
				continue;
			}
			Student::TotalNum = 0;
			while (input >> tmp) {
				if (tmp.length() <= 0)break;

				Student::TotalNum += 1;
				
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				stu[i].SetStuID(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				stu[i].SetKey(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				stu[i].SetName(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				stu[i].SetSex(str[0]);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				stu[i].SetID(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				int year = 0, month = 0, day = 0, ii = 0;
				for (ii = 0; ii < tmp.length() && str[ii] != '/'; ii++)
					year = year * 10 + str[ii] - '0';
				ii++;
				while (ii < tmp.length() && str[ii] != '/')
					month = month * 10 + str[ii++] - '0';
				ii++;
				while (ii < tmp.length())
					day = day * 10 + str[ii++] - '0';
				stu[i].SetDate(Date(year, month, day));

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				stu[i].SetStuClass(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				stu[i].SetStuDepartment(str);


				int cour_num = 0;
				char str_id[20], tmp_g[20];
				double tmp_score, tmp_gp;
				input >> cour_num;
				stu[i].SetCouserNum(0);
				for (ii = 0; ii < cour_num; ii++) {
					input >> tmp;
					tmp.copy(str_id, tmp.length(), 0);
					*(str_id + tmp.length()) = '\0';
					input >> tmp_score;
					input >> tmp;
					tmp.copy(tmp_g, tmp.length(), 0);
					*(tmp_g + tmp.length()) = '\0';
					input >> tmp_gp;
					stu[i].AddCourse(str_id, tmp_score, tmp_gp, tmp_g[0]);
				}
				i++;
			}
			input.close();
			cout << "=============成功读入信息如下=============\n";
			for (int ii = 0; ii < Student::TotalNum; ii++)
				stu[ii].Show();
			cout << "按下任意键继续...\n";
			if (getch()) continue;
		}
		if (ch == 'b')
		{
			cout << "================学生登录================\n";
			int stu_flag = 0;
			char tmp_id[20], tmp_key[20];
			int stu_num;
			while (!stu_flag) {
				cout << "请输入学号：";
				cin >> tmp_id;
				cout << "请输入密码：";
				cin >> tmp_key;
				int i = 0;
				for (i = 0; i < Student::TotalNum; i++) {
					if (stu[i].compare_ID(tmp_id)) {
						if (stu[i].JudgeKey(tmp_key)) {
							cout << "================登陆成功================\n";
							stu_num = i;
							stu_flag = 1;
							break;
						}
						else {
							cout << "密码错误！请重试！\n";
							cout << "按下任意键继续...\n";
							if (getch()) break;
						}
					}
				}
				if (i == Student::TotalNum) {
					cout << "***尚未录入该学生信息！\n";
					cout << "按下任意键继续...\n";
					if (getch()) break;
				}
			}
			while (stu_flag) {
				cout << endl;
				cout << "================选项================\n";
				cout << "a.显示详细信息\n";
				cout << "b.修改密码\n";
				cout << "c.修改系名\n";
				cout << "d.修改班级\n";
				cout << "e.查询成绩\n";
				cout << "q.退出登录\n";
				cin.get(ch);
				while (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != 'e' && ch != 'q')cin.get(ch);
				if (ch == 'a') {
					stu[stu_num].Show();
					cout << "按下任意键继续...\n";
					if (getch()) continue;
				}
				else if (ch == 'b') {
					char new_key[20];
					cout << "请输入新密码：";
					cin >> new_key;
					stu[stu_num].SetKey(new_key);
					if (stu[stu_num].JudgeKey(new_key))cout << "设置成功！\n";
					else cout << "设置失败！\n";
				}
				else if (ch == 'c') {
					char new_depart[20];
					cout << "请输入新系名：";
					cin >> new_depart;
					if (stu[stu_num].SetStuDepartment(new_depart))cout << "设置成功！\n";
					else cout << "设置失败\n";
				}
				else if (ch == 'd') {
					char new_class[20];
					cout << "请输入新班级：";
					cin >> new_class;
					if (stu[stu_num].SetStuClass(new_class))cout << "设置成功\n";
					else cout << "设置失败\n";
				}
				else if (ch == 'e') {
					stu[stu_num].ShowScores();
					cout << "按下任意键继续...\n";
					if (getch()) continue;
				}
				else if (ch == 'q')break;
			}
		}
		if (ch == 'q') {
			break;
		}
	}
}


void Teacher_Module()
{
	char ch;
	while (true) {
		cout << endl;
		cout << "================教师================" << endl;
		cout << "a.创建教师账号" << endl;
		cout << "b.登录教师账号" << endl;
		cout << "q.返回主菜单" << endl;
		cin.get(ch);
		while (ch != 'a' && ch != 'b' && ch != 'q')cin.get(ch);
		if (ch == 'a') {
			flag_teacher_modify = 1;
			cout << "==============创建教师账号==============\n";
			cout << "从文件读入中……\n";
			ifstream input("TeacherInfo.txt");
			string tmp;
			char str[1000];
			int i = 0;
			if (!input.is_open()) {
				cout << "未能成功打开文件，请重试！" << endl;
				continue;
			}
			Teacher::TotalNum = 0;
			while (input >> tmp) {
				if (tmp.length() <= 0)break;

				Teacher::TotalNum += 1;

				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				tea[i].SetTeaID(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				tea[i].SetKey(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				tea[i].SetName(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				tea[i].SetSex(str[0]);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				tea[i].SetID(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				int year = 0, month = 0, day = 0, ii = 0;
				for (ii = 0; ii < tmp.length() && str[ii] != '/'; ii++)
					year = year * 10 + str[ii] - '0';
				ii++;
				while (ii < tmp.length() && str[ii] != '/')
					month = month * 10 + str[ii++] - '0';
				ii++;
				while (ii < tmp.length())
					day = day * 10 + str[ii++] - '0';
				tea[i].SetDate(Date(year, month, day));

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				tea[i].SetDuty(str);

				input >> tmp;
				tmp.copy(str, tmp.length(), 0);
				*(str + tmp.length()) = '\0';
				tea[i].SetTeaDepartment(str);


				int cour_num = 0;
				tea[i].SetCouserNum(0);
				char str_id[20], tmp_name[20];
				int tmp_c, tmp_h;
				input >> cour_num;
				for (ii = 0; ii < cour_num; ii++) {
					input >> tmp;
					tmp.copy(str_id, tmp.length(), 0);
					*(str_id + tmp.length()) = '\0';
					input >> tmp;
					tmp.copy(tmp_name, tmp.length(), 0);
					*(tmp_name + tmp.length()) = '\0';
					input >> tmp_c >> tmp_h;
					tea[i].AddCourse(str_id, tmp_name, tmp_c, tmp_h);
				}
				i++;
			}
			input.close();
			cout << "=============成功读入信息如下=============\n";
			for (int ii = 0; ii < Teacher::TotalNum; ii++)
				tea[ii].Show();
			cout << "按下任意键继续...\n";
			if (getch()) continue;
		}
		if (ch == 'b')
		{
			cout << "================教师登录================\n";
			int tea_flag = 0;
			char tmp_id[20], tmp_key[20];
			int tea_num;
			while (!tea_flag) {
				cout << "请输入教职工号：";
				cin >> tmp_id;
				cout << "请输入密码：";
				cin >> tmp_key;
				int i = 0;
				for (i = 0; i < Teacher::TotalNum; i++) {
					if (tea[i].compare_ID(tmp_id)) {
						if (tea[i].JudgeKey(tmp_key)) {
							cout << "================登陆成功================\n";
							tea_num = i;
							tea_flag = 1;
							break;
						}
						else {
							cout << "***密码错误！请重试！\n";
							cout << "按下任意键继续...\n";
							if (getch()) break;
						}
					}
				}
				if (i == Teacher::TotalNum) {
					cout << "***尚未录入该教师信息！\n";
					cout << "按下任意键继续...\n";
					if (getch()) break;
				}
			}
			while (tea_flag) {
				cout << endl;
				cout << "================选项================\n";
				cout << "a.显示详细信息\n";
				cout << "b.修改密码\n";
				cout << "c.修改系名\n";
				cout << "d.修改职务\n";
				cout << "e.授课信息\n";
				cout << "q.退出登录\n";
				cin.get(ch);
				while (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != 'e' && ch != 'q')cin.get(ch);
				if (ch == 'a') {
					tea[tea_num].Show();
					cout << "按下任意键继续...\n";
					if (getch()) continue;
				}
				else if (ch == 'b') {
					char new_key[20];
					cout << "请输入新密码：";
					cin >> new_key;
					tea[tea_num].SetKey(new_key);
					if (tea[tea_num].JudgeKey(new_key))cout << "设置成功！\n";
					else cout << "设置失败！\n";
				}
				else if (ch == 'c') {
					char new_depart[20];
					cout << "请输入新系名：";
					cin >> new_depart;
					if (tea[tea_num].SetTeaDepartment(new_depart))cout << "设置成功！\n";
					else cout << "设置失败\n";
				}
				else if (ch == 'd') {
					char new_duty[20];
					cout << "请输入新职务：";
					cin >> new_duty;
					if (tea[tea_num].SetDuty(new_duty))cout << "设置成功\n";
					else cout << "设置失败\n";
				}
				else if (ch == 'e') {
					tea[tea_num].ShowClasses();
					if (Student::TotalNum == 0)cout << "======尚未录入学生信息！请先录入学生信息以查看成绩！======\n";
					else
					{
						while (true) {
							cout << endl;
							cout << "==============授课信息选项==============\n";
							cout << "a.显示学生成绩\n";
							cout << "b.修改学生成绩\n";
							cout << "c.查看成绩排名\n";
							cout << "q.返回\n";
							cin.get(ch);
							while (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'q')cin.get(ch);
							if (ch == 'a') {
								int ii = 0, score_flag = 0;
								char* tmp_str = new char[20];
								double tmp_s, tmp_gp;
								char tmp_g;
								for (ii = 0; ii < tea[tea_num].get_coursenum(); ii++) {
									tea[tea_num].get_couseid(ii, tmp_str);
									cout << "==============课程序号:" << tmp_str << "==============\n";
									double average = 0;
									int tmp_stu_num = 0;
									for (int j = 0; j < Student::TotalNum; j++) {
										if (stu[j].search_course(tmp_str, tmp_s, tmp_g, tmp_gp)) {
											char* tmp_name = new char[20];
											stu[j].GetName(tmp_name);
											cout << "学生：" << tmp_name << "   成绩：" << tmp_s << "   绩点：" << tmp_gp << endl;
											score_flag = 1;
											average += tmp_s;
											tmp_stu_num += 1;
										}
									}
									average /= tmp_stu_num;
									cout << "------------平均分：" << average << "------------" << endl;
									if (!score_flag)cout << "***没有学生选择此课程！" << endl;
								}
								delete[] tmp_str;
							}
							else if (ch == 'b') {
								char* tmp_id = new char[20];
								char* tmp_course = new char[20];
								double tmp_score, tmp_gp;
								int student_i = 0, course_i = 0;
								char tmp_g;

								cout << "请输入学生学号：";
								cin >> tmp_id;
								cout << "请输入课程序号：";
								cin >> tmp_course;
								cout << "请输入课程百分制成绩：";
								cin >> tmp_score;
								for (student_i = 0; student_i < Student::TotalNum; student_i++) {
									if (stu[student_i].compare_ID(tmp_id))break;
								}
								if (student_i == Student::TotalNum) {
									cout << "***此学生不存在！请确认录入情况！" << endl;
									continue;
								}
								else {
									GPA_cal(tmp_score, tmp_g, tmp_gp);
									if (tea[tea_num].search_course(tmp_course)) {
										if (stu[student_i].set_course(tmp_course, tmp_score, tmp_g, tmp_gp))
											cout << "修改成功！" << endl;
										else
											cout << "修改失败！" << endl;
									}
									else
										cout << "***此课程不是您的授课科目！无法修改！" << endl;
								}
								delete[] tmp_id;
								delete[] tmp_course;
							}
							else if (ch == 'c') {
								char* tmp_course = new char[20];
								double tmp_s, tmp_gp;
								char tmp_g;
								int score_flag = 0;
								cout << "请输入课程序号：";
								cin >> tmp_course;
								if (tea[tea_num].search_course(tmp_course) == false) {
									cout << "***此课程不是您的授课科目！无法查看！" << endl;
									continue;
								}
								vector<sort_score> stu_score;
								for (int j = 0; j < Student::TotalNum; j++) {
									if (stu[j].search_course(tmp_course, tmp_s, tmp_g, tmp_gp)) {
										char* tmp_name = new char[20];
										stu[j].GetName(tmp_name);
										stu_score.push_back(sort_score(tmp_name, tmp_s));
										score_flag = 1;
									}
								}
								if (!score_flag) {
									cout << "***没有学生选择此课程！" << endl;
									continue;
								}
								sort(stu_score.begin(), stu_score.end(), comp);
								int k = 0;
								for (vector<sort_score>::iterator it = stu_score.begin(); it != stu_score.end(); it++) {
									k++;
									cout << "第" << k << "名：" << (*it).name << "   成绩：" << (*it).score << endl;
								}
							}
							else if (ch == 'q')break;
						}
					}
					cout << "按下任意键继续...\n";
					if (getch()) continue;
				}
				else if (ch == 'q')break;
			}
		}
		if (ch == 'q') {
			break;
		}
	}
}


int main() {
	char ch;
	cout << setiosflags(ios::fixed) << setprecision(1);
	while (true) {
		cout << endl;
		cout << "==================学生成绩管理系统==================" << endl;
		cout << "a.学生" << endl;
		cout << "b.教师" << endl;
		cout << "q.退出" << endl;
		cin.get(ch);
		while (ch != 'a' && ch != 'b' && ch != 'q')cin.get(ch);
		if (ch == 'a') {
			Student_Module();
		}
		else if (ch == 'b') {
			Teacher_Module();
		}
		else if (ch == 'q') {
			if (flag_student_modify) {
				ofstream output("StudentInfo.txt");
				char* str = new char[1000];
				int y, m, d;
				int i = 0, course_num;
				double s, gp;
				char g;
				for (i = 0; i < Student::TotalNum; i++) {
					stu[i].GetStuID(str);
					output << str;
					output << " ";
					stu[i].GetKey(str);
					output << str;
					output << " ";
					stu[i].GetName(str);
					output << str;
					output << " ";
					stu[i].GetSex(str[0]);
					output << str[0];
					output << " ";
					stu[i].GetID(str);
					output << str;
					output << " ";
					stu[i].GetDate(y, m, d);
					output << y << "/" << m << "/" << d;
					output << " ";
					stu[i].GetClass(str);
					output << str;
					output << " ";
					stu[i].GetDepart(str);
					output << str;
					output << endl;
					course_num = stu[i].GetCourseNum();
					output << course_num << endl;
					for (int j = 0; j < course_num; j++) {
						stu[i].GetCourseID(j, str);
						stu[i].search_course(str, s, g, gp);
						output << str << " " << s << " " << g << " " << gp << endl;
					}
				}
				output.close();
				delete[] str;
			}
			if (flag_teacher_modify) {
				ofstream output2("TeacherInfo.txt");
				char* str = new char[1000];
				int y, m, d;
				int i = 0, course_num;
				char* name = new char[1000];
				int c, h;
				for (i = 0; i < Teacher::TotalNum; i++) {
					tea[i].GetTeaID(str);
					output2 << str;
					output2 << " ";
					tea[i].GetKey(str);
					output2 << str;
					output2 << " ";
					tea[i].GetName(str);
					output2 << str;
					output2 << " ";
					tea[i].GetSex(str[0]);
					output2 << str[0];
					output2 << " ";
					tea[i].GetID(str);
					output2 << str;
					output2 << " ";
					tea[i].GetDate(y, m, d);
					output2 << y << "/" << m << "/" << d;
					output2 << " ";
					tea[i].GetDuty(str);
					output2 << str;
					output2 << " ";
					tea[i].GetDepart(str);
					output2 << str;
					output2 << endl;
					course_num = tea[i].GetCourseNum();
					output2 << course_num << endl;
					for (int j = 0; j < course_num; j++) {
						tea[i].get_couseid(j, str);
						tea[i].Get_course(str, name, c, h);
						output2 << str << " " << name << " " << c << " " << h << endl;
					}
				}
				output2.close();
				delete[] str;
				delete[] name;
			}
			return 0;
		}
	}
	return 0;
}