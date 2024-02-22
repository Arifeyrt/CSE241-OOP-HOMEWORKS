#include "roomba.h"

roomba::roomba() : Robot(2,3,10,"roomba") {}
roomba::roomba(world* W, int x_, int y_):Robot(2,3,10,W,x_,y_) {}


string roomba::getType(){
   return robotname;//robot is name
}

int roomba::getDamage(){////the roomba robot has 2 times the power
    int damage_1=Robot::getDamage();
    int damage_2=Robot::getDamage();
    int damage=damage_1+damage_2;
    return damage;

}
roomba::~roomba(){};
