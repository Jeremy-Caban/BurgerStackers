//
// Created by joshu on 11/4/2020.
//

#include "Burger.h"

Burger::Burger(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Burger::addIngredient(Item *item) {
    ingredientList.push(item);
}

void Burger::render(){
    int counter = 1;
    stack<Item*, vector<Item*> > toRender = this->getIngredients();
    stack<Item*, vector<Item*> > toRender2;
    while(toRender.size() > 0){
        toRender2.push(toRender.top());
        toRender.pop();
    }
    int size = toRender2.size();
    for (int i = size; i>0; i--){
        toRender2.top()->sprite.draw(x,y-(counter * 10),width,height);
        counter++;
        toRender2.pop();
    }
}

void Burger::clear(){
    ingredientList.empty();
}

void Burger::removeIngredient(){
    if(!ingredientList.empty()){
        ingredientList.pop();
    }
    
}