#pragma once
#include "Entity.h"
#include "Burger.h"
#include <map>
class Client: public Entity{
    private:
        Burger* burger;
        int originalPatience;
        int patience=2000;
    public:
        Client(int, int, int, int, ofImage, Burger*);
        ~Client();
        void tick();
        void render();
        int serve(Burger*);
        Client* nextClient=nullptr;
        bool isLeaving=false;
        bool isServed=false; //used when checking if a client was served
        bool equals(Burger*); //determines if two burgers are the same.
        int getPatience(){ return this->patience; } //patience getter
        int losingPatience = 255; //used to display the client's patience by slowly turning red the color of their image.
        map<string, int> countBurgerIngredients(Burger* Burger);
        int countClients();
        void calmClients(int);
};