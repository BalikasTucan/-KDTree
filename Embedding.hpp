#ifndef EMBEDDING_HPP
#define EMBEDDING_HPP

#include <string>
#include <vector>
#include "InvalidFileException.hpp"
#include "InvalidDimensionsException.hpp"

class Embedding {
private:
    std::string word;
    std::vector<double> v;

public:
    
    Embedding(const char* line);
    Embedding(const std::string& line);
    Embedding(const Embedding& e);

    
    std::string getWord() const;
    std::vector<double> getVector() const;
    int getDimensions() const;


    Embedding& operator=(const Embedding& e);
    Embedding& operator+=(const Embedding& e);
    Embedding& operator-=(const Embedding& e);

    
    Embedding operator+(const Embedding& e) const;
    Embedding operator-(const Embedding& e) const;

    
    double operator*(const Embedding& e) const;  
    double operator!() const;                   


    friend std::ostream& operator<<(std::ostream& stream, const Embedding& e);
};


std::vector<Embedding> readVectors(const std::string& filename);

#endif
