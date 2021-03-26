#pragma once
#include "PowerUp.h"
#include "EntityManager.h"

class RandomPowerUp: public PowerUp{

  private:

    EntityManager* entityManager;
    
  public:

    RandomPowerUp(EntityManager* entityManager);
    virtual void activate();

};