#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
#include "course.h"


using namespace std;
namespace PA4{

class Course;

class Student{
private:
string student_name;
int ID;
int size;

public:
Course *course_ref;

Student();
Student(string name,int Id);
Student(const  Student &C);
int getsize();
int getId();
string getname();
void setsize(int size_);
void setId(int Id);
void setname(string name);
Student &operator=(const Student &C);
void addcourse(Course c);
void delete_course(Course c);

~ Student();

};
}
#endif