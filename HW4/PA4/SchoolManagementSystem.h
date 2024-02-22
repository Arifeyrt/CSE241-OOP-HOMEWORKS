#ifndef SCHOOLMANAGEMENTSYSTEM_H
#define SCHOOLMANAGEMENTSYSTEM_H
#include <string>
#include <iostream>
#include "course.h"
#include "student.h"

using namespace std;
namespace PA4{

class SchoolManagementSystem{
private:

int student_size;
int course_size;

public:
Student *student_ref;
Course *course_ref;
SchoolManagementSystem();
SchoolManagementSystem(const SchoolManagementSystem& oth);
//void setstudentref(Student *student_ref_,int size);
//void setcourseref(Course *course_ref_,int size);
//int getstudentref();
//int getcourseref();
void setstudent_size(int s_size);
void setcourse_size(int c_size);
int getstudent_size();
int getcourse_size();

void Menu();
void Student_menu();
void Select_student();
void Course_menu();
void Select_course();
void Listallstudent_menu();
void Listallcourse_menu();
~SchoolManagementSystem();







};
}
#endif