#include "InvisiblePowerUp.h"
#include "Entity.h"
#include "Player.h"
#include "EntityManager.h"


InvisiblePowerUp::InvisiblePowerUp(EntityManager* em){
  entityManager = em;
}

void InvisiblePowerUp:: activate(){
   entityManager->isInvisible = true;
}