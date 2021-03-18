#pragma once
#include "Player.h"


class PowerUp {
    private:

    public:
        PowerUp();
        virtual void activate() = 0;
};