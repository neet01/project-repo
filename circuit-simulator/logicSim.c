#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
//list methods
struct Node
{
  char *data;
  struct Node *next;
};

struct Node *head = NULL;
struct Node *tempHead = NULL;

void insertHead(char *string)
{
  struct Node *newNode = malloc(sizeof(struct Node));
  newNode->data = malloc(strlen(string) + 1);
  strcpy(newNode->data, string);
  if (head == NULL)
  {
    head = newNode;
    head->next = NULL;
    return;
  }
  newNode->next = head;
  head = newNode;
}

void insertTemp(char *string)
{
  struct Node *newNode = malloc(sizeof(struct Node));
  newNode->data = malloc(strlen(string) + 1);
  strcpy(newNode->data, string);
  if (tempHead == NULL)
  {
    tempHead = newNode;
    tempHead->next = NULL;
    return;
  }
  newNode->next = tempHead;
  tempHead = newNode;
}

int index = 0;
int getIndex(char *target)
{
  struct Node *ptr = head;
  while (1)
  {
    if (strcmp(ptr->data, target) == 0)
    {
      return index;
    }
    index++;
    ptr = ptr->next;
  }
}

int tempIndex = 0;
int getIndexT(char *target)
{
  struct Node *ptr = tempHead;
  while (1)
  {
    if (strcmp(ptr->data, target) == 0)
    {
      return tempIndex;
    }
    tempIndex++;
    ptr = ptr->next;
  }
}

void printList(struct Node *head)
{
  struct Node *ptr = head;
  if (ptr == NULL)
  {
    return;
  }
  printList(ptr->next);
  printf("%s---", ptr->data);
}

//table methods

void printTable(int **matrix, int rows, int cols)
{
  int print = 0;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      print = matrix[i][j];
      printf("%d ", print);
    }
    printf("\n");
  }
}

void freeTable(int **matrix, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

void fillTable(int **matrix, int rows, int cols)
{
  int div = rows;
  int sep = rows / 2;
  for (int i = 0; i < cols; i++)
  {
    div = div / 2;
    for (int j = 0; j < sep; j++)
    {
      if (i == 0) //fill 1
      {
        matrix[j][i] = 0;
        matrix[j + div][i] = 1;
      }
      else
      {
        if (j < div && div == sep / 2) //fill 2
        {
          matrix[j][i] = 0;
          matrix[j + div][i] = 1;
          matrix[j + sep][i] = 0;
          matrix[j + sep + div][i] = 1;
        }
        else if (j < div && div < sep / 2)
        {
          matrix[j][i] = 0;
          matrix[j + div][i] = 1;
          matrix[j + sep][i] = 0;
          matrix[j + sep + div][i] = 1;
          //return;
        }
        else if (j > div && div < sep / 2)
        {
          if (matrix[j][i] != 1)
          {
            matrix[j][i] = 0;
            matrix[j + div][i] = 1;
            matrix[j + sep][i] = 0;
            matrix[j + sep + div][i] = 1;
          }
        }
      }
    }
  }
}

//temp methods
int checkTemp(char *string)
{
  struct Node *ptr = tempHead;
  while (ptr != NULL)
  {
    if (strcmp(ptr->data, string) == 0)
    {
      return 1;
    }
    ptr = ptr->next;
  }
  return 0;
}

int tempCount(FILE *fp)
{
  int temps = 0;
  char grab[15];
  while (fscanf(fp, "%s", grab) != EOF)
  {
    if (islower(grab[0]) != 0 && checkTemp(grab) == 0)
    {
      temps++;
      insertTemp(grab);
    }
  }
  return temps;
}

int main(int argc, char *argv[])
{
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    printf("Error: Invalid File\n");
    return 0;
  }
  int tempVals = tempCount(fp); //grabs number of temps
  rewind(fp);
  char var[10];
  char scan[10];
  char skip[16];
  char out[10];
  int inVal;
  int outVal;
  fscanf(fp, "%s %d\n", scan, &inVal); //skips INPUTVAR and grabs arg count

  //GRAB ARGUMENTS HERE------
  for (int i = 0; i < inVal; i++) //grabs input vars
  {
    fscanf(fp, "%s", var);
    insertHead(var);
  }
  fgets(skip, sizeof(skip), fp);
  fscanf(fp, "%s %d\n", scan, &outVal);
  for (int i = 0; i < outVal; i++) //grabs output vars
  {
    fscanf(fp, "%s", var);
    insertHead(var);
  }

  int size = inVal + outVal - 1;
  //END ARG GRAB------

  int rows = pow(2, inVal);
  int cols = inVal + outVal;
  int **truthTable = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
  {
    truthTable[i] = malloc(sizeof(int) * cols);
  }
  fillTable(truthTable, rows, cols);

  int **tempTable = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
  {
    tempTable[i] = malloc(tempVals * sizeof(int));
  }
  //table allocated and filled -> scan operators
  //scan -> operator
  int arg1;   //var
  int arg2;   //skip
  int argOut; //out
  //int ctr=0;
  while (fscanf(fp, "%s", scan) != EOF)
  {
    if (strcmp(scan, "NOT") == 0) //done
    {
      fscanf(fp, "%s %s\n", var, out); //grabs args
      if (islower(var[0]) != 0 || islower(out[0]) != 0)
      {
        if (islower(var[0] != 0) && islower(out[0] != 0)) //both temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else if (tempTable[i][arg1] == 1)
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0] != 0) && islower(out[0] == 0)) //input temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0)
            {
              truthTable[i][argOut] = 1;
            }
            else if (tempTable[i][arg1] == 1)
            {
              truthTable[i][argOut] = 0;
            }
          }
        }
        else //output temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else if (truthTable[i][arg1] == 1)
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
      }
      else
      {
        arg1 = abs(getIndex(var) - size);
        index = 0;
        argOut = abs(getIndex(out) - size);
        index = 0;
        for (int i = 0; i < rows; i++)
        {
          if (truthTable[i][arg1] == 0)
          {
            truthTable[i][argOut] = 1;
          }
          else if (truthTable[i][arg1] == 1)
          {
            truthTable[i][argOut] = 0;
          }
        }
      }
    }
    if (strcmp(scan, "AND") == 0) //done
    {
      fscanf(fp, "%s %s %s\n", var, skip, out); //grabs args
      if (islower(var[0]) != 0 || islower(skip[0]) != 0 || islower(out[0]) != 0)
      {
        if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) // all temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) // input temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - (size));
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 1;
            }
            else
            {
              truthTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //output temp
        {
          //update temp array for output
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (truthTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) == 0) //input1 temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 1;
            }
            else
            {
              truthTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) //input 2 temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 1;
            }
            else
            {
              truthTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) //last 2 temp
        {
          arg1 = abs(getIndex(var) - (size));
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (truthTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //in1 and out temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - (size));
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
      }
      else //no temp
      {
        arg1 = abs(getIndex(var) - size);
        index = 0;
        arg2 = abs(getIndex(skip) - size);
        index = 0;
        argOut = abs(getIndex(out) - size);
        index = 0;
        for (int i = 0; i < rows; i++)
        {
          if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
          {
            truthTable[i][argOut] = 0;
          }
          else if (truthTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
          {
            truthTable[i][argOut] = 1;
          }
          else
          {
            truthTable[i][argOut] = 0;
          }
        }
      }
    }
    if (strcmp(scan, "OR") == 0) //done
    {
      fscanf(fp, "%s %s %s\n", var, skip, out); //grabs args
      if (islower(var[0]) != 0 || islower(skip[0]) != 0 || islower(out[0]) != 0)
      {
        if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) // all temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) // input temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - (size));
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //output temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) == 0) //input1 temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) //input 2 temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) //last 2 temp
        {
          arg1 = abs(getIndex(var) - (size));
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //in1 and out temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - (size));
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
      }
      else //no temp
      {
        arg1 = abs(getIndex(var) - size);
        index = 0;
        arg2 = abs(getIndex(skip) - size);
        index = 0;
        argOut = abs(getIndex(out) - size);
        index = 0;
        for (int i = 0; i < rows; i++)
        {
          if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
          {
            truthTable[i][argOut] = 0;
          }
          else
          {
            truthTable[i][argOut] = 1;
          }
        }
      }
    }
    if (strcmp(scan, "NAND") == 0) //done
    {
      fscanf(fp, "%s %s %s\n", var, skip, out); //grabs args
      if (islower(var[0]) != 0 || islower(skip[0]) != 0 || islower(out[0]) != 0)
      {
        if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) // all temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) // input temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - (size));
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 1;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //output temp
        {
          //update temp array for output
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else if (truthTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) == 0) //input1 temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 1;
            }
            else if (tempTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) //input 2 temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 1;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) //last 2 temp
        {
          arg1 = abs(getIndex(var) - (size));
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else if (truthTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //in1 and out temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - (size));
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else if (tempTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
      }
      else //no temp
      {
        arg1 = abs(getIndex(var) - size);
        index = 0;
        arg2 = abs(getIndex(skip) - size);
        index = 0;
        argOut = abs(getIndex(out) - size);
        index = 0;
        for (int i = 0; i < rows; i++)
        {
          if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
          {
            truthTable[i][argOut] = 1;
          }
          else if (truthTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
          {
            truthTable[i][argOut] = 0;
          }
          else
          {
            truthTable[i][argOut] = 1;
          }
        }
      }
    }
    if (strcmp(scan, "NOR") == 0) //done
    {
      fscanf(fp, "%s %s %s\n", var, skip, out); //grabs args
      if (islower(var[0]) != 0 || islower(skip[0]) != 0 || islower(out[0]) != 0)
      {
        if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) // all temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) // input temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - (size));
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 1;
            }
            else
            {
              truthTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //output temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) == 0) //input1 temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 1;
            }
            else
            {
              truthTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) //input 2 temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 1;
            }
            else
            {
              truthTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) //last 2 temp
        {
          arg1 = abs(getIndex(var) - (size));
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //in1 and out temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - (size));
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 1;
            }
            else
            {
              tempTable[i][argOut] = 0;
            }
          }
        }
      }
      else //no temp
      {
        arg1 = abs(getIndex(var) - size);
        index = 0;
        arg2 = abs(getIndex(skip) - size);
        index = 0;
        argOut = abs(getIndex(out) - size);
        index = 0;
        for (int i = 0; i < rows; i++)
        {
          if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
          {
            truthTable[i][argOut] = 1;
          }
          else
          {
            truthTable[i][argOut] = 0;
          }
        }
      }
    }
    if (strcmp(scan, "XOR") == 0) //done
    {
      fscanf(fp, "%s %s %s\n", var, skip, out); //grabs args
      if (islower(var[0]) != 0 || islower(skip[0]) != 0 || islower(out[0]) != 0)
      {
        if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) // all temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) // input temps
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - (size));
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //output temp
        {
          //update temp array for output
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (truthTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) == 0) //input1 temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - size);
          index = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) == 0) //input 2 temp
        {
          arg1 = abs(getIndex(var) - size);
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndex(out) - size);
          index = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              truthTable[i][argOut] = 0;
            }
            else if (truthTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              truthTable[i][argOut] = 0;
            }
            else
            {
              truthTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) == 0 && islower(skip[0]) != 0 && islower(out[0]) != 0) //last 2 temp
        {
          arg1 = abs(getIndex(var) - (size));
          index = 0;
          arg2 = abs(getIndexT(skip) - (tempVals - 1));
          tempIndex = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (truthTable[i][arg1] == 0 && tempTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (truthTable[i][arg1] == 1 && tempTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
        else if (islower(var[0]) != 0 && islower(skip[0]) == 0 && islower(out[0]) != 0) //in1 and out temp
        {
          arg1 = abs(getIndexT(var) - (tempVals - 1));
          tempIndex = 0;
          arg2 = abs(getIndex(skip) - (size));
          index = 0;
          argOut = abs(getIndexT(out) - (tempVals - 1));
          tempIndex = 0;
          for (int i = 0; i < rows; i++)
          {
            if (tempTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
            {
              tempTable[i][argOut] = 0;
            }
            else if (tempTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
            {
              tempTable[i][argOut] = 0;
            }
            else
            {
              tempTable[i][argOut] = 1;
            }
          }
        }
      }
      else //no temp
      {
        arg1 = abs(getIndex(var) - size);
        index = 0;
        arg2 = abs(getIndex(skip) - size);
        index = 0;
        argOut = abs(getIndex(out) - size);
        index = 0;
        for (int i = 0; i < rows; i++)
        {
          if (truthTable[i][arg1] == 0 && truthTable[i][arg2] == 0)
          {
            truthTable[i][argOut] = 0;
          }
          else if (truthTable[i][arg1] == 1 && truthTable[i][arg2] == 1)
          {
            truthTable[i][argOut] = 0;
          }
          else
          {
            truthTable[i][argOut] = 1;
          }
        }
      }
    }
  }
  fclose(fp);
  printTable(truthTable, rows, cols);
  freeTable(truthTable, rows, cols);
  freeTable(tempTable, rows, tempVals);
}
