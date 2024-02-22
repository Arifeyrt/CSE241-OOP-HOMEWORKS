#include "SchoolManagementSystem.h"

namespace PA4
{
void setname_id_student(string& name,int& id);
void setname_code_course(string& name,string& code);


SchoolManagementSystem::SchoolManagementSystem(){
    student_ref=nullptr;
    course_ref=nullptr;
    student_size=0;
    course_size=0;
}

SchoolManagementSystem::SchoolManagementSystem(const SchoolManagementSystem& oth) {
student_size=oth.student_size;//sets size value for course
course_size=oth.course_size;//sets size valu for course

course_ref=new Course[course_size];
for(int i=0;i<course_size;i++){
   course_ref[i]=oth.course_ref[i];//sets course objets
}

student_ref=new Student[student_size];
for(int i=0;i<student_size;i++){
   student_ref[i]=oth.student_ref[i]; //sets student objets
}

}



SchoolManagementSystem::~SchoolManagementSystem(){
if(course_ref!= nullptr) {
            delete[] course_ref; 
        }

if(student_ref != nullptr) {
            delete[] student_ref; 
        }

}

void SchoolManagementSystem::setstudent_size(int s_size){student_size=s_size;}
void SchoolManagementSystem::setcourse_size(int c_size){course_size=c_size;}
int SchoolManagementSystem::getstudent_size(){return student_size;}
int SchoolManagementSystem::getcourse_size(){return course_size;}

void SchoolManagementSystem::Menu(){
int choice=5;
do{
    cout<< "Main_menu"<<endl;
    cout<< "0 exit"<<endl;
    cout<< "1 student"<<endl;
    cout<< "2 course"<<endl;
    cout<< "3 list_all_students" << endl;
    cout<< "4 list_all_courses" << endl;
    cout<<">> ";
    cin >> choice;

    switch(choice){
        case 0://exit
        exit(0);
        break;
        
        case 1://student
          Student_menu();
        break;

        case 2://coruse
          Course_menu();
        break;

        case 3://list all student
           Listallstudent_menu();
        break;

        case 4://list all course
           Listallcourse_menu();
        break;
    
    }
}while(choice!=5);
} 


void SchoolManagementSystem::Student_menu(){
    int choice=5;
    do{
        cout << "0 up" << endl;
        cout << "1 add_student" << endl;
        cout << "2 select_student" << endl;
        cout << ">> ";
        cin >> choice;
        string name;
        int id;
        Student *temp=new Student[student_size+1];//ekleme yapıcaz hepsini tempe atıyoruz
        switch(choice){
            case 0:
                Menu();
                break;
            case 1://add student
    
                setname_id_student(name,id);
                for(int i = 0;i < student_size;i++) {
                    temp[i] = student_ref[i]; // Set student objects one by one
                }
                delete[] student_ref;//siliyoruz
                temp[student_size]=Student(name,id);  
                student_size++;
                student_ref=temp;
                break;
            case 2:
                Select_student();
                break;
        }
    }while(choice != 5);
}
void  SchoolManagementSystem::Select_student(){
   string name;
   int select;
   int id;
   int choice=5;
   setname_id_student(name,id);
    //ogrencinin arlığını yoklugunu jontrol et
   for(int i = 0;i < student_size;i++) {
            if(student_ref[i].getId() == id) {
                select= i;//hangi indexteki öğrenciyi seçtim
                break;
                 }     
        }
    do{
            cout << "0 up" << endl;
            cout << "1 delete_student" << endl;
            cout << "2 add_selected_student_to_a_course" << endl;
            cout << "3 drop_selected_student_from_a_course" << endl;
            cout << ">> ";
            cin >> choice;
             int t=1;
      int choice_course;
      Course *tempcourse=new Course[course_size];
      Student *temp = new Student[student_size-1];
       int size=course_size-student_ref[select].getsize();

      switch(choice){

      case 0:
      Student_menu();
      break;

      case 1://delete student
      for(int i=0;i<course_size;i++){
        for(int j=0;j<course_ref[i].getcourse_size();j++){
            if(course_ref[i].student_ref[j].getId()==student_ref[select].getId()){
                course_ref[i].delete_student(student_ref[select]);//sor
            }
        }
      }
     for (int i = 0; i < select; i++) {
            temp[i] = student_ref[i];
        }
        for(int i=select+1;i<student_size;i++){
            temp[i-1]=student_ref[i];
        }
    for(int i=0;i<student_size-1;i++){
        cout<<temp[i].getname()<<" " << temp[i].getId()<<endl;//silindikten sonra ogrenci listesi
    }
    delete[] student_ref;
    student_ref = temp;
    student_size--;
    delete[] temp;
    break;
      case 2://sectiğin ögrenciyi bir kursa ekle
      cout<<"0 up"<<endl;
      //bütün kursları listele
      for(int i=0;i<course_size;i++){
      tempcourse[i]=course_ref[i];
      }
      for (int i = 0; i < course_size; i++) {
            bool is_enrolled = false;
            for (int j = 0; j < student_ref[select].getsize(); j++) {
              if (tempcourse[i].getcourse_code() == student_ref[select].course_ref[j].getcourse_code()) {
                    is_enrolled = true;
                    break;
                    }
                }
                    if (!is_enrolled) {
                        cout << t << " "<< tempcourse[i].getcourse_name() <<" " << tempcourse[i].getcourse_code() << endl;
                        t++;
                    }
                }

      
      cout<<">> ";
      cin>> choice_course;
     
       if(choice_course <= 0 || choice_course > size) {

        }
       else {
        student_ref[select].addcourse(tempcourse[choice_course-1]);

       }
       delete[]tempcourse;
       break;
       case 3:// drop_selected_student_from_a_course (this will list the courses which are taken by the student)
       break;
    }}while(choice!=5);
    

}

void  SchoolManagementSystem::Course_menu(){
    int choice=5;
        // Loop until user choose zero
        do {
            cout << "0 up" << endl;
            cout << "1 add_course" << endl;
            cout << "2 select_course" << endl;
            cout << ">> ";
            cin >> choice;
            string name = "";
            string code = "";
            Course *temp=new Course[course_size+1];//ekleme yapıcaz hepsini tempe atıyoruz
         switch(choice){
                case 0:
                Menu();
                break;
                case 1:
                setname_code_course(name,code);
        
        for(int i = 0;i < course_size;i++) {
                 temp[i] = course_ref[i]; // Set student objects one by one
        }
        delete[]course_ref;//siliyoruz
        temp[course_size]=Course(name,code);  
        course_size++;
        course_ref=temp;
        Course_menu();
        break;
        case 2:
        Select_course();
        Course_menu();
        break;
         }
}while(choice!=5);


}
void SchoolManagementSystem::Select_course(){
    int choice=5;
    int select;
    string name = "";
    string code = "";
    setname_code_course(name,code); // Call function and get name and code values from user
    for(int i = 0;i < course_size;i++) {
            if(course_ref[i].getcourse_code() == code) {//seçilen kurs
                select = i;
                break;
            }
        }

   do{
            cout << "0 up" << endl;
            cout << "1 delete_course" << endl;
            cout << "2 list_students_registered_to_the_selected_course" << endl;
            cout << ">> ";
            cin >> choice;
             Course *temp = new Course[course_size-1];

   switch(choice){
    case 0:
    Course_menu();
    break;
    case 1://delete course
    for(int i=0;i<student_size;i++){
        for(int j=0;j<student_ref[i].getsize();j++){
            if(student_ref[i].course_ref[j].getcourse_code()==course_ref[select].getcourse_code()){
                student_ref[i].delete_course(course_ref[select]);
            }
        }
      }
   
     for (int i = 0; i < select; i++) {
            temp[i] = course_ref[i];
        }
        for(int i=select+1;i<course_size;i++){
            temp[i-1]=course_ref[i];
        }
    delete[] course_ref;
    course_ref = temp;
    course_size--;
    delete[] temp;
      break;

    case 2://2 list_students_registered_to_the_selected_course"
    for(int i=0;i<course_ref[select].getcourse_size();i++){
        cout<<i+1<<" "<<course_ref[select].student_ref[i].getname()<< " "<<course_ref[select].student_ref[i].getId()<<endl;
    }
    break;
   }

   }while(choice!=5);
}


void SchoolManagementSystem::Listallstudent_menu(){
    // List all students
        for(int i = 0;i < student_size;i++) {
            cout << student_ref[i].getname()<<" " <<  student_ref[i].getId()<< endl;
        }
}
void SchoolManagementSystem::Listallcourse_menu(){
     // List all courses
        for(int i = 0;i < course_size;i++) {
            cout << course_ref[i].getcourse_name()<<" "<<course_ref[i].getcourse_code() << endl;
        }
}


void setname_id_student(string& name,int& id){
 string line;
 string num = "";

cout << ">> ";
getline(cin, line); // Klavyeden okuma yapılıyor ve tamamı "line" değişkenine atılıyor

// "line" içerisindeki karakterleri tek tek kontrol ediyoruz
    for(char c : line) {
        if(c == ' ') { // Eğer karakter boşluk ise isim ve ID'yi ayırmışız demektir, döngüden çıkıyoruz
            break;
        } else if(c > 47 && c < 58) { // Eğer karakter bir sayı ise, ID'ye ekliyoruz
            num += c;
        } else { // Değilse karakter isim içindir
            name += c;
        }
    }

    // Son olarak, string formatındaki ID'yi integer'a çeviriyoruz
    id = stoi(num);
}


void setname_code_course(string& name,string& code){
        cout << ">> ";
        cin.ignore(2,'\n');
        getline(cin, code, ' ');
        getline(cin, name);
    
}

}



