#include <iostream>
#include <cstdlib>
#include "stack.h"

using namespace std;

template<class T>
Stack<T>::Stack(): top(NULL){}

template<class T>
Stack<T>::Stack(const Stack<T>& aStack){
    if(aStack.isEmpty()) top=NULL;
    else{
        Node<T>* temp=aStack.top;
        Node<T>* end;
        end = new Node<T>(temp->getData(),temp->getLink());
        top=end;
        temp=temp->getLink();
        while(temp!=NULL){
            end->setLink(new Node<T>(temp->getData(),NULL));
            temp=temp->getLink();
            end = end->getLink();
        }
    }
}

template<class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& rigthSide){
    if(top==rigthSide.top) return *this;
    else{
        T next;
        while(!isEmpty()) next = pop();
    }
    if(rigthSide.isEmpty()){
        top=NULL;
        return *this;

    }
    else{
        Node<T> *temp= rigthSide.top;
        Node<T> *end;
        end= new Node<T>(temp->getData(), NULL);
        top= end;
        temp = temp->getLink();
        while( temp!=NULL){
            end->setLink(new Node<T>(temp->getData(),NULL));
            temp=temp->getLink();
            end = end->getLink();
        }
        return *this;
    }
}

template<class T>
Stack<T>::~Stack(){
    T next;
    while(!isEmpty()) next = pop();
}

template<class T>
bool Stack<T>::isEmpty() const{
    return (top==NULL);
}


template <class T>
void Stack<T>::push(T stackFrame){
    top = new Node<T>(stackFrame,top);
}


template<class T>
T Stack<T>::pop(){
    if(isEmpty()){
        throw PopEmptyStackException();
    }
    else {
        T result = top->getData();
        Node<T>* discard;
        discard = top;
        top = top->getLink();
        delete discard;
        return result;
    }
}


int main(){

    Stack<int> s;
    s.push(4);
    s.push(10);
    s.push(54);

    try{
        cout<<s.pop()<<endl;
        cout<<s.pop()<<endl;
        cout<<s.pop()<<endl;
        cout<<s.pop()<<endl;
    }
    catch(PopEmptyStackException){
        cout<< "Tried to pop an empty stack!"<<endl;
    }


    return 0;

}