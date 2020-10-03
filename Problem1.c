#include "stdio.h"
#include "stdlib.h"
#include "DataParser.h"

#define INPUT_COUNT 3
#define PARAMETER_COUNT (INPUT_COUNT + 1)
#define MAX_UPDATE_COUNT 1000000
#define ALPHA 0.1

double HypothesisFunction(DataSet DataSet, double* Theta, unsigned int Index);
void UpdateTheta(DataSet DataSet, double* Theta, double alpha);

int main()
{
  FILE* pData = fopen("D3.csv", "r");
  DataSet DataSet = CreateDataSet(pData, INPUT_COUNT);
  fclose(pData);
  
  for (unsigned int UpdateCount = 1; UpdateCount < MAX_UPDATE_COUNT; UpdateCount *= 10) 
  {  
    double Theta[PARAMETER_COUNT] = { 0 };

    for (unsigned int i = 0; i < UpdateCount; i++)
    { /* This is the gradient decent */
      UpdateTheta(DataSet, Theta, ALPHA);
    }

    printf("Step Count: %d\n", UpdateCount);
    printf("Theta_0: %lf\n", Theta[0]);
    printf("Theta_1: %lf\n", Theta[1]);
    printf("Theta_2: %lf\n", Theta[2]);
    printf("Theta_3: %lf\n\n", Theta[3]);
  }
  
  DestroyDataSet(DataSet);

  return 0;
}

double HypothesisFunction(DataSet DataSet, double* Theta, unsigned int Index)
{
  double Output = Theta[0];
  for (unsigned int x = 0; x < DataSet.InputCount; x++)
  {
    Output += Theta[x + 1] * DataSet.x[Index][x];
  }
  return Output;
}

void UpdateTheta(DataSet DataSet, double* Theta, double alpha)
{ 
  double NewTheta[PARAMETER_COUNT] = { 0 };
  
  /* Calulate Theta[0] term (without coefficients) */ 
  double GradientTerm = 0.0; 
  for (unsigned int i = 0; i < DataSet.Length; i++)
  {
    GradientTerm += (HypothesisFunction(DataSet, Theta, i) - DataSet.y[i]) * (1);
  }
  GradientTerm /= (double)DataSet.Length;
  GradientTerm *= (double)alpha;
  NewTheta[0] = Theta[0] - GradientTerm;

  /* Calulate other Theta[x] terms (with coefficients) */ 
  for (unsigned int x = 0; x < DataSet.InputCount; x++)
  {
    GradientTerm = 0.0; 
    for (unsigned int i = 0; i < DataSet.Length; i++)
    {
      GradientTerm += (HypothesisFunction(DataSet, Theta, i) - DataSet.y[i]) * (DataSet.x[i][x]);
    }
    GradientTerm /= (double)DataSet.Length;
    GradientTerm *= (double)alpha;
    NewTheta[x + 1] = Theta[x + 1] - GradientTerm;
  }

  /* Update all theta's together */
  for (unsigned int i = 0; i < PARAMETER_COUNT; i++)
  {
    Theta[i] = NewTheta[i];
  }
}
