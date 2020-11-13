//
// Created by joshu on 11/4/2020.
//

#ifndef APGAMEENGINE_BURGER_H
#define APGAMEENGINE_BURGER_H

#include "Item.h"
#include "Entity.h"
#include <stack>
class Burger {
private:
    int x,y,width,height;
    stack<Item*, vector<Item*> > ingredientList;
public:
    Burger(int, int, int, int);
    stack<Item*, vector<Item*> > getIngredients() { return ingredientList;} //ingredients getter.
    void addIngredient(Item *item);
    void render();
    void clear();
    void setY(int y){
        this->y = y;
    }
    void removeIngredient();
};


#endif //APGAMEENGINE_BURGER_H
