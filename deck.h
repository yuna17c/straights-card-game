#ifndef DECK
#define DECK
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
#include "card.h"

class Card;

class Deck {
    std::vector<std::unique_ptr<Card>> deck;
    public:
        Deck(std::vector<std::unique_ptr<Card>> deck);
        void createDeck();
        void printDeck();
        void createSuit(char c);
        void shuffle(std::default_random_engine rng);
        std::vector<std::unique_ptr<Card>>* getDeck();
};

#endif
