//
//  Header.h
//  Mattrix
//
//  Created by Matthew Hokinson on 12/8/19.
//

#ifndef Equation_h
#define Equation_h

//My Files
#include <MatrixUtil/interface/Matrix.h>

namespace CalculationUtil {
    class Equation {
    public:
        //==============
        // Constants
        //==============
        inline static const char EQUALS_SIGN = '=';
        inline static const char VARIABLE_CHAR = 'x';
        
        //==============
        // Constructor
        //==============
        Equation() = default;
        Equation(const std::string & equInput);
        
        //==============
        // Set input
        //==============
        void setInput(const std::string & equInput);
        
        //==============
        // Get Result
        //==============
        MatrixUtil::Matrix solve();
        
        MatrixUtil::Matrix leastSquaresSolve();
        
    private:
        //==============
        // Solving Functions
        //==============
        void parseInput(const std::string & input);
        
        void checkBasicSyntax(const std::string & input);
        
        //==============
        // Data Members
        //==============
        std::string rawInput;
        
        MatrixUtil::Matrix a;
        MatrixUtil::Matrix b;
    };
}

#endif /* Equation_h */
