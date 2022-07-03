#include<iostream>
#include<iomanip>
#include<conio.h>
#include<fstream>
#include<algorithm>
#include<vector>
#pragma warning(disable:4996)
#define Maxlen 20 //�������鳤������
#define IDlen 19 //���֤���鳤������
#define CourseIDlen 10 //�γ̺����鳤������
#define CourseNamelen 20 //�γ������鳤������
#define StudentIDlen 15 //ѧ�����鳤������
#define TeacherIDlen 15 //��ְ�������鳤������
#define StudentKeylen 20 //ѧ���������鳤������
#define StudentClassNamelen 10 //ѧ���༶���鳤������
#define Dutylen 20 //��ʦְ�����鳤������
#define Departmentlen 20 //ѧ��Ժϵ���鳤������
#define MaxCourse 100 //�γ���������
#define Accountlen 40 //�˺��ܳ�������
#define Keylen 20 //�����ܳ�������
#define Emaillen 40 //�����ܳ�������
#define MaxStu 10000 //ѧ������������
#define MaxTea 1000 //ѧ������������
using namespace std;
int flag_student_modify = 0, flag_teacher_modify = 0;


//�����ඨ��
class Date {
protected:
	int year;//��
	int month;//��
	int day;//��
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


//�����࣬ѧ������ʦ���ɴ˼̳�
class Person {
protected:
	char name[Maxlen];//����
	char sex;//�Ա�M���У�F��Ů
	char ID[IDlen];//���֤��
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
	virtual void Show() const = 0; //���麯��
};

//�˺���Ϣ��,ѧ������ʦ���ɴ˼̳�
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

//�γ���
class Course {
protected:
	char CourseID[CourseIDlen]; //�γ̺�
	char CourseName[CourseNamelen]; //�γ���
	int Credits; //ѧ��
	int ClassHours; //ѧʱ
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
		cout << "�γ̺ţ�" << CourseID << "  �γ�����" << CourseName << "  ѧ�֣�" << Credits << "  ѧʱ��" << ClassHours;
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

//�γ̳ɼ���
class CourseScore {
protected:
	char CourseID[CourseIDlen]; //�γ̺�
	double score; //����
	char grade; //�ȵ�
	double gradepoint; //����
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


//ѧ����
class Student :public Person, public AccountInfo{
protected:
	char StuID[StudentIDlen];//ѧ��
	char StuClass[StudentClassNamelen];//�༶
	char Department[Departmentlen];//Ժϵ
	int CourseNum;//ѡ������
	CourseScore Scores[MaxCourse];//ѡ�γɼ�
public:
	friend class Teacher;
	static int TotalNum; //ѧ��������
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
			cout << "��δ¼��ѡ����Ϣ" << endl;
			return;
		}
		int i;
		for (i = 0; i < CourseNum; i++) {
			char* tmp_id = new char[10];
			double tmp_s, tmp_gp;
			char tmp_g;
			Scores[i].Get(tmp_id, tmp_s, tmp_g, tmp_gp);
			cout << "========��" << i + 1 << "��========\n";
			cout << "�γ̺ţ� " << tmp_id <<  endl;
			if (tmp_s > 0)cout << "�ɼ��� " << tmp_s << "  �ȵڣ� " << tmp_g << "  ���㣺 " << tmp_gp << endl;
			else cout << "���ſγ̳ɼ���δ����" << endl;
		}
	}
	void Show() const {
		cout << "������" << name << "   ";
		cout << "ѧ�ţ�" << StuID << "   ";
		cout << "Ժϵ��" << Department << "   ";
		cout << "�༶��" << StuClass << endl;
		if (sex == 'M' || sex == 'm') cout << "�Ա���" << "   ";
		else if (sex == 'F' || sex == 'f') cout << "�Ա�Ů" << "   ";
		else cout << "�Ա�δ֪" << "   ";
		cout << "���գ�" << date << "   ";
		cout << "���֤�ţ�" << ID << endl;
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


//��ʦ��
class Teacher :public Person, public AccountInfo {
protected:
	char TeacherID[TeacherIDlen];//��ְ����
	char Department[Departmentlen];//Ժϵ
	char duty[Dutylen];//ְλ
	int CourseNum;//�ο�����
	Course courses[MaxCourse];//�ο���Ϣ
public:
	static int TotalNum; //��ʦ������
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
			cout << "��δ¼��γ���Ϣ" << endl;
			return;
		}
		int i;
		for (i = 0; i < CourseNum; i++) {
			char* tmp_id = new char[10];
			char* tmp_name = new char[20];
			int tmp_c, tmp_h;
			courses[i].GetCourse(tmp_id, tmp_name, tmp_c, tmp_h);
			cout << "========��" << i + 1 << "��========\n";
			cout << "�γ̺ţ� " << tmp_id << endl;
			cout << "�γ����� " << tmp_name << endl;
			cout << "ѧ�֣� " << tmp_c << endl;
			cout << "ѧʱ�� " << tmp_h << endl;
			delete[] tmp_id;
			delete[] tmp_name;
		}
		cout << endl;
	}
	void Show() const {
		cout << "������" << name << "   ";
		cout << "��ְ���ţ�" << TeacherID << "   ";
		cout << "Ժϵ��" << Department << "   ";
		cout << "ְλ��" << duty << endl;
		if (sex == 'M' || sex == 'm') cout << "�Ա���" << "   ";
		else if (sex == 'F' || sex == 'f') cout << "�Ա�Ů" << "   ";
		else cout << "�Ա�δ֪" << "   ";
		cout << "���գ�" << date << "   ";
		cout << "���֤�ţ�" << ID << endl;
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


//�������ṹ��
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
		cout << "================ѧ��================" << endl;
		cout << "a.����ѧ���˺�" << endl;
		cout << "b.��¼ѧ���˺�" << endl;
		cout << "q.�������˵�" << endl;
		cin.get(ch);
		while (ch != 'a' && ch != 'b' && ch != 'q')cin.get(ch);
		if (ch == 'a') {
			flag_student_modify = 1;
			cout << "==============����ѧ���˺�==============\n";
			cout << "���ļ������С���\n";
			ifstream input("StudentInfo.txt");
			string tmp;
			char str[1000];
			int i = 0;
			if (!input.is_open()) {
				cout << "δ�ܳɹ����ļ��������ԣ�" << endl;
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
			cout << "=============�ɹ�������Ϣ����=============\n";
			for (int ii = 0; ii < Student::TotalNum; ii++)
				stu[ii].Show();
			cout << "�������������...\n";
			if (getch()) continue;
		}
		if (ch == 'b')
		{
			cout << "================ѧ����¼================\n";
			int stu_flag = 0;
			char tmp_id[20], tmp_key[20];
			int stu_num;
			while (!stu_flag) {
				cout << "������ѧ�ţ�";
				cin >> tmp_id;
				cout << "���������룺";
				cin >> tmp_key;
				int i = 0;
				for (i = 0; i < Student::TotalNum; i++) {
					if (stu[i].compare_ID(tmp_id)) {
						if (stu[i].JudgeKey(tmp_key)) {
							cout << "================��½�ɹ�================\n";
							stu_num = i;
							stu_flag = 1;
							break;
						}
						else {
							cout << "������������ԣ�\n";
							cout << "�������������...\n";
							if (getch()) break;
						}
					}
				}
				if (i == Student::TotalNum) {
					cout << "***��δ¼���ѧ����Ϣ��\n";
					cout << "�������������...\n";
					if (getch()) break;
				}
			}
			while (stu_flag) {
				cout << endl;
				cout << "================ѡ��================\n";
				cout << "a.��ʾ��ϸ��Ϣ\n";
				cout << "b.�޸�����\n";
				cout << "c.�޸�ϵ��\n";
				cout << "d.�޸İ༶\n";
				cout << "e.��ѯ�ɼ�\n";
				cout << "q.�˳���¼\n";
				cin.get(ch);
				while (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != 'e' && ch != 'q')cin.get(ch);
				if (ch == 'a') {
					stu[stu_num].Show();
					cout << "�������������...\n";
					if (getch()) continue;
				}
				else if (ch == 'b') {
					char new_key[20];
					cout << "�����������룺";
					cin >> new_key;
					stu[stu_num].SetKey(new_key);
					if (stu[stu_num].JudgeKey(new_key))cout << "���óɹ���\n";
					else cout << "����ʧ�ܣ�\n";
				}
				else if (ch == 'c') {
					char new_depart[20];
					cout << "��������ϵ����";
					cin >> new_depart;
					if (stu[stu_num].SetStuDepartment(new_depart))cout << "���óɹ���\n";
					else cout << "����ʧ��\n";
				}
				else if (ch == 'd') {
					char new_class[20];
					cout << "�������°༶��";
					cin >> new_class;
					if (stu[stu_num].SetStuClass(new_class))cout << "���óɹ�\n";
					else cout << "����ʧ��\n";
				}
				else if (ch == 'e') {
					stu[stu_num].ShowScores();
					cout << "�������������...\n";
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
		cout << "================��ʦ================" << endl;
		cout << "a.������ʦ�˺�" << endl;
		cout << "b.��¼��ʦ�˺�" << endl;
		cout << "q.�������˵�" << endl;
		cin.get(ch);
		while (ch != 'a' && ch != 'b' && ch != 'q')cin.get(ch);
		if (ch == 'a') {
			flag_teacher_modify = 1;
			cout << "==============������ʦ�˺�==============\n";
			cout << "���ļ������С���\n";
			ifstream input("TeacherInfo.txt");
			string tmp;
			char str[1000];
			int i = 0;
			if (!input.is_open()) {
				cout << "δ�ܳɹ����ļ��������ԣ�" << endl;
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
			cout << "=============�ɹ�������Ϣ����=============\n";
			for (int ii = 0; ii < Teacher::TotalNum; ii++)
				tea[ii].Show();
			cout << "�������������...\n";
			if (getch()) continue;
		}
		if (ch == 'b')
		{
			cout << "================��ʦ��¼================\n";
			int tea_flag = 0;
			char tmp_id[20], tmp_key[20];
			int tea_num;
			while (!tea_flag) {
				cout << "�������ְ���ţ�";
				cin >> tmp_id;
				cout << "���������룺";
				cin >> tmp_key;
				int i = 0;
				for (i = 0; i < Teacher::TotalNum; i++) {
					if (tea[i].compare_ID(tmp_id)) {
						if (tea[i].JudgeKey(tmp_key)) {
							cout << "================��½�ɹ�================\n";
							tea_num = i;
							tea_flag = 1;
							break;
						}
						else {
							cout << "***������������ԣ�\n";
							cout << "�������������...\n";
							if (getch()) break;
						}
					}
				}
				if (i == Teacher::TotalNum) {
					cout << "***��δ¼��ý�ʦ��Ϣ��\n";
					cout << "�������������...\n";
					if (getch()) break;
				}
			}
			while (tea_flag) {
				cout << endl;
				cout << "================ѡ��================\n";
				cout << "a.��ʾ��ϸ��Ϣ\n";
				cout << "b.�޸�����\n";
				cout << "c.�޸�ϵ��\n";
				cout << "d.�޸�ְ��\n";
				cout << "e.�ڿ���Ϣ\n";
				cout << "q.�˳���¼\n";
				cin.get(ch);
				while (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != 'e' && ch != 'q')cin.get(ch);
				if (ch == 'a') {
					tea[tea_num].Show();
					cout << "�������������...\n";
					if (getch()) continue;
				}
				else if (ch == 'b') {
					char new_key[20];
					cout << "�����������룺";
					cin >> new_key;
					tea[tea_num].SetKey(new_key);
					if (tea[tea_num].JudgeKey(new_key))cout << "���óɹ���\n";
					else cout << "����ʧ�ܣ�\n";
				}
				else if (ch == 'c') {
					char new_depart[20];
					cout << "��������ϵ����";
					cin >> new_depart;
					if (tea[tea_num].SetTeaDepartment(new_depart))cout << "���óɹ���\n";
					else cout << "����ʧ��\n";
				}
				else if (ch == 'd') {
					char new_duty[20];
					cout << "��������ְ��";
					cin >> new_duty;
					if (tea[tea_num].SetDuty(new_duty))cout << "���óɹ�\n";
					else cout << "����ʧ��\n";
				}
				else if (ch == 'e') {
					tea[tea_num].ShowClasses();
					if (Student::TotalNum == 0)cout << "======��δ¼��ѧ����Ϣ������¼��ѧ����Ϣ�Բ鿴�ɼ���======\n";
					else
					{
						while (true) {
							cout << endl;
							cout << "==============�ڿ���Ϣѡ��==============\n";
							cout << "a.��ʾѧ���ɼ�\n";
							cout << "b.�޸�ѧ���ɼ�\n";
							cout << "c.�鿴�ɼ�����\n";
							cout << "q.����\n";
							cin.get(ch);
							while (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'q')cin.get(ch);
							if (ch == 'a') {
								int ii = 0, score_flag = 0;
								char* tmp_str = new char[20];
								double tmp_s, tmp_gp;
								char tmp_g;
								for (ii = 0; ii < tea[tea_num].get_coursenum(); ii++) {
									tea[tea_num].get_couseid(ii, tmp_str);
									cout << "==============�γ����:" << tmp_str << "==============\n";
									double average = 0;
									int tmp_stu_num = 0;
									for (int j = 0; j < Student::TotalNum; j++) {
										if (stu[j].search_course(tmp_str, tmp_s, tmp_g, tmp_gp)) {
											char* tmp_name = new char[20];
											stu[j].GetName(tmp_name);
											cout << "ѧ����" << tmp_name << "   �ɼ���" << tmp_s << "   ���㣺" << tmp_gp << endl;
											score_flag = 1;
											average += tmp_s;
											tmp_stu_num += 1;
										}
									}
									average /= tmp_stu_num;
									cout << "------------ƽ���֣�" << average << "------------" << endl;
									if (!score_flag)cout << "***û��ѧ��ѡ��˿γ̣�" << endl;
								}
								delete[] tmp_str;
							}
							else if (ch == 'b') {
								char* tmp_id = new char[20];
								char* tmp_course = new char[20];
								double tmp_score, tmp_gp;
								int student_i = 0, course_i = 0;
								char tmp_g;

								cout << "������ѧ��ѧ�ţ�";
								cin >> tmp_id;
								cout << "������γ���ţ�";
								cin >> tmp_course;
								cout << "������γ̰ٷ��Ƴɼ���";
								cin >> tmp_score;
								for (student_i = 0; student_i < Student::TotalNum; student_i++) {
									if (stu[student_i].compare_ID(tmp_id))break;
								}
								if (student_i == Student::TotalNum) {
									cout << "***��ѧ�������ڣ���ȷ��¼�������" << endl;
									continue;
								}
								else {
									GPA_cal(tmp_score, tmp_g, tmp_gp);
									if (tea[tea_num].search_course(tmp_course)) {
										if (stu[student_i].set_course(tmp_course, tmp_score, tmp_g, tmp_gp))
											cout << "�޸ĳɹ���" << endl;
										else
											cout << "�޸�ʧ�ܣ�" << endl;
									}
									else
										cout << "***�˿γ̲��������ڿο�Ŀ���޷��޸ģ�" << endl;
								}
								delete[] tmp_id;
								delete[] tmp_course;
							}
							else if (ch == 'c') {
								char* tmp_course = new char[20];
								double tmp_s, tmp_gp;
								char tmp_g;
								int score_flag = 0;
								cout << "������γ���ţ�";
								cin >> tmp_course;
								if (tea[tea_num].search_course(tmp_course) == false) {
									cout << "***�˿γ̲��������ڿο�Ŀ���޷��鿴��" << endl;
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
									cout << "***û��ѧ��ѡ��˿γ̣�" << endl;
									continue;
								}
								sort(stu_score.begin(), stu_score.end(), comp);
								int k = 0;
								for (vector<sort_score>::iterator it = stu_score.begin(); it != stu_score.end(); it++) {
									k++;
									cout << "��" << k << "����" << (*it).name << "   �ɼ���" << (*it).score << endl;
								}
							}
							else if (ch == 'q')break;
						}
					}
					cout << "�������������...\n";
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
		cout << "==================ѧ���ɼ�����ϵͳ==================" << endl;
		cout << "a.ѧ��" << endl;
		cout << "b.��ʦ" << endl;
		cout << "q.�˳�" << endl;
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