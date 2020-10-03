#include "DataParser.h"

DataSet CreateDataSet(FILE* pData, unsigned int InputCount)
{
  DataSet DataSet = { 0 };

  DataSet.InputCount = InputCount;
  DataSet.Length = GetRows(pData);
  
  DataSet.x = (double**)calloc(DataSet.Length, sizeof(*DataSet.x));
  for (unsigned int i = 0; i < DataSet.Length; i++)
  {
    DataSet.x[i] = (double*)calloc(DataSet.InputCount, sizeof(*DataSet.x[i]));
  }
  DataSet.y = (double*)calloc(DataSet.Length, sizeof(*DataSet.y));
  
  for (unsigned int r = 0; r < DataSet.Length; r++)
  {
    char c;
    for (unsigned int x = 0; x < DataSet.InputCount; x++)
    {
      fscanf(pData, "%lf", &DataSet.x[r][x]);
      c = getc(pData);
    }
    
    fscanf(pData, "%lf", &DataSet.y[r]);
    c = getc(pData);
  }
 
  return DataSet;
}

void DestroyDataSet(DataSet DataSet)
{
  for (unsigned int i = 0; i < DataSet.Length; i++)
  {
    free(DataSet.x[i]);
  }
  free(DataSet.x);

  free(DataSet.y);
}

unsigned int GetRows(FILE* pData)
{
  unsigned int Rows = 0;
  for (char c = getc(pData); c != EOF; c = getc(pData))
  { 
    if (c == '\n') { Rows++; }
  }

  fseek(pData, 0, SEEK_SET);

  return Rows;
}
