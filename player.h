#ifndef PLAYER
#define PLAYER
#include <memory>
#include <vector>
#include <string>
#include "card.h"

class Card;

class Player {
    protected:
        int id;
        std::vector<int> score;
        std::vector<std::unique_ptr<Card>> hand;
        std::vector<std::unique_ptr<Card>> discards;
        char type;
    public:
        Player(int id, std::vector<int> score, std::vector<std::unique_ptr<Card>> h, std::vector<std::unique_ptr<Card>> d, char t);
        char getType();
        void setScore();
        std::vector<int> getScore();
        void setHand(std::vector<std::unique_ptr<Card>> v);
        std::vector<std::unique_ptr<Card>>* getHand();
        std::vector<std::unique_ptr<Card>>* getDiscards();
        std::vector<std::unique_ptr<Card>> getLegalPlays(std::vector<std::unique_ptr<Card>>);
        void removePlayed(char c, int i);
        bool checkValid(std::string s, std::vector<std::unique_ptr<Card>>* v);
        void resetPlayer();
        int intRank(char c);
        std::string stringRank(int i);
        void printDiscards();
        virtual std::unique_ptr<Card> play(std::vector<std::unique_ptr<Card>>* v)=0;
        virtual void discard(std::string input)=0;
        virtual ~Player();
};

#endif
