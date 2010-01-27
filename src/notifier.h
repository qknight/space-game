#ifndef NOTIFIER_H
#define NOTIFIER_H
#include "notifyable.h"

class notifyable;

class Notifier
{
  public:
    Notifier();
    void notify( notifyable* obj);
};

#endif // NOTIFIER_H
