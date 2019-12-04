//
//  Matrix.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/18/19.
//
//Libraries
#include <iostream>
#include <cmath>

//My files
#include <MatrixUtil/interface/Matrix.h>
#include <MatrixUtil/interface/Exceptions/InvalidSyntaxException.h>
#include <MatrixUtil/interface/Exceptions/UnsupportedComputationException.h>

#include <RandomUtils/interface/CoolUtilities.h>

using Matrix = MatrixUtil::Matrix;

//===================
// Constructors
//===================
Matrix::Matrix(double scalar) : isScalar(true) {
    matrix = arma::mat(1,1, arma::fill::zeros);
    
    matrix << scalar << arma::endr;
}

Matrix::Matrix(int row, int col) {
    matrix = arma::mat(row, col, arma::fill::zeros);
}

Matrix::Matrix(const std::string & matStr) {
    parseString(matStr);
}

//==================
// Assignment Operators
//==================
Matrix& Matrix::operator=(const Matrix & other) {
    this->matrix = other.matrix;
    this->isScalar = other.isScalar;
    
    return *this;
}

//==================
// Getters
//===================
double Matrix::getScalarValue() const {
    return isScalar ? matrix(0,0) : -1; //TODO add exceptions
}

//==================
// Operator Overloads
//==================
Matrix Matrix::operator+(const Matrix & rhs) {
    try {
        return Matrix(matrix + rhs.matrix);
    }
    catch(std::logic_error& err) {
        throw InvalidSyntaxException(err.what());
    }
}

Matrix Matrix::operator-(const Matrix & rhs) {
    try {
        return Matrix(matrix - rhs.matrix);
    }
    catch(std::logic_error& err) {
        throw InvalidSyntaxException(err.what());
    }
}

Matrix Matrix::operator*(const Matrix & rhs) {
    if(isScalar) {return Matrix(rhs.scalarMultiply(getScalarValue()));}
    if(rhs.isScalar) {return Matrix(scalarMultiply(rhs.getScalarValue()));}
    
    try {
        return Matrix(matrix * rhs.matrix);
    }
    catch(std::logic_error & er) {
        throw InvalidSyntaxException(er.what());
    }
}

Matrix Matrix::operator/(const Matrix & rhs) {
    if(!rhs.isScalar) {
        throw InvalidSyntaxException("You cannot divide by a non-scalar!");
    }
    
    return Matrix(scalarMultiply(1.0 / rhs.getScalarValue()));
}

Matrix Matrix::operator^(const Matrix & exp) {
    //As of right now, only going to support integer values
    if(!exp.isScalar) {
        throw InvalidSyntaxException(
                "You cannot raise to a non-scalar power!");
    }
    if(!RandomUtils::isIntegerValue(exp.getScalarValue())) {
        throw UnsupportedComputationException(
                "Non-Integer powers are not currently supported");
    }
    if(matrix.n_cols != matrix.n_rows) {
        throw InvalidSyntaxException("Matrix is not square");
    }
    
    if(RandomUtils::doubleEqual(exp.getScalarValue(), -1)) {
        return inverse();
    }
    else if(exp.getScalarValue() < 0) {
        *this = inverse();
    }
    
    Matrix returnMat(matrix);
    for(int i = 1; i < std::abs(exp.getScalarValue()); ++i) {
        returnMat = returnMat * (*this);
    }
    
    return returnMat;
}

//For Scalar Multiplication
Matrix Matrix::scalarMultiply(double scalar) const {
    arma::mat newMat = matrix;
    
    for(int row = 0; row < matrix.n_rows; ++row) {
        for(int col = 0; col < matrix.n_cols; ++col) {
            newMat(row, col) = matrix(row, col) * scalar;
        }
    }
    
    return newMat;
}

//=================
// Functional Operations
//=================
Matrix Matrix::inverse() {
    return Matrix(arma::inv(matrix));
}

Matrix Matrix::transpose() {
    return Matrix(matrix.t());
}

//=================
// Printing
//=================
std::string Matrix::prettyPrint() const {
    std::string returnString = "";
    
    returnString += "┌";
    for(int i = 0; i < matrix.n_cols*9 + 1; ++i) {returnString += " ";}
    returnString += "┐\n";
    
    for(int row = 0; row < matrix.n_rows; ++row) {
        returnString += "│ ";
        for(int col = 0; col < matrix.n_cols; ++col) {
            returnString += RandomUtils::getStringFromDouble(matrix(row, col)) + " ";
        }
        returnString += "│\n";
    }
    
    returnString += "└";
    for(int i = 0; i < matrix.n_cols*9 + 1; ++i) {returnString += " ";}
    returnString += "┘\n";
    
    return returnString;
}

std::string Matrix::regularPrint() const {
    std::string returnString = "";
    
    returnString += Matrix::OPENING_BRACKET;
    
    for(int row = 0; row < matrix.n_rows; ++row) {
        if(!isScalar) {returnString += Matrix::OPENING_BRACKET;}
        
        for(int col = 0; col < matrix.n_cols; ++col) {
            returnString += (col != 0 ? ", " : "");
            returnString += RandomUtils::getStringFromDouble(matrix(row, col));
        }
        
        if(!isScalar) {returnString += Matrix::CLOSING_BRACKET;}
    }
    
    return returnString + Matrix::CLOSING_BRACKET;
}

//==================
// String Parsing
//==================
void Matrix::parseString(const std::string& matStr) {
    int numCol = 0;
    int numRows = 0;
    std::vector<std::vector<double>> rowVectors;
    std::vector<double> currentRow;
    std::string currentNumAsString = "";
    
    checkBasicSyntax(matStr);
    for(int i = 0; i < matStr.size(); ++i) {
        if(matStr[i] == ' ') {
            continue;
        }
        else if(matStr[i] == Matrix::OPENING_BRACKET) {
            currentRow.clear(); //Make sure row is cleared before starting new row
        }
        else if(matStr[i] == Matrix::CLOSING_BRACKET || matStr[i] == Matrix::LINE_END_CHARACTER) {
            currentRow.push_back(RandomUtils::getDoubleFromString(currentNumAsString));
            currentNumAsString = "";
            
            rowVectors.push_back(currentRow);
            currentRow.clear();
        }
        else if(matStr[i] == Matrix::SEPERATION_CHARACTER) {
            currentRow.push_back(RandomUtils::getDoubleFromString(currentNumAsString));
            currentNumAsString = "";
        }
        else if(i == (matStr.size() - 1)) { //For scalar use only (won't hit otherwise)
            currentNumAsString += matStr[i];
            
            currentRow.push_back(RandomUtils::getDoubleFromString(currentNumAsString));
            
            rowVectors.push_back(currentRow);
        }
        else {
            currentNumAsString += matStr[i];
        }
    }
    
    setMatrix(rowVectors);
}

void Matrix::checkBasicSyntax(const std::string &matStr) {
    //Check to make sure it's a scalar
    if(matStr.find(Matrix::OPENING_BRACKET) == std::string::npos) {
        return;
    }
    
    if(matStr[0] != Matrix::OPENING_BRACKET ||
       matStr[matStr.size() - 1] != Matrix::CLOSING_BRACKET) {
        throw InvalidSyntaxException("Invalid Matrix Syntax!");
    }
    
    //Check that all brackets are closed
    int numOpenBrackets = 0;
    for(auto& c : matStr) {
        if(c == Matrix::OPENING_BRACKET) {
            numOpenBrackets++;
        }
        else if(c == Matrix::CLOSING_BRACKET) {
            numOpenBrackets--;
        }
    }
    
    if(numOpenBrackets != 0) {
        throw InvalidSyntaxException("Invalid Matrix Syntax!");
    }
}

void Matrix::setMatrix(const std::vector<std::vector<double>>& rowVectors) {
    int numRows = rowVectors.size();
    int numCols = rowVectors[0].size();
    
    matrix = arma::mat(numRows, numCols);
    
    for(int row = 0; row < numRows; ++row) {
        for(int col = 0; col < numCols; ++col) {
            try {
                matrix(row, col) = rowVectors.at(row).at(col);
            }
            catch(std::out_of_range& er) {
                throw InvalidSyntaxException("Inconsistent Matrix Dimension");
            }
        }
    }
    
    isScalar = numRows == 1 && numCols == 1;
}

//=================
// Stream Overloads
//=================
std::ostream& MatrixUtil::operator<<(std::ostream& os, const Matrix & mat) {
    return os << mat.regularPrint();
}

std::istream& MatrixUtil::operator>>(std::istream& is, Matrix & mat) {
   int numberOfOpenBrackets = 0;
    
    char currentChar;
    std::string matrixString = "";
    
    while(is.get(currentChar)) {
        if(currentChar == Matrix::OPENING_BRACKET) {numberOfOpenBrackets++;}
        else if(currentChar == Matrix::CLOSING_BRACKET) {numberOfOpenBrackets--;}
        
        matrixString += currentChar;
        
        if(numberOfOpenBrackets == 0) {break;}
    }
    
    mat.parseString(matrixString);
    
    return is;
}
