/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:08:33 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 16:33:12 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    for (size_t i = 0; i < date.length(); ++i)
    {
        if (i != 4 && i != 7 && !std::isdigit(date[i]))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    
    return (year >= 1000 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
}

bool BitcoinExchange::isValidValue(const std::string& value) const
{
    if (value.empty())
        return false;
    
    char* endptr;
    double val = std::strtod(value.c_str(), &endptr);
    
    return (*endptr == '\0' && val >= 0 && val <= 1000);
}

double BitcoinExchange::stringToDouble(const std::string& str) const
{
    return std::strtod(str.c_str(), NULL);
}

bool BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
        return false;
    
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        size_t pos = line.find(',');

        if (pos != std::string::npos)
        {
            std::string date = line.substr(0, pos);
            
            std::string price = line.substr(pos + 1);

            _database[date] = stringToDouble(price);
        }
    }
    return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const
{
    std::map<std::string, double>::const_iterator it = _database.lower_bound(date);
    
    if (it != _database.begin() && (it == _database.end() || it->first != date))
        --it;
    return (it != _database.end()) ? it->second : 0.0;
}

void BitcoinExchange::processInput(const std::string& filename) const
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line))
    {
        size_t pos = line.find(" | ");
        if (pos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        
        std::string date = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 3);

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!isValidValue(valueStr))
        {
            double val = stringToDouble(valueStr);
            if (val < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            else
                std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double value = stringToDouble(valueStr);
        double rate = getExchangeRate(date);

        std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
    }
}