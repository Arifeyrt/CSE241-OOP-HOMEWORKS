#ifndef ROBOCOP_H
#define ROBOCOP_H
#include <string>
#include "humanic.h"
#include "Robot.h"
using namespace std;

class robocop : public humanic{
     friend class world;
public:
   robocop();  // Constructor
   robocop(int newType, int newStrength, int newHit, string name); // Constructor
   robocop(world* W, int x_, int y_); // Constructor
  

   int getDamage();//trun damage
   string getType();//turn robot type

   ~robocop();//destructor
  

};



#endif