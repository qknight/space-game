#ifndef NOTIFYABLE_H
#define NOTIFYABLE_H

#include <list>

#include "notifier.h"
#include "mylogger.h"
class movObjChangedNotifier;
class notifyable {
protected:
    void notifyDelet();
    void notify();
public:
    void addNotifier(movObjChangedNotifier *notifier);
    void removeNotifier(movObjChangedNotifier *notifier);

    std::list<movObjChangedNotifier*> mustBeNotified;
};

#endif // NOTIFYABLE_H
