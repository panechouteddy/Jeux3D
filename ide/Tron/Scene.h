#pragma once
#include "lib/Window.h"

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(sr::Window& window) = 0;
};