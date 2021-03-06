/* A tool for collecting, visualizing and annotating 3D Interaction data
 *
 * Copyright (C) 2017-2019 University of Illinois at Chicago
 *
 * Author: Harish G. Naik <hnaik2@uic.edu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "logger.h"

#include <cstring>
#include <ctime>
#include <string>

#include <boost/log/attributes/mutable_constant.hpp>

#include "utils.h"

namespace ipme {
namespace utils {
namespace attrs = logging::attributes;
namespace src = logging::sources;
namespace expr = logging::expressions;
namespace kw = logging::keywords;

logging::sources::severity_logger<logging::trivial::severity_level> Logger::log;

template <typename Value>
Value set_get_attrib(const char* name, Value value)
{
    auto attr = logging::attribute_cast<attrs::mutable_constant<Value>>(
        logging::core::get()->get_thread_attributes()[name]);
    attr.set(value);
    return attr.get();
}

std::string path_to_filename(const std::string& path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

/* static */ void Logger::init(const std::string& file_prefix)
{
    logging::core::get()->add_thread_attribute(
        "file", attrs::mutable_constant<std::string>{""});
    logging::core::get()->add_thread_attribute("line",
                                               attrs::mutable_constant<int>{0});

    logging::add_file_log(
        kw::auto_flush = true,
        kw::file_name = file_prefix + "_" +
                        create_timestamp_string("%Y%m%d_%H%M%S") + "_%N.log",
        kw::format = (expr::stream
                      << expr::format_date_time<boost::posix_time::ptime>(
                             "TimeStamp", "%Y%m%d %H:%M:%S")
                      << " [" << std::left << std::setw(8) << std::setfill(' ')
                      << logging::trivial::severity << "] " << expr::smessage));
    logging::add_common_attributes();
}

void Logger::set_severity(const trivial::severity_level severity)
{
    logging::core::get()->set_filter(trivial::severity >= severity);
}

} // namespace utils
} // namespace ipme
