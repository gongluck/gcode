/*
 * @Author: gongluck 
 * @Date: 2020-03-23 15:11:50 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-03-23 15:17:58
 */

// Profile read, dependent on boost

#pragma once

#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>

namespace gconf
{
class config
{
public:
    int open(const char *configfile);
    template <typename T>
    int read(const char *session, const char *key, T &value, const char *configfile = nullptr)
    {
        if (configfile != nullptr && open(configfile) != 0)
        {
            return -1;
        }

        try
        {
            auto lvbtItems = lvptProperties_.get_child(session);
            value = lvbtItems.get<T>(key);
        }
        catch (std::exception &e)
        {
            std::cerr << __FILE__ << " : " << __LINE__ << " : " << e.what() << std::endl;
            return -1;
        }

        return 0;
    }
    int readall(const char *session,
                std::vector<std::pair<std::string, std::string>> &results,
                const char *configfile = nullptr);

private:
    boost::property_tree::ptree lvptProperties_;
};
} // namespace gconf
