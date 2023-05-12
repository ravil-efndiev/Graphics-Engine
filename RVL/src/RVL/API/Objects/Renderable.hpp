#ifndef RVL_RENDERABLE_HPP
#define RVL_RENDERABLE_HPP

class IRenderable
{
public:
    virtual ~IRenderable() {}

    virtual void Draw() = 0;

private:

};

#endif
