#include "notifyable.h"
#include "movobjchangednotifier.h"

void notifyable::notify()
{
  std::list<movObjChangedNotifier*>::iterator it;
  for (it = this->mustBeNotified.begin(); it != this->mustBeNotified.end(); ++it){    
    (*it)->notify(this);          
  }
// mylogger::log("notifyable hat notify()) aufgerufen.");
}

void notifyable::addNotifier(movObjChangedNotifier* notifier)
{

  this->mustBeNotified.push_front(notifier);
}

void notifyable::removeNotifier(movObjChangedNotifier* notifier)
{

  this->mustBeNotified.remove(notifier);
}

void notifyable::notifyDelet()
{
  std::list<movObjChangedNotifier*>::iterator it;
  for (it = this->mustBeNotified.begin(); it != this->mustBeNotified.end(); ++it){

    (*it)->notifyDelet(this);
  }

}
