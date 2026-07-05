#include "Embedding.hpp"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>


Embedding::Embedding(const char* line)
    : Embedding(std::string(line)) {}


Embedding::Embedding(const std::string& line) {
    std::stringstream ss(line);
    std::string token;

    
    if (!std::getline(ss, token, ',')) {
        throw InvalidFileException();
    }
    word = token;

    
    v.clear();
    while (std::getline(ss, token, ',')) {
        try {
            v.push_back(std::stod(token));
        }
        catch (...) {
            
            throw InvalidFileException();
        }
    }
}


Embedding::Embedding(const Embedding& e)
    : word(e.word), v(e.v) {}


std::string Embedding::getWord() const {
    return word;
}

std::vector<double> Embedding::getVector() const {
    return v;
}

int Embedding::getDimensions() const {
    return static_cast<int>(v.size());
}


Embedding& Embedding::operator=(const Embedding& e) {
    if (this != &e) {
        word = e.word;
        v    = e.v;
    }
    return *this;
}


Embedding& Embedding::operator+=(const Embedding& e) {
    if (getDimensions() != e.getDimensions()) {
        throw InvalidDimensionsException();
    }
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] += e.v[i];
    }
    word = word + "+" + e.word;
    return *this;
}


Embedding& Embedding::operator-=(const Embedding& e) {
    if (getDimensions() != e.getDimensions()) {
        throw InvalidDimensionsException();
    }
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] -= e.v[i];
    }
    word = word + "-" + e.word;
    return *this;
}


Embedding Embedding::operator+(const Embedding& e) const {
    Embedding result(*this);
    result += e;
    return result;
}


Embedding Embedding::operator-(const Embedding& e) const {
    Embedding result(*this);
    result -= e;
    return result;
}


double Embedding::operator*(const Embedding& e) const {
    if (getDimensions() != e.getDimensions()) {
        throw InvalidDimensionsException();
    }
    double dotNorm = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        dotNorm += v[i] * e.v[i];
    }
    double normA = !(*this);
    double normB = !(e);
    if (normA == 0.0 || normB == 0.0) {
        
        return 0.0;
    }
    return dotNorm / (normA * normB);
}


double Embedding::operator!() const {
    double sumsq = 0.0;
    for (double x : v) {
        sumsq += x * x;
    }
    return std::sqrt(sumsq);
}

std::ostream& operator<<(std::ostream& stream, const Embedding& e) {
    stream << "[" << e.word << "] ";
    for (size_t i = 0; i < e.v.size(); ++i) {
        stream << e.v[i];
        if (i + 1 < e.v.size()) {
            stream << ", ";
        }
    }
    stream << "\n";
    return stream;
}



std::vector<Embedding> readVectors(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw InvalidFileException();
    }

    std::vector<Embedding> embeddings;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        embeddings.emplace_back(line);
    }
    return embeddings;
}
