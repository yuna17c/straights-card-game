#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyTable();
  void notifyScore(std::vector<int> v);
  void notifyRagequit();
  virtual ~Subject() = default;
};

#endif
