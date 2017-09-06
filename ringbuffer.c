/*
 * ringbuffer.c
 *
 *  Created on: Sep 4, 2017
 *      Author: pablo martinez
 *
 * Description: Simple ring buffer implemented as FIFO register.
 * Implemented for tests purposes.
 */

#include <stdint.h>

#include "ringbuffer.h"

/*
 ************************************************************************
 ** Private variables
 ************************************************************************
 */

// Ring buffer
static uint32_t buffer[RING_BUFFER_MAX_LENGTH] = {0};
// Read and write indexes
static uint32_t readIndex = 0;
static uint32_t writeIndex = 0;
static uint32_t numElements = 0;

// TODO: Check RING_BUFFER_MAX_LENGTH limits

/*
 ************************************************************************
 ** Public functions
 ************************************************************************
 */

/************************************************************************/
uint32_t RBCurrentSizeGet()
{
  return numElements;
}

/************************************************************************/
uint32_t RBMaximumSizeGet()
{
  return RING_BUFFER_MAX_LENGTH;
}

/************************************************************************/
RB_bool_t RBEmpty()
{
  return (numElements == 0) ? TRUE : FALSE;
}

/************************************************************************/
RB_bool_t RBFull()
{
  return (numElements == RING_BUFFER_MAX_LENGTH) ? TRUE : FALSE;
}

/************************************************************************/
RB_result_t RBPush(uint32_t value)
{
  RB_result_t res = RB_NO_ERROR;

  if (RBFull())
  {
    res = RB_BUFF_FULL;
  }
  else
  {
    buffer[writeIndex] = value;
    numElements++;

    if(writeIndex >= RING_BUFFER_MAX_LENGTH -1)
    {
      writeIndex = 0;
    }
    else
    {
      writeIndex++;
    }
  }

  return res;
}

/************************************************************************/
RB_result_t RBPop(uint32_t *value)
{
  RB_result_t res = RB_NO_ERROR;

  if (RBEmpty())
  {
    res = RB_BUFF_EMPTY;
  }
  else
  {
    *value = buffer[readIndex];
    numElements--;

    readIndex = (readIndex >= RING_BUFFER_MAX_LENGTH -1) ? 0 : (readIndex + 1);
  }

  return res;
}

/************************************************************************/
RB_result_t RBPeek(uint32_t index, uint32_t *value)
{
  RB_result_t res = RB_NO_ERROR;
  uint32_t real_index;

  if (RBEmpty())
  {
    res = RB_BUFF_EMPTY;
  }

  if(res == RB_NO_ERROR)
  {
    real_index = readIndex + index;
    real_index = (real_index >= RING_BUFFER_MAX_LENGTH) ? (real_index - RING_BUFFER_MAX_LENGTH) : real_index;

    if(writeIndex > readIndex)
    {
      if ((real_index >= writeIndex) || (real_index < readIndex))
      {
	res = RB_INVALID_PARAM;
      }
    }
    else if(writeIndex < readIndex)
    {
      if ((real_index >= writeIndex) && (real_index < readIndex))
      {
	res = RB_INVALID_PARAM;
      }
    }
    //else buffer full, all positions contain valid values

    if(res == RB_NO_ERROR)
    {
      *value = buffer[real_index];
    }
  }

  return res;
}

/************************************************************************/
void RBClear(void)
{
  readIndex = 0;
  writeIndex = 0;
  numElements = 0;
}
