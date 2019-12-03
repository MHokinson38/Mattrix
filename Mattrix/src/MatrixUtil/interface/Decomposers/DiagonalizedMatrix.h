//
//  DiagonalizedMatrix.h
//  Mattrix
//
//  Created by Matthew Hokinson on 12/3/19.
//

#ifndef DiagonalizedMatrix_h
#define DiagonalizedMatrix_h

namespace MatrixUtil {
    class DiagonalizedMatrix {
    public:
        //============
        // Constructors
        //============
        DiagonalizedMatrix() = default;
        DiagonalizedMatrix(const Matrix & mat); //Throw Exception if not square
        DiagonalizedMatrix(const DiagonalizedMatrix & dMat); //Copy
        ~DiagonalizedMatrix() = default;
        
        //============
        // Getters
        //============
        COBMatrix getIEB() const {return iEB;}
        Matrix getD() const {return d;}
        COBMatrix getIBE const {return iBE;}
        
    private:
        //=============
        // Helping Functions
        //=============
        
        
        //=============
        // Matrices
        //=============
        COBMatrix iEB;
        Matrix d;
        COBMatrix iBE;
        
        //=============
        // Other data Members
        //=============
        int dim;
        std::vector<double> eigenvalues;
    };
}

#endif /* DiagonalizedMatrix_h */
