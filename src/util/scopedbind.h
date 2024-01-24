#ifndef UTIL_H
#define UTIL_H

template<typename T>
class ScopedBind {
public:
    ScopedBind(T const* t)
        : old(T::current), needs_reset(false)
    {
        if (old != t) {
            t->bind();
            if (old != nullptr)
                needs_reset = true;
        }
    }
    ~ScopedBind()
    {
        if (needs_reset)
            old->bind();
    }

private:
    T const* old;
    bool needs_reset;
};

#endif // UTIL_H
