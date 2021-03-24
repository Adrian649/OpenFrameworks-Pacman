#pragma once
#include "EntityManager.h"
#include "Animation.h"
#include "Ghost.h"

class RandomGhost: public Ghost{
    public:
        RandomGhost(int, int, int, int, ofImage, EntityManager*, string);
        ~RandomGhost();
        void tick();
        void render();
        bool getKillable();
        void setKillable(bool);
        void spawnRandomGhost(int, int, string);
        void randomGhostSpawner();
        void respawnRandomGhost();
        bool isAlive = true;

    private:
        bool killable = false;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=3;
        EntityManager* em;
        Animation* killableAnim;

};