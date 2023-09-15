#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "controller.h"
#include "round.h"
#include "view.h"
#include "computer.h"
using namespace std;

int main ( int argc, char * argv[] ) {
  bool quit = false;
  vector<unique_ptr<Card>> d;
  Deck deck{move(d)};
  deck.createDeck();
  Round round;
  View view{&round};
  Controller controller(&round);

  // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	} // if

	std::default_random_engine rng{seed};
  controller.startRound(rng, &deck);
  if (!controller.isQuit()) {
    while (!controller.checkDone()) {
      int counter=0;
      cout << "A new round begins." << endl;
      while (counter < 13) {
        int turn = round.getTurn();
        for (int j=turn;j<turn+4;j++) {
          int i = j;
          if (j>3) i = j%4;   // gets the index of the current player in turn
          round.startPlayer(i);
          controller.getInput(i, &deck);
          quit = controller.isQuit();
          if (quit) break;
        }
        counter++;
        if (quit) break;
      }
      if (quit) break;
      round.endRound(rng, &deck);
    }
  }
}
