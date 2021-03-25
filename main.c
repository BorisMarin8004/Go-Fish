#include <stdio.h>

char* createDeck();
char * shuffleDeck(char* deck, int shuffleNumber);
void swap (char *a, char*b);

int main() {


    return 0;
}


char* createDeck() {
    static char d[52];
    char type[13] = {'A','2','3','4','5','6','7','8','9','F','J','Q','K'};
    int i;
    int j;
    for(i  = 0; i < 4; i++ ) {
        for (j = 0; j < 13; j++) {
            d[j + i*13] = type[j % 52];
        }
    }
    return d;
}

//random from https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
char * shuffleDeck(char* deck, int shuffleNumber) {
    int i;

    for (int i = 52-1; i > 0; i--)
    {
        int j = shuffleNumber % (i+1);

        swap(&deck[i], &deck[j]);
    }
    for(i  = 0; i < 52; i++) {
        printf("*(deck + [%d]) : %c\n", i, *(deck + i) );
    }

    return deck;
}

void swap (char *a, char*b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
