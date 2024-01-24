#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include <memory>
#include <util/scopedbind.h>

class GraphicsContext {
public:
    virtual void bind() const = 0;
    virtual void* get_native_handle() const = 0;

    static std::shared_ptr<GraphicsContext> create();
};

#endif // GRAPHICSCONTEXT_H
