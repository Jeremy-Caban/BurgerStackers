//
// Created by joshu on 11/3/2020.
//

#include "Restaurant.h"

Player *Restaurant::getPlayer() {
    return player;
}

void Restaurant::setPlayer(Player *player) {
    this->player = player;
}

Restaurant::Restaurant() {
    floor.load("images/floor.jpg");
    loadDecorations(); //Load images for the restaurants' decoration.
    entityManager = new EntityManager();
    ofImage chefPlayerImage;
    chefPlayerImage.load("images/chef.png");
    this->player = new Player(0, 600, 64, 64, chefPlayerImage, entityManager);    
    initItems();
    initCounters();
    initClients();
    generateClient();

}
void Restaurant::initItems(){
    ofImage burgerSpriteSheet, cheeseImg, lettuceImg, tomatoImg, burgerImg, botBreadImg, topBreadImg, plateImg;
    burgerSpriteSheet.load("images/burger.png");
    topBreadImg.cropFrom(burgerSpriteSheet, 25, 16, 112, 43); // top bun
    burgerImg.cropFrom(burgerSpriteSheet, 30, 134, 103, 48); // patty
    cheeseImg.cropFrom(burgerSpriteSheet, 169, 213, 102, 39); // cheese
    tomatoImg.cropFrom(burgerSpriteSheet, 169, 158, 110, 41); // tomato
    lettuceImg.cropFrom(burgerSpriteSheet, 161, 62, 117, 34); // lettuce
    botBreadImg.cropFrom(burgerSpriteSheet, 444, 270, 115, 39); // bottom bun
    plateImg.cropFrom(burgerSpriteSheet, 575, 263, 131, 51); // plate

    cheese = new Item(cheeseImg, "cheese");
    lettuce = new Item(lettuceImg, "lettuce");
    tomato = new Item(tomatoImg, "tomato");
    burger = new Item(burgerImg, "patty");
    botBread = new Item(botBreadImg, "bottomBun");
    topBread = new Item(topBreadImg, "topBun");
}
void Restaurant::initCounters(){
    int counterWidth = 96;
    int yOffset = 500;
    ofImage counterSheet, plateCounterImg, cheeseCounterImg, stoveCounterImg, lettuceCounterImg, emptyCounterImg, tomatoCounterImg, breadCounterImg;
    counterSheet.load("images/kitchen_cabinets_by_ayene_chan.png");
    stoveCounterImg.cropFrom(counterSheet, 224,12,32,43);//stoveTop
    lettuceCounterImg.cropFrom(counterSheet,96,76,32,43);//Vegetables
    emptyCounterImg.cropFrom(counterSheet,0,245,30,43);//Empty
    tomatoCounterImg.cropFrom(counterSheet,96,200,32,48);//fruit basket
    cheeseCounterImg.cropFrom(counterSheet,64,73,32,46);//cheese
    plateCounterImg.cropFrom(counterSheet,0,133,32,50);//plates
    breadCounterImg.cropFrom(counterSheet,0,63,34,56);//buns
    entityManager->addEntity(new BaseCounter(0,yOffset-16, counterWidth, 117, nullptr, plateCounterImg));
    entityManager->addEntity( new BaseCounter(counterWidth,yOffset-7, counterWidth,108, cheese, cheeseCounterImg));
    entityManager->addEntity(new StoveCounter(counterWidth*2,yOffset, counterWidth, 102, burger, stoveCounterImg)); //stove
    entityManager->addEntity(new BaseCounter(counterWidth*3, yOffset, counterWidth, 102, lettuce, lettuceCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*4,yOffset, counterWidth, 102, nullptr, emptyCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*5, yOffset -10, counterWidth, 113, tomato, tomatoCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*6, yOffset-32, counterWidth, 133, botBread, breadCounterImg));
    entityManager->addEntity(new BaseCounter(counterWidth*7, yOffset-32, counterWidth, 133, topBread, breadCounterImg));

}
void Restaurant::initClients(){
    ofImage temp;
    temp.load("images/People/Car_Designer3Female.png");
    people.push_back(temp);
    temp.load("images/People/Freedom_Fighter2Male.png");
    people.push_back(temp);
    temp.load("images/People/Hipster.png");
    people.push_back(temp);
    temp.load("images/People/Lawyer2Male.png");
    people.push_back(temp);
    temp.load("images/People/Mad_Scientist3Female.png");
    people.push_back(temp);
    temp.load("images/People/Programmer2Male.png");
    people.push_back(temp);
    temp.load("images/People/Songwriter3Male.png");
    people.push_back(temp);
    temp.load("images/People/Weather_Reporter2Female.png");
    people.push_back(temp);
    temp.load("images/People/Inspector.png");
    temp.cropFrom(temp,56,131,32,59); //Inspector Image.
    people.push_back(temp);
}
void Restaurant::tick() {
    ticks++;
    int randGenerate = ofRandom(5); //Generate 5 random numbers to create a 20% chance of generating an inspector instead of a client.
    if(ticks % 400 == 0 && !clientLimitReached){
        if( randGenerate == 0 && spawnInspector == true){
            generateInspector();
            spawnInspector = false; //do not spawn inspector if one is already in line. 
        }
        else{
            generateClient();
        }
        
    }if(this->entityManager->firstClient == nullptr){ //if there are no clients, countClients() can't be called 
        clientLimitReached = false; //as such we start spawning again
    }
    else if(this->entityManager->firstClient->countClients() < 6){ //the client limit is 6
        clientLimitReached = false;
    }else{
        clientLimitReached = true;
    }
//this->entityManager->firstClient->countClients() == 6
    player->tick();
    entityManager->tick();

}


void Restaurant::generateClient(){
    Burger* b = new Burger(72, 100, 50, 25);
    randomIngredients(b); //Add ingredients to client.
    entityManager->addClient(new Client(0, 50, 64, 72,people[ofRandom(8)], b));
}

 void Restaurant::generateInspector(){
    Burger* b = new Burger(72, 100, 50, 25);
    randomIngredients(b); //Add ingredients to inspector.
    entityManager->addClient(new Inspector(0, 50, 64, 72,people[people.size()-1], b));
 }

void Restaurant::randomIngredients(Burger* &b){
    int randIngr;
    b->addIngredient(botBread); //Bottom bread will be the first ingredient in the burger.
    for(int i =0 ; i <3 ; i++){ //Generate 3 random ingredients.
        randIngr = round(ofRandom(4));
        switch(randIngr){
            case(0):
                b->addIngredient(cheese);
                break;
            case(1):
                b->addIngredient(lettuce);
                break;
            case(2):
                b->addIngredient(tomato);
                break;
            default:
                b->addIngredient(burger);
                break;
        }
    }
    b->addIngredient(topBread); //Top bread will be the last ingredient in the burger.
}

void Restaurant::loadDecorations(){ //Function that loads all the decoration of the restaurant. 
    decorations.load("images/sprite.png");  //load image for tables.
    table.cropFrom(decorations, 21, 27, 62, 63);

    decorations.load("images/flower.png"); //load new image for flowers.
    flower.cropFrom(decorations, 29, 35, 17, 18);
    flower.resize(24,25);

    decorations.load("images/lpc_misc.png"); //load new image for lamp.
    lamp.cropFrom(decorations, 70, 8, 19, 80);
    lamp.resize(30,90);

    decorations.load("images/house_inside.png"); //load new image for rightchair and leftchair.
    leftchair.cropFrom(decorations, 387, 399, 25, 34);
    rightchair.cropFrom(decorations, 419, 399, 25, 34);
}

void Restaurant::drawDecorations(){ //Function that draws all the decoration of the restaurant. 
    for(int i = 0 ; i < 4 ; i++){ 
        table.draw(192, 400 -100*i); //Tables.
        table.draw(384 , 400 -100*i); 
        table.draw(576, 400 -100*i); 
        

        flower.draw(213, 400 -100*i); //Flowers.
        flower.draw(405 , 400 -100*i); 
        flower.draw(597, 400 -100*i); 
        
        
        lamp.draw(300, 350 -100*i); //Lamps.
        lamp.draw(500 , 350 -100*i); 
        

        leftchair.draw(158, 400 -100*i); //Leftchair.
        leftchair.draw(350 , 400 -100*i); 
        leftchair.draw(542, 400 -100*i); 
        

        rightchair.draw(254, 400 -100*i); //Rightchair.
        rightchair.draw(450 , 400 -100*i);
        rightchair.draw(640, 400 -100*i); 
    }
}

void Restaurant::render() {
    ofSetColor(256, 256, 256);
    floor.draw(0,0, ofGetWidth(), ofGetHeight());
    drawDecorations(); //Draw the restaurants decoration for ambiance.
    player->render();
    entityManager->render();
    ofSetColor(255, 111, 0);
    if(player->takeControl){ //Display the type of control the player has.
        ofDrawBitmapString("Control: Manual", (ofGetWidth()/2)-200, 10);
    }
    else{
        ofDrawBitmapString("Control: Automatic", (ofGetWidth()/2)-200, 10);
    }
    ofSetColor(0, 100, 0);
    ofDrawBitmapString("Money: " + to_string(money), ofGetWidth()/2, 10);
    ofSetColor(255,0,0);
    ofDrawBitmapString("Angry clients: " + to_string(clientsThatLeft),ofGetWidth() - 300, 10);
}
void Restaurant::serveClient(){
    if(entityManager->firstClient!= nullptr){
        money += entityManager->firstClient->serve(player->getBurger());
        Inspector * inspector = dynamic_cast<Inspector*>(this->entityManager->firstClient);
        if(inspector != NULL){ //If an isnpector was served another one can be spawned.
            spawnInspector = true;
        }
    }
}

void Restaurant::countAngryClients(){
    //checks the first client to see if they are about to leave without being served and adds 1 to the count if so
    if(this->entityManager->firstClient != nullptr && this->entityManager->firstClient->getPatience() == 1 && !this->entityManager->firstClient->isServed){
        this->clientsThatLeft++;
        Inspector * inspector = dynamic_cast<Inspector*>(this->entityManager->firstClient);
        if(inspector != NULL){ //If an inspector has left then this if statement will run.
            if(money !=0){
                money = money/2; //Halves the money earned.
            }
            spawnInspector = true; //Since an isnpector has left, another one can be spawned.
        }
    }
}

void Restaurant::keyPressed(int key) {
    player->keyPressed(key);
    if(key == 's'){
        serveClient();
    }
    if(key == '+'){ //Activate WinState.
        setMoney(100);
    }
    if(key == '-'){ //Activate LoseState.
        clientsThatLeft = 10;
    }
    if(key == '1'){
        if(this->entityManager->firstClient != nullptr && this->money >= 15){
            this->entityManager->firstClient->calmClients(0);
            this->money -= 15;
        }
    }
}
