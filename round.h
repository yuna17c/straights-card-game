#ifndef ROUND
#define ROUND
#include <memory>
#include <vector>
#include <string>
#include "player.h"
#include "card.h"
#include "subject.h"
#include "deck.h"

class Round : public Subject {
    std::vector<std::unique_ptr<Player>> playerList;
    std::vector<std::unique_ptr<Card>> hearts;
    std::vector<std::unique_ptr<Card>> diamonds;
    std::vector<std::unique_ptr<Card>> spades;
    std::vector<std::unique_ptr<Card>> clubs;
    std::vector<std::unique_ptr<Card>> legalCards;
    int current;
    int turn;
    public:
        void setTurn(int i);
        int getTurn();
        int getCurr();
        std::vector<std::unique_ptr<Card>>* getHearts();
        std::vector<std::unique_ptr<Card>>* getDiamonds();
        std::vector<std::unique_ptr<Card>>* getSpades();
        std::vector<std::unique_ptr<Card>>* getClubs();
        std::vector<std::unique_ptr<Card>>*  getLegalCards();
        std::vector<std::unique_ptr<Player>>* getPlayers();
        void resetTable();
        void updateSuit(std::vector<std::unique_ptr<Card>> *suit, std::unique_ptr<Card> card);
        void updateTable(std::unique_ptr<Card> card);
        void setPlayers(std::vector<std::unique_ptr<Player>> lst);
        void updateLegals(std::vector<std::unique_ptr<Card>> *suits);
        std::vector<std::unique_ptr<Card>> legalPlays();
        std::vector<int> getWinner();
        void startPlayer(int i);
        void rageQuit(int i);
        void endRound(std::default_random_engine rng, Deck* deck);
};

#endif
    