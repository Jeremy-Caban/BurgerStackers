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
        int clientsThatLeft = 0;
    public:
        Restaurant();
        Player* getPlayer();
        int getMoney(){ return money; } //getter used to evaluate if player has won.
        int getClientsThatLeft(){ return this->clientsThatLeft; } //clients that left getter
        void setMoney(int money){ this-> money = money; } //establish money when needed. 
        void countAngryClients(); //will keep track of clients that left without being served
        void setPlayer(Player *player);
        bool spawnInspector = true; //bool that will mantain only one inspector in line.
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
        void randomIngredients(Burger* &burger); //generate random ingredients for different clients.
        void loadDecorations(); //Member function that loads all the images used for the decorations.
        void drawDecorations(); //Member function that holds all the decorations for render.
        void initItems();
        void initCounters();
        void initClients();
        void generateClient();
        void generateInspector(); //generate an Inspector.
        void serveClient();
        void tick();
        void render();
        void keyPressed(int key);
};


#endif //APGAMEENGINE_RESTAURANT_H
