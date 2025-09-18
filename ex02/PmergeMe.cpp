/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:00:46 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/18 19:23:19 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

long PmergeMe::get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000L + tv.tv_usec;
}

bool PmergeMe::parse_args(int argc, char **argv, std::vector<int> &vec, std::deque<int> &deq)
{
    for (int i = 1; i < argc; i++)
    {
        char *endptr;
        long val = std::strtol(argv[i], &endptr, 10);
        if (*endptr != '\0' || val <= 0 || val > INT_MAX)
            return false;
        vec.push_back(static_cast<int>(val));
        deq.push_back(static_cast<int>(val));
    }
    return true;
}

template <typename Container>
void PmergeMe::binary_insert(Container &c, typename Container::value_type value)
{
    typename Container::iterator low = c.begin();
    typename Container::iterator high = c.end();

    while (low < high)
    {
        typename Container::iterator mid = low + (high - low) / 2;
        if (*mid < value)
            low = mid + 1;
        else
            high = mid;
    }
    c.insert(low, value);
}

std::vector<size_t> PmergeMe::jacobsthal_sequence(size_t n)
{
    std::vector<size_t> seq;
    if (n == 0) return seq;

    std::vector<size_t> jac;
    jac.push_back(0);
    jac.push_back(1);
    while (jac.back() < n)
        jac.push_back(jac[jac.size() - 1] + 2 * jac[jac.size() - 2]);

    size_t prev = 1;
    for (size_t i = 2; i < jac.size(); ++i)
    {
        size_t cur = jac[i];
        if (cur > n) cur = n;
        for (size_t j = prev + 1; j <= cur; ++j)
            seq.push_back(j);
        prev = cur;
    }

    if (seq.empty() || seq[0] != 1)
        seq.insert(seq.begin(), 1);

    return seq;
}

template <typename Container>
void PmergeMe::ford_johnson_alg(Container &c)
{
    if (c.size() <= 1)
        return;

    Container large;
    Container small;
    typename Container::value_type rest;
    bool has_rest = false;

    for (size_t i = 0; i + 1 < c.size(); i += 2)
    {
        if (c[i] < c[i + 1])
        {
            small.push_back(c[i]);
            large.push_back(c[i + 1]);
        }
        else
        {
            small.push_back(c[i + 1]);
            large.push_back(c[i]);
        }
    }

    if (c.size() % 2 != 0)
    {
        rest = c.back();
        has_rest = true;
    }

    ford_johnson_alg(large);

    Container result = large;

    std::vector<size_t> order = jacobsthal_sequence(small.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        size_t idx = order[i];
        if (idx > 0 && idx <= small.size())
            binary_insert(result, small[idx - 1]);
    }

    if (has_rest)
        binary_insert(result, rest);

    c = result;
}

void PmergeMe::run(int argc, char **argv)
{
    std::vector<int> vec;
    std::deque<int> deq;
    
    long vec_start = get_time();
    long deq_start = get_time();
    if (!parse_args(argc, argv, vec, deq))
        throw std::runtime_error("Error");

    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    ford_johnson_alg(vec);
    long vec_end = get_time();
    double vec_time = static_cast<double>(vec_end - vec_start);

    ford_johnson_alg(deq);
    long deq_end = get_time();
    double deq_time = static_cast<double>(deq_end - deq_start);

    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << vec_time << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque  : " << deq_time << " us" << std::endl;
}
