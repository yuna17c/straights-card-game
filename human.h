#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER
#include "player.h"

class Human : public Player {
    public:
        Human(int id, std::vector<int> score, std::vector<std::unique_ptr<Card>> h, std::vector<std::unique_ptr<Card>> d);
        std::unique_ptr<Card> play(std::vector<std::unique_ptr<Card>>* v) override;
        void discard(std::string input) override;
};

#endif
