#include "JAGE/core.h"

namespace JAGE
{
    LogicalPath::LogicalPath(char delimiter) : m_delimiter { delimiter } {}
    LogicalPath::LogicalPath(std::string_view raw, char delimiter) : m_delimiter { delimiter }
    { parse(raw); }

    std::ostream& operator<<(std::ostream& os, const LogicalPath& path)
    { return os << path.string(); }
}