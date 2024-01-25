#include <context.h>
#include <memory>
#include <platform/linux/context.h>

using namespace graphics;

std::shared_ptr<Context> Context::create()
{
    return std::make_shared<LinuxContext>();
}
