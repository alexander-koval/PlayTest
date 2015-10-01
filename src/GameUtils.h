#pragma once
class GameUtils {
public:
	static std::map<std::string, float> GetConfigParams(std::string filename);
private:
	static std::pair<std::string, float> GetKeyValuePair(std::string content);
};

