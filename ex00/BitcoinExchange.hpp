/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:37:48 by ilchahbi          #+#    #+#             */
/*   Updated: 2025/09/13 17:27:37 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <cctype>

class BitcoinExchange
{
    private:
        std::map<std::string, double> data;
        bool isValidDate(const std::string& date) const;
        bool isValidValue(const std::string& valueStr, double& value) const;
        std::string findClosestDate(const std::string& date) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
        void loadDatabase(const std::string& filename);
        void processInput(const std::string& filename);
};

#endif