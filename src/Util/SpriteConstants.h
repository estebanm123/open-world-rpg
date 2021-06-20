#pragma once

#include <string>
#include <unordered_map>
#include <vector>

inline const std::string NPC_BASE_PATH = "Npc/";
inline const std::string NPC_SHADOW_PATH = NPC_BASE_PATH + "Shadow/";

namespace BeastSpritesConstants {
inline const std::string CAT = NPC_SHADOW_PATH + "Cat";
inline const std::string SNAKE = NPC_SHADOW_PATH + "Snake";
inline const std::string BUGS = NPC_SHADOW_PATH + "Bugs";
inline const std::string BUGS2 = NPC_SHADOW_PATH + "Bugs2";

struct VariantMetadata {
	std::vector<int> whiteListedVariantIds;
	int numSizeVariations = 2;
};

inline const std::unordered_map<std::string, VariantMetadata> VariantMetadataMap{
	{CAT, VariantMetadata{std::vector<int>{500}}}

};

}  // namespace BeastSpritesConstants
