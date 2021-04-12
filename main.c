#include <stdio.h>
#include <stdlib.h>
//for later https://stackoverflow.com/questions/54962681/2d-array-c-to-mips
const int DECK_SIZE = 52;
int hands[4][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
int deckTop = 0;
int deck[52];
int pairLimit = 4;
int numberOfPlayers = 0; 


// ALL PLAYERS *****MUST***** BE REFERENCED AS INDEXES OF HANDS ARRAY
void startGame();
void createDeck();
void shuffleDeck(int shuffleNumber);
void swap (int *a, int*b);
void dealCards (int numberOfPlayer, int cardPerHand);
int goFish (int player, int expCard);
void moveCards(int srcPlayer, int targetPlayer, int card);
void turn(int targetPlayer);
int cardInHand(int targetPlayer, int card);
void printOptions(int player);
int draw();

int isFinished();
void endGame();
void printScores();


//Tests
void testHands();


int main(void) {

    // int shuffleNumber;

    // int numberOfPlayers;
    // int players[4];
    // int boolFourPair = 0;
    // printf("Enter an integer between 50 - 1000(seed): ");
    // scanf("%d", &shuffleNumber);
    // createDeck();
    // shuffleDeck(shuffleNumber);

    // printf("Enter number of players between 2-4: ");
    // scanf("%d", &numberOfPlayers);

    // dealCards(numberOfPlayers, 5);
    // testHands();
    // //print Options Test
    // printOptions(1);
    // moveCards(1, 0, 2);
    // testHands();
    // goFish(1, 10);
    // testHands();
    // printf("Card in hand: %d\n", cardInHand(1, 9));


    // turn(0);
    // testHands();
    startGame();
    return 0;
}

void startGame() {
    int shuffleNumber;

    int numberOfPlayers;
    int players[4];
    int boolFourPair = 0;
    int turnOrder = 0;
    printf("Enter an integer between 50 - 1000(seed): ");
    scanf("%d", &shuffleNumber);
    createDeck();
    shuffleDeck(shuffleNumber);

    printf("Enter number of players between 2-4: ");
    scanf("%d", &numberOfPlayers);

    dealCards(numberOfPlayers, 5);
    if(!isFinished()) {
    while(turnOrder != numberOfPlayers){
        if(turnOrder == numberOfPlayers){
            turnOrder = 0;
        }
        printf("\nPlayer %d's turn!\n", turnOrder+1);
        turn(turnOrder);

        turnOrder++;
        }
    }
    endGame();

    //printf("ENDGAME\n");
}

void testHands(){
    printf("----ALL HANDS----\n");
    for (int i = 0; i < 4; i++){
        printf("*Player %d hand\n",i+1);
        for (int j = 0; j < 13; j++){
            if(hands[i][j] != 0) {
                printf("You have %d, %d's\n", hands[i][j], j);
            }
        }
    }
}


//Generates array of integers, e.g. deck of cards, there cards are integer from 0 to 12, and there are 4 of each integer.
void createDeck() {
    int type[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12};
    for(int i = 0; i < 4; i++ ) {
        for (int j = 0; j < 13; j++) {
            deck[j + i*13] = type[j % 52];
        }
    }
}

//random from https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
void shuffleDeck(int shuffleNumber) {
    for (int i = 52-1; i > 0; i--){
        int j = shuffleNumber % (i+1);
//        int j = (rand() % ((shuffleNumber+5) - shuffleNumber + 1)) + shuffleNumber;
        swap(&deck[i], &deck[j]);
    }
    for(int i = 0; i < 52; i++) {
        printf("*(deck + [%d]) : %d\n", i, *(deck + i) );
    }
}


//swaps two integers by address.
void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Distributes integers, e.g. cards to each player from deck (numberOfPlayers - how many players there are)
void dealCards (int numberOfPlayers, int cardPerHand) {
    for(int i = 0; i < cardPerHand; i++){
        for(int j = 0; j < numberOfPlayers; j++){
            int card = draw(deck, deckTop);
            hands[j][card]++;
        }
    }
}

//Prints options that player can choose. Like choose a player to take a card from.
void printOptions(int player){
    printf("*Player %d hand\n",player+1);
    int hasCardInHand = 0;
    for (int j = 0; j < 13; j++){
        if(hands[player][j] != 0 && hands[player][j] != pairLimit) { // change hard coded 4
            printf("You have %d, %d's\n", hands[player][j], j);
            hasCardInHand = 1;
        }
    }
    if (!hasCardInHand){
        printf("You can only fish, your hand is empty.\n");
    }
    printf("Which Player would you like to ask for which card in your hand? (Player Number, Card Number): \n");
}

//Calls draw() to take card from deck and adds it to player's hand
int goFish (int player, int expCard){
    int card = draw(deck, deckTop);
    hands[player][card]++;
    return expCard == card;
}

//Decrease cards from one hand to increases to current player
void moveCards(int srcPlayer, int targetPlayer, int card){
    while(cardInHand(srcPlayer, card)) {
        hands[srcPlayer][card]--;
        hands[targetPlayer][card]++;
    }
}

//Checks if targetPlayer has desired card
int cardInHand(int targetPlayer, int card){
    if(hands[targetPlayer][card] > 0){
        return 1;
    } else {
        return 0;
    }
}

//Handles the turn in Go-Fish game. It calls printOptions(), takes player input, checks is card player inputted is in the opponents hand,
//if so calls moveCards(), otherwise calls goFish(). If player fished successfully makes recursive call to turn().
void turn(int targetPlayer){
    printOptions(targetPlayer);
    int playerToAsk;
    int cardToAsk;
    scanf("%d", &playerToAsk);
    scanf("%d", &cardToAsk);
    if (cardInHand(playerToAsk, cardToAsk)){
        moveCards(playerToAsk, targetPlayer, cardToAsk);
        turn(targetPlayer);
    } else {
        if (goFish(targetPlayer, cardToAsk)){
            turn(targetPlayer);
        } else {
            return;
        }
    }
}

//Increments Deck top and returns card
int draw () {
    int card = deck[deckTop];
    deckTop = deckTop + 1;
    return card;
}

void endGame() {

    printScores();
    int answer = 0;
    printf("Would you like to play again?(1 for yes, 0 for no): \n");
    scanf("%d", &answer);
    if (answer == 1) {
        startGame();
    }
}

int isFinished() { //changed from void
    int countBooks = 0;
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < 13; j++) {
            if (hands[i][j] == 4)
            countBooks++;
        }
    }
    if (countBooks == 13) {
        printScores();
        return 1;
    }
    else {
        return 0;
    }
}

void printScores(){
    printf("----ALL HANDS----\n");
    for (int i = 0; i < numberOfPlayers; i++){ 
        printf("*Player %d hand\n",i+1);
        for (int j = 0; j < 13; j++){
            //score is defined as count of 4
            if (hands[i][j] == 4) {
                printf("    %d: %d's\n", hands[i][j], j+1); 
            }
        }
    }
}