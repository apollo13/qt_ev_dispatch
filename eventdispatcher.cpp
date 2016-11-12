#include "eventdispatcher.h"

EventDispatcher::EventDispatcher(QObject *parent) : BaseEventDispatcher(parent) {}

EventDispatcher::~EventDispatcher() {}

void EventDispatcher::enableUserInput(bool on, bool interrupt)
{
    userInput = on;
    if (interrupt) {
        this->interrupt();
    }
}

bool EventDispatcher::userInputEnabled()
{
    return userInput;
}

bool EventDispatcher::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    if (userInput) {
        flags &= ~QEventLoop::ExcludeUserInputEvents;
    } else {
        flags |= QEventLoop::ExcludeUserInputEvents;
    }
    return BaseEventDispatcher::processEvents(flags);
}

EventDispatcher *EventDispatcher::instance()
{
    return dynamic_cast<EventDispatcher*>(QAbstractEventDispatcher::instance());
}

ScopedUserInputHandler::ScopedUserInputHandler(bool allowUserInput, bool interrupt) : interrupt(interrupt)
{
    auto dispatcher = EventDispatcher::instance();
    oldUserInput = dispatcher->userInputEnabled();
    dispatcher->enableUserInput(allowUserInput, interrupt);
}

ScopedUserInputHandler::~ScopedUserInputHandler()
{
    EventDispatcher::instance()->enableUserInput(oldUserInput, interrupt);
}
