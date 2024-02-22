#ifndef WORLD_H
#define WORLD_H
#include <string>
//tüm dünyam
#include "Robot.h"


using namespace std;

const int INITIALANTS=5;
const int WORLDSIZE=10;
const int ROOMBA=2;
const int BULLDOZER=3;
const int ROBOCOP=1;
const int OPTIMUSPRIMA=0;




class Robot;
class bulldozer;
class roomba;
class optimusprime;
class robocop;

class world {
friend class Robot;
friend class bulldozer;
friend class roomba;
friend class optimusprime;
friend class robocop;

public:
   world();  // Constructor
   
   Robot* getrob(int x,int y);//assigned x and y
   void setrob(int x,int y,Robot *rob);
   void display();//similasyon
   bool onestep();
   bool fight(Robot* attacker,Robot* victim );//fight function
    ~world();//destructor
   void winner();
private:
   int numberOfRobots;
   Robot* grid[WORLDSIZE][WORLDSIZE];


};

#endif