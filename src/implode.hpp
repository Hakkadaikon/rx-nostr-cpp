#ifndef IMPLODE_HPP
#define IMPLODE_HPP

#include <string>

namespace rx_nostr
{
template <typename Iter>
std::string implode(Iter begin, Iter end, const std::string& separator)
{
    std::string result;
    if (begin != end) {
        result += std::to_string(*begin++);
    }
    while (begin != end) {
        result += separator + std::to_string(*begin++);
    }
    return result;
}
}  // namespace rx_nostr

#endif  // IMPLODE_HPP
