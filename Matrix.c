#include "Matrix.h"

Matrix CreateMatrix(unsigned int Height, unsigned int Width)
{
  Matrix Output = { 0 };

  Output.Height = Height;
  Output.Width = Width;

  Output.Data = (double**)calloc(Height, sizeof(*Output.Data));
  for (unsigned int i = 0; i < Output.Height; i++)
  {
    Output.Data[i] = (double*)calloc(Width, sizeof(*Output.Data[i]));
  }
  
  return Output;
}

void DestroyMatrix(Matrix InputMatrix)
{
  for (unsigned int i = 0; i < InputMatrix.Height; i++)
  {
    free(InputMatrix.Data[i]);
  }

  free(InputMatrix.Data);
}

void FillMatrix(Matrix InputMatrix, double** Data, unsigned int Height, unsigned int Width)
{
  if (InputMatrix.Height != Height && InputMatrix.Width != Width)
  { 
    printf("Error filling matrix!");  
    return; 
  }
  
  for (unsigned int r = 0; r < InputMatrix.Height; r++)
  {
    for (unsigned int c = 0; c < InputMatrix.Width; c++)
    {
      InputMatrix.Data[r][c] = Data[r][c];
    }
  }

  return;
}

Matrix CreateTranspose(Matrix InputMatrix)
{
  Matrix Output = CreateMatrix(InputMatrix.Width, InputMatrix.Height);
 
  for (unsigned int r = 0; r < InputMatrix.Height; r++)
  {
    for (unsigned int c = 0; c < InputMatrix.Width; c++)
    {
      Output.Data[c][r] = InputMatrix.Data[r][c];
    }
  }

  return Output;
}

Matrix CreateAdjoint(Matrix InputMatrix)
{
  Matrix Output = CreateMatrix(InputMatrix.Height, InputMatrix.Width);
  if (InputMatrix.Height != InputMatrix.Width)
    { return Output; }

  if (InputMatrix.Height == 1)
    { Output.Data[0][0] = 1; return Output;}
  
  int sign = 1;
  Matrix Temp = CreateMatrix(InputMatrix.Height, InputMatrix.Width);
  
  for (unsigned int r = 0; r < InputMatrix.Height; r++)
  {
    for (unsigned int c = 0; c < InputMatrix.Width; c++)
    {
      Matrix Temp = CreateCofactor(InputMatrix, r, c, InputMatrix.Height);
      
      sign = ((r + c) % 2 == 0) ? 1 : -1;

      Output.Data[c][r] = (sign) * GetDeterminant(Temp, InputMatrix.Height - 1);

      DestroyMatrix(Temp);
    }
  }
  
  DestroyMatrix(Temp);

  return Output;
}

Matrix CreateCofactor(Matrix InputMatrix, unsigned int Row, unsigned int Col, unsigned int Dim)
{
  Matrix Output = CreateMatrix(Dim - 1, Dim - 1);
  if (InputMatrix.Height != InputMatrix.Width)
    { return Output; }

  unsigned int i = 0;
  unsigned int j = 0;
  
  for (unsigned int r = 0; r < InputMatrix.Height; r++)
  {
    for (unsigned int c = 0; c < InputMatrix.Width; c++)
    {
      if (r != Row && c != Col)
      {
        Output.Data[i][j++] = InputMatrix.Data[r][c];

        if (j == Dim - 1)
        {
          j = 0;
          i++;
        }
      }
    }
  }

  return Output;
}

Matrix CreateInverse(Matrix InputMatrix)
{
  Matrix Output = CreateMatrix(InputMatrix.Height, InputMatrix.Width);
  if (InputMatrix.Height != InputMatrix.Width)
    { return Output; }

  double Det = GetDeterminant(InputMatrix, InputMatrix.Height);

  if (Det == 0)
  {
    printf("Signular matrix, cannot take inverse");
    return Output;
  }
  
  Matrix Adjoint = CreateAdjoint(InputMatrix);

  for (unsigned int r = 0; r < InputMatrix.Height; r++)
  {
    for (unsigned int c = 0; c < InputMatrix.Width; c++)
    {
      Output.Data[r][c] = Adjoint.Data[r][c] / Det;
    }
  }

  return Output;
}

Matrix CreateDotProduct(Matrix MatrixA, Matrix MatrixB)
{
  Matrix Output = CreateMatrix(MatrixA.Height, MatrixB.Width);
  if (MatrixA.Width != MatrixB.Height)
    { return Output; }

  for (unsigned int r = 0; r < Output.Height; r++)
  {
    for (unsigned int c = 0; c < Output.Width; c++)
    {
      for (unsigned int i = 0; i < MatrixA.Width; i++)
      {
        Output.Data[r][c] += MatrixA.Data[r][i] * MatrixB.Data[i][c];
      }
    }
  }

  return Output;
}

double GetDeterminant(Matrix InputMatrix, unsigned int Dim)
{
  double Output = NAN;
  if (InputMatrix.Height != InputMatrix.Width)
    { return Output; }
  Output = 0.0;

  if (Dim == 1)
    { return InputMatrix.Data[0][0]; }

  int sign = 1;

  for (unsigned int c = 0; c < Dim; c++)
  {
    Matrix Temp = CreateCofactor(InputMatrix, 0, c, Dim);
    Output += sign * InputMatrix.Data[0][c] * GetDeterminant(Temp, Dim - 1);
    sign = -sign;
    DestroyMatrix(Temp);
  }

  return Output;
}

void PrintMatrix(Matrix InputMatrix)
{
  printf("[%d x %d] Matrix\n", InputMatrix.Height, InputMatrix.Width);

  for (unsigned int r = 0; r < InputMatrix.Height; r++)
  {
    for (unsigned int c = 0; c < InputMatrix.Width; c++)
    {
      if (c == InputMatrix.Width - 1)
      {
        printf("%lf\n", InputMatrix.Data[r][c]);
      }
      else
      {
        printf("%lf, ", InputMatrix.Data[r][c]);
      }    
    }
  }
}
