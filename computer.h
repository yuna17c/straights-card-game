#ifndef COMPUTER_PLAYER
#define COMPUTER_PLAYER
#include "player.h"

class Computer : public Player {
    public:
        Computer(int id, std::vector<int> score, std::vector<std::unique_ptr<Card>> h, std::vector<std::unique_ptr<Card>> d);
        std::unique_ptr<Card> play(std::vector<std::unique_ptr<Card>>* v) override;
        void discard(std::string input) override;
};

#endif
