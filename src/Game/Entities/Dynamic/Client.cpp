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
    isLeaving = true;
    isServed = true; //client has been served
    return 10;
}