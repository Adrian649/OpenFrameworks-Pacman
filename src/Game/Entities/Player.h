#pragma once
#include "Animation.h"

#include "EntityManager.h"
#include "PowerUp.h"
#include "RandomPowerUp.h"
#include "InvisiblePowerUp.h"

class Player: public Entity{

    private:
        int spawnX, spawnY;
        int health=3;
        int score=0;
        bool canMove;
        int speed = 4;
        bool walking = false;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        PowerUp* powerup;
        RandomPowerUp* r_powerup;
        InvisiblePowerUp* invisible;
        ofImage in_powerup;
        ofImage rand_powerup;
        
    public:
        Player(int, int, int , int, EntityManager*);
        ~Player();
        int getHealth();
        void setHealth(int);
        int getScore();
        void setScore(int);
        int getPos();
        void setPos(int);
        void setPosY(int);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void checkCollisions();
        void die();
        float timer = 0;
};