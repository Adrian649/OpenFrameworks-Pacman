#include "RandomPowerUp.h"
#include "Entity.h"
#include "Dot.h"
#include "BigDot.h"
#include "Player.h"
#include "EntityManager.h"


RandomPowerUp::RandomPowerUp(EntityManager* em){
  entityManager = em;
}

void RandomPowerUp:: activate(){
   //--------------------------------------------------//
    int randNum = ofRandom(0, entityManager->entities.size() + 1);
   //--------------------------------------------------//

  for(Entity *en: entityManager->entities){
     
    if(dynamic_cast<Dot*>(entityManager->entities[randNum]) || dynamic_cast<BigDot*>(entityManager->entities[randNum])){
     //Dot position
      int posX = entityManager->entities[randNum]->getPosX();
		  int posY = entityManager->entities[randNum]->getPosY();
		  entityManager->entities[randNum]->remove = true;
      entityManager->PosX = posX;
      entityManager->PosY = posY;
    }
  }



}