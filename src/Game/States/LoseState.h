#include "State.h"

#pragma once

class LoseState : public State{
    private:
        ofImage gameOverImg;
        
    public:
        LoseState();
        void reset();
        void keyPressed(int key);
        void tick();
        void render();
        void mousePressed(int x, int y, int button);
};