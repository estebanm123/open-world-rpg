#pragma once

#include <string>
class NpcPath;

struct AiDebug {
	static void printPath(NpcPath path, const std::string& message = "");
};
