#pragma once
#include "EntityManager.h"
#include "Animation.h"
#include "Ghost.h"

class PeekABooGhost: public Ghost{
    public:
        PeekABooGhost(int, int, int, int, ofImage, EntityManager*, string);
        ~PeekABooGhost();
        void tick();
        void render();
        bool getKillable();
        void setKillable(bool);
        bool isInvisible = true;
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