#ifndef __BASE_CONFIG__
#define __BASE_CONFIG__

#include <map>
#include <string>

namespace base
{
    const char EXECUTABLE_PATH[] = "path";

    class Config
    {
    public:
        Config() : _data() {}

        std::string getConfig(std::string key)
        {
            return _data[key];
        }

        void addConfig(std::string key, std::string value)
        {

            _data[key] = value;
        }

        static Config *getingleton()
        {
            if (_config == nullptr)
            {
                _config = new Config;
            }
            return _config;
        }

    private:
        std::map<std::string, std::string> _data;
        static Config *_config;
    };
}
#endif