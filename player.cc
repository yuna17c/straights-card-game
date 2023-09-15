#include "player.h"
#include "card.h"
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>
#include <cctype>
using namespace std;

Player::Player(int id, vector<int> score, vector<unique_ptr<Card>> h, vector<unique_ptr<Card>> d, char t)
    : id{id}, score{score}, hand{move(h)}, discards{move(d)}, type{t}
{};

vector<int> Player::getScore() {
    return score;
}

char Player::getType() {
    return type;
}

void Player::setScore() {
    // calculates the score by going through the discards
    if (hand.size()==0) {
        for (long unsigned int i=0; i<discards.size();i++) {
            auto card = discards.at(i).get();
            int rank = card->getRank();
            score[1]+=rank;
        }
    }
}

void Player::setHand(vector<unique_ptr<Card>> v) {
    for (int i=0; i<13; i++) {
        hand.emplace_back(move(v[i]));
    }
}

vector<unique_ptr<Card>>* Player::getHand() {
    return &hand;
}

vector<unique_ptr<Card>>* Player::getDiscards() {
    return &discards;
}

void Player::printDiscards() {
    cout << "Player " << id << "'s discards: ";
    for (long unsigned int i=0; i<discards.size(); i++) {
        auto card = *discards.at(i).get();
        int rank_num = card.getRank();
        string rank = stringRank(rank_num);
        cout << rank << card.getSuit() << " " ;
    }
    cout << "\n";
}

void Player::removePlayed(char c, int n) {
    // removes the card with suit c and rank n from hand
    for (long unsigned int i=0; i<hand.size(); i++) {
        auto card = hand.at(i).get();
        int rank = card->getRank();
        char suit = card->getSuit();
        if (rank==n && suit==c) {
            hand.erase(hand.begin()+i);
        }
    }
}

int Player::intRank(char c) {
    // returns an integer representation of the rank
    int rank;
    if (c=='T') rank=10;
    else if (c=='J') rank=11;
    else if (c=='Q') rank=12;
    else if (c=='K') rank=13;
    else if (c=='A') rank=1;
    else rank=c-'0';
    return rank;
}

string Player::stringRank(int i) {
    // returns a string representation of the rank
    string rank;
    if (i==1) rank = "A";
    else if (i==10) rank = "T";
    else if (i==11) rank = "J";
    else if (i==12) rank = "Q";
    else if (i==13) rank = "K";
    else {
        stringstream ss;
        ss << i;
        ss >> rank; 
    }
    return rank;
}

bool Player::checkValid(string s, vector<unique_ptr<Card>>* v) {
    // checks if s (card in a string format) can be found in v
    int rank = intRank(s[0]);
    if (s.length()!=2) {
        return false;
    }
    for (long unsigned int j=0; j<v->size(); j++) {
        auto c = v->at(j).get();
        int rank2 = c->getRank();
        char suit2 = c->getSuit();
        if (rank==rank2 && toupper(s[1])==suit2) {
            return true;
        }
    }
    return false;
}

vector<unique_ptr<Card>> Player::getLegalPlays(vector<unique_ptr<Card>> v) {
    // returns the legal cards that the player can play (that they have in hand) from possible cards 
    vector<unique_ptr<Card>> legal_cards;
    for (long unsigned int i=0; i<hand.size(); i++) {
        auto c1 = hand.at(i).get();
        int rank1 = c1->getRank();
        char suit1 = c1->getSuit();
        if (rank1==7) {
            auto new_card = make_unique<Card>(suit1, 7);
            legal_cards.emplace_back(move(new_card));
            continue;
        }
        for (long unsigned int j=0; j<v.size(); j++) {
            auto c2 = v.at(j).get();
            int rank2 = c2->getRank();
            char suit2 = c2->getSuit();
            if (rank1==rank2 && suit1==suit2) {
                auto new_card = make_unique<Card>(suit2, rank2);
                legal_cards.emplace_back(move(new_card));
            }
        }
    }
    return legal_cards;
}

void Player::resetPlayer() {
    discards.clear();
    score[0] += score[1];
    score[1] = 0;
}

Player::~Player() {}
