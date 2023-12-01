#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <regex>
#include <windows.h> 
#include "dependencies/include/nlohmann/json.hpp"

void runProgram(const std::string& programPath, const std::string& filePath, const std::string& parameters = "") {
    std::string command = programPath + " " + filePath;
    if (parameters != "")
    {
        command += " " + parameters;
    }
    system(command.c_str());
}

nlohmann::json data(std::string file = "")
{

    std::ifstream ifs(file);
    nlohmann::json jf = nlohmann::json::parse(ifs);
    return jf;
}

std::string getPythonPath(std::string selfPath)

{
    //std::string configFile = "E:/Projects/core/GeterozisProjectManager/GeterosisProjectManager/Python.json";
    std::string configFile = std::regex_replace(selfPath, std::regex("GSPMWindows.exe"), "Python.json");
    std::string pythonPath;
    nlohmann::json config = data(configFile);

    if (config["is custom python"] == true)
    {
        pythonPath = config["cutsom python path"];
        std::ifstream file(pythonPath);
        if (!file) {
            pythonPath = config["default python path"];
            std::ifstream file(pythonPath);
            if (!file)
            {
                std::string customPython = config["cutsom python path"];
                std::string defaultPython = config["default python path"];
                throw std::runtime_error("Error: Cutsom python path not found: " + customPython + ", and default python path not found: " + defaultPython);
            }
        }
    }
    else
    {
        pythonPath = config["default python path"];
        std::ifstream file(pythonPath);
        if (!file)
        {
            pythonPath = config["cutsom python path"];
            std::ifstream file(pythonPath);
            if (!file)
            {
                std::string customPython = config["cutsom python path"];
                std::string defaultPython = config["default python path"];
                throw std::runtime_error("Error: Default python path not found: " + defaultPython + ", and Cutsom python path not found: " + customPython);
            }
        }
    }
    return pythonPath;
}

int main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    std::string pythonPath = getPythonPath(argv[0]);
    //std::string mainPython = "E:/Projects/core/GeterozisProjectManager/GeterosisProjectManager/main.py";
	std::string mainPython = std::regex_replace(argv[0], std::regex("GSPMWindows.exe"), "main.py");

    if (argc < 2) {
        runProgram(pythonPath, mainPython);
    }
    else
    {
        if (strcmp(argv[1], "-console") == 0)
        {
            std::cout << argv[0] << std::endl;
            std::cout << argv[1] << std::endl;
            ShowWindow(GetConsoleWindow(), SW_SHOW);
            runProgram(pythonPath, mainPython);
        }
        else
        {
            runProgram(pythonPath, mainPython, argv[1]);
        }
    }
    return 0;

}
