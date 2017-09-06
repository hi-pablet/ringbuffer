/*
 * ringtests.c
 *
 *  Created on: Sep 6, 2017
 *      Author: pablo martinez
 *
 *  These are very simple tests which cover the basic functionality of
 *  the ringbuffer. We could also test variables boundaries.
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ringbuffer.h"

/*
 ************************************************************************
 ** Private typedefs
 ************************************************************************
 */

typedef enum
{
  PASSED = 0,
  FAILED = 1,
}testResult_t;

typedef testResult_t (*testFunction_t)(void);

/*
 ************************************************************************
 ** Private function declaration
 ************************************************************************
 */

static testResult_t testPushPop(void);
static testResult_t testPushLimits(void);
static testResult_t testPopLimits(void);
static testResult_t testCurrentSize(void);
static testResult_t testEmptyFullFlags(void);
static testResult_t testOverflow(void);
static testResult_t testPeek(void);

/*
 ************************************************************************
 ** Private variables
 ************************************************************************
 */

static testFunction_t arrTests[] = {
    testPushPop,
    testPushLimits,
    testPopLimits,
    testCurrentSize,
    testEmptyFullFlags,
    testOverflow,
    testPeek,
    NULL};

/************************************************************************/
static testResult_t testPushPop(void)
{
  testResult_t res = PASSED;
  uint32_t i;
  uint32_t value;

  for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
  {
    if(RBPush(i) != RB_NO_ERROR)
    {
      res = FAILED;
      break;
    }
  }

  if(res == PASSED)
  {
    for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
    {
      if(RBPop(&value) != RB_NO_ERROR)
      {
	res = FAILED;
	break;
      }
      if(value != i)
      {
	res = FAILED;
	break;
      }
    }
  }

  return res;
}

/************************************************************************/
static testResult_t testPeek(void)
{
  testResult_t res = PASSED;
  uint32_t i;
  uint32_t value;

  for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
  {
    if(RBPush(i) != RB_NO_ERROR)
    {
      res = FAILED;
      break;
    }
  }

  if(res == PASSED)
  {
    for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
    {
      if(RBPeek(i,&value) != RB_NO_ERROR)
      {
	res = FAILED;
	break;
      }
      if(value != i)
      {
	res = FAILED;
	break;
      }
    }
  }

  if(res == PASSED)
  {
    for(i = 0; i<RING_BUFFER_MAX_LENGTH/2; i++)
    {
      if(RBPop(&value) != RB_NO_ERROR)
      {
	res = FAILED;
	break;
      }
    }
  }

  if(res == PASSED)
  {
    if(RBPeek(0,&value) != RB_NO_ERROR)
    {
      res = FAILED;
    }
    if(value != RING_BUFFER_MAX_LENGTH/2)
    {
      res = FAILED;
    }
  }
  return res;
}

/************************************************************************/
static testResult_t testPushLimits()
{
  testResult_t res = PASSED;
  uint32_t i;

  for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
  {
    if(RBPush(i) != RB_NO_ERROR)
    {
      res = FAILED;
      break;
    }
  }

  if(res == PASSED)
  {
    if(RBPush(0) != RB_BUFF_FULL)
    {
      res = FAILED;
    }
  }
  return res;
}

/************************************************************************/
static testResult_t testPopLimits()
{
  testResult_t res = PASSED;
  uint32_t i;
  uint32_t value;

  for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
  {
    if(RBPush(i) != RB_NO_ERROR)
    {
      res = FAILED;
      break;
    }
  }

  if(res == PASSED)
  {
    for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
    {
      if(RBPop(&value) != RB_NO_ERROR)
      {
	res = FAILED;
	break;
      }
    }
  }

  if(res == PASSED)
  {
    if(RBPop(&value) != RB_BUFF_EMPTY)
    {
      res = FAILED;
    }
  }
  return res;
}

/************************************************************************/
static testResult_t testCurrentSize()
{
  testResult_t res = PASSED;
  uint32_t i;
  uint32_t value;

  for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
  {
    if(RBPush(i) != RB_NO_ERROR)
    {
      res = FAILED;
      break;
    }
  }

  if(res == PASSED)
  {
    if(RBCurrentSizeGet() != RING_BUFFER_MAX_LENGTH)
    {
      res = FAILED;
    }
  }

  if(res == PASSED)
  {
    for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
    {
      if(RBPop(&value) != RB_NO_ERROR)
      {
	res = FAILED;
	break;
      }
    }
  }

  if(res == PASSED)
  {
    if(RBCurrentSizeGet() != 0)
    {
      res = FAILED;
    }
  }
  return res;
}

/************************************************************************/
static testResult_t testEmptyFullFlags()
{
  testResult_t res = PASSED;
  uint32_t i;
  uint32_t value;

  if((RBEmpty() == FALSE) || (RBFull() == TRUE))
  {
    res = FAILED;
  }

  if(res == PASSED)
  {
    for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
    {
      if(RBPush(i) != RB_NO_ERROR)
      {
	res = FAILED;
	break;
      }
    }
  }
  if(res == PASSED)
  {
    if((RBEmpty() == TRUE) || (RBFull() == FALSE))
    {
      res = FAILED;
    }
  }

  if(res == PASSED)
  {
    for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
    {
      if(RBPop(&value) != RB_NO_ERROR)
      {
	res = FAILED;
	break;
      }
    }
  }

  if(res == PASSED)
  {
    if((RBEmpty() == FALSE) || (RBFull() == TRUE))
    {
      res = FAILED;
    }
  }

  return res;
}

/************************************************************************/
static testResult_t testOverflow()
{
  testResult_t res = PASSED;
  uint32_t i;
  uint32_t j;
  uint32_t value;

  for(j = 0; j<2; j++)
  {
    if(res == PASSED)
    {
      for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
      {
	if(RBPush(i) != RB_NO_ERROR)
	{
	  res = FAILED;
	  break;
	}
      }
    }

    if(res == PASSED)
    {
      for(i = 0; i<RING_BUFFER_MAX_LENGTH; i++)
      {
	if(RBPop(&value) != RB_NO_ERROR)
	{
	  res = FAILED;
	  break;
	}
	if(value != i)
	{
	  res = FAILED;
	  break;
	}
      }
    }
  }

  return res;
}

/************************************************************************/
int main(int argc,  char **argv)
{
  int index = 0;
  testResult_t ret;

  // Loop through all tests
  while((arrTests[index] != NULL) )
  {
    printf("\nRunning test %d...", index);
    RBClear();
    ret = arrTests[index]();

    if(ret == PASSED)
    {
      printf(" PASSED");
    }
    else
    {
      printf(" FAILED");
    }
    index++;
  }
  return 0;
}
