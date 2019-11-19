//
//  OperationType.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/17/19.
//
#ifndef OperationType_h
#define OperationType_h

//My files

//Libraries
#include <iostream>

namespace CalculationUtil {
    class OperationType {
    public:
        enum OpType {
            add,
            subtract,
            multiply,
            divide,
            inverse,
            exponent,
            transpose //TODO add the other operations
        };
        
        //===================
        // Constructors
        //===================
        OperationType() = default;
        OperationType(OpType op) : operation(op) {}
        OperationType(const OperationType & other) : operation(other.operation) {} //Copy Constructor
        
        //===================
        // Assignment Overloads
        //===================
        OperationType& operator=(const OperationType & other);
        
        //===================
        // Getters and Setters
        //===================
        OpType getOperation() const {return operation;}
        void setOperation(OpType op) {operation = op;}
        
        //===================
        // Operator Overloads
        //===================
        bool operator==(OperationType other) const {return operation == other.operation;}
    
    private:
        OpType operation;
    };

    //=============
    // Ostream Overload
    //=============
    std::ostream& operator<<(std::ostream& ostream, const OperationType & op);
}


#endif /* OperationType_h */
