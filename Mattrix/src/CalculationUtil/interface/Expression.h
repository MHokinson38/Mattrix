//
//  Expression.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/30/19.
//

#ifndef Expression_h
#define Expression_h
//Libraries
#include <iostream>
#include <vector>
#include <string>

//My Files
#include <CalculationUtil/interface/Operations/Operation.h>
#include <CalculationUtil/interface/Operations/FunctionalOperation.h>
#include <CalculationUtil/interface/Operations/ArithmeticOperation.h>
#include <CalculationUtil/interface/Operations/OperationType.h>
#include <MatrixUtil/interface/Matrix.h>

namespace CalculationUtil {
    class Expression {
    public:
        //=============
        // Constants
        //=============
        static inline const char OPENING_PARENTHESE = '(';
        static inline const char CLOSING_PARENTHESE = ')';
        static inline const char TRANSPOSE_CHARACTER = 'T';
        static inline const char INVERSE_CHARACTER = '-';
        
        //=============
        // Constructors
        //=============
        Expression() = default;
        Expression(const std::string & input);
        
        //=============
        // Getters and Setters
        //=============
        std::string getInputLine() {return inputLine;}
        void setInputLine(const std::string & input);
        
        void reset();
        //=============
        // Evaluation
        //=============
        MatrixUtil::Matrix evaluate();
        
        //=============
        // Stream Overloads (No need for ostream)
        //=============
        friend std::istream& operator>>(std::istream& is, Expression & exp);
        
    private:
        //=============
        // Parsing Functions
        //=============
        void parseInputLine();
        void getBaseOperation();
        
        //=============
        // Data Members
        //=============
        std::string inputLine;
        std::vector<Expression> internalExpressions;
        std::vector<OperationType> operations;
        
        OperationType baseOperation; //Operation level with lowest order of ops (thing that is going to execute last in expression)
        
        bool isBase; //Contains only one matrix (Ends the splitting / parsing)
        MatrixUtil::Matrix baseMatrix; //This may be empty
    };
}


#endif /* Expression_h */
