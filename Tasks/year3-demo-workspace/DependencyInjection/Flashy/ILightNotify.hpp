#ifndef __ILIGHTNOTIFY__
#define __ILIGHTNOTIFY__

class ILightNotify {
    public:
    virtual void lightOn() = 0;
    virtual void lightOff() = 0;
    virtual bool lightStatus() = 0;
};
#endif

