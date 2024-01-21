#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include <memory>

class GraphicsContext {
public:
    virtual void make_current() = 0;
    virtual void* get_native_handle() const = 0;

    static std::shared_ptr<GraphicsContext> create();
};

#endif // GRAPHICSCONTEXT_H
