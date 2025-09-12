/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 19:15:16 by yabukirento       #+#    #+#             */
/*   Updated: 2025/09/12 19:19:30 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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