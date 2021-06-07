#pragma once

#include <memory>

class Item;

class ItemInitializer {
public:
	struct Config {};

	virtual std::unique_ptr<Item> initializeItem(Config config);
};
