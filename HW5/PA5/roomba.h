#ifndef ROOMBA_H
#define ROOMBA_H
#include <string>
#include "Robot.h"
using namespace std;

class roomba : public Robot{

    friend class world;
public:
   roomba();  // Constructor
   roomba(world* W, int x_, int y_);//constructor
   int getDamage(); //turn damage
   string getType();//trun robot type
    ~roomba();//destructor

};

#endif