#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
class NetParser
{
public:
	static std::string NetSettings(const int gamemode,const int timeControl,const int increment,const bool playerColor)
	{
		nlohmann::json jsonData;
		jsonData["gameMode"] = gamemode;
		jsonData["timeControl"] = timeControl;
		jsonData["increment"] = increment;
		jsonData["playerColor"] = playerColor;
		std::string jsonString = jsonData.dump();
		std::cout << jsonData.dump() << std::endl;
		return jsonString;
	}
};

