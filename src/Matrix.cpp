#include <Matrix.hpp>
#include <Exception.hpp>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

Matrix::Matrix(const size_t rows, const size_t columns, const double value) : 
    _columns(columns),
    _rows(rows)
{
    _data = std::vector<std::vector<double>>(rows, std::vector<double>(columns, value));
}

Matrix::Matrix(const std::initializer_list<double> data, size_t rows, size_t columns) :
    _columns(columns),
    _rows(rows)
{
    if (_rows == 0) _rows = data.size();
    
    _data = std::vector<std::vector<double>>(_rows, std::vector<double>(_columns, 0.0));

    for (size_t i = 0; i < data.size(); i++) {
        at(i, 0) = data.begin()[i];
    }
}

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> data, size_t rows, size_t columns) :
    _columns(columns),
    _rows(rows)
{
    if (_rows == 0) _rows = data.size();
    if (_columns == 0) {
        for (auto c : data) {
            _columns = std::max(c.size(), _columns);
        }
    }

    _data = std::vector<std::vector<double>>(_rows, std::vector<double>(_columns, 0.0));

    for (size_t r = 0; r < data.size(); r++) {
        for (size_t c = 0; c < data.begin()[r].size(); c++) {
            at(r, c) = data.begin()[r].begin()[c];
        }
    }

}

Matrix::~Matrix() {
}

size_t Matrix::ncolumns() const {
    return _columns;
}

size_t Matrix::nrows() const {
    return _rows;
}

double& Matrix::at(const size_t i, const size_t j) {
    return _data.at(i).at(j);
}

const double& Matrix::at(const size_t i, const size_t j) const {
    return _data.at(i).at(j);
}

const std::vector<double> Matrix::getRow(const size_t index) const {
    return _data.at(index);
}

std::vector<double> Matrix::getColumn(const size_t index) const {
    std::vector<double> col = std::vector<double>();
    col.reserve(_rows);
    
    for (auto i : _data) {
        col.push_back(i.at(index));
    }

    return col;
}

Matrix Matrix::transpose() const {
    Matrix tr = Matrix(_columns, _rows);

    for ( size_t i = 0; i < _rows; i++ ) {
        for (size_t j = 0; j < _columns; j++)
            tr.at(j, i) = at(i, j);
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
            buff << std::setw(8) << std::setprecision(6) << at(i, j);
        }
        buff << " ]";
        if (i != _rows - 1) buff << "," << std::endl;
    }
    buff << " ]" << std::endl;

    return buff.str();
}

bool Matrix::operator== (const Matrix& other) const {
    if ( other._columns == _columns && 
         other._rows == _rows &&
         other._data == _data) return true;
    else return false;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix res = Matrix(_rows, _columns);

    if (_columns != other._columns && _rows != _columns)
        throw size_mismatch("Size of Matrix does not match size of other. Operation not applicable.");

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i,j) = at(i, j) + other.at(i, j); 
        }
    }

    return res;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix res = Matrix(_rows, _columns);

    if (_columns != other._columns && _rows != _columns)
        throw size_mismatch("Size of Matrix does not match size of other. Operation not applicable.");

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i,j) = at(i, j) - other.at(i, j); 
        }
    }

    return res;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix res = Matrix(_rows, other._columns);

    if (_columns != other._rows) throw size_mismatch(
        "Number of rows in Matrix other does not match number of columns in this. Operation not applicable.");

    Matrix tr = other.transpose();

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < other._columns; j++) {
            double val = 0.0;
            for (size_t k = 0; k < _columns; k++) {
                val += getRow(i).at(k) * tr.getRow(j).at(k);
            }
            res.at(i, j) = val;
        }
    }

    return res;
}

Matrix Matrix::operator+(const double s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) + s;
        }
    }

    return res;
}

Matrix operator+(const double s, const Matrix& matrix) {
    return matrix + s;
}

Matrix Matrix::operator-(const double s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) - s;
        }
    }

    return res;
}

Matrix operator-(const double s, const Matrix& matrix) {
    return matrix - s;
}

Matrix Matrix::operator*(const double s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) * s;
        }
    }

    return res;
}

Matrix operator*(const double s, const Matrix& matrix) {
    return matrix * s;
}

Matrix Matrix::operator/(const double s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) / s;
        }
    }

    return res;
}

Matrix operator/(const double s, const Matrix& matrix) {
    return matrix / s;
}