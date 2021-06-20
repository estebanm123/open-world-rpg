#pragma once

#include <string>
#include <unordered_map>
#include <vector>

inline const std::string NPC_BASE_PATH = "Npc/";
inline const std::string NPC_SHADOW_PATH = NPC_BASE_PATH + "Shadow/";

inline const std::string SHADOW_SUFFIX = "-sh";
inline const std::string COlOR_TEST_SUFFIX = "-co";
inline const std::string SIZE_TEST_SUFFIX = "-si";

namespace SpriteConstants {
inline const std::string CAT = NPC_SHADOW_PATH + "Cat";
inline const std::string SNAKE = NPC_SHADOW_PATH + "Snake";
inline const std::string BUGS = NPC_SHADOW_PATH + "Bugs";
inline const std::string BUGS2 = NPC_SHADOW_PATH + "Bugs2";

constexpr int NO_VARIANT = 0;
constexpr int NO_SIZE_ID = 0;

struct Paths {
	std::string
		basePath;  // includes size id; excludes variant id - shadows, silhouettes, etc.. are based on this
	std::string variantPath;  // includes variant id
};

struct VariantMetadata {
	const std::vector<int> whiteListedVariantIds;
	const int numSizeVariations = 1;
};

struct SpriteVariantInfo {	// for a single sprite, both zero-indexed with 0s as default sprites
	int id;
	int sizeAmount;
};

inline const std::unordered_map<std::string, VariantMetadata> variantMetadataMap{
	{CAT, VariantMetadata{std::vector<int>{NO_VARIANT, 1003}, 2}}};
}  // namespace SpriteConstants
