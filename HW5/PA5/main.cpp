#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

#include "world.h"
#include "Robot.h"
#include "bulldozer.h"
#include "roomba.h"
#include "humanic.h"
#include "optimusprime.h"
#include "robocop.h"


using namespace std;


int main(){
    srand(time(NULL));
    world w;

    int robotcount = 0;
    //sets random locations for robots
    while(robotcount < INITIALANTS){
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if(w.getrob(x, y) == NULL){
            robotcount++;
            roomba* room = new roomba(&w, x, y);
            room->setRname("roomba_" + to_string(robotcount - 1));
        }
    }

    //sets random locations for robots
    robotcount=0;
    while(robotcount < INITIALANTS){
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if(w.getrob(x, y) == NULL){
            robotcount++;
            bulldozer* bull= new bulldozer(&w, x, y);
            bull->setRname("bulldozer_" + to_string(robotcount - 1));
        }
    }
    //sets random locations for robots
    robotcount=0;
     while(robotcount < INITIALANTS){
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if(w.getrob(x, y) == NULL){
            robotcount++;
            optimusprime* prime= new optimusprime(&w, x, y);
            prime->setRname("optimusprime_" + to_string(robotcount - 1));
        }
    }
    //sets random locations for robots
    robotcount=0;
     while(robotcount < INITIALANTS){
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if(w.getrob(x, y) == NULL){
            robotcount++;
            robocop* robo = new robocop(&w, x, y);
            robo->setRname("robocop_" + to_string(robotcount - 1));

        }
    }
   
while(w.onestep()==false){////fight until a robot wins
//w.display();
w.onestep();
}
w.winner();
    return 0;

}