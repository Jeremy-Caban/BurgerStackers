//
// Created by joshu on 11/3/2020.
//

#ifndef APGAMEENGINE_RESTAURANT_H
#define APGAMEENGINE_RESTAURANT_H
#include "ofMain.h"
#include "Player.h"
#include "EntityManager.h"
#include "BaseCounter.h"

class Restaurant {
    private:
        Player* player;
        EntityManager* entityManager;
        int ticks=0;
        std::vector<ofImage> people;
        int money =0;

    public:
        Restaurant();
        Player* getPlayer();
        void setPlayer(Player *player);
        Item* cheese;
        Item* lettuce;
        Item* tomato;
        Item* burger;
        Item* botBread;
        Item* topBread;
        ofImage floor;
        ofImage decorations; //Image that loads the decorations for the restaurant.
        ofImage table; 
        ofImage flower; 
        ofImage lamp; 
        ofImage leftchair; 
        ofImage rightchair;
        void loadDecorations(); //Member function that loads all the images used for the decorations.
        void drawDecorations(); //Member function that holds all the decorations for render.
        void initItems();
        void initCounters();
        void initClients();
        void generateClient();
        void serveClient();
        void tick();
        void render();
        void keyPressed(int key);
};


#endif //APGAMEENGINE_RESTAURANT_H
