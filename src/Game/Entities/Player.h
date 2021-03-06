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
        bool isPacman = true;
        int goomba_counter = 0;
        int sans_counter = 0;
        int speed = 4;
        bool walking = false;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        Animation *goomWalkUp;
        Animation *goomWalkDown;
        Animation *goomWalkLeft;
        Animation *goomWalkRight;
        Animation *sansWalkUp;
        Animation *sansWalkDown;
        Animation *sansWalkLeft;
        Animation *sansWalkRight;
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
        bool isGoomba = false;
        bool isSans = false; 
        float timer = 0;
        int removedDots = 0;
};