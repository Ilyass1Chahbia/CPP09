/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:29:56 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/17 14:15:02 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv) {
    try {
        PmergeMe::run(argc, argv);
    } catch (...) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}

