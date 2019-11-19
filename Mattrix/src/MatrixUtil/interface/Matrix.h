//
//  Matrix.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/18/19.
//
#ifndef Matrix_h
#define Matrix_h

//Libraries
#include <armadillo>
#include <iostream>
#include <string>

namespace MatrixUtil {
    /**
            This is essentially a wrapper class for the armadillo Matrix, just so that I can add things if I need to /
            make is cleaner to integrate with my work. As of right now, we are going to use a double only matrix, but
            if I have time, I would like to implement a templating system.
     */
    class Matrix {
    public:
        //===================
        // Constants
        //===================
        inline static const double APPROX_EQUAL_ALLOWANCE = .001;
        
        inline static const char OPENING_BRACKET = '[';
        inline static const char CLOSING_BRACKET = ']';
        inline static const char SEPERATION_CHARACTER = ',';
        inline static const char LINE_END_CHARACTER = ';';
        //=============================
        // Constructors
        //=============================
        Matrix() = default;
        Matrix(double scalar); //Scalar constructor
        Matrix(int row, int col); //Creates empty matrix of 0's
        Matrix(const arma::mat & mat) : matrix(mat), isScalar(false) {}
        Matrix(const std::string & matStr); //Constructor to parse a string
        
        //Copy Constructor
        Matrix(const Matrix & other) : matrix(other.matrix), isScalar(other.isScalar) {}
        //Move Constructor
        Matrix(Matrix&& source) : matrix(std::move(source.matrix)), isScalar(std::move(source.isScalar)) {}
        ~Matrix() = default;
        
        //====================
        // Getters and Setters
        //====================
        double getElement(int row, int col) {return matrix(row, col);}
        void setElement(int row, int col, double el) {matrix(row, col) = el;}

        //====================
        // Operator Overloads
        //====================
        Matrix operator+(const Matrix & rhs);
        Matrix operator-(const Matrix & rhs);
        Matrix operator*(const Matrix & rhs); //Needs Matrix Scalar or Matrix of valid Dimension 
        Matrix operator/(const Matrix & rhs); //Needs Matrix Scalar
        Matrix operator^(const Matrix & exp); //Needs Matrix Scalar
        
        //Boolean operation
        bool operator==(const Matrix & rhs) {return arma::approx_equal(matrix, rhs.matrix, "absdiff", Matrix::APPROX_EQUAL_ALLOWANCE);}
        
        //====================
        // Functional Operations
        //====================
        Matrix inverse();
        Matrix transpose();
        
        //====================
        // Functinons for printing
        //====================
        std::string prettyPrint();
        
        //====================
        // Reading input from string
        //====================
        void parseString(const std::string & matStr);
        void setMatrix(const std::vector<std::vector<int>> & rowVectors);
        
        //====================
        // Reading and Writing
        //====================
        friend std::ostream& operator<<(std::ostream& os, const Matrix & mat);
        friend std::istream& operator>>(std::istream& is, Matrix & mat);
        
    private:
        arma::mat matrix;
        
        bool isScalar;
    };
}

#endif /* Matrix_h */
