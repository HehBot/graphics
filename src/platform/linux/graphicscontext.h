#ifndef PLATFORM_LINUX_GRAPHICSCONTEXT_H
#define PLATFORM_LINUX_GRAPHICSCONTEXT_H

#include <graphicscontext.h>

struct GLFWwindow;

class LinuxGraphicsContext : public GraphicsContext {
public:
    LinuxGraphicsContext();
    virtual ~LinuxGraphicsContext();

    virtual void bind() const override;
    virtual void* get_native_handle() const override { return (void*)context_handle; }

private:
    GLFWwindow* context_handle;
    static size_t nr_contexts;
};

#endif // PLATFORM_LINUX_GRAPHICSCONTEXT_H
