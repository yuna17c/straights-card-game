#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::detach(Observer *o) {
  for (auto it = observers.begin(); it != observers.end(); ) {
    if (*it == o) it = observers.erase(it);
    else ++it;
  }
}

void Subject::notifyTable() {
  for (auto &ob : observers) ob->updateTable();
}

void Subject::notifyScore(std::vector<int> winners) {
  for (auto &ob : observers) ob->updateScores(winners);
}

void Subject::notifyRagequit() {
  for (auto &ob : observers) ob->updateRagequit();
}
