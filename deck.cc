#include "deck.h"
#include "card.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

class Card;

Deck::Deck(vector<unique_ptr<Card>> deck)
    : deck{move(deck)}
{}

void Deck::createSuit(char c) {
    for (int i=1; i<=13; i++) {
        auto card = make_unique<Card>(c, i);
        deck.push_back(move(card));
    }
}

void Deck::createDeck() {
    createSuit('C');
    createSuit('D');
    createSuit('H');
    createSuit('S');
}

void Deck::printDeck() {
    for (long unsigned int i=0; i<deck.size(); i++) {
        auto card = *deck[i];
        int rank_num = card.getRank();
        string rank;
        stringstream ss;
        ss << rank_num;
        ss >> rank; 
        if (rank_num==1) rank = "A";
        else if (rank_num==10) rank = "T";
        else if (rank_num==11) rank = "J";
        else if (rank_num==12) rank = "Q";
        else if (rank_num==13) rank = "K";
        cout << rank << card.getSuit() << " " ;
        if ((i+1)%13==0) cout << "\n";
    }
}

void Deck::shuffle(std::default_random_engine rng) {
    std::shuffle( deck.begin(), deck.end(), rng );
}

vector<unique_ptr<Card>>* Deck::getDeck() {
    return &deck;
}
