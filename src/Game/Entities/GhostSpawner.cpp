#include "GhostSpawner.h"
#include "Ghost.h"
#include "RandomGhost.h"
#include "PeekABooGhost.h"
#include <random>
#include <iterator>
#include "Dot.h"
#include "BigDot.h"

GhostSpawner::GhostSpawner(int x, int y, int width, int height, EntityManager* em, ofImage sprite) : Entity(x, y, width, height){
    this->em = em;
    this->sprite = sprite;
    spawnGhost("red");
    spawnGhost("pink");
    spawnGhost("cyan");
    spawnGhost("orange");

}

void GhostSpawner::tick(){
    std::vector<string> colors;
   
    colors.push_back("red");
    colors.push_back("pink");
    colors.push_back("cyan");
    colors.push_back("orange");
 //-------------------------------------------------   
    random_color = colors[rand() % colors.size()]; //variable that gets a random string from the color vector
 //-------------------------------------------------
    if(em->ghosts.size()<4 || em->normalGhostCount < 4){
        if(spawnCounter == 0){
            spawnGhost(colors[ofRandom(4)]);
            spawnCounter = 30*5;
            em->normalGhostCount += 1;
        }else{
            spawnCounter--;
        }
    }
    if (score == 500 && !flag) {
        randomGhostSpawner();
    }
    if (score > 500 && em->randGhostCount == 0) {
        randomGhostSpawner();
    }
    if (score == 1000 && !peekABooFlag) {
        spawnPeekABooGhost("grey");
    }
    if (score > 1000 && em->peekGhostCount == 0) {
        spawnPeekABooGhost("grey");
    }
}

void GhostSpawner::spawnGhost(string color){
    Ghost* g = new Ghost(x,y,width-2,height-2,sprite,em, color);
    em->ghosts.push_back(g);
}

void GhostSpawner::spawnRandomGhost(int x, int y, string color) {
        RandomGhost* g = new RandomGhost(x,y,width-2,height-2,sprite,em, color);
        em->ghosts.push_back(g);
        em->randGhostCount++;
}

void GhostSpawner::randomGhostSpawner() {
    	int randNum = ofRandom(0, em->entities.size() + 1);

	if (dynamic_cast<Dot *>(em->entities[randNum]) || dynamic_cast<BigDot *>(em->entities[randNum]))
	{
		int posX = em->entities[randNum]->getPosX();
		int posY = em->entities[randNum]->getPosY();
		em->entities[randNum]->remove = true;
		spawnRandomGhost(posX, posY, "green");
		flag = true;
        em->removedDots += 1;
	}
}

void GhostSpawner::spawnPeekABooGhost(string color) {
    PeekABooGhost* g = new PeekABooGhost(x,y,width-2,height-2,sprite,em,color);
    em->ghosts.push_back(g);
    em->peekGhostCount++;
    peekABooFlag = true;
}

void GhostSpawner::keyPressed(int key){
    if(key == 'g'){
        spawnGhost(random_color);
    }
    if (key == 'l') {
        spawnRandomGhost(x, y, "green");
    }
    if (key == 'k') {
        spawnPeekABooGhost("grey");
    }
}

EntityManager* GhostSpawner::getEntityManager() {
    return em;
}