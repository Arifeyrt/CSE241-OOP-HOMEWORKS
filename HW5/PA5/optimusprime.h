#ifndef OPTIMUSPRIME_H
#define OPTIMUSPRIME_H
#include <string>
#include "Robot.h"
#include "humanic.h"
using namespace std;

class optimusprime : public humanic{
     friend class world;
public:
   optimusprime();  // Constructor
   optimusprime(int newType, int newStrength, int newHit, string name);//constructor
   optimusprime(world* W, int x_, int y_);//constructor
   

   int getDamage();//get damage
   string getType();//get robot type
 
   ~optimusprime();

};

#endif