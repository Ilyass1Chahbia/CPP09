/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:29:56 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/18 18:05:45 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        PmergeMe p;
        p.run(argc, argv);
    }
    catch (...)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}

