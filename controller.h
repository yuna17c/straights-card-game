#ifndef CONTROLLER
#define CONTROLLER
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "player.h"
#include "view.h"
#include "round.h"
#include "deck.h"

class Controller {
    Round *round;
    bool quit=false;
    public:
        Controller(Round *round);
        void startRound(std::default_random_engine rng, Deck* deck);
        bool checkDone();
        void getInput(int i, Deck* deck);
        bool isQuit();
};

#endif
