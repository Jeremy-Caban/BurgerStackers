#include "State.h"

#pragma once

class WinState : public State{
    private:
        ofImage WinStateImg;
        
    public:
        WinState();
        void reset();
        void keyPressed(int key);
        void tick();
        void render();
        void mousePressed(int x, int y, int button);
};