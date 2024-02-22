#include "robocop.h"
#include "humanic.h"

robocop::robocop() : humanic(1,30,40,"robocop") {

}
robocop::robocop(world* world_, int x_, int y_):humanic( 1,30,40,world_, x_,  y_){}


string robocop::getType(){
 return robotname;//turn robot is name
}
int robocop::getDamage() {//get the damage of the humanşc function
    int damage = humanic::getDamage();
    return damage;
}

robocop::~robocop(){}

