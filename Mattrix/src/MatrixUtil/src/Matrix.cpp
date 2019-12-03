//
//  Matrix.cpp
//  Mattrix
//
//  Created by Matthew Hokinson on 11/18/19.
//
//Libraries
#include <stdio.h>
#include <iostream>

//My files
#include <MatrixUtil/interface/Matrix.h>
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
    return Matrix(matrix + rhs.matrix);
}

Matrix Matrix::operator-(const Matrix & rhs) {
    return Matrix(matrix - rhs.matrix);
}

Matrix Matrix::operator*(const Matrix & rhs) {
    if(isScalar) {return Matrix(rhs.scalarMultiply(getScalarValue()));}
    if(rhs.isScalar) {return Matrix(scalarMultiply(rhs.getScalarValue()));}
    
    return Matrix(matrix * rhs.matrix); //Add Exception if Necessary
}

Matrix Matrix::operator/(const Matrix & rhs) {
    return Matrix(scalarMultiply(1.0 / rhs.getScalarValue())); //Add Exception
}

Matrix Matrix::operator^(const Matrix & exp) {
    //As of right now, only going to support integer values 
    return Matrix(arma::pow(matrix, exp.getScalarValue()));
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
    
    for(int row = 0; row < matrix.n_cols; ++row) {
        if(!isScalar) {returnString += Matrix::OPENING_BRACKET;}
        
        for(int col = 0; col < matrix.n_rows; ++col) {
            returnString += (col != 0 ? ", " : "");
            returnString += RandomUtils::getStringFromDouble(matrix(row, col));
        }
        
        if(!isScalar) {returnString += Matrix::CLOSING_BRACKET;}
    }
    
    return returnString += Matrix::CLOSING_BRACKET;
}

void Matrix::parseString(const std::string& matStr) {
    int numCol = 0;
    int numRows = 0;
    std::vector<std::vector<double>> rowVectors;
    std::vector<double> currentRow;
    std::string currentNumAsString = "";
    
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

void Matrix::setMatrix(const std::vector<std::vector<double>>& rowVectors) {
    int numRows = rowVectors.size();
    int numCols = rowVectors[0].size();
    
    matrix = arma::mat(numRows, numCols);
    
    for(int row = 0; row < numRows; ++row) {
        for(int col = 0; col < numCols; ++col) {
            matrix(row, col) = rowVectors[row][col];
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
