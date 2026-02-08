/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:09:10 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 16:35:51 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    
    if (!btc.loadDatabase("data.csv"))
    {
        std::cerr << "Error: could not load database." << std::endl;
        return 1;
    }
    
    btc.processInput(argv[1]);
    
    return 0;
}