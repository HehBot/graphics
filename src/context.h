#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include <memory>
#include <util/scopedbind.h>

namespace graphics {
class Context {
public:
    virtual void bind() const = 0;
    virtual void* get_native_handle() const = 0;

    static std::shared_ptr<Context> create();
};
}

#endif // GRAPHICSCONTEXT_H
