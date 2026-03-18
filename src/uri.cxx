#include "JAGE/core.h"

namespace JAGE
{
    static bool is_unreserved(char c)
    {
        return std::isalnum(static_cast<unsigned char>(c))
            || c == '-' || c == '_' || c == '.' || c == '~';
    }

    static char hex_to_nibble(char c)
    {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        throw URI::ParseError("invalid hex digit \""s + c + "\""s);
    }

    static char nibble_to_hex(unsigned char v) { return "0123456789ABCDEF"[v & 0x0F]; }

    namespace Data
    {
        std::string URI::to_string() const
        {
            std::ostringstream ss;

            switch (scheme)
            {
                case Scheme::UNDEFINED:
                    ss << "undef" << ':';
                break;

                case Scheme::FILE:
                    ss << "file" << ':';
                break;

                case Scheme::GPU:
                    ss << "gpu" << ':';
                break;
            }

            if (!host.empty())
            {
                ss << "//";
                if (!userinfo.empty()) ss << userinfo << '@';
                ss << host;
                if (port) ss << ':' << *port;
            }

            ss << path;

            if (!query.empty()) ss << '?' << query;
            if (!fragment.empty()) ss << '#' << fragment;

            return ss.str();
        }
    }

    namespace URI
    {
        std::string percent_encode(const std::string& input, std::string_view safe_chars)
        {
            std::string out;
            out.reserve(input.size() * 3);
            for (unsigned char c : input)
            {
                if (is_unreserved(c) || safe_chars.find(c) != std::string::npos) out += c;
                else
                {
                    out += '%';
                    out += nibble_to_hex(c >> 4);
                    out += nibble_to_hex(c);
                }
            }
            return out;
        }

        std::string percent_decode(const std::string& input)
        {
            std::string out;
            out.reserve(input.size());

            for (size_t i {}; i < input.size(); i++)
            {
                if (input[i] == '%')
                {
                    if (i + 2 >= input.size())
                    throw URI::ParseError("incomplete percent-encoding for string \"" +
                        input + "\" at position " + std::to_string(i) + ".");

                    char hi = hex_to_nibble(input[i + 1]);
                    char lo = hex_to_nibble(input[i + 2]);
                    out += static_cast<char>((hi << 4) | lo);
                    i += 2;
                }
                
                else if (input[i] == '+') out += ' ';
                else out += input[i];
            }

            return out;
        }

        ParseError::ParseError(const std::string& msg)
        : std::runtime_error("JAGE URI parser error: " + msg)
        {}

        Data::URI Parser::parse(const std::string& raw)
        {
            if (raw.empty()) throw ParseError("input is empty.");

            Data::URI out {};
            size_t pos {};

            // 1. scheme
            out.scheme = extract_scheme(raw, pos);

            // 2. authority (present when next two chars are "//")
            if (pos + 1 < raw.size() && raw[pos] == '/' && raw[pos + 1] == '/')
            {
                pos += 2; // skip "//"
                extract_authority(raw, pos, out);
            }

            // 3. path
            out.path = extract_path(raw, pos);

            // 4. query
            out.query = extract_query(raw, pos);

            // 5. fragment
            out.fragment = extract_fragment(raw, pos);

            // 6. parsed query params (convenience)
            out.query_params = parse_query_params(out.query);

            return out;
        }

        bool Parser::is_valid_scheme_char(char c, bool first)
        {
            if (first) return std::isalpha(static_cast<unsigned char>(c));
            return std::isalnum(static_cast<unsigned char>(c))
                || c == '+' || c == '-' || c == '.';
        }

        bool Parser::is_valid_host_char(char c)
        {
            return std::isalnum(static_cast<unsigned char>(c))
                || c == '-' || c == '.' || c == '[' || c == ']' || c == ':'; // IPv6 brackets
        }

        Data::URI::Scheme Parser::extract_scheme(const std::string& raw, size_t& pos)
        {
            // scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":"
            size_t i {};
            for (; i < raw.size() && raw[i] != ':' && raw[i] != '/' && raw[i] != '?' && raw[i] != '#'; i++)
            if (!is_valid_scheme_char(raw[i], i == 0)) return Data::URI::Scheme::UNDEFINED;

            if (i == 0 || i >= raw.size() || raw[i] != ':') return Data::URI::Scheme::UNDEFINED;
            std::string scheme { raw.substr(0, i) };

            // schemes are case-insensitive – normalise to lowercase
            std::transform(scheme.begin(), scheme.end(), scheme.begin(),
            [](unsigned char c){ return std::tolower(c); });

            pos = i + 1; // skip ':'
            if (scheme == "file") return Data::URI::Scheme::FILE;
            if (scheme == "gpu") return Data::URI::Scheme::GPU;
            else return Data::URI::Scheme::UNDEFINED;
        }

        void Parser::extract_authority(const std::string& raw, size_t& pos, Data::URI& out)
        {
            // authority = [ userinfo "@" ] host [ ":" port ]
            size_t end { raw.find_first_of("/?#", pos) };
            if (end == std::string::npos) end = raw.size();
            std::string authority { raw.substr(pos, end - pos) };
            pos = end;

            // userinfo
            size_t at { authority.find('@') };
            size_t host_start {};

            if (at != std::string::npos)
            {
                out.userinfo = percent_decode(authority.substr(0, at));
                host_start = at + 1;
            }

            // IPv6 literal host e.g. [::1]
            if (host_start < authority.size() && authority[host_start] == '[')
            {
                size_t close { authority.find(']', host_start) };

                if (close == std::string::npos)
                throw ParseError("unterminated IPv6 address in authority in string \"" + raw + "\".");

                out.host = authority.substr(host_start, close - host_start + 1);
                host_start = close + 1;
            }
            
            else
            {
                size_t colon { authority.find(':', host_start) };
                // watch out: colon inside IPv6 literal is already handled above
                size_t host_end { (colon != std::string::npos) ? colon : authority.size() };
                out.host = authority.substr(host_start, host_end - host_start);
                // normalise host to lowercase
                std::transform(out.host.begin(), out.host.end(), out.host.begin(),
                [](unsigned char c){ return std::tolower(c); });
                host_start = host_end;
            }

            // port
            if (host_start < authority.size() && authority[host_start] == ':')
            {
                std::string port_str { authority.substr(host_start + 1) };
                if (!port_str.empty())
                {
                    try
                    {
                        int p { std::stoi(port_str) };
                        if (p < 0 || p > 65535) throw ParseError("port out of range - " + port_str);
                        out.port = static_cast<u16>(p);
                    }
                    
                    catch (const std::invalid_argument&)
                    {
                        throw ParseError("invalid port - " + port_str);
                    }
                }
            }
        }

        std::string Parser::extract_path(const std::string& raw, size_t& pos)
        {
            size_t end { raw.find_first_of("?#", pos) };
            if (end == std::string::npos) end = raw.size();
            std::string path { raw.substr(pos, end - pos) };
            pos = end;
            return path; // deliberately NOT percent-decoded – paths may have encoded slashes
        }

        std::string Parser::extract_query(const std::string& raw, size_t& pos)
        {
            if (pos >= raw.size() || raw[pos] != '?') return "";
            ++pos; // skip '?'
            size_t end { raw.find('#', pos) };
            if (end == std::string::npos) end = raw.size();
            std::string q { raw.substr(pos, end - pos) };
            pos = end;
            return q;
        }

        std::string Parser::extract_fragment(const std::string& raw, size_t& pos)
        {
            if (pos >= raw.size() || raw[pos] != '#') return "";
            ++pos; // skip '#'
            return raw.substr(pos);
        }

        std::unordered_map<std::string,std::string>
        Parser::parse_query_params(const std::string& query)
        {
            std::unordered_map<std::string,std::string> params {};
            if (query.empty()) return params;

            std::istringstream ss { query };
            std::string token {};
            while (std::getline(ss, token, '&'))
            {
                if (token.empty()) continue;
                size_t eq { token.find('=') };
                std::string key, val;
                if (eq == std::string::npos) key = percent_decode(token);
                else
                {
                    key = percent_decode(token.substr(0, eq));
                    val = percent_decode(token.substr(eq + 1));
                }
                params[key] = val; // last-write-wins for duplicate keys
            }
            return params;
        }

        Builder& Builder::add_query_param(const std::string& key, const std::string& value)
        {
            data.query_params[key] = value;
            // rebuild raw query string
            std::ostringstream ss;
            bool first { true };
            for (const std::pair<const std::string, std::string>& query_param : data.query_params)
            {
                if (!first) ss << '&';
                ss << percent_encode(query_param.first) << '=' << percent_encode(query_param.second);
                first = false;
            }
            data.query = ss.str();
            return *this;
        }
    }
}