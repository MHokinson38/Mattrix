//
//  ArithmeticOperation.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/17/19.
//
#ifndef ArithmeticOperation_h
#define ArithmeticOperation_h

//My Files
#include "CalculationUtil/interface/Operations/OperationType.h"
#include "CalculationUtil/interface/Operations/Operation.h"
#include <MatrixUtil/interface/Matrix.h>


//Libraries
#include <vector>

using Matrix = MatrixUtil::Matrix;

namespace CalculationUtil {
    class ArithmeticOperation : public Operation {
    public:
        //===================
        // Constructors
        //===================
        ArithmeticOperation(OperationType op, Matrix l, Matrix r) : Operation(op), lhs(l), rhs(r) {}
        
        //===================
        // Perform Overload
        //===================
        Matrix perform();
        
        //===================
        // Ostream Print overload
        //===================
        std::ostream& print(std::ostream& os) const;
        
    private:
        Matrix lhs;
        Matrix rhs;
    };
}


#endif /* ArithmeticOperation_h */
