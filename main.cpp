/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:05:03 by yabukirento       #+#    #+#             */
/*   Updated: 2025/09/12 20:05:05 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Log.hpp"

int	main(int argc, char **argv) {
	(void) argc;
	(void) argv;
	Log::info("Server Starting ...");
	Log::info("Server Finishing ...");
	return 0;
}