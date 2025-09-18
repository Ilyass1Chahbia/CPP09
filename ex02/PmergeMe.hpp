/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:29:45 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/18 18:01:22 by ilchahbi         ###   ########.fr       */
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
    void run(int argc, char **argv);

private:
    bool parse_args(int argc, char **argv, std::vector<int> &vec, std::deque<int> &deq);
    long get_time();

    std::vector<size_t> jacobsthal_sequence(size_t n);
    void ford_johnson_vect(std::vector<int> &arr);
    void ford_johnson_deq(std::deque<int> &arr);

    template <typename Container>
    void ford_johnson_alg(Container &c);

    template <typename Container>
    void binary_insert(Container &sorted, typename Container::value_type value);
};

#endif


