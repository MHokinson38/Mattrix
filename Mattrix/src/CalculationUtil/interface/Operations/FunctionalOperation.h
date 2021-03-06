//
//  FunctionalOperation.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/17/19.
//

#ifndef FunctionalOperation_h
#define FunctionalOperation_h

//My Files
#include "CalculationUtil/interface/Operations/OperationType.h"
#include "CalculationUtil/interface/Operations/Operation.h"
#include <MatrixUtil/interface/Matrix.h>

//Libraries
#include <vector>

using Matrix = MatrixUtil::Matrix;

namespace CalculationUtil {
    class FunctionalOperation : public Operation {
    public:
        //===================
        // Constructors
        //===================
        FunctionalOperation(OperationType op, Matrix ob, double exp = 0) : Operation(op), object(ob), pow(exp) {}
        
        //===================
        // Perform Overload
        //===================
        Matrix perform();
        
        //===================
        // Ostream Print overload
        //===================
        std::ostream& print(std::ostream& os) const;
        
    private:
        Matrix object;
        
        double pow; //If doing an exponent operation
    };
}

#endif /* FunctionalOperation_h */
