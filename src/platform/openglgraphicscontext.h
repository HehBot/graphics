#ifndef OPENGLGRAPHICSCONTEXT_H
#define OPENGLGRAPHICSCONTEXT_H

struct GLFWwindow;

class OpenGLGraphicsContext : public GraphicsContext {
public:
    OpenGLGraphicsContext();
    virtual ~OpenGLGraphicsContext();

    virtual void make_current() override;
    virtual void* get_native_handle() const override { return (void*)context_handle; }

private:
    GLFWwindow* context_handle;
    static size_t nr_contexts;
};

#endif // OPENGLGRAPHICSCONTEXT_H
