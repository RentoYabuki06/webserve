/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 04:57:55 by yabukirento       #+#    #+#             */
/*   Updated: 2025/05/19 04:59:40 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/Server.hpp"

int	main(int argc, char *argv) {
	try
	{
		Server server(8080);
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}