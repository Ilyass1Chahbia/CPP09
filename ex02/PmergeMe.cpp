/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:00:46 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/17 18:27:50 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

long PmergeMe::getTimeUSec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000L + tv.tv_usec;
}

bool PmergeMe::parseArgs(int argc, char **argv,
                         std::vector<int> &vec,
                         std::deque<int> &deq)
{
    for (int i = 1; i < argc; i++)
    {
        char *end;
        long val = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || val <= 0 || val > INT_MAX)
            return false;

        vec.push_back(static_cast<int>(val));
        deq.push_back(static_cast<int>(val));
    }
    return true;
}

template <typename Container>
void PmergeMe::binaryInsert(Container &sorted, typename Container::value_type value)
{
    typename Container::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

template <typename Container>
void PmergeMe::fordJohnson(Container &c)
{
    if (c.size() <= 1)
        return;

    Container larger;
    Container smaller;
    typename Container::value_type leftover;
    bool hasLeftover = false;

    for (size_t i = 0; i + 1 < c.size(); i += 2)
    {
        if (c[i] < c[i + 1])
        {
            smaller.push_back(c[i]);
            larger.push_back(c[i + 1]);
        }
        else
        {
            smaller.push_back(c[i + 1]);
            larger.push_back(c[i]);
        }
    }
    if (c.size() % 2 != 0)
    {
        leftover = c[c.size() - 1];
        hasLeftover = true;
    }

    fordJohnson(larger);

    Container result = larger;
    for (typename Container::iterator it = smaller.begin(); it != smaller.end(); ++it)
        binaryInsert(result, *it);

    if (hasLeftover)
        binaryInsert(result, leftover);

    c = result;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &arr)
{
    fordJohnson(arr);
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &arr)
{
    fordJohnson(arr);
}

void PmergeMe::run(int argc, char **argv)
{
    std::vector<int> vec;
    std::deque<int> deq;

    if (!parseArgs(argc, argv, vec, deq))
        throw std::runtime_error("Error");

    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    long startVec = getTimeUSec();
    fordJohnsonVector(vec);
    long endVec = getTimeUSec();
    double durVec = static_cast<double>(endVec - startVec);

    long startDeq = getTimeUSec();
    fordJohnsonDeque(deq);
    long endDeq = getTimeUSec();
    double durDeq = static_cast<double>(endDeq - startDeq);

    std::cout << "After:  ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << durVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque  : " << durDeq << " us" << std::endl;
}

