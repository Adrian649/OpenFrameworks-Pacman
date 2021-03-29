#pragma once
#include "PowerUp.h"
#include "EntityManager.h"

class InvisiblePowerUp: public PowerUp{

  private:

    EntityManager* entityManager;
    
  public:

    InvisiblePowerUp(EntityManager* entityManager);
    virtual void activate();

};