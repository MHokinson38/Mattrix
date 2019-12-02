//
//  InputLine.h
//  Mattrix
//
//  Created by Matthew Hokinson on 11/17/19.
//

#ifndef InputLine_h
#define InputLine_h
//This is going to read the input line and create a Matrix Expression -> Which is a list
//Libraries
#include <iostream>
#include <string>

//My files
#include <MatrixUtil/interface/Matrix.h>

namespace CalculationUtil {
    /**
            This class will serve as a wrapper for the Expression class, and have the operator overloads, etc.
            The reason for this is to handle the control of trhe expression that doesn't belong in Expression itself,
            but that I think is still important to be maintained somewhere other than the main
     */
    class InputLine {
    public:
        //==============
        //Constructor
        //==============
        InputLine() = default;
        
        //==============
        // Public functions
        //==============
        std::string getOutputPrettyPrint() {return output.prettyPrint();}
        std::string getOutputMatrixString() {return output.regularPrint();}
        
        //==============
        // Stream Overloads
        //==============
        friend std::ostream& operator<<(std::ostream& os, const InputLine & line);
        friend std::istream& operator>>(std::istream& is, InputLine & line);
        
    private:
        //==============
        // Private Functions
        //==============
        
        
        //==============
        // Data Members
        //==============
        Expression exp;
        
        MatrixUtil::Matrix output; //To make sure we only evaluate one time
    };
}


#endif /* InputLine_h */
