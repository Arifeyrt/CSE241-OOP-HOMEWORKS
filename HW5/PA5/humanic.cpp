#include "humanic.h"

humanic::humanic() : Robot() {
}
   
humanic::humanic(int newType, int newStrength, int newHit, string name):Robot(newType,newStrength,newHit,name){}

humanic::humanic(int newType, int newStrength, int newHit, world* W, int x_, int y_):Robot( newType,newStrength,newHit,W, x_,  y_){}

int humanic::getDamage(){
    int damage;
    damage=Robot::getDamage();
     if ((rand() % 100) < 10) {//+50 point
        damage += 50;
        return damage;
    }
    else{
    return damage;}
}
humanic::~humanic(){}