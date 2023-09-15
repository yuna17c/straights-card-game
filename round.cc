#include "round.h"
#include "player.h"
#include "deck.h"
#include "human.h"
#include "computer.h"
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <iostream>
using namespace std;

vector<unique_ptr<Card>>* Round::getHearts() {
    return &hearts;
}

vector<unique_ptr<Card>>* Round::getDiamonds() {
    return &diamonds;
}

vector<unique_ptr<Card>>* Round::getSpades() {
    return &spades;
}

vector<unique_ptr<Card>>* Round::getClubs() {
    return &clubs;
}

void Round::setTurn(int i) {
    turn = i;
}

int Round::getTurn() {
    current = turn;
    return turn;
}

int Round::getCurr() {
    // returns the index of the current player
    return (current-1)%4;
}

vector<unique_ptr<Player>> *Round::getPlayers() {
    return &playerList;
}

vector<unique_ptr<Card>> *Round::getLegalCards() {
    return &legalCards;
}

void Round::setPlayers(vector<unique_ptr<Player>> lst) {
    for (int i=0; i<4; i++) {
        playerList.emplace_back(move(lst[i]));
    }
}

void Round::resetTable() {
    clubs.clear();
    diamonds.clear();
    hearts.clear();
    spades.clear();
}

void Round::updateSuit(vector<unique_ptr<Card>> *suit, unique_ptr<Card> card) {
    int rank = card.get()->getRank();
    if (suit->size()==0) {
        suit->emplace_back(move(card)); 
    } else if (suit->back().get()->getRank() < rank) {
        if (suit->size()!=1) suit->pop_back();
        suit->emplace_back(move(card));
    } else {
        if (suit->size()!=1) suit->erase(suit->begin());
        suit->insert(suit->begin(), move(card));
    }
}

void Round::updateTable(unique_ptr<Card> card) {
    // adds card to the table
    char suit = card.get()->getSuit();
    if (suit=='H') updateSuit(&hearts, move(card));
    else if (suit=='S') updateSuit(&spades, move(card));
    else if (suit=='D') updateSuit(&diamonds, move(card));
    else if (suit=='C') updateSuit(&clubs, move(card));
};

void Round::updateLegals(vector<unique_ptr<Card>> *suits) {
    // adds legal cards of each suit
    if (suits->size()!=0) {
        char suit = suits->front().get()->getSuit();
        int new_rank1 = suits->front().get()->getRank()-1;
        int new_rank2 = suits->back().get()->getRank()+1;
        auto new_card1 = make_unique<Card>(suit, new_rank1);
        auto new_card2 = make_unique<Card>(suit, new_rank2);
        legalCards.emplace_back(move(new_card1));
        legalCards.emplace_back(move(new_card2));
    }
}

void Round::startPlayer(int i) {
    auto curr = &*playerList.at(i).get();
    auto possible_cards = legalPlays();
    auto legal_moves = curr->getLegalPlays(move(possible_cards));
    legalCards = move(legal_moves);
    current++;
    notifyTable();
}

vector<unique_ptr<Card>> Round::legalPlays() {
    // returns legal plays from the cards on the table
    legalCards.clear();
    updateLegals(&hearts);
    updateLegals(&diamonds);
    updateLegals(&spades);
    updateLegals(&clubs);
    if (legalCards.size()==0) {
        auto first_card = make_unique<Card>('S', 7);
        legalCards.emplace_back(move(first_card));
    }
    return move(legalCards);
}

vector<int> Round::getWinner() {
    int max_score = playerList[0].get()->getScore()[0] + playerList[0].get()->getScore()[1];
    vector<int> winners;
    for (int i=0; i<4; i++) {
        int score = playerList[i].get()->getScore()[0]+playerList[i].get()->getScore()[1];
        int player_id = i+1;
        if (score < max_score) {
            winners.clear();
            winners.emplace_back(player_id);
            max_score = score;
        } else if (score == max_score) {
            winners.emplace_back(player_id);
        }
    }
    return winners;
}

void Round::rageQuit(int i) {
    auto curr = &*playerList.at(i).get();
    auto new_player = make_unique<Computer>(i+1, curr->getScore(), move(*curr->getHand()), move(*curr->getDiscards()));
    playerList.at(i) = move(new_player);
    notifyRagequit();
}

void Round::endRound(default_random_engine rng, Deck* deck) {
    auto winners = getWinner();
    notifyScore(winners);
    resetTable();
    deck->shuffle(rng);
    auto card_deck = deck->getDeck();
    for (int i=1; i<=4; i++) {
        vector<unique_ptr<Card>> hands;
        for (int j=0; j<13; j++) {
            auto new_card = *card_deck->at(13*(i-1)+j).get();
            if (new_card.getRank() == 7 && new_card.getSuit() == 'S') {
                // determines the player who has 7 of Spades
                setTurn(i-1);
            }
            auto c = make_unique<Card>(new_card.getSuit(), new_card.getRank());
            hands.emplace_back(move(c));
        }
        auto curr = &*playerList.at(i-1).get();
        curr->setHand(move(hands));
        curr->resetPlayer();
    }
}
