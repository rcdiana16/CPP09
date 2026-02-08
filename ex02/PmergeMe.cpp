/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:53:22 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 16:45:07 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    (void)other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::binaryInsertVector(std::vector<int>& vec, int value)
{
    if (vec.empty())
    {
        vec.push_back(value);
        return;
    }

    int left = 0;
    int right = vec.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (value < vec[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    vec.insert(vec.begin() + left, value);
}

void PmergeMe::sortVector(std::vector<int>& vec)
{
    if (vec.size() <= 1)
        return;
    
    if (vec.size() == 2)
    {
        if (vec[0] > vec[1])
            std::swap(vec[0], vec[1]);
        return;
    }

    if (vec.size() <= 20)
    {
        std::sort(vec.begin(), vec.end());
        return;
    }

    int straggler = -1;
    bool hasStraggler = (vec.size() % 2 != 0);
    
    if (hasStraggler)
    {
        straggler = vec.back();
        vec.pop_back();
    }
    
    std::vector<int> larger;
    std::vector<int> smaller;

    for (size_t i = 0; i < vec.size(); i += 2)
    {
        int a = vec[i];
        int b = vec[i + 1];

        if (a > b)
        {
            larger.push_back(a);
            smaller.push_back(b);
        }
        else
        {
            larger.push_back(b);
            smaller.push_back(a);
        }
    }
    sortVector(larger);
    for (size_t i = 0; i < smaller.size(); ++i)
    {
        binaryInsertVector(larger, smaller[i]);
    }
    if (hasStraggler)
    {
        binaryInsertVector(larger, straggler);
    }
    vec = larger;
}

void PmergeMe::binaryInsertDeque(std::deque<int>& deq, int value)
{
    if (deq.empty())
    {
        deq.push_back(value);
        return;
    }
    
    int left = 0;
    int right = deq.size() - 1;
    
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        
        if (value < deq[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    
    deq.insert(deq.begin() + left, value);
}

void PmergeMe::sortDeque(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return;
    
    if (deq.size() == 2)
    {
        if (deq[0] > deq[1])
            std::swap(deq[0], deq[1]);
        return;
    }
    
    if (deq.size() <= 20)
    {
        std::sort(deq.begin(), deq.end());
        return;
    }
    
    int straggler = -1;
    bool hasStraggler = (deq.size() % 2 != 0);
    
    if (hasStraggler)
    {
        straggler = deq.back();
        deq.pop_back();
    }
    
    std::deque<int> larger;
    std::deque<int> smaller;
    
    for (size_t i = 0; i < deq.size(); i += 2)
    {
        int a = deq[i];
        int b = deq[i + 1];
        
        if (a > b)
        {
            larger.push_back(a);
            smaller.push_back(b);
        }
        else
        {
            larger.push_back(b);
            smaller.push_back(a);
        }
    }
    
    sortDeque(larger);
    
    for (size_t i = 0; i < smaller.size(); ++i)
    {
        binaryInsertDeque(larger, smaller[i]);
    }
    
    if (hasStraggler)
    {
        binaryInsertDeque(larger, straggler);
    }
    
    deq = larger;
}
