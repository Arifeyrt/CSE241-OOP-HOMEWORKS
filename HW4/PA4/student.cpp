#include "student.h"
#include "course.h"

namespace PA4{
Student::Student() {
    student_name = "";
    ID = 0;
    size = 0;
    course_ref = nullptr;
}

Student::Student(string name, int Id) {
    student_name = name;
    ID = Id;
    size = 0;
    course_ref = nullptr;
}

Student::Student(const Student &C) {
    student_name = C.student_name;
    ID = C.ID;
    size = C.size; 
    course_ref = new Course [size];
    for(int i=0;i<size;i++){
        course_ref[i]=C.course_ref[i];
    }
}

int Student::getsize() {
    return size;
}

int Student::getId() {
    return ID;
}

string Student::getname() {
    return student_name;
}

void Student::setsize(int size_) {
    size = size_;
}

void Student::setId(int Id) {
    ID = Id;
}

void Student::setname(string name) {
    student_name = name;
}

Student& Student::operator=(const Student &C) {
    student_name = C.student_name;
    ID = C.ID;
    size = C.size;
    course_ref = new Course[size];
            for(int i=0; i<size; i++){
                course_ref[i] = C.course_ref[i];
            }
        
    return *this;
}

void Student::addcourse(Course c){
       if (size == 0) {
        course_ref = new Course[1];
        course_ref[0] = c;
        size = 1;
    }
    else{
    Course *temp = new Course[size + 1];
    for (int i = 0; i < size; i++) {
            temp[i] = course_ref[i];
        }
    delete[] course_ref;
    temp[size] = c;
    course_ref = temp;
    size++;

    }
}

void Student::delete_course(Course c){
int index=-1;
for (int i = 0; i < size; i++)
    {
       if (course_ref[i].getcourse_code()== c.getcourse_code())
        {
            index = i; // Store the index of the string to be deleted
            break;
        }
    }
    if (index == -1 ){
Course *temp = new Course[size-1];
for (int i = 0; i < index + 1; i++) {
            temp[i] = course_ref[i];
        }
        for(int i=index+1;i<size;i++){
            temp [i-1] = course_ref[i];
        }
    delete[] course_ref;
    course_ref = temp;
    size--;
}
}

Student::~Student() {
    delete[] course_ref;
}}