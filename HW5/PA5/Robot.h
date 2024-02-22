#ifndef ROBOT_H
#define ROBOT_H
#include <string>
#include "world.h"

using namespace std;

class world;
class Robot {

friend class world;
public:
  Robot();  // Constructor
  Robot(int newType, int newStrength, int newHit, string name);//// Constructor
  Robot(world* W, int x_, int y_);// Constructor
  Robot(int newType,int newStrength,int newHit,world* W, int x_, int y_);// Constructor
  //************SET**************//
  void settype(int type_);
  void setStength(int strength_);
  void setRname(string robot_name);
  void setHit(int newhits);

  //***********GET*****************//
  int gettype();
  int getStrength();
  int getHit();
  string getRname();
  
  void move(int& a,int& b);//MOVE FUNCTİONS
  virtual int getDamage()=0;//RANDOM DAMAGE
  virtual string getType()=0;
  void sethit(int damage);
  virtual ~Robot();//DESTRUCTOR

protected:
  int type;
  int strength;
  int hitpoint;
  string robotname;
  world* World;
  int x;
  int y;
  bool moved;
  

};

#endif