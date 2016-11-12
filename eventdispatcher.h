#pragma once
#include <QtGlobal>

#ifdef Q_OS_LINUX
#include <QtPlatformSupport/private/qeventdispatcher_glib_p.h>
using BaseEventDispatcher = QPAEventDispatcherGlib;
#endif

#ifdef Q_OS_WIN
#include <QtPlatformSupport/private/qwindowsguieventdispatcher_p.h>
using BaseEventDispatcher = QWindowsGuiEventDispatcher;
#endif

#ifdef Q_OS_MACOS
#TODO
#endif

class EventDispatcher : public BaseEventDispatcher
{
public:
    explicit EventDispatcher(QObject *parent = 0);
    ~EventDispatcher();
    void enableUserInput(bool on, bool interrupt=true);
    bool userInputEnabled();
    bool processEvents(QEventLoop::ProcessEventsFlags flags) override;
    static EventDispatcher* instance();
private:
    bool userInput = true;
};

class ScopedUserInputHandler
{
public:
    explicit ScopedUserInputHandler(bool allowUserInput, bool interrupt=false);
    ~ScopedUserInputHandler();
private:
    bool oldUserInput = true;
    bool interrupt = false;
};

