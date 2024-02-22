#include<iostream>
using namespace std;

template <typename T>
class Set{
public:
int size;
T *array;
Set<T>(){
array = NULL;
size = 0;
}
Set(T data){
size = 0;
array = new T[1];
array[0] = data;
size++;
cout<<"Set initialized with "<<data<<endl;
}
void add(T data){
T *temp = new T[size+1];
for(int i=0; i<size; i++){
temp[i] = array[i];
}
temp[size] = data;
size++;
delete[] array;
array = temp;
cout<<data<<" added successfully!"<<endl;
}
void display(){
for(int i=0; i<size; i++)
cout<<array[i]<<" ";
cout<<endl;
}
};

int main(){
cout<<"Integer Set"<<endl;
Set<int> s1(10);
s1.add(22);
s1.add(30);
cout<<"Elements in set are ";
s1.display();
cout<<"Size of set: "<<s1.size<<endl;

cout<<"\nString Set"<<endl; 
Set<string> s2("AB"); 
s2.add("BC"); 
s2.add("CD"); 
s2.add("DE"); 
cout<<"Elements in set are "; 
s2.display(); 
cout<<"Size of set: "<<s2.size<<endl; 

cout<<"\nFloat Set"<<endl; 
Set<float> s3(22.5f); 
s3.add(31.2f); 
s3.add(12.6f); 
cout<<"Elements in set are "; 
s3.display(); 
cout<<"Size of set: "<<s3.size<<endl; 
}