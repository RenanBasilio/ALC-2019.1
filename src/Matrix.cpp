#include <Matrix.hpp>
#include <Exception.hpp>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

Matrix::Matrix(const size_t rows, const size_t columns, const real value) : 
    _columns(columns),
    _rows(rows)
{
    _data = std::vector<std::vector<real>>(rows, std::vector<real>(columns, value));
}

/* Matrix::Matrix(const std::initializer_list<real> data, size_t rows, size_t columns) :
    _columns(columns),
    _rows(rows)
{
    if (_rows == 0) _rows = data.size();
    
    _data = std::vector<std::vector<real>>(_rows, std::vector<real>(_columns, 0.0));

    for (size_t i = 0; i < data.size(); i++) {
        at(i, 0) = data.begin()[i];
    }
} */

Matrix::Matrix(const std::vector<std::vector<real>> data, size_t rows, size_t columns) :
    _columns(columns),
    _rows(rows)
{
    if (_rows == 0) _rows = data.size();
    if (_columns == 0) {
        for (auto c : data) {
            _columns = std::max(c.size(), _columns);
        }
    }

    _data = std::vector<std::vector<real>>(_rows, std::vector<real>(_columns, 0.0));

    for (size_t r = 0; r < data.size(); r++) {
        for (size_t c = 0; c < data.begin()[r].size(); c++) {
            at(r, c) = data.begin()[r].begin()[c];
        }
    }

}

/* Matrix::Matrix(const std::initializer_list<std::initializer_list<real>> data, size_t rows, size_t columns) :
    _columns(columns),
    _rows(rows)
{
    if (_rows == 0) _rows = data.size();
    if (_columns == 0) {
        for (auto c : data) {
            _columns = std::max(c.size(), _columns);
        }
    }

    _data = std::vector<std::vector<real>>(_rows, std::vector<real>(_columns, 0.0));

    for (size_t r = 0; r < data.size(); r++) {
        for (size_t c = 0; c < data.begin()[r].size(); c++) {
            at(r, c) = data.begin()[r].begin()[c];
        }
    }

} */

Matrix::~Matrix() {
}

size_t Matrix::ncolumns() const {
    return _columns;
}

size_t Matrix::nrows() const {
    return _rows;
}

real& Matrix::at(const size_t i, const size_t j) {
    return _data.at(i).at(j);
}

const real& Matrix::at(const size_t i, const size_t j) const {
    return _data.at(i).at(j);
}

const std::vector<real> Matrix::getRow(const size_t index) const {
    return _data.at(index);
}

std::vector<real> Matrix::getColumn(const size_t index) const {
    std::vector<real> col = std::vector<real>();
    col.reserve(_rows);
    
    for (auto i : _data) {
        col.push_back(i.at(index));
    }

    return col;
}

void Matrix::insertRow(const size_t position, const std::vector<real> l) {
    _data.insert(_data.begin()+position, l);
    _rows++;
}

void Matrix::insertColumn(const size_t position, const std::vector<real> l) {
    for (size_t i = 0; i < _rows; i++) {
        _data.at(i).insert(_data.at(i).begin()+position, l.at(i));
    }
    _columns++;
}

std::vector<real> Matrix::removeRow(const size_t position) {
    std::vector<real> vr = _data.at(position);
    _data.erase(_data.begin()+position);
    _rows--;
    return vr;
}

std::vector<real> Matrix::removeColumn(const size_t position) {
    std::vector<real> vr;
    for (size_t i = 0; i < _rows; i++) {
        vr.push_back(_data.at(i).at(position));
        _data.at(i).erase(_data.at(i).begin()+position);
    }
    _columns--;
    return vr;
}

void Matrix::swapRow(const size_t pos1, size_t pos2) {

    if (pos1 == pos2) return;

    real tmp;
    for (size_t i = 0; i < _columns; i++) {
        tmp = at(pos1, i);
        at(pos1, i) = at(pos2, i);
        at(pos2, i) = tmp;
    }
}

Matrix Matrix::transpose() const {
    Matrix tr = Matrix(_columns, _rows);

    for ( size_t i = 0; i < _rows; i++ ) {
        for (size_t j = 0; j < _columns; j++)
            tr.at(j, i) = at(i, j);
    }

    return tr;
}

Matrix::operator std::string() const {
    std::stringstream buff;

    buff << "[ ";
    for (size_t i = 0; i < _rows; i++) {
        if (i > 0) buff << "  ";
        buff << "[ ";
        for (size_t j = 0; j < _columns; j++) {
            if (j > 0) buff << ", ";
            buff << std::setw(8) << std::setprecision(5) << at(i, j);
        }
        buff << " ]";
        if (i != _rows - 1) buff << "," << std::endl;
    }
    buff << " ]" << std::endl;

    return buff.str();
}

bool Matrix::operator== (const Matrix& other) const {
    for ( size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            if ( fabs(at(i, j) - other.at(i, j)) >= 1E-3 ) return false;
        }
    }
    return true;
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
            real val = 0.0;
            for (size_t k = 0; k < _columns; k++) {
                val += getRow(i).at(k) * tr.getRow(j).at(k);
            }
            res.at(i, j) = val;
        }
    }

    return res;
}

Matrix Matrix::operator+(const real s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) + s;
        }
    }

    return res;
}

Matrix operator+(const real s, const Matrix& matrix) {
    return matrix + s;
}

Matrix Matrix::operator-(const real s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) - s;
        }
    }

    return res;
}

Matrix operator-(const real s, const Matrix& matrix) {
    return matrix - s;
}

Matrix Matrix::operator*(const real s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) * s;
        }
    }

    return res;
}

Matrix operator*(const real s, const Matrix& matrix) {
    return matrix * s;
}

Matrix Matrix::operator/(const real s) const {
    Matrix res = Matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _columns; j++) {
            res.at(i, j) = at(i, j) / s;
        }
    }

    return res;
}

Matrix operator/(const real s, const Matrix& matrix) {
    Matrix res = Matrix(matrix._rows, matrix._columns);

    for (size_t i = 0; i < matrix._rows; i++) {
        for (size_t j = 0; j < matrix._columns; j++) {
            res.at(i, j) = s / matrix.at(i, j);
        }
    }

    return res;
}

bool Matrix::isSymmetric() const {
    if ( _rows != _columns ) return false;
    
    for ( size_t i = 0; i < _rows; i ++ ) {
        for ( size_t j = 0; j < _columns; j++ ) {
            if ( at(i, j) != at(j, i) ) return false;
        }
    }

    return true;
}

bool Matrix::isDiagonalDominant() const {
    if ( _rows != _columns ) return false;

    for ( size_t i = 0; i < _rows; i++ ) {
        std::vector<real> row = getRow(i);
        std::vector<real> col = getColumn(i);
        real sum_r = 0.0, sum_c = 0.0, diag = at(i,i);

        for ( size_t j = 0; j < _rows; j++ ) {
            if (j != i) {
                sum_r += row.at(j);
                sum_c += col.at(j);
            }
        }

        if ( diag < sum_r || diag < sum_c ) return false;
    }
    return true;
}

std::ostream& operator<< (std::ostream& s, const Matrix& mtx) {
    s << std::string(mtx);
    return s;
}

Matrix Matrix::Identity(const size_t size) {
    Matrix mtx = Matrix(size, size, 0.0);
    for (size_t i = 0; i < size; i++) {
        mtx.at(i, i) = 1;
    }
    return mtx;
}

real computeNorm( const Matrix& vec ) {
    if ( vec.ncolumns() > 1 ) throw size_mismatch("Norm not available for matrices of width higher than 1.");

    real sum = 0.0;
    for ( size_t i = 0; i < vec.nrows(); i++ ) {
        sum += pow(vec.at(i), 2);
    }

    return sqrt(sum);
}