#pragma once

#include <animated_image.h>

class JsAnimatedImage : public Persimmon::AnimatedImage
{
public:
    JsAnimatedImage();
    virtual ~JsAnimatedImage();

    virtual void setData(void* data);

protected:

private:

};
