/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:03:36 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 16:42:30 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>  
#include <iomanip>      

double getTimeInMicroseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

bool isValidNumber(const std::string& str)
{
    if (str.empty())
        return false;
    
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    char* endptr;
    long num = std::strtol(str.c_str(), &endptr, 10);
    return (*endptr == '\0' && num >= 0 && num <= 2147483647);
}

void printNumbers(const std::vector<int>& vec)
{
    size_t limit = (vec.size() > 5) ? 5 : vec.size();
    
    for (size_t i = 0; i < limit; ++i)
    {
        std::cout << vec[i];
        if (i < limit - 1)
            std::cout << " ";
    } 
    if (vec.size() > 5)
        std::cout << " [...]";
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::vector<int> numbers;
    
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        
        if (!isValidNumber(arg))
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }

        int num = std::atoi(arg.c_str());
        numbers.push_back(num);
    }

    std::vector<int> vec = numbers;

    std::deque<int> deq;
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        deq.push_back(numbers[i]);
    }

    std::cout << "Before: ";
    printNumbers(numbers);
    std::cout << std::endl;

    PmergeMe sorter;
    
    double startVector = getTimeInMicroseconds();

    sorter.sortVector(vec);

    double endVector = getTimeInMicroseconds();

    double timeVector = endVector - startVector;
    
    double startDeque = getTimeInMicroseconds();

    sorter.sortDeque(deq);

    double endDeque = getTimeInMicroseconds();

    double timeDeque = endDeque - startDeque;

    std::cout << "After: ";
    printNumbers(vec);
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);

    std::cout << "Time to process a range of " << numbers.size() 
              << " elements with std::vector : " 
              << timeVector << " us" << std::endl;

    std::cout << "Time to process a range of " << numbers.size() 
              << " elements with std::deque : " 
              << timeDeque << " us" << std::endl;
    
    return 0;
}
