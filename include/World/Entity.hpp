#pragma once

class Entity
{
public:
    Entity();
    virtual ~Entity();

    virtual void update(float dt) {};

private:
};