/*
 * @Author: gongluck 
 * @Date: 2020-03-23 15:13:13 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-03-23 15:17:56
 */

#include "config.h"
#include <boost/property_tree/ini_parser.hpp>

namespace gconf
{
int config::open(const char *configfile)
{
    if (configfile == nullptr)
    {
        return G_ERROR_INVALIDPARAM;
    }

    try
    {
        boost::property_tree::ini_parser::read_ini(configfile, lvptProperties_);
    }
    catch (std::exception &e)
    {
        std::cerr << __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
        return G_ERROR_INVALIDPARAM;
    }

    return G_ERROR_SUCCEED;
}

int config::readall(const char *session,
                    std::vector<std::pair<std::string, std::string>> &results,
                    const char *configfile /*= nullptr*/)
{
    if (configfile != nullptr && open(configfile) != 0)
    {
        std::cerr << __FILE__ << " : " << __LINE__ << " : "
                  << " can not open " << configfile << std::endl;
        return G_ERROR_INVALIDPARAM;
    }

    try
    {
        auto lvbtItems = lvptProperties_.get_child(session);
        for (const auto &i : lvbtItems)
        {
            results.push_back(std::make_pair(i.first.data(), i.second.data()));
        }
    }
    catch (std::exception &e)
    {
        std::cerr << __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
        return G_ERROR_INVALIDPARAM;
    }

    return G_ERROR_SUCCEED;
}
} // namespace gconf
