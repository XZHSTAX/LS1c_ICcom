#pragma once

#include <pm_clock.h>

class JsClock : public Persimmon::Clock
{
public:
    JsClock();
    virtual ~JsClock();

    virtual void setData(void* data);

private:

};

