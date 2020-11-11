#pragma once

#include <unordered_map>
#include <string>

template<typename Resource>
class ResourceManager
{
    public:
        ResourceManager (const std::string& folder, const std::string& extension)
       :   folder    ("res/" + folder + "/")
        ,   extension ("." + extension)
        { }

        const Resource& get(const std::string& name)
        {
            if (!exists(name)) {
                add(name);
            }

            return resources.at(name);
        }

        bool exists(const std::string& name) const
        {
            return resources.find(name) != resources.end();
        }

        void add(const std::string& name)
        {
            Resource r;

            std::string fullName = getFullFilename(name);
            if(!r.loadFromFile(fullName)) {
                Resource fail;
                fail.loadFromFile(folder + "_fail_" + extension);
                resources.insert(std::make_pair(name, fail));
            } else {
                resources.insert(std::make_pair(name, r));
            }
        }

    private:
        std::string getFullFilename(const std::string& name) const
        {
            return folder + name + extension;
        }

        const std::string folder;
        const std::string extension;

        std::unordered_map<std::string, Resource> resources;
};