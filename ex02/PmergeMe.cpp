/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:00:46 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/16 15:54:03 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


bool PmergeMe::parseArgs(int argc, char **argv, std::vector<int>& vec, std::deque<int>& deq)
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        for (size_t j = 0; j < arg.size(); j++)
        {
            if (!isdigit(arg[j]))
                return false;
        }
        long val = std::stol(arg);
        if (val <= 0)
            return false;
        vec.push_back(static_cast<int>(val));
        deq.push_back(static_cast<int>(val));
    }
    return true;
}

template <typename Container>
void PmergeMe::binaryInsert(Container& sorted, typename Container::value_type value)
{
    typename Container::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

template <typename Container>
void PmergeMe::fordJohnson(Container& c)
{
    if (c.size() <= 1)
        return;

    Container larger, smaller;
    typename Container::value_type leftover;
    bool hasLeftover = false;

    for (size_t i = 0; i + 1 < c.size(); i += 2)
    {
        if (c[i] < c[i+1])
        {
            smaller.push_back(c[i]);
            larger.push_back(c[i+1]);
        }
        else
        {
            smaller.push_back(c[i+1]);
            larger.push_back(c[i]);
        }
    }
    if (c.size() % 2 != 0)
    {
        leftover = c.back();
        hasLeftover = true;
    }

    fordJohnson(larger);

    Container result = larger;
    for (size_t i = 0; i < smaller.size(); i++)
    {
        binaryInsert(result, smaller[i]);
    }

    if (hasLeftover)
    {
        binaryInsert(result, leftover);
    }
    c = result;
}

void PmergeMe::fordJohnsonSort(std::vector<int>& container)
{
    fordJohnson(container);
}

void PmergeMe::fordJohnsonSort(std::deque<int>& container)
{
    fordJohnson(container);
}

void PmergeMe::run(int argc, char **argv) {
    std::vector<int> vec;
    std::deque<int> deq;

    if (!parseArgs(argc, argv, vec, deq))
        throw std::runtime_error("Invalid input");

    // Display before
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    // Vector timing
    clock_t startVec = clock();
    fordJohnsonSort(vec);
    clock_t endVec = clock();

    // Deque timing
    clock_t startDeq = clock();
    fordJohnsonSort(deq);
    clock_t endDeq = clock();

    // Display after
    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    double durVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;
    double durDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << durVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque  : " << durDeq << " us" << std::endl;
}
