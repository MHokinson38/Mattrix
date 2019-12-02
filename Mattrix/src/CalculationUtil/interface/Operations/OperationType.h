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
            transpose,
            empty
        };
        
        //===================
        // Constructors
        //===================
        OperationType() = default;
        OperationType(char c);
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
        
        char getOpAsChar();
        
        bool isNull() const {return operation == OpType::empty;}
        
        int getHierarchyLevel() {return pemdas[operation];}
        
        bool isFunctional();
        bool isTranspose() {return operation == OpType::transpose;}
        bool isInverse() {return operation == OpType::inverse;}
        bool isExponent() {return operation == OpType::exponent;}
        
        //===================
        // Operator Overloads
        //===================
        bool operator==(OperationType other) const {return operation == other.operation;}
        
        //=============
        // Ostream Overload
        //=============
        friend std::ostream& operator<<(std::ostream& ostream, const OperationType & op);
        
        //==============
        // Static Helping Functions
        //==============
        static int getPemdasFromChar(char opChar);
        
        static bool isOperationCharacter(char opChar);
    
    private:
        //==============
        // Data Members
        //==============
        OpType operation;
        
        //===================
        // Order of Operation Hierarchy
        //===================
        static inline std::map<OpType, int> pemdas = {{OpType::add, 0}, {OpType::subtract, 0},
                                                     {OpType::multiply, 1}, {OpType::divide, 1},
                                                     {OpType::inverse, 2}, {OpType::exponent, 2},
                                                     {OpType::transpose, 2}};
        
        static inline std::map<char, OpType> charToOpMap = {{'+', OpType::add},
                                                            {'-', OpType::subtract},
                                                            {'*', OpType::multiply},
                                                            {'/', OpType::divide},
                                                            {'^', OpType::exponent},
                                                            {'T', OpType::transpose}};
    };
}


#endif /* OperationType_h */
