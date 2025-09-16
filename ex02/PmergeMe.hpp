/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:29:45 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/16 15:44:53 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <ctime> 
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <algorithm>

class PmergeMe
{
public:
    static void run(int argc, char **argv);

private:
    static bool parseArgs(int argc, char **argv, std::vector<int>& vec, std::deque<int>& deq);

    static void fordJohnsonSort(std::vector<int>& container);
    static void fordJohnsonSort(std::deque<int>& container);

    template <typename Container>
    static void fordJohnson(Container& c);

    template <typename Container>
    static void binaryInsert(Container& sorted, typename Container::value_type value);
};

#endif
