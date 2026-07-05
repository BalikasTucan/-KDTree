#ifndef DISTANCE_HPP
#define DISTANCE_HPP

#include <string>
#include <ostream>

struct Distance {
    double distance;
    std::string word;
};
std::ostream& operator<<(std::ostream& out, const Distance& d);

#endif