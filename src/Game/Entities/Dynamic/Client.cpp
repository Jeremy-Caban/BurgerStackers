#include "Client.h"

Client::Client(int x, int y, int width, int height, ofImage sprite, Burger* burger): Entity(x, y, width, height, sprite){
    this->burger = burger;
}
Client::~Client(){
    burger->~Burger();
}
void Client::render(){
    ofSetColor (255,255,255); //Set color to white so burger conserves its original colored image.
    burger->render();

    ticks++;
    if(ticks % 60 == 0){ //Once a second has passed decrease value by nine.
        losingPatience -= 9;
    }
    ofSetColor (255,losingPatience,losingPatience); //Each second slowly turns the client red as he loses his patience.
    sprite.draw(x, y, width, height);

    // ofDrawRectangle(getBounds());
    if(nextClient != nullptr){
        nextClient->render();
    }
}

void Client::tick(){
    patience--;
    burger->setY(y);
    if(patience == 0){
        isLeaving = true;
    }
    if(nextClient != nullptr){
        nextClient->tick();
    }
}

int Client::serve(Burger* burger){
    int sum = 0;
    if(this->nextClient == nullptr){ //checks if its the last one
        if(equals(burger) && !isServed){
            isLeaving = true;
            isServed = true;
            sum += 10;
        }
    }else if(equals(burger) && !isServed){ //True if the burger served is equal to the order of the client.
        isLeaving = true;
        isServed = true; //client has been served (will additionally not be served anymore)
        sum += (10 + this->nextClient->serve(burger));
    }else{ //Is not the same order that the client wanted, check the rest.
        sum += this->nextClient->serve(burger);
    }
    return sum; //returns total earnings
}

bool Client::equals(Burger* chefBurger){
    bool areEqual;
    vector<Item*> clientIngr = this->burger->getIngredients();
    vector<Item*> chefIngr = chefBurger->getIngredients();

    //Compare types and quantities of ingredients to determine if two burgers are the same.
    if( clientIngr.size() == chefIngr.size()){ 
        for(unsigned int i = 0 ; i < clientIngr.size() ; i++){
            areEqual = false;   
            for(unsigned int j = 0 ; j <  chefIngr.size() ; j++){
               if(clientIngr[i]->name == chefIngr[j]->name){
                   areEqual = true;
                   break; //stop comparing and go to the next iteration since the ingredient is in both burgers.
               }
            
            }
            if(areEqual == false) return areEqual; //If an ingredient from the target burger is not found in the parameter burger then they are not equal.
        }
    }
    else{
        areEqual = false;
    }
    return areEqual; 
}