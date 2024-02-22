#include "course.h"
#include "student.h"

using namespace std;
namespace PA4{
Course::Course(){
    course_name=" ";
    course_code=" ";
    size=0;
    student_ref=nullptr;

}

Course::Course(string name, string code) {
    course_name = name;
    course_code=code;
    size = 0;
    student_ref = nullptr;
}

Course::Course(const Course &C) {
    course_name = C.course_name;
    course_code=C.course_code;
    size = C.size;
    student_ref = new Student [size];
    for(int i=0;i<size;i++){
        student_ref[i]=C.student_ref[i];
    }
}

void Course::setsize(int size_) {
    size = size_;
}

void Course::setcourse_code(string code) {
   course_code = code;
}

void Course::setcourse_name(string name) {
    course_name = name;

}
int Course::getcourse_size() {
    return size;
}

string Course::getcourse_code() {
    return course_code;
}

string Course::getcourse_name() {
    return course_name;
}

Course &Course::operator=(const Course &C){

     if (this == &C) {
        return *this;
    }
    
    course_name = C.course_name;
    course_code = C.course_code;
    size = C.size;
    student_ref = new Student[size];
            for(int i=0; i<size; i++){
                student_ref[i] = C.student_ref[i];
            }
        
    return *this;
    

}

void Course::addstudent(Student s){
if (size==0) {
    size = 1;
    student_ref = new Student[size];
    student_ref[0] = s;
}
else{
    Student *temp = new Student[size + 1];
    for (int i = 0; i < size; i++) {
            temp[i] = student_ref[i];
        }
    delete[] student_ref;
    temp[size] = s;
    student_ref = temp;
    size++;

    }
}

void Course::delete_student(Student s){
int index=-1;
for (int i = 0; i < size; i++)
    {
       if (student_ref[i].getId() ==s.getId())
        {
            index = i; // Store the index of the string to be deleted
            break;
        }
    }
Student *temp = new Student[size-1];
for (int i = 0; i < index; i++) {
            temp[i] = student_ref[i];
        }
        for(int i=index+1;i<size;i++){
            temp[i-1]=student_ref[i];
        }
    delete[] student_ref;
    student_ref = temp;
    size--;
    delete[] temp;

}


Course::~Course() {
    delete[] student_ref;
}}