
#include<stdio.h>
#include<stdlib.h>

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2);
double** transposeMatrix(double** mat, int row, int col);
double** inverseMatrix(double **matA, int dimension);

void freeMat(double **matrix, int rows) //to free transpose swap rows w/ cols
{
    for(int i=0; i<rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void printMat(double **matrix, int rows, int cols) //to print tranpose swap rows w/ cols
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            double value = matrix[i][j];
            printf("%lf ", value);
        }
        printf("\n");
    }
}


// main method starts here
int main(int argc, char** argv)
{
  if(argc < 3)
  {
    printf("insufficient arguments\n");
    return 0;
  }
  int rows;
  int cols;
  FILE *fp = fopen(argv[1], "r");
  if(fp==NULL)
  {
    printf("file1 empty\n");
    return 0;
  }
  fscanf(fp, "%d\n%d\n", &cols, &rows);
  //matrix dimensions stored -> allocate -> populate matrix

  double **matX = malloc(rows*sizeof(double*));
  for(int i=0; i<rows; i++)
  {
    matX[i] = malloc((cols+1)*sizeof(double));
  }

  //train matrix allocated

  double **matY = malloc(rows*sizeof(double*));
  for(int i=0; i<rows; i++)
  {
    matY[i] = malloc(1*sizeof(double));
  }

  //prices matrix allocated

  //printf("allocation success\n" );

  //loads attribute matrix & prices matrix

  double value;
  for(int p=0; p<rows; p++)
  {
    for(int i=0; i<cols+1; i++)
    {
      if(i==0)
      {
        //printf("beginning 1\n");
        matX[p][i] = 1.000000;
      }
      else
      {
        fscanf(fp, "%lf%*c", &value);
        matX[p][i] = value;
        //printf("inserted %f\n", value);
        if(i==cols)
        {
          fscanf(fp, "%lf%*c\n", &value);
          matY[p][0] = value;
          //printf("added %f to prices\n", value );
          break;
        }
      }
    }
  }

  //allocate and load weights(k+1) matrix (to be solved for)
  int k = cols+1;
  double **matW = malloc(k*sizeof(double*));
  for(int i=0; i<k; i++)
  {
    matW[i] = malloc(1*sizeof(double));
  }

  //allocated -> load

  for(int j=0; j<k; j++)
  {
    matW[j][0] = 0.000000;
  }

  //deal with second file Input
  double f2Value;
  int testAttributes = cols+1; //check
  int f2Rows;
  FILE *fp2 = fopen(argv[2], "r");
  if(fp2 == NULL)
  {
    printf("file2 empty\n");
    return 0;
  }
  fscanf(fp2, "%d\n", &f2Rows);

  //allocate memory for test matrix

  double **testFile = malloc(f2Rows*sizeof(double*));
  for(int i=0; i<f2Rows; i++)
  {
    testFile[i] = malloc(testAttributes*sizeof(double));
  }

  //allocated -> now load

  for(int j=0; j<f2Rows; j++)
  {
    for(int k=0; k<testAttributes; k++)
    {
      if(k==0)
      {
        testFile[j][k] = 1.000000;
      }
      else
      {
        fscanf(fp2, "%lf%*c", &f2Value);
        testFile[j][k] = f2Value;
      }
    }
  }
  double **transX = transposeMatrix(matX, rows, cols+1);
  double **xty = multiplyMatrix(transX, matY, cols+1, rows, rows, 1);
  double **xtx = multiplyMatrix(transX, matX, cols+1, rows, rows, cols+1);
  double **xtxInv = inverseMatrix(xtx, cols+1);
  double **multAll = multiplyMatrix(xtxInv, xty, cols+1, cols+1, cols+1, 1);
  double **finPrices = multiplyMatrix(testFile, multAll, f2Rows, testAttributes, k, 1);

  double roundedPrice; //rounds final answers
  for(int i=0; i<f2Rows; i++)
  {
    for(int j=0; j<1; j++)
    {
      roundedPrice = finPrices[i][j];
      printf("%0.0lf\n", roundedPrice);
    }
  }

  freeMat(matY, rows);
  freeMat(matX, rows);
  freeMat(matW, k);
  freeMat(transX, cols+1);
  freeMat(xty, cols+1);
  freeMat(xtx, cols+1);
  freeMat(xtxInv, cols+1);
  freeMat(multAll, cols+1);
  freeMat(testFile, f2Rows);
  freeMat(finPrices, f2Rows);
  fclose(fp);
  fclose(fp2);
  return 0;
}

double** multiplyMatrix(double **matA, double **matB, int r1, int c1, int r2, int c2)
{
  if(c1 != r2)
  {
    printf("dimension error\n");
    return 0;
  }
  double multVal = 0.000000;
  double** result=malloc(r1*sizeof(double*));
  for(int i=0; i<r1; i++)
  {
    result[i] = malloc(c2*sizeof(double));
  }
  //malloc complete -> ready for manipulation
  for(int rowA=0; rowA<r1; rowA++)//traverses a rows
  {
    for(int colB=0; colB<c2; colB++)//traverses b cols
    {
      for(int colA=0; colA<c1; colA++)//traverses a cols
      {
        multVal += (matA[rowA][colA] * matB[colA][colB]);
      }
      result[rowA][colB] = multVal; //dumps value into matrix after row cycle
      multVal = 0; //reset
    }
  }
  return result;
}

double** transposeMatrix(double** mat, int row, int col)
{
  double value;
	double** matTran = malloc(col*sizeof(double*));
  for(int i=0; i<col; i++)
  {
    matTran[i] = malloc(row*sizeof(double));
  }
  //allocation for transpose complete

  for(int i=0; i<row; i++) //traverses -> swaps vals
  {
    for(int j=0; j<col; j++)
    {
      value = mat[i][j];
      matTran[j][i] = value;
    }
  }

  return matTran;
}

//check pseudocode
void scalerSub(double **matrix, int mainRow, int edit, double scaler, int dimension)
{
  for(int i=0; i<dimension; i++)
  {
    matrix[edit][i] = matrix[edit][i] - (matrix[mainRow][i] * scaler);
  }
}

double** inverseMatrix(double **matA, int dimension)
{
    double** matI=malloc(dimension*sizeof(double*));
    for(int i=0; i<dimension; i++)
    {
      matI[i] = malloc(dimension*sizeof(double));
    }
    //malloc done -> make identity
    for(int i=0; i<dimension; i++)
    {
      for(int j=0; j<dimension; j++)
      {
        if(i!=j)
        {
          matI[i][j] = 0;
        }
        else
        {
          matI[i][j] = 1;
        }
      }
    }
    //loaded identity matrix
    //matrix ready for row operations
    double pivot;
    for(int i=0; i<dimension; i++) //traverses rows of matrix
    {
      pivot = matA[i][i];
      for(int j=0; j<dimension; j++) //loop divides -> makes pivot values 1
      {
          matA[i][j] = (matA[i][j] / pivot);
          matI[i][j] = (matI[i][j] / pivot);
          //printf("sub loop broken\n");
      }
      for(int rowUnder=i+1; rowUnder<dimension; rowUnder++) //zeroes out values under pivot
      {
          double scaler = matA[rowUnder][i];
          scalerSub(matA, i, rowUnder, scaler, dimension);
          scalerSub(matI, i, rowUnder, scaler, dimension);
      }
    }
    //matrix is now in upper triangular form -> reverse traverse
    for(int i=dimension-1; i >= 0; i--)
    {
      for(int j=i-1; j >= 0; j--)
      {
        double factor = matA[j][i];
        scalerSub(matA, i, j, factor, dimension);
        scalerSub(matI, i, j, factor, dimension);
      }
    }
	return matI;
}
