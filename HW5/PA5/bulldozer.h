#ifndef BULLDOZER_H
#define BULLDOZER_H
#include <string>
#include "Robot.h"

using namespace std;

class world;

class bulldozer : public Robot{
   friend class world;
public:
   bulldozer();  // Constructor
   bulldozer(world* W, int x_, int y_);//constructor
   int getDamage();
   string getType();
   ~bulldozer();



};

#endif