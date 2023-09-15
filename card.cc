#include "card.h"
using namespace std;

Card::Card(char suit, int rank)
    : suit{suit}, rank{rank}
{};

char Card::getSuit() {
    return suit;
}

int Card::getRank() {
    return rank;
}
