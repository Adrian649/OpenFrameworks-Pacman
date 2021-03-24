#pragma once

#include "EntityManager.h"

class GhostSpawner: public Entity{
    public:
        GhostSpawner(int, int, int , int, EntityManager*, ofImage);
        void spawnGhost(string);
        void spawnRandomGhost(int, int, string);
        void randomGhostSpawner();
        EntityManager* getEntityManager();
        void keyPressed(int);
        void tick();
        string random_color;
        int score = 0;
        bool flag = false;
        
    private:
        EntityManager* em;
        int spawnCounter = 30*5;

};