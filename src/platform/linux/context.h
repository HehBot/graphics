#ifndef PLATFORM_LINUX_CONTEXT_H
#define PLATFORM_LINUX_CONTEXT_H

#include <context.h>

struct GLFWwindow;

class LinuxContext : public graphics::Context {
public:
    LinuxContext();
    virtual ~LinuxContext();

    virtual void bind() const override;
    virtual void* get_native_handle() const override { return (void*)context_handle; }

private:
    GLFWwindow* context_handle;
    static size_t nr_contexts;
};

#endif // PLATFORM_LINUX_CONTEXT_H
