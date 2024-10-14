#pragma once

#include "Entity.h"

namespace chert {
class NativeScript {
private:
    friend class Scene;
    Entity entity;

protected:
    template <typename T> T &getComponent() { return entity.getComponent<T>(); }

public:
    NativeScript() {}
    virtual ~NativeScript() {}

    virtual void onCreate() {}
    virtual void onUpdate(float timestep) {}
    virtual void onDestroy() {}
    virtual void onEvent(const Event &e) {}
};
} // namespace chert