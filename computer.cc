#include "computer.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

Computer::Computer(int id, vector<int> score, vector<unique_ptr<Card>> h, vector<unique_ptr<Card>> d)
    : Player{id, score, move(h), move(d), 'c'}
{};

std::unique_ptr<Card> Computer::play(vector<unique_ptr<Card>>* v) {
    auto first_card = *v->front().get();    // picks the first legal card
    int rank = first_card.getRank();
    char suit = first_card.getSuit();
    removePlayed(suit, rank);   // removes the card played from hand
    setScore();
    cout << "Player " << id << " plays " << stringRank(rank) << suit << "." << endl;
    // returns the card that has been played
    auto new_card = make_unique<Card>(suit, rank);
    return new_card;
}

void Computer::discard(string input) {
    auto first_card = hand.front().get();   // picks the first card in hand
    int rank = first_card->getRank();
    char suit = first_card->getSuit();
    // removes the discarded card from hand and adds to the discards
    removePlayed(suit, rank);
    auto new_discard = make_unique<Card>(suit, rank);
    discards.emplace_back(move(new_discard));
    cout << "Player " << id << " discards " << stringRank(rank) << suit << "." << endl;
    setScore();
    printDiscards();
}
