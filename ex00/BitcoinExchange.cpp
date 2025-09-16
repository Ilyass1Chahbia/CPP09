#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    this->data = other.data;
    return *this;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
}
BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("could not open file.");

    file.seekg(0, std::ios::end); // set cursor position !!!
    if (file.tellg() == 0) // get cusor postion !!!
        throw std::runtime_error("file is empty.");
    file.seekg(0, std::ios::beg);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date, rest;
        if (!std::getline(ss, date, ',') || !std::getline(ss, rest))
            continue;
        double rate = std::strtod(rest.c_str(), NULL);
        data[date] = rate;
    }
}

bool isValidNumber(const std::string& str)
{
    bool pt = false;

    if (str.empty())
        return false;

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            if (!std::isdigit(str[i + 1]) )
                return false;
            if (pt)
                return false;
            pt = true;
        }
        else if (!std::isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

void BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    if (line != "date | value")
    {
        throw std::runtime_error("Error: bad header, expected \"date | value\"");
    }
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::istringstream ss(line);
        std::string date, valueStr;

        if (!std::getline(ss, date, '|'))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!std::getline(ss, valueStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (line[11] != '|' || line[12] != ' ' || !std::isdigit(line[13]))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;            
        }
        while (!date.empty() && std::isspace(date[date.size() - 1]))
            date.erase(date.size() - 1);
        while (!valueStr.empty() && std::isspace(valueStr[0]))
            valueStr.erase(0, 1);

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        if (!isValidNumber(valueStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        double value;
        if (!isValidValue(valueStr, value))
            continue;

        std::string dbDate = findClosestDate(date);
        if (dbDate.empty())
        {
            std::cerr << "Error: no suitable date found in database." << std::endl;
            continue;
        }

        double result = value * data[dbDate];
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10)
        return false;

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
        {
            if (date[i] != '-')
                return false;
        }
        else
        {
            if (!std::isdigit(date[i]))
                return false;
        }
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2000 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (leap) daysInMonth[1] = 29;
    if (day > daysInMonth[month - 1])
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const
{
    char* end;
    value = std::strtod(valueStr.c_str(), &end);
    if (*end != '\0')
    {
        std::cerr << "Error: bad input => " << valueStr << std::endl;
        return false;
    }
    if (value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const
{
    std::map<std::string, double>::const_iterator it = data.lower_bound(date);
    if (it == data.end())
    {
        --it;
    }
    else if (it->first != date)
    {
        if (it == data.begin())
            return "";
        --it;
    }
    return it->first;
}
