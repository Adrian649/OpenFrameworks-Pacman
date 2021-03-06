#include "PeekABooGhost.h"
#include "BoundBlock.h"

PeekABooGhost::PeekABooGhost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color): Ghost(x, y, width, height, spriteSheet, em, color){
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
    if(color == "red"){
        sprite.cropFrom(spriteSheet,456,64,16,16);
    }else if(color=="grey"){
        sprite.cropFrom(image,456,78,16,16);
    }else if(color=="cyan"){
        sprite.cropFrom(spriteSheet,456,96,16,16);
    }else if(color=="orange"){
        sprite.cropFrom(spriteSheet,456,113,16,16);
    }

}

void PeekABooGhost::tick(){
    killableAnim->tick();
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
        }else if(facing == DOWN){
            y+=speed;
        }else if(facing == LEFT){
            x-=speed;
        }else if(facing == RIGHT){
            x+=speed;
        }
    }else{
        int randInt;
        if(justSpawned){
            randInt = ofRandom(2);

        }else{
            randInt = ofRandom(4);
        }
        if(randInt == 0){
            facing = LEFT;
        }else if(randInt == 1){
            facing = RIGHT;
        }else if(randInt == 2){
            facing = DOWN;
        }else if(randInt == 3){
            facing = UP;
        }
        justSpawned = false;

    }
    if (em->playerPositionX - x > 28 || em->playerPositionY - y > 28) {
        isInvisible = true;
    }else {
        isInvisible = false;
    }
}

void PeekABooGhost::render(){
    if(killable && !isInvisible){
        killableAnim->getCurrentFrame().draw(x,y,width,height);
    }else if (!isInvisible){
        Entity::render();
    }
}

bool PeekABooGhost::getKillable(){
    return killable;
}
void PeekABooGhost::setKillable(bool k){
    killable = k;
}
void PeekABooGhost::checkCollisions(){
    for(BoundBlock* BoundBlock: em->BoundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
}

PeekABooGhost::~PeekABooGhost(){
    delete killableAnim;
}