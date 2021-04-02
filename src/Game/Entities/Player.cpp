#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"

Player::Player(int x, int y, int width, int height, EntityManager *em) : Entity(x, y, width, height)
{
    spawnX = x;
    spawnY = y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);

    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for (int i = 0; i < 3; i++)
    {
        temp.cropFrom(sprite, i * 16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1, downAnimframes);
    walkUp = new Animation(1, upAnimframes);
    walkLeft = new Animation(1, leftAnimframes);
    walkRight = new Animation(1, rightAnimframes);
    this->em = em;
    r_powerup = new RandomPowerUp(em);
    invisible = new InvisiblePowerUp(em);


}
void Player::tick()
{
    canMove = true;
    checkCollisions();
    if (canMove)
    {
        if (facing == UP)
        {
            y -= speed;
            walkUp->tick();
        }
        else if (facing == DOWN)
        {
            y += speed;
            walkDown->tick();
        }
        else if (facing == LEFT)
        {
            x -= speed;
            walkLeft->tick();
        }
        else if (facing == RIGHT)
        {
            x += speed;
            walkRight->tick();
        }
      
    }
    if(em->isInvisible == true){
        timer += 1;
    }
    if(timer > 600){
        em->isInvisible = false;
        timer = 0;
    }
}

void Player::render()
{
    ofSetColor(256, 256, 256);
    // ofDrawRectangle(getBounds());
   if (em->isInvisible == false){
     if (facing == UP)
     {
        walkUp->getCurrentFrame().draw(x, y, width, height);
     }
     else if (facing == DOWN)
     {
        walkDown->getCurrentFrame().draw(x, y, width, height);
     }
     else if (facing == LEFT)
     {
        walkLeft->getCurrentFrame().draw(x, y, width, height);
     }
     else if (facing == RIGHT)
     { 
        walkRight->getCurrentFrame().draw(x, y, width, height);
     }
    }
   else if(em->isInvisible == true){
     ofSetColor(255,255,0,127); /*Pacman turns transparent when invisible powerup is activated 
                                so the player can be aware of the pacman postion.*/
     if (facing == UP)            
     {
        walkUp->getCurrentFrame().draw(x, y, width, height);
     }
     else if (facing == DOWN)
     {
        walkDown->getCurrentFrame().draw(x, y, width, height);
     }
     else if (facing == LEFT)
     {
       walkLeft->getCurrentFrame().draw(x, y, width, height);
     }
     else if (facing == RIGHT)
     {
        walkRight->getCurrentFrame().draw(x, y, width, height);
     }
   }
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth() / 2 + 100, 50);

    for (unsigned int i = 0; i < health; i++)
    {
        ofDrawCircle(ofGetWidth() / 2 + 25 * i + 200, 50, 10);
    }
    ofDrawBitmapString("Score:" + to_string(score), ofGetWidth() / 2 - 200, 50);

    //--------------------------------------------------------// Icons for power-ups
    if(em->in_counter >= 1){ 
        in_powerup.load("images/InvisiblePowerUp.png");
        ofSetColor(25,224,227);
        in_powerup.draw(ofGetWidth() / 2 + 350, 70, 80,52);
    }
    if(em->r_counter >= 1){
        rand_powerup.load("images/RandomPowerUp.png");
        ofSetColor(25,224,227);
        rand_powerup.draw(ofGetWidth() / 2 + 350, 150, 80,52);
    }
}

void Player::keyPressed(int key)
{
    switch (key)
    {
    case 'w':
        setFacing(UP);
        break;
    case 's':
        setFacing(DOWN);
        break;
    case 'a':
        setFacing(LEFT);
        break;
    case 'd':
        setFacing(RIGHT);
        break;
    case 'n':
        die();
        break;
    case 'm':
        if (health < 3)
        {
            health++;
        }
        break;
    case ' ':  //When spacebar is Pressed it teleports the player to a random position
     if (em->r_counter >= 1){
        powerup = r_powerup;
        powerup->activate();
        setPos(em->PosX);
        setPosY(em->PosY);
        em->r_counter -= 1;
        removedDots += 1;
      }
      if(em->in_counter >=1){
        powerup = invisible;
        powerup->activate();
        em->in_counter -= 1;
      }
    }
    
}

void Player::keyReleased(int key)
{
    if (key == 'w' || key == 's' || key == 'a' || key == 'd')
    {
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button)
{
}

void Player::setFacing(FACING facing)
{
    this->facing = facing;
}

int Player::getHealth()
{
    return health;
}

void Player::setHealth(int h)
{
    health = h;
}
int Player::getScore()
{
    return score;
}

void Player::setScore(int h)
{
    score = h;
}

int Player::getPos()
{
    return x;
}

void Player::setPos(int pos)
{
    x = pos;
}
void Player::setPosY(int posY)
{
    y = posY;
}
void Player::checkCollisions()
{
    for (BoundBlock *BoundBlock : em->BoundBlocks)
    {
        switch (facing)
        {
        case UP:
            if (this->getBounds(x, y - speed).intersects(BoundBlock->getBounds()))
            {
                canMove = false;
            }
            break;
        case DOWN:
            if (this->getBounds(x, y + speed).intersects(BoundBlock->getBounds()))
            {
                canMove = false;
            }
            break;
        case LEFT:
            if (this->getBounds(x - speed, y).intersects(BoundBlock->getBounds()))
            {
                canMove = false;
            }
            break;
        case RIGHT:
            if (this->getBounds(x + speed, y).intersects(BoundBlock->getBounds()))
            {
                canMove = false;
            }
            break;
        }
    }
    for (Entity *entity : em->entities)
    {
        if (collides(entity))
        {
            if (dynamic_cast<Dot *>(entity))
            {
                entity->remove = true;
                score += 10;
                removedDots += 1;
            }
            if (dynamic_cast<BigDot *>(entity))
            {
                score += 20;
                entity->remove = true;
                em->setKillable(true);
                removedDots += 1;
            }
        }
    }
    for (Entity *entity : em->ghosts)
    {
        if (collides(entity))
        {
            Ghost *ghost = dynamic_cast<Ghost *>(entity);
            if (ghost->getKillable())
            {
                if (dynamic_cast<RandomGhost*>(entity)) {
                    em->randGhostCount = 0;
                    em->r_counter += 1;
                }
                if (dynamic_cast<PeekABooGhost*>(entity)) {
                    em->peekGhostCount = 0;
                    em->in_counter += 1;
                }
                if (em->randGhostCount != 0) {
                    if (dynamic_cast<Ghost*>(entity)) {
                        em->normalGhostCount -= 1;
                    }
                }
                ghost->remove = true;
                
            }
            else
            {
               
                if(em->isInvisible == false){
                    die();
                }
                
            }
            
        }
    }
}

void Player::die()
{
    health--;
    x = spawnX;
    y = spawnY;
}

Player::~Player()
{
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}