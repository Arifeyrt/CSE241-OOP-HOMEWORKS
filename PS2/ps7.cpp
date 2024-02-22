#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

const int WORLDSIZE = 20;
const int INITIALANTS = 100;
const int INITIALBUGS = 5;
const int DOODLEBUG = 1;
const int ANT = 2;
const int ANTBREED = 3;
const int DOODLEBREED = 8;
const int DOODLESTARVE = 3;

class Organism;
class Doodlebug;
class Ant;

class World{
    friend class Organism;
    friend class Doodlebug;
    friend class Ant;

    public:
        World();
        ~World();
        Organism* getAt(int x, int y);
        void setAt(int x, int y, Organism *org);
        void Display();
        void SimulateOneStep(); 

    private:
        Organism* grid[WORLDSIZE][WORLDSIZE];
};

class Organism{
    friend class World;

    public: 
        Organism();
        Organism(World* world, int x, int y);
        ~Organism();
        virtual void breed() = 0;
        virtual void move() = 0;
        virtual int getType() = 0;
        virtual bool starve() = 0;

    protected:
        int x,y;
        bool moved;
        int breedTicks;
        World* world;

};

class Ant : public Organism{
    friend class World;

    public:
        Ant();
        Ant(World* world, int x, int y);
        void breed();
        void move();
        int getType() ;
        bool starve(){
            return false;
        }

};

class Doodlebug : public Organism{
    friend class World;

    public:
        Doodlebug();
        Doodlebug(World* world, int x, int y);
        void breed();
        void move();
        int getType() ;
        bool starve();

    private:
        int starveTicks;

};

World::World(){
    int i,j;
    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            grid[i][j] = NULL;
        }
    }
}

World::~World(){
    int i,j;
    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            if(grid[i][j] != NULL) delete grid[i][j];
        }
    }
}


Organism* World::getAt(int x, int y){
    if(x >= 0 && (x < WORLDSIZE) && y >= 0 && (y<WORLDSIZE))
        return grid[x][y];  

    return NULL;
}

void World::setAt(int x, int y, Organism *org)
{
    if ((x>=0) && (x<WORLDSIZE) && (y>=0) && (y<WORLDSIZE))
    {
    grid[x][y] = org;
}
}

void World::Display(){
    int i,j;
    cout << endl << endl;

    for(j = 0; j<WORLDSIZE; j++){
        for(i = 0; i < WORLDSIZE; i++){
            if(grid[i][j] == NULL) cout << ".";
            else if(grid[i][j]->getType() == ANT) cout << "o";
            else cout << "x";
        }
        cout << endl;
    }
}

void World::SimulateOneStep(){
    int i, j;

    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            if(grid[i][j] != NULL) grid[i][j]->moved = false;
        }
    }

    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            if(grid[i][j] != NULL && grid[i][j]->getType() == DOODLEBUG){
                if(grid[i][j]->moved == false){
                    grid[i][j]->moved = true;
                    grid[i][j]->move();
                }
            }
        }
    }

    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            if(grid[i][j] != NULL && grid[i][j]->getType() == ANT){
                if(grid[i][j]->moved == false){
                    grid[i][j]->moved = true;
                    grid[i][j]->move();
                }
            }
        }
    }


    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            if(grid[i][j] != NULL && grid[i][j]->getType() == DOODLEBUG){
                if(grid[i][j]->starve()){
                    delete (grid[i][j]);
                    grid[i][j] = NULL;
                } 
            }
        }
    }


    for(i = 0; i < WORLDSIZE; i++){
        for(j = 0; j < WORLDSIZE; j++){
            if(grid[i][j] != NULL && grid[i][j]->moved == true){
                    grid[i][j]->breed();
                } 
            }
        }
    }


Organism::Organism(){
    world = NULL;
    moved = false;
    breedTicks = 0;
    x = 0;
    y = 0;
}

Organism::Organism(World* world, int x, int y){
    this->world = world;
    moved = false;
    breedTicks = 0;
    this->x = x;
    this->y = y;
    world->setAt(x, y, this);
}

Organism::~Organism(){}

Ant::Ant() : Organism()
{
}

Doodlebug::Doodlebug() : Organism()
{
starveTicks = 0;
}

Doodlebug::Doodlebug(World *world, int x, int y) : Organism(world,x,y)
{
starveTicks = 0;
}
Ant::Ant(World *world, int x, int y) : Organism(world,x,y)
{
}

int Ant::getType()
{
return ANT;
}


void Ant::breed(){
    breedTicks++;
    if(breedTicks == ANTBREED){
        breedTicks = 0;

        if((y>0) && (world->getAt(x, y-1))==NULL){
            Ant *newAnt = new Ant(world, x, y-1);
        }

        else if((y<WORLDSIZE-1) && (world->getAt(x, y+1))==NULL){
            Ant *newAnt = new Ant(world, x, y+  1);
        }

        if((x>0) && (world->getAt(x-1, y))==NULL){
            Ant *newAnt = new Ant(world, x-1, y);
        }

        else if((x<WORLDSIZE-1) && (world->getAt(x+1, y))==NULL){
            Ant *newAnt = new Ant(world, x+1, y);
        }
    }
}


void Doodlebug::breed(){
    breedTicks++;
    if(breedTicks == DOODLEBREED){
        breedTicks = 0;

        if((y>0) && (world->getAt(x, y-1))==NULL){
            Doodlebug* newDoodle = new Doodlebug(world, x, y-1);
        }

        else if((y<WORLDSIZE-1) && (world->getAt(x, y+1))==NULL){
            Doodlebug* newDoodle = new Doodlebug(world, x, y+1);
        }

        if((x>0) && (world->getAt(x-1, y))==NULL){
            Doodlebug* newDoodle = new Doodlebug(world, x-1, y);
        }

        else if((x<WORLDSIZE-1) && (world->getAt(x+1, y))==NULL){
            Doodlebug* newDoodle = new Doodlebug(world, x+1, y);
        }
    }
}


void Ant::move(){
    int dir = rand() % 4;
    if (dir==0) {
        if ((y>0) && (world->getAt(x,y-1)==NULL))
        {
            world->setAt(x,y-1,world->getAt(x,y));
            world->setAt(x,y,NULL);  
            y--;
        }
    }

    else if (dir==1){
        if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL)){
            world->setAt(x,y+1,world->getAt(x,y));
            world->setAt(x,y,NULL);
            y++;
        }
    }

    else if (dir==2){
        if ((x>0) && (world->getAt(x-1,y)==NULL)){
            world->setAt(x-1,y,world->getAt(x,y));  
            world->setAt(x,y,NULL);  
            x--;
        }
    }

    else{
        if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL)){
            world->setAt(x+1,y,world->getAt(x,y));  
            world->setAt(x,y,NULL); 
            x++;
        }
    }
}

void Doodlebug::move(){
    if((y > 0) && (world->getAt(x, y-1) != NULL) && (world->getAt(x,y-1)->getType() == ANT)){
        delete (world->grid[x][y-1]);
        world->grid[x][y-1] = this;   
        world->setAt(x,y,NULL);  
        starveTicks =0 ;    
        y--;
        return;
    }
    
    else if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)!=NULL) && (world->getAt(x,y+1)->getType() == ANT)){
        delete (world->grid[x][y+1]); 
        world->grid[x][y+1] = this;  
        world->setAt(x,y,NULL);  
        starveTicks =0 ;  
        y++;
        return;
    }

    else if ((x>0) && (world->getAt(x-1,y)!=NULL) && (world->getAt(x-1,y)->getType() == ANT)) {
        delete (world->grid[x-1][y]);  
        world->grid[x-1][y] = this;   
        world->setAt(x,y,NULL);  
        starveTicks =0 ;  
        x--;
        return;
    }

    else if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)!=NULL) && (world->getAt(x+1,y)->getType() == ANT)){
        delete (world->grid[x+1][y]);  
        world->grid[x+1][y] = this;   
        world->setAt(x,y,NULL);  
        starveTicks =0 ;   
        x++;
        return;
    }

    int dir = rand() % 4;

    if (dir==0){
        if ((y>0) && (world->getAt(x,y-1)==NULL)){
            world->setAt(x,y-1,world->getAt(x,y));
            world->setAt(x,y,NULL);  
            y--;
        }
    }

    else if (dir==1){
        if ((y<WORLDSIZE-1) && (world->getAt(x,y+1)==NULL)){
            world->setAt(x,y+1,world->getAt(x,y));  
            world->setAt(x,y,NULL); 
            y++;
        }
    }
    else if (dir==2){
        if ((x>0) && (world->getAt(x-1,y)==NULL)){
            world->setAt(x-1,y,world->getAt(x,y)); 
            world->setAt(x,y,NULL); 
            x--;
        }
    }

    else{
        if ((x<WORLDSIZE-1) && (world->getAt(x+1,y)==NULL)){
            world->setAt(x+1,y,world->getAt(x,y));  
            world->setAt(x,y,NULL);  
            x++;
        }
    }

    starveTicks++;

}

bool Doodlebug::starve()
{
    if (starveTicks > DOODLESTARVE){
        return true;
    }
    else{
        return false;
    }
}

int Doodlebug::getType()
{
    return DOODLEBUG;
}

int main(){
    string s;
    srand(time(NULL));
    World w;

    int antcount = 0;
    while(antcount < INITIALANTS){
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if(w.getAt(x, y) == NULL){
            antcount++;
            Ant* a1 = new Ant(&w, x, y);
        }
    }

    int doodlecount = 0;
    while(doodlecount < INITIALBUGS){
        int x = rand() % WORLDSIZE;
        int y = rand() % WORLDSIZE;
        if(w.getAt(x, y) == NULL){
            doodlecount++;
            Doodlebug* a1 = new Doodlebug(&w, x, y);
        }
    }

    while(true){
        w.Display();
        w.SimulateOneStep();
        cout << endl << "Press enter for next step" << endl;
        getline(cin, s);
    }

    return 0;

}