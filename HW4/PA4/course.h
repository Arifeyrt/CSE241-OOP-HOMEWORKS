#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <string>
#include "student.h"

using namespace std;
namespace PA4{
class Student;

class Course{

    private:
    string course_name;
    string course_code;
    int size;
    

    public:
    Student *student_ref; 
Course();
Course(string name, string code);
Course(const Course &C);

int getcourse_size();
string getcourse_code();
string getcourse_name();
void setsize(int size_);
void setcourse_code(string code);
void setcourse_name(string name);
Course &operator=(const Course &C);
void addstudent(Student s);
void delete_student(Student s);

~Course();

};
}
#endif