#include "Distance.hpp"
#include <ostream>
#include <sstream>
#include <iomanip>

static std::string fmt(double x, int prec) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(prec) << x;
    std::string s = ss.str();
    size_t p = s.find('.');
    if (p != std::string::npos) {
        while (!s.empty() && s.back()=='0') s.pop_back();
        if (!s.empty() && s.back()=='.') s.pop_back();
    }
    return s;
}

std::ostream& operator<<(std::ostream& out, const Distance& d) {
    out << fmt(d.distance, 4)
        << " [" << d.word << "]";
    return out;
}