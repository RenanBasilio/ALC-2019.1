#include <Vector.hpp>
#include <Exception.hpp>

Vector::Vector(const size_t length) : _length(length) {
    _data = std::vector<double>(length, 0.0);
}

Vector::Vector(const size_t length, const std::initializer_list<double> data) : _length(length) {
    _data = std::vector<double>(length, 0.0);
    for (size_t i = 0; i < length; i++) {
        _data.at(i) = data.begin()[i];
    }
}

Vector::Vector(const size_t length, double* data) : _length(length) {
    _data = std::vector<double>(length, 0.0);
    for (size_t i = 0; i < length; i++) {
        _data.at(i) = data[i];
    }
}

Vector::Vector(const Vector& v) : _length(v._length) {
    _data.reserve(v._length);
    _data = v._data;
}

Vector& Vector::operator=(Vector other) {
    swap(*this, other);
    return *this;
}

Vector::~Vector() {
}

double& Vector::at(const size_t i) {
    return _data.at(i);
}

const double& Vector::at(const size_t i) const {
    return _data.at(i);
}

size_t Vector::length() const {
    return _length;
}

void swap(Vector& first, Vector& second) {
    using std::swap;

    swap(first._length, second._length);
    swap(first._data, second._data);
}