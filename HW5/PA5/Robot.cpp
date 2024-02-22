#include "Robot.h"
#include <iostream>
using namespace std;
///////////////////***************ROBOT CLASS***************/////////////////////////////
Robot::Robot() {//default constructor
    type=0;
    strength=0;
    hitpoint=0;
    robotname="";
    x=0;
    y=0;
    World=NULL;
    moved=false;

}

Robot::Robot(int newType, int newStrength, int newHit, string name){//constructer
    robotname=name;
    type=newType;
    strength=newStrength;
    hitpoint=newHit;
}

Robot::Robot(world* W, int x_, int y_){//constructer
    type=0;
    strength=0;
    hitpoint=0;
    robotname="";
    x=x_;
    y=y_;
    moved=false;
    this ->World= W;
    World->setrob(x,y,this);

}
Robot::Robot(int newType,int newStrength,int newHit,world* W, int x_, int y_){//constructer
    type=newType;
    strength=newStrength;
    hitpoint=newHit;
    x=x_;
    y=y_;
    moved=false;
    this ->World= W;
    World->setrob(x,y,this);
}
/************SET************/
void Robot::settype(int type_){
    type=type_;
}

void Robot::setStength(int strength_){
    strength=strength_;
}
void Robot::setRname(string robot_name){
    robotname=robot_name;
}

void Robot::setHit(int newhits){   
    hitpoint=newhits;
}

/*************GET******************/
int Robot::gettype(){
    return type;
}

int Robot:: getStrength(){
    return strength;
}
   
int Robot::getHit(){
    return hitpoint;
}

string Robot:: getRname(){
    return robotname;
}

int Robot::getDamage(){//getting random damage
int damage; 
damage=rand() % strength;
return damage;
}

void Robot::sethit(int damage) {//hit target mean that we will takr from our hitpoints with the damege value
    hitpoint-= damage;
}

void Robot::move(int& a,int& b){

   //if there is a robot on the right of the robot, on the left, down or up, he fights with it
    if((y > 0) && (World->getrob(x, y-1) != NULL)){
     if( World->fight(World->getrob(x,y),World->getrob(x,y-1))==true){
        delete (World->grid[x][y-1]);//delete victim
        World->grid[x][y-1] = this;
        World->setrob(x,y,NULL);
        y--;
     }
     else{
     a=x;
     b=y;
     moved=true;
     }
     return;
    }
    
    //if there is a robot on the right of the robot, on the left, down or up, he fights with it
    else if ((y<WORLDSIZE-1) && (World->getrob(x,y+1)!=NULL)){
       if( World->fight(World->getrob(x,y),World->getrob(x,y+1))==true){
        delete (World->grid[x][y+1]); //delete victim
        World->grid[x][y+1] = this;  
        World->setrob(x,y,NULL); 
        y++;
       }
    else{
     a=x;
     b=y;
     moved=true;
     }
    return; 
    }
    
    //if there is a robot on the right of the robot, on the left, down or up, he fights with it
    else if ((x>0) && (World->getrob(x-1,y)!=NULL) ) {
    if(World->fight(World->getrob(x,y),World->getrob(x-1,y))==true){
        delete (World->grid[x-1][y]);  //delete victim
        World->grid[x-1][y] = this;   
        World->setrob(x,y,NULL); 
        x--;
      
    }
    else{
     a=x;
     b=y;
     moved=true;
     }
    return;
    }
    
    //if there is a robot on the right of the robot, on the left, down or up, he fights with it
    else if ((x<WORLDSIZE-1) && (World->getrob(x+1,y)!=NULL)){
       if(World->fight(World->getrob(x,y),World->getrob(x+1,y))==true){
        delete (World->grid[x+1][y]);  //delete victim
        World->grid[x+1][y] = this;   
        World->setrob(x,y,NULL);   
        x++;
       }
    else{
     a=x;//victim won
     b=y;
     moved=true;
    }
    return;
       
    }
    


  int dir;
  int lastMove = -1; // İlk başta geçmiş hareket bilgisi yok
  int prevx;//holds the value of the x and y that we get from the start
  int prevy;

    do {
        dir = rand() % 4; //random  turn

        // Make the necessary checks to move in the selected direction

        if (dir == 0 && y > 0 && World->getrob(x, y - 1) == NULL && (y-1 != prevy)) {
            World->setrob(x, y - 1, World->getrob(x, y));
            World->setrob(x, y, NULL);
            y--;
            moved=true; 
        } 
        prevx= x;
        prevy =y;

        // Make the necessary checks to move in the selected direction

        if (dir == 1 && y < WORLDSIZE - 1 && World->getrob(x, y + 1) == NULL && (y+1 != prevy)) {
            World->setrob(x, y + 1, World->getrob(x, y));
            World->setrob(x, y, NULL);
            y++;
            moved=true;
        }
        prevx= x;
        prevy =y;
        
        // Make the necessary checks to move in the selected direction
        if (dir == 2 && x > 0 && World->getrob(x - 1, y) == NULL && (x-1 != prevx)) {
            World->setrob(x - 1, y, World->getrob(x, y));
            World->setrob(x, y, NULL);
            x--;
            moved=true;
        } 
        prevx= x;
        prevy =y;

        // Make the necessary checks to move in the selected direction
         if (dir == 3 && x < WORLDSIZE - 1 && World->getrob(x + 1, y) == NULL && (x+1 != prevx)) {
            World->setrob(x + 1, y, World->getrob(x, y));
            World->setrob(x, y, NULL);
            x++;
            moved=true;
        }
        prevx= x;
        prevy =y;
        
    } while (!moved); //in cases where he has not moved before, he enters donguye
}

Robot::~Robot(){}