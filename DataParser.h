#include "stdio.h"
#include "stdlib.h"

typedef struct
{
  double** x;
  double* y;
  unsigned int InputCount;
  unsigned int Length;
            
}
DataSet;

DataSet CreateDataSet(FILE* pData, unsigned int InputCount);
void DestroyDataSet(DataSet DataSet);
unsigned int GetRows(FILE* pData);


