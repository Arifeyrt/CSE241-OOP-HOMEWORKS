#include "optimusprime.h"

optimusprime::optimusprime () : humanic(0,100,100,"optimusprime") {
}

optimusprime::optimusprime(world* W, int x_, int y_):humanic( 0,100,100,W, x_,  y_){}


string optimusprime::getType(){
    return robotname;//return robot is name
}

int optimusprime::getDamage() {
    int damage = humanic::getDamage();

    // 15% chance of strong attack
    if ((rand() % 100) < 15) {
        damage *= 2;//double attack
        return damage;
    }else{
    return damage;
 }
}

optimusprime::~optimusprime(){}
