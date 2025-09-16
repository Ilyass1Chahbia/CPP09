/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:02:27 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/15 17:09:32 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <cctype>

int RPN::evaluate(const std::string& expression)
{
    std::istringstream iss(expression);
    std::stack<int> stack;
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1 && std::isdigit(token[0]))
        {
            stack.push(token[0] - '0');
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error: need more numbers");

            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int result = 0;

            if (token == "+")
                result = a + b;
            else if (token == "-")
                result = a - b;
            else if (token == "*")
                result = a * b;
            else if (token == "/")
            {
                if (b == 0)
                    throw std::runtime_error("Error: division by zero");
                result = a / b;
            }
            stack.push(result);
        }
        else
        {
            throw std::runtime_error("Error: invalid token");
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("Error: need more operators");
    return stack.top();
}
