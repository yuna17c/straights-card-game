#ifndef _OBSERVER_
#define _OBSERVER_
#include <vector>

class Observer {
 public:
  virtual void updateTable() = 0;
  virtual void updateScores(std::vector<int> v) = 0;
  virtual void updateRagequit() = 0;
  virtual ~Observer() = default;
};
#endif
