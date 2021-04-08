#include "RandomGhost.h"
#include "BoundBlock.h"
#include "Player.h"
#include "Dot.h"
#include "BigDot.h"

RandomGhost::RandomGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager *em, string color) : Ghost(x, y, width, height, spriteSheet, em, color)
{
    this->em = em;
    vector<ofImage> killableFrames;
    ofImage temp;
    ofImage image;
    image.load("images/newGhosts.png");
    temp.cropFrom(spriteSheet, 584, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 600, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 616, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 632, 64, 16, 16);
    killableFrames.push_back(temp);
    killableAnim = new Animation(10, killableFrames);
    if (color == "green")
    {
        sprite.cropFrom(image, 456, 64, 16, 16);
    }
    else if (color == "pink")
    {
        sprite.cropFrom(spriteSheet, 456, 78, 16, 16);
    }
    else if (color == "cyan")
    {
        sprite.cropFrom(spriteSheet, 456, 96, 16, 16);
    }
    else if (color == "orange")
    {
        sprite.cropFrom(spriteSheet, 456, 113, 16, 16);
    }
}

void RandomGhost::tick()
{
    killableAnim->tick();
    canMove = true;
    checkCollisions();
    if (canMove)
    {
        if (facing == UP)
        {
            y -= speed;
        }
        else if (facing == DOWN)
        {
            y += speed;
        }
        else if (facing == LEFT)
        {
            x -= speed;
        }
        else if (facing == RIGHT)
        {
            x += speed;
        }
    }
    else
    {
        int randInt;
        if (justSpawned)
        {
            randInt = ofRandom(2);
        }
        else
        {
            randInt = ofRandom(4);
        }
        if (randInt == 0)
        {
            facing = LEFT;
        }
        else if (randInt == 1)
        {
            facing = RIGHT;
        }
        else if (randInt == 2)
        {
            facing = DOWN;
        }
        else if (randInt == 3)
        {
            facing = UP;
        }
        justSpawned = false;
    }
}

void RandomGhost::render()
{
    if (killable)
    {
        killableAnim->getCurrentFrame().draw(x, y, width, height);
    }
    else
    {
        Entity::render();
    }
}

bool RandomGhost::getKillable()
{
    return killable;
}
void RandomGhost::setKillable(bool k)
{
    killable = k;
}
void RandomGhost::checkCollisions()
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
}

void RandomGhost::spawnRandomGhost(int x, int y, string color)
{
    RandomGhost *g = new RandomGhost(x, y, width - 2, height - 2, sprite, em, color);
    em->ghosts.push_back(g);
}

RandomGhost::~RandomGhost()
{
    delete killableAnim;
}