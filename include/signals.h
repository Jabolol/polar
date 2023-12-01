#ifndef SIGNALS_H
#define SIGNALS_H

#include <vector>

class Signal {
  private:
    static std::vector<int> signals;

  public:
    Signal() = default;
    bool register_signal(int signal, void (*handler)(int));
    ~Signal();
};
#endif
