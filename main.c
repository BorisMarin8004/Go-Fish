#include <stdio.h>
//for later https://stackoverflow.com/questions/54962681/2d-array-c-to-mips
const int DECK_SIZE = 52;
int hands[4][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
int deckTop = 0;
int deck[DECK_SIZE];
int pairLimit = 2;
int scores[4] = {0,0,0,0};
int numberOfPlayers = 0;


//ALL PLAYERS *****MUST***** BE REFERENCED AS INDEXES OF HANDS ARRAY
void startGame();
void createDeck();
void shuffleDeck(int shuffleNumber);
void swap (int *a, int*b);
void dealCards (int cardPerHand);
int goFish (int player, int expCard); // clear t
void moveCards(int srcPlayer, int targetPlayer, int card);
void turn(int targetPlayer); // clear t
int cardInHand(int targetPlayer, int card); // clear t
void printOptions(int player); // clear t
void updateScores(int player); // clear t
int draw(); // clear t
int isEmpty(); // remove
int isFinished(); // clear t
void endGame();
void printScores(); // clear t


//Tests
void testHands();


int main(void) {
    startGame();
    return 0;
}

//Starts the game by calling createDeck(), shuffleDeck() and dealCards(). Then controls
//the turn order, calling turn() while the game is not finished.
void startGame() {
    int shuffleNumber;
    int turnOrder = 0;
    printf("Enter how many pair you want to play(put either 2 or 4): ");
    scanf("%d", &pairLimit);

    printf("Enter an integer between 50 - 1000(seed): ");
    scanf("%d", &shuffleNumber);
    createDeck();
    shuffleDeck(shuffleNumber);

    printf("Enter number of players between 2-4: ");
    scanf("%d", &numberOfPlayers);
    int players[numberOfPlayers];

    dealCards(5);
    for (int i = 0; i < numberOfPlayers; i++){
        updateScores(i);
    }
    while(!isFinished()) {
        while(turnOrder != numberOfPlayers){
            printf("\nPlayer %d's turn!\n", turnOrder+1);
            turn(turnOrder);
            if (isFinished()){
                endGame();
                return;
            }
            turnOrder++;
        }
        turnOrder = 0;
    }
    endGame();
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
            deck[j + i*13] = type[j % DECK_SIZE];
        }
    }
}

//random from https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
void shuffleDeck(int shuffleNumber) {
    for (int i = DECK_SIZE-1; i > 0; i--){
        int j = shuffleNumber % (i+1);
//        int j = (rand() % ((shuffleNumber+5) - shuffleNumber + 1)) + shuffleNumber;
        swap(&deck[i], &deck[j]);
    }
    for(int i = 0; i < DECK_SIZE; i++) {
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
void dealCards (int cardPerHand) {
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
        if(hands[player][j] != 0 && hands[player][j] != 4) {
            if (pairLimit == 4 || (hands[player][j] != 2 && pairLimit == 2)){
                printf("You have %d, %d's\n", hands[player][j], j);
                hasCardInHand = 1;
            }
        }
    }
    if (!hasCardInHand){
        printf("You can only fish, your hand is empty.\n");
    }
    printf("Which Player would you like to ask for which card in your hand? (Player Number, Card Number): \n");
}

//Calls draw() to take card from deck and adds it to player's hand
int goFish (int player, int expCard) {
    if (isEmpty()) {
        printf("All fish is DEAD(deck is empty).\n");
        return 0;
    } else {
        printf("You are fishing(email) now. (Bad hacker stuff)\n");
        int card = draw(deck, deckTop);
        hands[player][card]++;
        printf("You got: %d\n", card);
        return expCard == card;
    }
}


//Decrease cards from one hand to increases to current player
void moveCards(int srcPlayer, int targetPlayer, int card){
    printf("You got the card you asked for, in your nasty hands!\n");
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
    updateScores(targetPlayer);
    printOptions(targetPlayer);
    int playerToAsk;
    int cardToAsk;
    scanf("%d", &playerToAsk);
    scanf("%d", &cardToAsk);
    playerToAsk--;
    if (targetPlayer != playerToAsk){
        if (cardInHand(playerToAsk, cardToAsk)){
            moveCards(playerToAsk, targetPlayer, cardToAsk);
            if (isFinished()){
                endGame();
            }
            turn(targetPlayer);
        } else {
            if (goFish(targetPlayer, cardToAsk)){
                if (isFinished()){
                    endGame();
                }
                turn(targetPlayer);
            } else {
                return;
            }
        }
    } else {
        printf("Sorry, cannot choose yourself ya'\n");
        turn(targetPlayer);
    }
}

//Increments Deck top and returns card
int draw () {
    int card = deck[deckTop];
    deckTop = deckTop + 1;
    return card;
}

//Prints scores and resets game if user so desires(answers yes).
void endGame() {
    printScores();
    int answer = 0;
    printf("Would you like to play again?(1 for yes, 0 for no): \n");
    scanf("%d", &answer);
    if (answer == 1) {
        for (int i = 0; i < numberOfPlayers; i++){
            scores[i] = 0;
            for (int k = 0; k < 13; k++){
                hands[i][k] = 0;
            }
        }
        deckTop = 0;
        pairLimit = 2;
        numberOfPlayers = 0;
        startGame();
    }
    printf("ENDGAME\n");
}

//Checks if all matches have been made
int isFinished() {
    int countTotalScores = 0;
    for (int i = 0; i < numberOfPlayers; i++) {
        countTotalScores+=scores[i];
    }
    if ((countTotalScores == 13 && pairLimit == 4) || (countTotalScores == 5 && pairLimit == 2)) {
        return 1;
    } else {
        return 0;
    }
}

//Prints each set made by players
void printScores(){
    printf("----Printing Scores----\n");
    for (int i = 0; i < numberOfPlayers; i++){
        printf("*Player %d score: %d\n", i+1, scores[i]);
    }
}

//Checks if deck is empty
int isEmpty(){
    return deckTop == DECK_SIZE;
}

//Updates given player score according to pairLimit.
void updateScores(int player){
    for (int j = 0; j < 13; j++){
        if (hands[player][j] == pairLimit) {
            scores[player]++;
            hands[player][j]-=pairLimit;
        }
    }
}