#ifndef STACK_H
#define STACK_H
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
// Exce p t i on c l a s s f o r popp ing
// an empty s t a c k
// ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗
class PopEmptyStackException{} ;
template<class T>
class Node{

public :
Node (T theData , Node<T>* theLink ) :
data (theData) ,link( theLink ) {}
Node<T>* getLink ( ) const { return link ; }
const T getData ( ) const { return data ; }
void setData ( const T& theData ) { data = theData ; }
void setLink ( Node<T>* pointer ) { link = pointer ; }
private :
T data ;
Node<T> * link ;
} ;


template<class T>
class Stack
{
public :
Stack ( ) ;
Stack ( const Stack<T>& aStack ) ;
Stack<T>& operator =(const Stack<T>& rightSide ) ;
virtual ~ Stack ( ) ;
void push (T stackFrame ) ;
T pop ( );
bool isEmpty ( ) const ;
private :
Node<T> * top ;
} ;

#endif