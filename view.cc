#include "view.h"
#include "card.h"
#include "round.h"
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
using namespace std;

View::View( Round *round)
  : round{round} 
  {
      round->attach( this );
  }

string View::rankPrint(int rank_num) {
    string rank;
    stringstream ss;
    ss << rank_num;
    ss >> rank; 
    if (rank_num==1) rank = "A";
    else if (rank_num==10) rank = "T";
    else if (rank_num==11) rank = "J";
    else if (rank_num==12) rank = "Q";
    else if (rank_num==13) rank = "K";
    return rank;
}

void View::printSuit(vector<unique_ptr<Card>> *suit) {
    if (suit->size()!=0) {
        auto first = *suit->front().get();
        int first_num = first.getRank();
        auto last = *suit->back().get();
        int last_num = last.getRank();
        // prints cards in the suit from the first number to the last number
        for (int i=first_num; i<=last_num; i++) {
            string rank = rankPrint(i);
            cout << rank << " " ;
        }
    }
    cout << "\n";
}

void View::printTable() {
    cout << "Cards on the table" << endl;
    cout << "Clubs: ";
    printSuit(round->getClubs());
    cout << "Diamonds: ";
    printSuit(round->getDiamonds());
    cout << "Hearts: ";
    printSuit(round->getHearts());
    cout << "Spades: ";
    printSuit(round->getSpades());
}

void View::printCards(vector<unique_ptr<Card>> *v) {
    for (long unsigned int i=0; i<v->size(); i++) {
        auto card = *v->at(i).get();
        int rank_num = card.getRank();
        string rank = rankPrint(rank_num);
        cout << rank << card.getSuit() << " " ;
    }
    cout << "\n";
}

void View::updateTable() {
    auto playerList = round->getPlayers();
    int idx = round->getCurr();
    auto curr = playerList->at(idx).get();
    cout << "> It is player "<< idx+1 << "'s turn" << endl;
    printTable();
    cout << "Your Hand: ";
    printCards(curr->getHand());
    cout << "Legal plays: ";
    printCards(round->getLegalCards());
}

void View::updateScores(vector<int> winners) {
    auto playerList = round->getPlayers();
    cout << "-----------------------------------"<< endl;
    for (int i=0;i<4;i++) {
        auto curr = playerList->at(i).get();
        cout << "Player " << i+1 << "'s discards: ";
        printCards(curr->getDiscards());
        vector<int> score = curr->getScore();
        cout << "Player " << i+1 << "'s score: " << score[0] << " + " << score[1] << " = " << score[0]+score[1] <<endl;
    }
    cout << "-----------------------------------"<< endl;
    for (auto i: winners) {
        cout << "Player " << i << " wins!" << endl;
    }
    cout << "-----------------------------------"<< endl;
}

void View::updateRagequit() {
    int idx = round->getCurr();
    cout << "Player " << idx+1 << " ragequits. A computer will now take over." << endl;
}

View::~View() {
    round->detach( this );
}
