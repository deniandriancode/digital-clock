#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void fix_digit (int, int, int);
void print_block (int, int, int, int);
void print_colon (int);
int digit_convert (char);

/* add color and use ncurses */

int
main (int argc,
      char *argv[])
{
  int position;
  int i;
  int color_1 = 7;  // using default value

  char time_value[20];
  char date[20];
  time_t current_time; // time_t : data type used to store system time values

  while (1)
  {
    current_time = time(NULL); // time elapsed (in second) since Epoch

    struct tm *detailed_time = localtime (&current_time);

    strftime (time_value, 20, "%X", detailed_time); // get current time
    strftime (date, 20, "%Y-%m-%d", detailed_time); // get current date
    printf ("\033[?25l"); // hide the cursor
    printf ("\033[2J"); // clearn the screen
    for (i = 0; i < strlen(time_value); i++)
    {
      position = (i * 7) + 2;
      if (time_value[i] != ':')
      {
        int number = digit_convert(time_value[i]);
        fix_digit (number, position, 1);
      }
      else
        print_colon (position);
    }
    printf ("\n");
    sleep (1);
    printf ("\033[?25h"); // show the cursor
  }

  return 0;
}

int
digit_convert (char input)
{
  char array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for (int i = 0; i < strlen(array); i++)
  {
    if (array[i] == input)
    {
      return i;
    }
  }
}

void
print_block (int value, int position, int row, int col)
{
  printf ("\033[%d;%dH", row+2, col+position);
  if (value == 0)
  {
    printf ("\033[0m"); // reset bg
    printf (" ");
  }
  else if (value == 1)
  {
    printf ("\033[1;47m"); // set bg to white
    printf (" ");
    printf ("\033[0m"); // reset bg
  }
}

void
print_digit (int (*array)[6],
             int position,
             int colour)
{
  int row_index, column_index;

  for (row_index = 0; row_index < 5; row_index++)
  {
    for (column_index = 0; column_index < 6; column_index++)
    {
      print_block (array[row_index][column_index], position, row_index, column_index);
    }
    printf ("\n");
  }
}

void
print_colon (int position)
{
  int digit_array[5][6] = {
    {0,0,0,0,0,0},
    {0,0,1,1,0,0},
    {0,0,0,0,0,0},
    {0,0,1,1,0,0},
    {0,0,0,0,0,0}
  };
  
  print_digit (digit_array, position, 1);
}

void
fix_digit (int input,
           int position,
           int color)
{
  int digit_array[5][6];
  int digit = input;

  if (digit == 0)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {1,1,0,0,1,1},
      {1,1,0,0,1,1},
      {1,1,0,0,1,1},
      {1,1,1,1,1,1}
    };
  }
  else if (digit == 1)
  {
    int digit_array[5][6] = {
      {0,0,0,0,1,1},
      {0,0,0,0,1,1},
      {0,0,0,0,1,1},
      {0,0,0,0,1,1},
      {0,0,0,0,1,1}
    };
  }
  else if (digit == 2)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {0,0,0,0,1,1},
      {1,1,1,1,1,1},
      {1,1,0,0,0,0},
      {1,1,1,1,1,1}
    };
  }
  else if (digit == 3)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {0,0,0,0,1,1},
      {1,1,1,1,1,1},
      {0,0,0,0,1,1},
      {1,1,1,1,1,1}
    };
  }
  else if (digit == 4)
  {
    int digit_array[5][6] = {
      {1,1,0,0,1,1},
      {1,1,0,0,1,1},
      {1,1,1,1,1,1},
      {0,0,0,0,1,1},
      {0,0,0,0,1,1}
    };
  }
  else if (digit == 5)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {1,1,0,0,0,0},
      {1,1,1,1,1,1},
      {0,0,0,0,1,1},
      {1,1,1,1,1,1}
    };
  }
  else if (digit == 6)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {1,1,0,0,0,0},
      {1,1,1,1,1,1},
      {1,1,0,0,1,1},
      {1,1,1,1,1,1}
    };
  }
  else if (digit == 7)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {0,0,0,0,1,1},
      {0,0,0,0,1,1},
      {0,0,0,0,1,1},
      {0,0,0,0,1,1}
    };
  }
  else if (digit == 8)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {1,1,0,0,1,1},
      {1,1,1,1,1,1},
      {1,1,0,0,1,1},
      {1,1,1,1,1,1}
    };
  }
  else if (digit == 9)
  {
    int digit_array[5][6] = {
      {1,1,1,1,1,1},
      {1,1,0,0,1,1},
      {1,1,1,1,1,1},
      {0,0,0,0,1,1},
      {1,1,1,1,1,1}
    };
  }

  print_digit (digit_array, position, color);
}

