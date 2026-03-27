#include "JAGE/core.h"

namespace JAGE
{
    LogicalPath::LogicalPath(char delimiter) : m_delimiter { delimiter } {}
    LogicalPath::LogicalPath(std::string_view raw, char delimiter) : m_delimiter { delimiter }
    { parse(raw); }

    void LogicalPath::parse(std::string_view raw)
    {
        std::string token {};

    for (char c : raw)
        {
            if (c == m_delimiter)
            {
                if (!token.empty())
                {
                    m_segments.push_back(std::move(token));
                    token.clear();
                }
            } else token += c;
        }
        if (!token.empty()) m_segments.push_back(std::move(token));
    }

    void LogicalPath::validate_segment(std::string_view segment) const
    {
        if (segment.empty())
        throw std::invalid_argument("Path segment must not be empty");

        if (segment.find(m_delimiter) != std::string_view::npos)
        throw std::invalid_argument("Path segment must not contain the delimiter");
    }

    bool LogicalPath::empty() const { return m_segments.empty(); }
    size_t LogicalPath::depth() const { return m_segments.size(); }

    const std::vector<std::string>& LogicalPath::parts() const { return m_segments; }

    LogicalPath LogicalPath::parent() const
    {
        if (m_segments.empty()) return LogicalPath{ m_delimiter };
        LogicalPath p { m_delimiter };
        p.m_segments.assign(m_segments.begin(), m_segments.end() - 1);
        return p;
    }

    std::string_view LogicalPath::stem() const
    {
        if (m_segments.empty()) return "";
        std::string_view last { m_segments.back() };
        size_t dot { last.rfind('.') };
        if (dot == std::string::npos) return last;
        return last.substr(0, dot);
    }

    std::string LogicalPath::string() const
    {
        if (m_segments.empty()) return std::string{};
        std::ostringstream oss {};
        for (size_t i {}; i < m_segments.size(); i++)
        {
            if (i) oss << m_delimiter;
            oss << m_segments[i];
        }
        return oss.str();
    }

    bool LogicalPath::operator==(const LogicalPath& o) const
    { return m_delimiter == o.m_delimiter && m_segments == o.m_segments; }

    bool LogicalPath::operator!=(const LogicalPath& o) const
    { return !(*this == o); }

    LogicalPath operator/(LogicalPath lhs, std::string_view rhs)
    { return lhs.push(rhs); }

    LogicalPath operator/(LogicalPath lhs, const LogicalPath& rhs)
    { return lhs.append(rhs); }

    std::ostream& operator<<(std::ostream& os, const LogicalPath& path)
    { return os << path.string(); }
}