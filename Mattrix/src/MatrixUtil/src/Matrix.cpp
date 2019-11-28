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
    
    matrix(1,1) = scalar;
}

Matrix::Matrix(int row, int col) {
    matrix = arma::mat(row, col, arma::fill::zeros);
}

//==================
// Operator Overloads
//==================
Matrix Matrix::operator+(const Matrix & other) {
    return Matrix(matrix + other.matrix);
}

Matrix Matrix::operator-(const Matrix & other) {
    return Matrix(matrix - other.matrix);
}

Matrix Matrix::operator*(const Matrix & other) {
    return Matrix(matrix * other.matrix);
}

Matrix Matrix::operator/(const Matrix & other) {
    return Matrix(matrix / other.matrix);
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
std::string Matrix::prettyPrint() {
    //TODO this later
}

void Matrix::parseString(const std::string& matStr) {
    int numCol = 0;
    int numRows = 0;
    std::vector<std::vector<int>> rowVectors;
    std::vector<int> currentRow;
    std::string currentNumAsString = "";
    
    for(auto& currentChar : matStr) {
        if(currentChar == ' ') {
            continue;
        }
        else if(currentChar == Matrix::OPENING_BRACKET) {
            currentRow.clear(); //Make sure row is cleared before starting new row
        }
        else if(currentChar == Matrix::CLOSING_BRACKET) {
            rowVectors.push_back(currentRow);
            currentRow.clear();
        }
        else if(currentChar == Matrix::SEPERATION_CHARACTER) {
            currentRow.push_back(RandomUtils::getIntFromString(currentNumAsString));
        }
        else {
            currentNumAsString += currentChar;
        }
    }
    
    setMatrix(rowVectors);
}

void Matrix::setMatrix(const std::vector<std::vector<int>>& rowVectors) {
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
    os << Matrix::OPENING_BRACKET;
    
    for(int col = 0; col < mat.matrix.n_cols; ++col) {
        if(!mat.isScalar) {os << Matrix::OPENING_BRACKET;}
        
        for(int row = 0; row < mat.matrix.n_rows; ++row) {
            os << (row != 0 ? ", " : "") << mat.matrix(row, col);
        }
        
        if(!mat.isScalar) {os << Matrix::CLOSING_BRACKET;}
    }
    
    return os << Matrix::CLOSING_BRACKET;
}

std::istream& MatrixUtil::operator>>(std::istream& is, Matrix & mat) {
    int numCol = 0;
    int numRows = 0;
    std::vector<std::vector<int>> rowVectors;
    std::vector<int> currentRow;
    std::string currentNumAsString = "";
    int numberOfOpenBrackets = 0;
    
    char currentChar;
    while(is.get(currentChar)) {
        if(currentChar == ' ') {
            continue;
        }
        else if(currentChar == Matrix::OPENING_BRACKET) {
            currentRow.clear(); //Make sure row is cleared before starting new row
            numberOfOpenBrackets++;
        }
        else if(currentChar == Matrix::CLOSING_BRACKET) {
            rowVectors.push_back(currentRow);
            currentRow.clear();
            
            numberOfOpenBrackets--;
            
            if(numberOfOpenBrackets == 0) {
                break; //We have closed all brackets => done with parsing
            }
        }
        else if(currentChar == Matrix::SEPERATION_CHARACTER) {
            currentRow.push_back(RandomUtils::getIntFromString(currentNumAsString));
        }
        else {
            currentNumAsString += currentChar;
        }
    }
    
    mat.setMatrix(rowVectors);
    
    return is;
}
