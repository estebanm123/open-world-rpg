#pragma once

#include <dirent.h>

#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../Util/SpriteShadowGenerator.h"

inline const std::string ROOT = "res/";	 // refactor to portable path

namespace fs = std::experimental::filesystem;

template <typename Resource>
class ResourceManager {
public:
	ResourceManager(const std::string &folder, const std::string &extension)
		: folder(ROOT + folder + "/"),
		  extension("." + extension) {}

	const Resource &get(const std::string &name) {
		if (!exists(name)) {
			add(name);
		}

		return resources.at(name);
	}

	std::unordered_set<std::string> fetchAllResourcesInFolder(const std::string &path) const {
		std::unordered_set<std::string> result;
		for (const auto &entry : fs::directory_iterator(fs::path(folder + path))) {
			auto filePath = entry.path();
			if (!filePath.has_extension()) continue;
			auto filename = removeFileExt(filePath.filename().string());
			auto pathRelativeToResource = path + filename;
			result.insert(pathRelativeToResource);
		}

		return result;
	}

	void clear() { resources.clear(); }

	bool exists(const std::string &name) const { return resources.find(name) != resources.end(); }

	void add(const std::string &name) {
		Resource r;

		std::string fullName = getFullFilename(name);
		if (!r.loadFromFile(fullName)) {
			Resource fail;
			fail.loadFromFile(folder + "_fail_" + extension);
			resources.insert(std::make_pair(name, fail));
		} else {
			resources.insert(std::make_pair(name, r));
		}
	}

	std::string getFullFilename(const std::string &name) const { return folder + name + extension; }

private:
	std::string removeFileExt(const std::string &str) const {
		auto lastindex = str.find_last_of(".");
		return str.substr(0, lastindex);
	}

	const std::string folder;
	const std::string extension;

	std::unordered_map<std::string, Resource> resources;
};