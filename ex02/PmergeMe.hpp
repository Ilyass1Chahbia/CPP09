/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:29:45 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/17 18:18:32 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <iomanip>
#include <sys/time.h>
#include <cstdlib>
#include <climits>
#include <algorithm>

class PmergeMe
{
public:
    static void run(int argc, char **argv);

private:
    static bool parseArgs(int argc, char **argv,
                          std::vector<int> &vec,
                          std::deque<int> &deq);
    static long getTimeUSec();

    static void fordJohnsonVector(std::vector<int> &arr);
    static void fordJohnsonDeque(std::deque<int> &arr);

    template <typename Container>
    static void fordJohnson(Container &c);

    template <typename Container>
    static void binaryInsert(Container &sorted, typename Container::value_type value);
};

#endif


