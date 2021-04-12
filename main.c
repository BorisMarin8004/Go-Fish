#include <stdio.h>
<<<<<<< Updated upstream

//for later https://stackoverflow.com/questions/54962681/2d-array-c-to-mips

int* createDeck(); 
int * shuffleDeck(int* deck, int shuffleNumber);
void swap (int *a, int*b);
void dealCards (int hands[4][13], int numberOfPlayer, int cardPerHand, int* deck, int *top);
void printOptions( int hands[4][13], int player);
int draw (int*deck, int* deckTop);

int main(void) {
    int *deck;
=======
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
int endGame();
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
>>>>>>> Stashed changes
    int shuffleNumber;
    int deckTop = 0;
    int numberOfPlayers;
    int players[4];
    int playerHands[4][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    int boolFourPair = 0;
<<<<<<< Updated upstream
    printf("Enter an integer between 50 - 1000: ");
=======
    int turnOrder = 0;
    printf("Enter an integer between 50 - 1000(seed): ");
>>>>>>> Stashed changes
    scanf("%d", &shuffleNumber);
    deck = createDeck();
    deck = shuffleDeck(deck,shuffleNumber);

    printf("Enter an integer between 2-4: ");
    scanf("%d", &numberOfPlayers);

<<<<<<< Updated upstream
    dealCards(playerHands, numberOfPlayers, 5,  deck, &deckTop);

    //print Options Test
    printOptions(playerHands, 2);

    return 0;
=======
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
>>>>>>> Stashed changes
}
//'A','2','3','4','5','6','7','8','9','','J','Q','K'};
int* createDeck() {

static int d[52];
int type[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
  for(int i = 0; i < 4; i++ ) {
    for (int j = 0; j < 13; j++) {
      d[j + i*13] = type[j % 52];
    }
  }
  return d;
}

//random from https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
int * shuffleDeck(int* deck, int shuffleNumber) {
    for (int i = 52-1; i > 0; i--){
        int j = shuffleNumber % (i+1);
        swap(&deck[i], &deck[j]);
    }
//     //Prints deck, for DEBUG Erase in FINAL
//     for(int i = 0; i < 52; i++) {
//         printf("*(deck + [%d]) : %d\n", i, *(deck + i) );
//     }
//     return deck;
// }



void swap (int *a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
  

void dealCards (int hands[4][13], int numberOfPlayers, int cardPerHand, int* deck, int *deckTop) {
   for(int i = 0; i < cardPerHand; i++){
        for(int j = 0; j < numberOfPlayers; j++){
            int card = draw(deck, deckTop);
            hands[j][card]++;
    
        }
    }

// //Prints players hands. FOR DEBUG, Erase in FINAL
//     for(int i = 0; i < numberOfPlayers; i++){
//         printf("*Player %d hand\n",i+1);
//         for(int j = 0; j < 13; j++){
//             if(hands[i][j] != 0) {
//                 printf("You have %d, %d's\n", hands[i][j], j);
//             }
//         }
//     }

}


void printOptions( int hands[4][13], int player)
{
  
  printf("*Player %d hand\n",player);
  for (int j = 0; j < 13; j++){
      if(hands[player-1][j] != 0) {
          printf("You have %d, %d's\n", hands[player-1][j], j);
      }
            
    }
  printf("Which Player would you like to ask for which card in your hand? (Player Number, Card Number): \n");


}

<<<<<<< Updated upstream
int draw (int*deck, int* deckTop) {
   int card = deck[*deckTop];
   *deckTop = *deckTop + 1;
   return card;

=======
//Increments Deck top and returns card
int draw () {
    int card = deck[deckTop];
    deckTop = deckTop + 1;
    return card;
}

int endGame() {

    printScores();
    int answer = 0;
    printf("Would you like to play again?(1 for yes, 0 for no): \n");
    scanf("%d", &answer);
    if (answer == 1) {
        return 0;
    }
    else {
        return 1;
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
>>>>>>> Stashed changes
}