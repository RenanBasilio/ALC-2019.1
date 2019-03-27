#include <SqMatrix.hpp>
#include <Exception.hpp>
#include <sstream>
#include <iostream>

SqMatrix::SqMatrix(size_t size) : _size(size) {
    _data = std::vector<Vector>(size, Vector(size));
}

SqMatrix::SqMatrix(size_t size, const std::initializer_list<Vector> data) : _size(size) {
    _data = std::vector<Vector>();
    _data.reserve(size);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            try
            {
                _data.at(i) = data.begin()[i];
            }
            catch(const std::exception&)
            {
                _data.at(i).at(j) = 0.0;
            }
        }
    }
}

SqMatrix::SqMatrix(size_t size, const std::initializer_list<std::initializer_list<double>> data) : _size(size) {
    _data = std::vector<Vector>();
    _data.reserve(size);
    for (size_t i = 0; i < data.size(); i++) {
        _data.push_back(Vector(size, data.begin()[i]));
    }
}

SqMatrix::SqMatrix(size_t size, const Vector* data ) : _size(size) {
    _data = std::vector<Vector>(size, Vector(size));
    for (size_t i = 0; i < size; i++) {
        _data.at(i) = data[i];
        for (size_t j = 0; j < size; j++) {
            _data.at(i) = data[i];
        }
    }
}

SqMatrix::SqMatrix(const SqMatrix& m) : _size(m._size) {
    _data = std::vector<Vector>(_size, Vector(m._size));
    for (size_t i = 0; i < _size; i++) {
        _data = m._data;
    }   
}

SqMatrix::~SqMatrix() {
}

double& SqMatrix::at(const size_t i, const size_t j) {
    return _data.at(i).at(j);
}

const double& SqMatrix::at(const size_t i, const size_t j) const {
    return _data.at(i).at(j);
}

Vector SqMatrix::operator* (const Vector& v) {
    if (v.length() != _size) throw size_mismatch("Length of vector does not match size of matrix.");

    Vector r = Vector(_size);
    for (size_t i = 0; i < _size; i++) {
        
    }

    return r;
    
}

std::string SqMatrix::toString() const {
    std::stringstream buff;
    
    buff << "[ ";
    for (size_t i = 0; i < _size; i++) {
        if (i > 0) buff << "  ";
        buff << "[ ";
        for (size_t j = 0; j < _size; j++) {
            if (j > 0) buff << ", ";
            buff << at(i, j);
        }
        buff << " ]";
        if (i != _size - 1) buff << "," << std::endl;
    }
    buff << " ]" << std::endl;

    return buff.str();
}

SqMatrix SqMatrix::transpose() const {
    SqMatrix tr = SqMatrix(_size);

    for (size_t i = 0; i < _size; i++) {
        for (size_t j = 0; j < _size; j++) {
            tr.at(j, i) = at(i, j);
        }
    }

    return tr;
}

size_t SqMatrix::size() const {
    return _size;
}