#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  char command[10];
  int lineNum = -1;
  short registers[4];
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    printf("Error: File Empty\n");
    return 0;
  }
  char skip[10];
  while (fscanf(fp, "%s ", command) != EOF)
  {
    lineNum++;
    //---------READ & PRINT----------//
    if (strcmp(command, "read") == 0) //READ
    {
      short userVal = 0;
      scanf("%hu", &userVal);      //grab user input
      fscanf(fp, "%s\n", command); //grab register
      if (command[0] == 'a')
      {
        registers[0] = userVal;
      }
      if (command[0] == 'b')
      {
        registers[1] = userVal;
      }
      if (command[0] == 'c')
      {
        registers[2] = userVal;
      }
      if (command[0] == 'd')
      {
        registers[3] = userVal;
      }
    }
    if (strcmp(command, "print") == 0) //PRINT
    {
      fscanf(fp, "%s\n", command);
      if (command[0] == 'a')
      {
        printf("%hi", registers[0]);
      }
      if (command[0] == 'b')
      {
        printf("%hi", registers[1]);
      }
      if (command[0] == 'c')
      {
        printf("%hi", registers[2]);
      }
      if (command[0] == 'd')
      {
        printf("%hi", registers[3]);
      }
    }
    //---------ARITHMETIC/MOV----------//
    if (command[0] == 'a' && command[1] == 'd') //ADD
    {
      short arg1;
      short arg2;
      for (int i = 0; i < 2; i++) //grabs args
      {
        if (i == 1) //second arg must be register
        {
          fscanf(fp, "%s", command);
          if (command[0] == 'a')
          {
            arg2 = registers[0];
          }
          if (command[0] == 'b')
          {
            arg2 = registers[1];
          }
          if (command[0] == 'c')
          {
            arg2 = registers[2];
          }
          if (command[0] == 'd')
          {
            arg2 = registers[3];
          }
        }
        else
        {
          fscanf(fp, "%s", command); //grabs arg1
          if (command[1] != 'x')     //checks if arg1 is register
          {
            arg1 = atoi(command); //stores arg1
          }
          else //assume arg1 is register val
          {
            if (command[0] == 'a')
            {
              arg1 = registers[0];
            }
            if (command[0] == 'b')
            {
              arg1 = registers[1];
            }
            if (command[0] == 'c')
            {
              arg1 = registers[2];
            }
            if (command[0] == 'd')
            {
              arg1 = registers[3];
            }
          }
        }
      }
      //ready to add + update register
      if (command[0] == 'a')
      {
        registers[0] = arg1 + arg2;
      }
      if (command[0] == 'b')
      {
        registers[1] = arg1 + arg2;
      }
      if (command[0] == 'c')
      {
        registers[2] = arg1 + arg2;
      }
      if (command[0] == 'd')
      {
        registers[3] = arg1 + arg2;
      }
    }
    if (command[0] == 's') //SUBTRACT
    {
      short arg1;
      short arg2;
      for (int i = 0; i < 2; i++) //grabs args
      {
        if (i == 1) //second arg must be register
        {
          fscanf(fp, "%s", command);
          if (command[0] == 'a')
          {
            arg2 = registers[0];
          }
          if (command[0] == 'b')
          {
            arg2 = registers[1];
          }
          if (command[0] == 'c')
          {
            arg2 = registers[2];
          }
          if (command[0] == 'd')
          {
            arg2 = registers[3];
          }
        }
        else
        {
          fscanf(fp, "%s", command); //grabs arg1
          if (command[1] != 'x')     //checks if arg1 is register
          {
            arg1 = atoi(command); //stores arg1
          }
          else //assume arg1 is register val
          {
            if (command[0] == 'a')
            {
              arg1 = registers[0];
            }
            if (command[0] == 'b')
            {
              arg1 = registers[1];
            }
            if (command[0] == 'c')
            {
              arg1 = registers[2];
            }
            if (command[0] == 'd')
            {
              arg1 = registers[3];
            }
          }
        }
      }
      //ready to subtract + update register
      if (command[0] == 'a')
      {
        registers[0] = arg2 - arg1;
      }
      if (command[0] == 'b')
      {
        registers[1] = arg2 - arg1;
      }
      if (command[0] == 'c')
      {
        registers[2] = arg2 - arg1;
      }
      if (command[0] == 'd')
      {
        registers[3] = arg2 - arg1;
      }
    }
    if (command[0] == 'm' && command[1] == 'u') //MULTIPLY
    {
      short arg1;
      short arg2;
      for (int i = 0; i < 2; i++) //grabs args
      {
        if (i == 1) //second arg must be register
        {
          fscanf(fp, "%s", command);
          if (command[0] == 'a')
          {
            arg2 = registers[0];
          }
          if (command[0] == 'b')
          {
            arg2 = registers[1];
          }
          if (command[0] == 'c')
          {
            arg2 = registers[2];
          }
          if (command[0] == 'd')
          {
            arg2 = registers[3];
          }
        }
        else
        {
          fscanf(fp, "%s", command); //grabs arg1
          if (command[1] != 'x')     //checks if arg1 is register
          {
            arg1 = atoi(command); //stores arg1
          }
          else //assume arg1 is register val
          {
            if (command[0] == 'a')
            {
              arg1 = registers[0];
            }
            if (command[0] == 'b')
            {
              arg1 = registers[1];
            }
            if (command[0] == 'c')
            {
              arg1 = registers[2];
            }
            if (command[0] == 'd')
            {
              arg1 = registers[3];
            }
          }
        }
      }
      //ready to multiply + update register
      if (command[0] == 'a')
      {
        registers[0] = arg1 * arg2;
      }
      if (command[0] == 'b')
      {
        registers[1] = arg1 * arg2;
      }
      if (command[0] == 'c')
      {
        registers[2] = arg1 * arg2;
      }
      if (command[0] == 'd')
      {
        registers[3] = arg1 * arg2;
      }
    }
    if (command[0] == 'm' && command[1] == 'o') //MOVE
    {
      short arg1;
      for (int i = 0; i < 2; i++) //grabs args
      {
        if (i == 1) //second arg must be register
        {
          fscanf(fp, "%s", command); //grabs register to update
        }
        else
        {
          fscanf(fp, "%s", command); //grabs arg1
          if (command[1] != 'x')     //checks if arg1 is register
          {
            arg1 = atoi(command); //stores arg1
          }
          else //assume arg1 is register val
          {
            if (command[0] == 'a')
            {
              arg1 = registers[0];
            }
            if (command[0] == 'b')
            {
              arg1 = registers[1];
            }
            if (command[0] == 'c')
            {
              arg1 = registers[2];
            }
            if (command[0] == 'd')
            {
              arg1 = registers[3];
            }
          }
        }
      }
      //args ready -> update registers
      if (command[0] == 'a')
      {
        registers[0] = arg1;
      }
      if (command[0] == 'b')
      {
        registers[1] = arg1;
      }
      if (command[0] == 'c')
      {
        registers[2] = arg1;
      }
      if (command[0] == 'd')
      {
        registers[3] = arg1;
      }
    }
    if (command[0] == 'd') //DIVIDE
    {
      short arg1;
      short arg2;
      for (int i = 0; i < 2; i++) //grabs args
      {
        if (i == 1) //second arg must be register
        {
          fscanf(fp, "%s", command);
          if (command[0] == 'a')
          {
            arg2 = registers[0];
          }
          if (command[0] == 'b')
          {
            arg2 = registers[1];
          }
          if (command[0] == 'c')
          {
            arg2 = registers[2];
          }
          if (command[0] == 'd')
          {
            arg2 = registers[3];
          }
        }
        else
        {
          fscanf(fp, "%s", command); //grabs arg1
          if (command[1] != 'x')     //checks if arg1 is register
          {
            arg1 = atoi(command); //stores arg1
          }
          else //assume arg1 is register val
          {
            if (command[0] == 'a')
            {
              arg1 = registers[0];
            }
            if (command[0] == 'b')
            {
              arg1 = registers[1];
            }
            if (command[0] == 'c')
            {
              arg1 = registers[2];
            }
            if (command[0] == 'd')
            {
              arg1 = registers[3];
            }
          }
        }
      }
      //ready to divide + update register
      if (arg2 != 0)
      {
        if (command[0] == 'a')
        {
          registers[0] = arg1 / arg2;
        }
        if (command[0] == 'b')
        {
          registers[1] = arg1 / arg2;
        }
        if (command[0] == 'c')
        {
          registers[2] = arg1 / arg2;
        }
        if (command[0] == 'd')
        {
          registers[3] = arg1 / arg2;
        }
      }
      else
      {
        printf("Error: Invalid Division\n");
        return 0;
      }
    }
    //---------JUMP----------//
    if (command[0] == 'j') //JUMP -> determines which kind of jump function
    {
      int jumpVal = 101;
      fscanf(fp, "%d\n", &jumpVal); //gets the jump line #
      if (command[1] == 'm')        //standard 1 arg jump function
      {
        rewind(fp);
        lineNum = jumpVal - 1;
        for (int i = jumpVal; i > 0; i--)
        {
          fgets(skip, sizeof(skip), fp);
        }
      }
      if (command[1] == 'l') //JLE and JL
      {
        int type = 0;
        if (command[2] == 'e') //checks whether command is jl or jle;
        {
          type = 1;
        }
        short arg1;
        short arg2;
        for (int i = 1; i < 3; i++) //grabs all 3 args
        {
          if (i == 0) //first val will be int
          {
            fscanf(fp, "%d", &jumpVal); //stores L into a var
          }
          if (i == 1) //determine if arg is register or input
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg1 = atoi(command);
            }
            else //if register val -> arg1
            {
              if (command[0] == 'a')
              {
                arg1 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg1 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg1 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg1 = registers[3];
              }
            }
          }
          if (i == 2) //determine arg2 and perform operations
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg2 = atoi(command);
            }
            else //if register val -> arg2
            {
              if (command[0] == 'a')
              {
                arg2 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg2 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg2 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg2 = registers[3];
              }
            }
          }
        }
        if (type == 0)
        {
          if (arg1 < arg2)
          {
            rewind(fp);
            lineNum = jumpVal - 1;
            for (int i = jumpVal; i > 0; i--)
            {
              fgets(skip, sizeof(skip), fp);
            }
          } //end inequality
        }   //end type
        if (type == 1)
        {
          if (arg1 <= arg2)
          {
            rewind(fp);
            lineNum = jumpVal - 1;
            for (int i = jumpVal; i > 0; i--)
            {
              fgets(skip, sizeof(skip), fp);
            }
          }                  //end inequality
        }                    //end if type1
      }                      //end if jle
      if (command[1] == 'g') //JGE and JG
      {
        int type = 0;
        if (command[2] == 'e') //checks whether command is jg or jge;
        {
          type = 1;
        }
        short arg1;
        short arg2;
        for (int i = 1; i < 3; i++) //grabs all 3 args
        {
          if (i == 0) //first val will be int
          {
            fscanf(fp, "%d", &jumpVal); //stores L into a var
          }
          if (i == 1) //determine if arg is register or input
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg1 = atoi(command);
            }
            else //if register val -> arg1
            {
              if (command[0] == 'a')
              {
                arg1 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg1 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg1 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg1 = registers[3];
              }
            }
          }
          if (i == 2) //determine arg2
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg2 = atoi(command);
            }
            else //if register val -> arg2
            {
              if (command[0] == 'a')
              {
                arg2 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg2 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg2 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg2 = registers[3];
              }
            }
          }
        }
        if (type == 0)
        {
          if (arg1 > arg2)
          {
            rewind(fp);
            lineNum = jumpVal - 1;
            for (int i = jumpVal; i > 0; i--)
            {
              fgets(skip, sizeof(skip), fp);
            }
          } //end inequality
        }   //end type
        if (type == 1)
        {
          if (arg1 >= arg2)
          {
            rewind(fp);
            lineNum = jumpVal - 1;
            for (int i = jumpVal; i > 0; i--)
            {
              fgets(skip, sizeof(skip), fp);
            }
          }                  //end inequality
        }                    //end type 1
      }                      //end jge/je
      if (command[1] == 'e') //JE
      {
        short arg1;
        short arg2;
        for (int i = 1; i < 3; i++) //grabs all 3 args
        {
          if (i == 0) //first val will be int
          {
            fscanf(fp, "%d", &jumpVal); //stores L into a var
          }
          if (i == 1) //determine if arg is register or input
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg1 = atoi(command);
            }
            else //if register val -> arg1
            {
              if (command[0] == 'a')
              {
                arg1 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg1 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg1 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg1 = registers[3];
              }
            }
          }
          if (i == 2) //determine arg2 and perform operations
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg2 = atoi(command);
            }
            else //if register val -> arg2
            {
              if (command[0] == 'a')
              {
                arg2 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg2 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg2 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg2 = registers[3];
              }
            }
          }
        }
        if (arg1 == arg2)
        {
          rewind(fp);
          lineNum = jumpVal - 1;
          for (int i = jumpVal; i > 0; i--)
          {
            fgets(skip, sizeof(skip), fp);
          }
        }                                         //end equality
      }                                           //end je
      if (command[1] == 'n' && command[2] == 'e') //JNE
      {
        short arg1;
        short arg2;
        for (int i = 1; i < 3; i++) //grabs all 3 args
        {
          if (i == 0) //first val will be int
          {
            fscanf(fp, "%d", &jumpVal); //stores L into a var
          }
          if (i == 1) //determine if arg is register or input
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg1 = atoi(command);
            }
            else //if register val -> arg1
            {
              if (command[0] == 'a')
              {
                arg1 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg1 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg1 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg1 = registers[3];
              }
            }
          }
          if (i == 2) //determine arg2 and perform operations
          {
            fscanf(fp, "%s", command);
            if (command[1] != 'x') //if non register val -> arg1
            {
              arg2 = atoi(command);
            }
            else //if register val -> arg2
            {
              if (command[0] == 'a')
              {
                arg2 = registers[0];
              }
              if (command[0] == 'b')
              {
                arg2 = registers[1];
              }
              if (command[0] == 'c')
              {
                arg2 = registers[2];
              }
              if (command[0] == 'd')
              {
                arg2 = registers[3];
              }
            }
          }
        }
        if (arg1 != arg2)
        {
          rewind(fp);
          lineNum = jumpVal - 1;
          for (int i = jumpVal; i > 0; i--)
          {
            fgets(skip, sizeof(skip), fp);
          }
        } //end inequality
      }   //end jne
    }     //end jump command
  }
  printf("\n"); //starts terminal on new line
}
