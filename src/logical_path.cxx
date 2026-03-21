#include "JAGE/core.h"

namespace JAGE
{
    std::ostream& operator<<(std::ostream& os, const LogicalPath& path)
    { return os << path.string(); }
}