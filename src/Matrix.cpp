#include <Matrix.hpp>
#include <Exception.hpp>
#include <sstream>
#include <iostream>
#include <algorithm>

Matrix::Matrix(size_t rows, size_t columns) : 
    _columns(columns),
    _rows(rows)
{
    _data = std::vector<std::vector<double>>(rows, std::vector<double>(columns));
}

Matrix::Matrix(const std::initializer_list<double> data, size_t rows, size_t columns) :
    _columns(columns),
    _rows(rows)
{
    if (_rows == 0) _rows = data.size();
    
    _data = std::vector<std::vector<double>>(_rows, std::vector<double>(_columns, 0.0));

    for (auto d : data) {
        _data.at(0).push_back(d);
    }
}

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> data, size_t rows, size_t columns) :
    _columns(columns),
    _rows(rows)
{
    if (_columns == 0) _columns = data.size();
    if (_rows == 0) {
        for (auto r : data) {
            _rows = std::max(r.size(), _rows);
        }
    }

    _data = std::vector<std::vector<double>>(_rows, std::vector<double>(_columns, 0.0));

    for (size_t r = 0; r < data.size(); r++) {
        for (size_t c = 0; c < data.begin()[r].size(); c++) {
            _data.at(r).at(c) = data.begin()[r].begin()[c];
        }
    }

}

Matrix::~Matrix() {
}

double& Matrix::at(const size_t i, const size_t j) {
    return _data.at(i).at(j);
}

const double& Matrix::at(const size_t i, const size_t j) const {
    return _data.at(i).at(j);
}

Matrix Matrix::transpose() const {
    Matrix tr = Matrix(_columns, _rows);

    for ( size_t i = 0; i < _rows; i++ ) {
        for (size_t j = 0; j < _columns; j++)
            tr.at(i, j) = at(j, i);
    }

    return tr;
}

std::string Matrix::toString() const {
    std::stringstream buff;

    buff << "[ ";
    for (size_t i = 0; i < _rows; i++) {
        if (i > 0) buff << "  ";
        buff << "[ ";
        for (size_t j = 0; j < _columns; j++) {
            if (j > 0) buff << ", ";
            buff << at(i, j);
        }
        buff << " ]";
        if (i != _rows - 1) buff << "," << std::endl;
    }
    buff << " ]" << std::endl;

    return buff.str();
}

size_t Matrix::ncolumns() const {
    return _columns;
}

size_t Matrix::nrows() const {
    return _rows;
}