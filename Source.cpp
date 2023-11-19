#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <regex>
//#include "dependencies/include/nlohmann/json.hpp"

void runProgram(const std::string& programPath, const std::string& filePath, const std::string& parameters = "") {
    std::string command = programPath + " " + filePath + " " + parameters;
    if (parameters != "")
    {
        command += " " + parameters;
    }

    system(command.c_str());
}





int main(int argc, char* argv[]) {
    //добавить проверку python программы
    /*
	std::string filePath = "C:/Users/AlexLip/Desktop/6) UE4.Coding.rar";

    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Error: File not found at " + filePath);
    }
     */




    std::string selfPath(argv[0]);
    //std::cout << selfPath << std::endl;
    std::string mainPython = std::regex_replace(selfPath, std::regex("GSPMWindows.exe"), "main.py");
    //std::cout << mainPython << std::endl;



    if (argc < 2) {
        runProgram("C:/Python3/pythonw.exe", mainPython);
    }
    else
    {
        std::string parameters = argv[1];
        //std::cout << parameters << std::endl;
        runProgram("C:/Python3/pythonw.exe", mainPython, parameters);
    }
    return 0;

}

