#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>

class Log
{
public:
	static void info(const std::string &m) { std::cout << "[INFO] :" << m << std::endl; }
	static void warn(const std::string &m) { std::cout << "[WARN] :" << m << std::endl; }
	static void error(const std::string &m) { std::cout << "[ERROR] :" << m << std::endl; }
};

#endif