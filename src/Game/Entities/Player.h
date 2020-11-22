#pragma once
#include "Animation.h"
#include "Burger.h"
#include "EntityManager.h"
#include "BaseCounter.h"
#include "StoveCounter.h"
class Player: public Entity{

    private:
        int speed = 5;
        int controlSpeed = 96;
        string facing = "right";
        Animation *chefAnim;
        Burger *burger;
        EntityManager* entityManager;
        int cookTimer = 0;
        bool startTimer = false;
    public:
        Player(int x, int y, int width, int height, ofImage sprite, EntityManager* em);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void mousePressed(int, int, int);
        void setFacing(string);
        void move(char c);
        bool takeControl = false;
        BaseCounter* getActiveCounter();
        Burger* getBurger(){
            return burger;
        }
};