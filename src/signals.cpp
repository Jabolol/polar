#include "signals.h"
#include <csignal>

std::vector<int> Signal::signals;

bool Signal::register_signal(int signal, void (*handler)(int))
{
    struct sigaction sigbreak {};
    sigbreak.sa_handler = handler;

    if (sigaction(signal, &sigbreak, NULL) != 0) {
        return false;
    }

    Signal::signals.push_back(signal);
    return true;
}

Signal::~Signal()
{
    struct sigaction sigbreak {};
    sigbreak.sa_handler = SIG_DFL;

    for (int signal : Signal::signals) {
        sigaction(signal, &sigbreak, NULL);
    }
}
