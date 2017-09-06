/*
 * main.c
 *
 *  Created on: Sep 6, 2017
 *      Author: pablo martinez
 */

#include <stdio.h>
#include <stdint.h>

#include "ringbuffer.h"


/************************************************************************/
void printHelp(void)
{
  printf("\nRing buffer test console");
  printf("\nCommands:");
  printf("\n u [x] - push a value x");
  printf("\n o     - pop the next value");
  printf("\n e [x] - peek a value at position x");
  printf("\n s     - Show buffer status");
  printf("\n q     - quit");
  printf("\n h     - show this help");
}

/************************************************************************/
void printBuffReport(void)
{
  printf("\nBuffer report:");
  printf("\n\tCurrent size: %u", RBCurrentSizeGet());
  printf("\n\tMaximum size: %u", RBMaximumSizeGet());
  printf("\n\tBuffer full : %s", RBFull()?"YES":"NO");
  printf("\n\tBuffer empty: %s", RBEmpty()?"YES":"NO");
}

/************************************************************************/
void handleError(uint32_t err)
{
  char* error_desc[] = {
      "No error",
      "Buffer full",
      "Buffer empty",
      "Invalid index",
  };

  if(err < RB_LAST_ERR_INDEX)
  {
    printf("Error performing requested action. Error (%u): %s", err, error_desc[err]);
  }
}

/************************************************************************/
void push(uint32_t value)
{
  RB_result_t op_res;

  op_res = RBPush(value);

  if(op_res != RB_NO_ERROR)
  {
    handleError((uint32_t)op_res);
  }
  else
  {
    printf("\nPush value %u", value);
  }
}

/************************************************************************/
void pop()
{
  RB_result_t op_res;
  uint32_t read_value;

  op_res = RBPop(&read_value);

  if(op_res != RB_NO_ERROR)
  {
    handleError((uint32_t)op_res);
  }
  else
  {
    printf("\nPop value %u", read_value);
  }
}

/************************************************************************/
void peek(uint32_t index)
{
  RB_result_t op_res;
  uint32_t read_value;

  op_res = RBPeek(index, &read_value);

  if(op_res != RB_NO_ERROR)
  {
    handleError((uint32_t)op_res);
  }
  else
  {
    printf("\nPeek value at %u : %u", index, read_value);
  }
}

/************************************************************************/
int main(int argc,  char **argv)
{
  char running = 1;
  char option;
  char invalid_input;
  char input[16]; //enough space to read 2^32
  uint32_t value;
  uint32_t read_res;

  printHelp();

  while(running == 1)
  {
    // Initialize variables
    value = 0;
    option = 'h';
    invalid_input = 0;
    read_res = 0;

    // Read new command
    printf("\n>");
    if( fgets(input, sizeof(input), stdin) != NULL)
    {
      read_res = sscanf(input, "%c %u", &option, &value);
    }

    // Check read values
    if((read_res == 0) || (read_res == EOF))
    {
      invalid_input = 1;
    }
    else
    {
      switch(option)
      {
	case 'u':
	  if(read_res == 2)
	  {
	    push(value);
	  }
	  else
	  {
	    invalid_input = 1;
	  }
	  break;

	case 'o':
	  pop();
	  break;

	case 'e':
	  if(read_res == 2)
	  {
	    peek(value);
	  }
	  else
	  {
	    invalid_input = 1;
	  }
	  break;

	case 's':
	  printBuffReport();
	  break;

	case 'q':
	  running = 0;
	  break;
	default:
	  invalid_input = 1;
	  break;
      }
    }

    if(invalid_input == 1)
    {
      printf("\nInvalid input parameters");
      printHelp();
    }
  }
  return 0;
}
