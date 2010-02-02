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
    
    std::list<movObjChangedNotifier*> mustBeNotified;
public:
    void addNotifier(movObjChangedNotifier *notifier);
    void removeNotifier(movObjChangedNotifier *notifier);

};

#endif // NOTIFYABLE_H
