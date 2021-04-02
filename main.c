#include <stdio.h>

//for later https://stackoverflow.com/questions/54962681/2d-array-c-to-mips

int* createDeck(); 
int * shuffleDeck(int* deck, int shuffleNumber);
void swap (int *a, int*b);
int dealCards (int hands[4][13], int numberOfPlayer, int cardPerHand, int* deck);
void printOptions( int hands[4][13], int player);

int main(void) {
    int *deck;
    int shuffleNumber;
    int deckTop = 0;
    int numberOfPlayers;
    int players[4];
    int playerHands[4][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    int boolFourPair = 0;
    printf("Enter an integer between 50 - 1000: ");
    scanf("%d", &shuffleNumber);
    deck = createDeck();
    deck = shuffleDeck(deck,shuffleNumber);

    printf("Enter an integer between 2-4: ");
    scanf("%d", &numberOfPlayers);

    deckTop = dealCards(playerHands, numberOfPlayers, 5,  deck);

    printOptions(playerHands, 2);

    return 0;
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
    //Prints deck, for DEBUG Erase in FINAL
    for(int i = 0; i < 52; i++) {
        printf("*(deck + [%d]) : %d\n", i, *(deck + i) );
    }
    return deck;
}



void swap (int *a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
  

int dealCards (int hands[4][13], int numberOfPlayers, int cardPerHand, int* deck) {

    int top = 0;

    for(int i = 0; i < cardPerHand; i++){
        for(int j = 0; j < numberOfPlayers; j++){
            int card = deck[top];
            hands[j][card]++;
            top++;
        }
    }

//Prints players hands. FOR DEBUG, Erase in FINAL
    for(int i = 0; i < numberOfPlayers; i++){
        printf("*Player %d hand\n",i+1);
        for(int j = 0; j < 13; j++){
            if(hands[i][j] != 0) {
                printf("You have %d, %d's\n", hands[i][j], j);
            }
        }
    }
    return 0;
}


void printOptions( int hands[4][13], int player)
{
  
  printf("*Player %d hand\n",player);
  for(int j = 0; j < 13; j++){
            if(hands[player-1][j] != 0) {
                printf("You have %d, %d's\n", hands[player-1][j], j);
            }
}

}