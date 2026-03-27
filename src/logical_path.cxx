#include "JAGE/core.h"

#include "log.h"

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

    bool LogicalPath::validate_segment(std::string_view segment) const
    {
        if (segment.empty())
        {
            JAGE_MSG_ERROR("JAGE logical path error: path segment must bot be empty.");
            return false;
        }

        if (segment.find(m_delimiter) != std::string_view::npos)
        {

            JAGE_MSG_ERROR("JAGE logical path error: path segment must not contain the delimiter.");
            return false;
        }

        return true;
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

    LogicalPath& LogicalPath::push(std::string_view segment)
    {
        validate_segment(segment);
        m_segments.emplace_back(segment);
        return *this;
    }

    std::string LogicalPath::pop()
    {
        if (m_segments.empty()) return ""s;
        std::string last = std::move(m_segments.back());
        m_segments.pop_back();
        return last;
    }

    LogicalPath& LogicalPath::append(const LogicalPath& other)
    {
        if (other.m_delimiter != m_delimiter)
        {
            JAGE_MSG_ERROR("JAGE logical path error: cannot append paths with different delimiters.");
            JAGE_MSG_ERROR("Cancelling appending path operation.");
            return *this;
        }

        for (const auto& s : other.m_segments) m_segments.push_back(s);

        return *this;
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

    bool LogicalPath::operator==(const LogicalPath& other) const
    { return m_delimiter == other.m_delimiter && m_segments == other.m_segments; }

    bool LogicalPath::operator!=(const LogicalPath& other) const
    { return !(*this == other); }

    LogicalPath operator/(LogicalPath lhs, std::string_view rhs)
    { return lhs.push(rhs); }

    LogicalPath operator/(LogicalPath lhs, const LogicalPath& rhs)
    { return lhs.append(rhs); }

    std::ostream& operator<<(std::ostream& os, const LogicalPath& path)
    { return os << path.string(); }
}