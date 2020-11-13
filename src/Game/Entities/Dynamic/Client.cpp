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
    burger->setY(y+60); //Set the burger alonside the client.
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

map<string, int> Client::countBurgerIngredients(Burger* Burger){
    map<string, int> BurgerCount;
    stack<Item*, vector<Item*> > bIngredients = Burger->getIngredients(); //get the stack of ingredients
    while(bIngredients.size() > 0){
        if(BurgerCount.find(bIngredients.top()->name) != BurgerCount.end()){ 
            BurgerCount[bIngredients.top()->name] += 1; //if already there add 1 to the count
        }else{
            BurgerCount.insert(make_pair(bIngredients.top()->name, 1)); //else add to the map with a count of 1 
        }
        bIngredients.pop();
    }
    return BurgerCount;
}

bool Client::equals(Burger* chefBurger){
    if(chefBurger->getIngredients().empty()){ //if chef burger is empty return false 
        return false;
    }
    if(this->burger->getIngredients().size() == chefBurger->getIngredients().size()){
        set<string> listOfIngredients;
        map<string, int> thisBurgerCount, chefBurgerCount;                                 
        stack<Item*, vector<Item*> > cThisIngredients = this->burger->getIngredients();//cThisIngredient = copy this ingredients                                                                                 
        //get the name of the ingredients, not the count, (sets are useful here)
        while(cThisIngredients.size() > 0){
            listOfIngredients.insert(cThisIngredients.top()->name); //will not allow duplicates, we care only about the type
            cThisIngredients.pop();
        }
        //get the counts labeled with their respective Ingredient (ej. lettuce x2, cheese x1, topBread x1 etc.)
        thisBurgerCount = countBurgerIngredients(this->burger); 
        chefBurgerCount = countBurgerIngredients(chefBurger);
        for(string iName: listOfIngredients){
            if(thisBurgerCount.find(iName)->second != chefBurgerCount.find(iName)->second){ //will check for different amounts
                return false;
            }
        }
        return true; //will return true if all the quantities are correct
    }else{
        return false;
    }
}