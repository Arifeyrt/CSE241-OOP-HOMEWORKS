#ifndef HUMANIC_H
#define HUMANIC_H
#include <string>
#include "Robot.h"
using namespace std;

class humanic : public Robot{

     friend class world;
public:
   humanic();  // Constructor
   humanic(int newType, int newStrength, int newHit, string name); // Constructor
   humanic(int newType, int newStrength, int newHit,world* world, int x, int y); // Constructor


   int getDamage();//get damage
   virtual string getType()=0;
   ~humanic();


};

#endif