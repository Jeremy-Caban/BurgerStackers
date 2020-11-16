#pragma once
#include "BaseCounter.h"

class StoveCounter: public BaseCounter{
    private:
        ofImage notCookingImg;
        bool burgerIsCooked = false;
    public:
        StoveCounter(int,int,int,int, Item*, ofImage);
        void displayIcon();
        void setBurgerIsCooked(bool c){ this->burgerIsCooked = c; }
        bool getBurgerIsCooked(){ return this->burgerIsCooked; }
};