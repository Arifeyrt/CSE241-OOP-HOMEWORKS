#include "bulldozer.h"

bulldozer::bulldozer() : Robot(3,50,200,"bulldozer") {}    

bulldozer::bulldozer(world* W, int x_, int y_): Robot(3,50,200,W,x_,y_){}


string bulldozer::getType(){
    return robotname;//get robot is name
}

int bulldozer::getDamage() {
    int damage = Robot::getDamage();
    return damage;
}

bulldozer::~bulldozer(){}