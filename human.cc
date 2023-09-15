#include "human.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

Human::Human(int id, vector<int> score, vector<unique_ptr<Card>> h, vector<unique_ptr<Card>> d)
    : Player{id, score, move(h), move(d), 'h'}
{};

unique_ptr<Card> Human::play(vector<unique_ptr<Card>>* v) {
    string input;
    int rank;
    char suit;
    try {
        cin >> input;
        // checks if the card is one of the legal plays
        if (!checkValid(input, v)) throw 'e';
        else {
            suit = toupper(input[1]);
            rank = intRank(input[0]);
            removePlayed(suit, rank);   // removes the card played from hand
            setScore();
            cout << "Player " << id << " plays " << rank << suit << "." << endl;
        }
    } 
    catch(char e) {
        suit='e';
        rank=0;
    }
    // returns the card that has been played
    auto new_card = make_unique<Card>(suit, rank);
    return new_card;
}

void Human::discard(string input) {
    int rank = intRank(input[0]);
    char suit = toupper(input[1]);
    // removes the discarded card from hand and adds to the discards
    removePlayed(suit, rank);
    auto new_discard = make_unique<Card>(suit, rank);
    discards.emplace_back(move(new_discard));
    cout << "Player " << id << " discards " << rank << suit << "." << endl;
    setScore();
    printDiscards();
}
