#ifndef CARD
#define CARD

class Card {
    char suit;
    int rank;
    public:
        Card(char suit, int rank);
        char getSuit();
        int getRank();
};

#endif
