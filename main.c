#include <stdio.h>
#include <stdlib.h>
//for later https://stackoverflow.com/questions/54962681/2d-array-c-to-mips
const int DECK_SIZE = 52;
int hands[4][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
int deckTop = 0;
int deck[52];
int pairLimit = 4;


// ALL PLAYERS *****MUST***** BE REFERENCED AS INDEXES OF HANDS ARRAY

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


//Tests
void testHands();


int main(void) {

    int shuffleNumber;

    int numberOfPlayers;
    int players[4];
    int boolFourPair = 0;
    printf("Enter an integer between 50 - 1000(seed): ");
    scanf("%d", &shuffleNumber);
    createDeck();
    shuffleDeck(shuffleNumber);

    printf("Enter number of players between 2-4: ");
    scanf("%d", &numberOfPlayers);

    dealCards(numberOfPlayers, 5);
    testHands();
    //print Options Test
    printOptions(1);
    moveCards(1, 0, 2);
    testHands();
    goFish(1, 10);
    testHands();
    printf("Card in hand: %d\n", cardInHand(1, 9));


    turn(0);
    testHands();
    return 0;
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

//'A','2','3','4','5','6','7','8','9','','J','Q','K'};
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



void swap (int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void dealCards (int numberOfPlayers, int cardPerHand) {
    for(int i = 0; i < cardPerHand; i++){
        for(int j = 0; j < numberOfPlayers; j++){
            int card = draw(deck, deckTop);
            hands[j][card]++;
        }
    }
}

void printOptions(int player){
    printf("*Player %d hand\n",player+1);
    for (int j = 0; j < 13; j++){
        if(hands[player][j] != 0 && hands[player][j] != pairLimit) { // change hard coded 4
            printf("You have %d, %d's\n", hands[player][j], j);
        }

    }
    printf("Which Player would you like to ask for which card in your hand? (Player Number, Card Number): \n");
}

int goFish (int player, int expCard){
    int card = draw(deck, deckTop);
    hands[player][card]++;
    return expCard == card;
}

void moveCards(int srcPlayer, int targetPlayer, int card){
    hands[srcPlayer][card]--;
    hands[targetPlayer][card]++;
}

int cardInHand(int targetPlayer, int card){
    if(hands[targetPlayer][card] > 0){
        return 1;
    } else {
        return 0;
    }
}

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
        while(1){
            int fishedSuccessful = goFish(targetPlayer, cardToAsk);
            if (fishedSuccessful){
                turn(targetPlayer);
            } else {
                return;
            }
        }
    }
}

int draw () {
    int card = deck[deckTop];
    deckTop = deckTop + 1;
    return card;
}