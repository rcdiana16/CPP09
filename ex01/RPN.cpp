/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:30:00 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 16:39:08 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cctype>      

RPN::RPN() {}
RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}
RPN::~RPN() {}

bool RPN::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isNumber(const std::string& token) const
{
    return (token.length() == 1 && std::isdigit(token[0]));
}

int RPN::performOperation(int a, int b, char op) const
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Error: division by zero");
            return a / b;
        default:
            throw std::runtime_error("Error: invalid operator");
    }
}

int RPN::evaluate(const std::string& expression)
{
    while (!_stack.empty())
        _stack.pop();
    
    std::istringstream iss(expression);
    std::string token;
    
    while (iss >> token)
    {
        if (isNumber(token))
        {
            int num = token[0] - '0';
            _stack.push(num);
        }
        else if (token.length() == 1 && isOperator(token[0]))
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error: insufficient operands");
            
            int b = _stack.top();
            _stack.pop();
            
            int a = _stack.top();
            _stack.pop();

            int result = performOperation(a, b, token[0]);

            _stack.push(result);
        }
        else
        {
            throw std::runtime_error("Error: invalid token");
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error: invalid expression");
    return _stack.top();
}
