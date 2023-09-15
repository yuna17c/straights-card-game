#ifndef _VIEW_
#define _VIEW_
#include "observer.h"
#include "round.h"
#include "card.h"
#include <memory>
#include <vector>
#include <string>

class View: public Observer {
  Round *round;
  public:
    void printTable();
    void printSuit(std::vector<std::unique_ptr<Card>> *suit);
    std::string rankPrint(int n);
    void printCards(std::vector<std::unique_ptr<Card>> *v);
    void updateTable() override;
    void updateRagequit() override;
    void updateScores(std::vector<int> v) override;
    View(Round *round);
    ~View();
};

#endif
