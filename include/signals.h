#ifndef __SIGNALS_H__
#define __SIGNALS_H__

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
