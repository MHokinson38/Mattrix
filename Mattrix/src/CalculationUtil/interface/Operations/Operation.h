//
//  Operation.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/17/19.
//

#ifndef Operation_h
#define Operation_h

//My Files
#include <CalculationUtil/interface/Operations/OperationType.h>
#include <MatrixUtil/interface/Matrix.h>

//Libraries
#include <vector>
#include <iostream>

using Matrix = MatrixUtil::Matrix;

namespace CalculationUtil {
    class Operation {
    public:
        //=================
        // Constructors
        //=================
        Operation(const OperationType & op) : operand(op) {}
        
        //=================
        // Getters
        //=================
        bool isFunctional() {return operand.isFunctional();}
        
        //=================
        // Virtual Functions
        //=================
        virtual Matrix perform() = 0; //Some operations return multiple vectors multiplied together
        virtual std::ostream& print(std::ostream& os) const = 0;
        
        //=================
        // Ostream Overload
        //=================
        friend std::ostream& operator<<(std::ostream& os, const Operation& op) {return op.print(os);}
        
    protected:
        OperationType operand;
    };
}


#endif /* Operation_h */
