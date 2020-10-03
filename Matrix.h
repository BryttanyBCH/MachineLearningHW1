#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct
{
  double** Data;
  unsigned int Height;
  unsigned int Width;
}
Matrix;

Matrix CreateMatrix(unsigned int Height, unsigned int Width);
void DestroyMatrix(Matrix Matrix);

void FillMatrix(Matrix Matrix, double** Data, unsigned int Height, unsigned int Width);

Matrix CreateTranspose(Matrix Matrix);
Matrix CreateAdjoint(Matrix InputMatrix);
Matrix CreateCofactor(Matrix InputMatrix, unsigned int Row, unsigned int Col, unsigned int Dim);
Matrix CreateInverse(Matrix InputMatrix);

double GetDeterminant(Matrix InputMatrix, unsigned int Dim);
Matrix CreateDotProduct(Matrix MatrixA, Matrix MatrixB);

void PrintMatrix(Matrix InputMatrix);
