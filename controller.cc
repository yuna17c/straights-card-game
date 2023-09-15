#include "controller.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "player.h"
#include "deck.h"
#include "human.h"
#include "computer.h"
#include "round.h"
using namespace std;

class Deck;

Controller::Controller( Round *round) 
    : round{round}
{}

void Controller::startRound(default_random_engine rng, Deck* deck) {
    string player_type;
    deck->shuffle(rng);
    auto card_deck = deck->getDeck();
    vector<unique_ptr<Player>> player_list;
    vector<unique_ptr<Card>> empty_vector;
    vector<int> score = {0,0};
    for (int i=1; i<=4; i++) {
        cout << "Is Player " << i << " a human (h) or a computer (c)?" << endl;
        cin >> player_type;
        vector<unique_ptr<Card>> hands;
        try {
            if (player_type == "quit") {
                quit = true;
                break;
            }
            if (player_type=="h" || player_type=="c" || player_type=="H" || player_type=="C") {
                // creates a hand of 13 cards
                for (int j=0; j<13; j++) {
                    auto new_card = *card_deck->at(13*(i-1)+j).get();
                    if (new_card.getRank() == 7 && new_card.getSuit() == 'S') {
                        // determines the player who has 7 of Spades
                        round->setTurn(i-1);
                    }
                    auto c = make_unique<Card>(new_card.getSuit(), new_card.getRank());
                    hands.emplace_back(move(c));
                }
                if (player_type=="h") {
                    auto player = make_unique<Human>(i, score, move(hands), move(empty_vector));
                    player_list.push_back(move(player));
                } else {
                    auto player = make_unique<Computer>(i, score, move(hands), move(empty_vector));
                    player_list.push_back(move(player));
                }
            } else {
                throw 505;
            }
        }
        catch (...) {
            cout << "Please enter \"h\" or \"c\"." << endl;
            i--;
        }
        if (quit) break;
    }
    if (!quit) round->setPlayers(move(player_list));
}

bool Controller::checkDone() {
    // checks if any player's score >= 80
    for (int i=0; i<4; i++) {
        auto player_list = round->getPlayers();
        auto curr = &*player_list->at(i).get();
        int score = curr->getScore()[0];
        if (score >= 80) {
            return true;
        }
    }
    return false;
}

void Controller::getInput(int i, Deck* d) {
    string command, input;
    bool rage = false;
    auto player_list = round->getPlayers();
    auto curr = &*player_list->at(i).get();
    char player_type = curr->getType();
    int legal_size = round->getLegalCards()->size();
    if (player_type=='h') {
        while (true) {
            try {
                cin >> command;
                if (command == "play") {
                    if (legal_size==0) {
                        cin >> input;
                        throw 'e';
                    }
                    auto new_card = curr->play(round->getLegalCards());
                    if (new_card.get()->getSuit()=='e') throw 'e';
                    round->updateTable(move(new_card));
                    break;
                } else if (command == "discard") {
                    cin >> input;
                    if (legal_size!=0) throw true;
                    // checks if the card is one of the cards in hand
                    if (!curr->checkValid(input, curr->getHand())) throw 'e';
                    else curr->discard(input);
                    break;
                } else if (command == "deck") {
                    d->printDeck();
                } else if (command == "quit") {
                    quit = true;
                    break;
                } else if (command == "ragequit") {
                    round->rageQuit(i);
                    curr = &*player_list->at(i).get();
                    rage = true;
                    break;
                } else {
                    throw 505;
                }
            }
            catch(int e) {
                cin.clear();
                cin.ignore();
                cout << "Unrecognized command." << endl;
            }
            catch(bool e) {
                cin.clear();
                cin.ignore();
                cout << "You have a legal play. You may not discard." << endl;
            }
            catch(char e) {
                cin.ignore();
                cin.clear();
                cout << "Illegal play." << endl;
            }
        }
    }
    if (player_type=='c' || rage) {
        rage = false;
        if (legal_size!=0) {
        auto new_card = curr->play(round->getLegalCards());
        round->updateTable(move(new_card));
        } else {
        curr->discard(input);
        }
    }
}

bool Controller::isQuit() {
    return quit;
}
