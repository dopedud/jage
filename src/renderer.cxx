#include "JAGE/core.h"
#include "JAGE/renderer/core.h"

namespace JAGE
{
    GraphicsContext::GraphicsContext(Window* window) : window { window } {}

    IndexBuffer::IndexBuffer(uint32_t count) : m_count { count } {}
}
