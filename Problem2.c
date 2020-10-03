#include "DataParser.h"
#include "Matrix.h"

#define INPUT_COUNT 3
#define PARAMETER_COUNT (INPUT_COUNT + 1)

double** CreateMassagedInputData(DataSet DataSet);
double** CreateMessagedOutputData(DataSet DataSet);
void DestroyMassagedData(double** Data, unsigned int Height);

int main()
{
  FILE* pData = fopen("P2.csv", "r");
  DataSet DataSet = CreateDataSet(pData, INPUT_COUNT);
  fclose(pData);
  
  double** InputData = CreateMassagedInputData(DataSet);
  double** OutputData = CreateMessagedOutputData(DataSet);
  
  Matrix X = CreateMatrix(DataSet.Length, DataSet.InputCount + 1);
  FillMatrix(X, InputData, DataSet.Length, DataSet.InputCount + 1);
  
  Matrix Y = CreateMatrix(DataSet.Length, 1);
  FillMatrix(Y, OutputData, DataSet.Length, 1);

  Matrix XTranspose = CreateTranspose(X);
  Matrix DotProduct1 = CreateDotProduct(XTranspose, X);
  Matrix Inverse = CreateInverse(DotProduct1);
  Matrix DotProduct2 = CreateDotProduct(Inverse, XTranspose);
  Matrix Result = CreateDotProduct(DotProduct2, Y);

  PrintMatrix(Result);

  DestroyMatrix(Result);
  DestroyMatrix(DotProduct2);
  DestroyMatrix(Inverse);
  DestroyMatrix(DotProduct1);
  DestroyMatrix(XTranspose);
  DestroyMatrix(Y);
  DestroyMatrix(X);
  DestroyMassagedData(OutputData, DataSet.Length);
  DestroyMassagedData(InputData, DataSet.Length);
  DestroyDataSet(DataSet);
  
  return 0;
}

double** CreateMassagedInputData(DataSet DataSet)
{
  double** InputData = (double**)calloc(DataSet.Length, sizeof(*InputData));
  for (unsigned int r = 0; r < DataSet.Length; r++)
    { InputData[r] = (double*)calloc(DataSet.InputCount + 1, sizeof(*InputData[r])); }

  for (unsigned int r = 0; r < DataSet.Length; r++)
  {
    for (unsigned int c = 0; c < DataSet.InputCount + 1; c++)
    {
      if (c == 0)
        { InputData[r][c] = 1;}
      else
        { InputData[r][c] = DataSet.x[r][c-1]; }
    }
  }
  
  return InputData;
}

double** CreateMessagedOutputData(DataSet DataSet)
{
  double** OutputData = (double**)calloc(DataSet.Length, sizeof(*OutputData));
  for (unsigned int r = 0; r < DataSet.Length; r++)
    { OutputData[r] = (double*)calloc(1, sizeof(*OutputData[r])); }

  for (unsigned int r = 0; r < DataSet.Length; r++) 
  {
    OutputData[r][0] = DataSet.y[r];
  }

  return OutputData;
}

void DestroyMassagedData(double** Data, unsigned int Height)
{
  for (unsigned int r = 0; r < Height; r++)
  {
    free(Data[r]);
  }

  free(Data);
}
