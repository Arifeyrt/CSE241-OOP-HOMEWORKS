#include <iostream>
#include "world.h"
using namespace std;
world::world(){
    int i,j;
//worldun builder here I am creating the field.i'm nullifying the beginnings    int i,j;
    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            grid[i][j] = NULL;
        }
    }
}
Robot* world::getrob(int x, int y){ //turning the places of the robot object
    if(x >= 0 && (x < WORLDSIZE) && y >= 0 && (y<WORLDSIZE))
        return grid[x][y];  

    return NULL;
}

void  world::setrob(int x,int y,Robot* rob){//i'm adding the robot to a specific location
 if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
    {
    grid[x][y] = rob;


}
}
void world::display() {//i place the robots in their places on the field
    int i,j;
    cout << endl << endl;
    for(j = 0; j < WORLDSIZE;j++) {
        for(i = 0;i < WORLDSIZE;i++) {
            if(grid[i][j] == NULL)
                cout << ".";
            else if(grid[i][j]->gettype()==0) 
                cout << "X"; 
            else if(grid[i][j]->gettype()==1) 
                cout << "Y";
            else if(grid[i][j]->gettype()== 2) 
                cout << "Z";
            else if(grid[i][j]->gettype()== 3) 
                cout << "K";
         
        }
        cout << endl;}}

bool world::onestep(){
 int i,j;

 int robotsay=0;
//I point out that all the robots in the field have never moved by scanning yet
    for(i = 0; i < WORLDSIZE;i++) {
        for(j = 0;j < WORLDSIZE;j++) {
            if(grid[i][j] != NULL) grid[i][j]->moved = false;
        }
    }
    for(i = 0; i < WORLDSIZE;i++) {
        for(j = 0;j < WORLDSIZE;j++) {
            if((grid[i][j] != NULL) ) {
                if(grid[i][j]->moved == false) {
                
                    grid[i][j]->moved = true;
                    int a = -1,b = -1;
                    grid[i][j]->move(a,b);
                    if(a != -1) {
                        delete (grid[a][b]);
                        grid[i][j] = NULL;
                        
                    }
                }
            }
        }
    }

    for(i = 0; i < WORLDSIZE;i++) {
        for(j = 0;j < WORLDSIZE;j++) {
            if((grid[i][j] != NULL) ) {
        robotsay++;
      
            }
        }
     }
     if(robotsay==1){
        return true;
     }
     else return false;
}
void world::winner(){//PRINTING THE WINNING ROBOT
    int i,j;
    if(onestep()==true){
        for(i = 0; i < WORLDSIZE;i++) {
        for(j = 0;j < WORLDSIZE;j++) {
            if((grid[i][j] != NULL) ) {
                cout<< "WINNER ROBOT  "<<grid[i][j]->getRname()<<endl;
      
            }
        }
     }

    }

}


bool world::fight(Robot* attacker,Robot* victim){
int damage;
int dead=0;//dead flag
cout<<endl;
//get dmage and hit until pne of them is dead
do{
damage=attacker->getDamage();//getting the damage value from the attacker
cout<<attacker->getRname()<<" hits "<<victim->getRname()<<" with "<<damage<<endl;
victim->sethit(damage);//getting the damage value from the victem
cout<<" the new hitpoints of "<<victim->getRname()<<" "<< victim->getHit()<<endl;

if(victim->getHit()<=0){//if the victeim is dead turn the flag into one and exit the loog
    cout<<"DEAD: "<<victim->getRname()<<endl;
    dead=1;
}

else{
damage=victim->getDamage();
cout<<victim->getRname()<<" hits "<<attacker->getRname()<<" with "<<damage<<endl;
attacker->sethit(damage);
cout<<" the new hitpoints of "<<attacker->getRname()<<" "<<attacker->getHit()<<endl;

if(attacker->getHit()<=0){
    dead=2;
    cout<<"DEAD: "<<attacker->getRname()<<endl;
}
}
}while(dead == 0);

    if(dead == 1){//attacker wons
        return true;
    }

    else{return false;}   //victim wons 

}

world::~world(){//destructer
    int i,j;
    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            if(grid[i][j] != NULL) delete grid[i][j];
        }
    }
}
