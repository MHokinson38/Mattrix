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
#include <map>

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
        
        int getHierarchyLevel() {return pemdas[operation];}
        
        //===================
        // Operator Overloads
        //===================
        bool operator==(OperationType other) const {return operation == other.operation;}
    
    private:
        OpType operation;
        
        //===================
        // Order of Operation Hierarchy
        //===================
        std::map<OpType, int> pemdas = { {OpType::add, 0}, {OpType::subtract, 0},
                                         {OpType::multiply, 1}, {OpType::divide, 1},
                                         {OpType::inverse, 2}, {OpType::exponent, 2},
                                         {OpType::transpose, 3}};
    };

    //=============
    // Ostream Overload
    //=============
    std::ostream& operator<<(std::ostream& ostream, const OperationType & op);
}


#endif /* OperationType_h */
