#ifndef IPME_UTILS_JSON_H
#define IPME_UTILS_JSON_H

#include <filesystem>
#include <iostream>
#include <istream>
#include <ostream>
#include <string_view>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace ipme {
namespace utils {
class Json {
public:
    void read(const std::filesystem::path& path);

    void read(std::istream& in);

    template <typename ElementValue = std::string>
    ElementValue get(std::string_view path) const;

    boost::property_tree::ptree get_node(std::string_view path)
    {
        return ptree_.get_child(path.data());
    }

    std::string to_string() const;

private:
    boost::property_tree::ptree ptree_;
};
} // namespace utils
} // namespace ipme

#include "json.ipp"

#endif // IPME_UTILS_JSON_H
