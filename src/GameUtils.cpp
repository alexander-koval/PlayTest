#include "stdafx.h"
#include "GameUtils.h"

std::map<std::string, float> GameUtils::GetConfigParams(std::string filename) {
	std::map<std::string, float> config_map;
	if (Core::fileSystem.FileExists(filename)) {
		IO::InputStreamPtr stream(Core::fileSystem.OpenRead("input.txt"));
		if (stream) {
			size_t start = 0;
			std::vector<uint8_t> data;
			stream->ReadAllBytes(data);
			std::string content(data.begin(), data.end());
			while (start < content.length()) {
				const size_t pos = content.find('\n', start);
				const std::string duplicate = content.substr(start, pos - start);
				if (duplicate[0] != '#') {
					std::pair<std::string, float> key_value = GetKeyValuePair(duplicate);
					if (!key_value.first.empty() && key_value.second) {
						config_map.insert(key_value);
					}
				}
				if (pos == std::string::npos) {
					break;
				}
				start = pos + 1;
			}
		}
	}
	return config_map;
}

std::pair<std::string, float> GameUtils::GetKeyValuePair(std::string content) {
	size_t start = 0;
	float result = 0.f;
	const size_t pos = content.find('=', start);
	const std::string key = content.substr(start, pos - start);
	const std::string value = content.substr(pos + 1, content.length() - 1);
	try {
		result = utils::lexical_cast<float>(value);
	} catch (std::exception&) {
		Log::log.WriteError("Error: Input string was not valid");
	}
	return std::make_pair(key, result);
}