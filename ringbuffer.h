/*
 * ringbuffer.h
 *
 *  Created on: Sep 4, 2017
 *      Author: ubuntu
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

/*
 ************************************************************************
 ** Public type definitions
 ************************************************************************
 */

typedef enum
{
  RB_NO_ERROR      = 0,
  RB_BUFF_FULL     = 1,
  RB_BUFF_EMPTY    = 2,
  RB_INVALID_PARAM = 3,
  RB_LAST_ERR_INDEX = 4,
}RB_result_t;

typedef enum
{
  FALSE = 0,
  TRUE = 1,
}RB_bool_t;

/*
 ************************************************************************
 ** Public function declarations
 ************************************************************************
 */

/**
 * @brief Inserts a new value in the buffer
 * @param[in] value value to being inserted
 * @return @ref RB_result_t
**/
RB_result_t RBPush(uint32_t value);

/**
 * @brief Extracts the next value to be read from the buffer. Once the value is
 * extracted it cannot be accessed again
 * @param[out] value Pointer to the variable where the next value will be copied
 * @return @ref RB_result_t
**/
RB_result_t RBPop(uint32_t *value);

/**
 * @brief Reads a value from a specified position.
 * @param[in] index Index of the position inside the buffer to be read. This index
 * is always relative to the current read position.
 * @param[out] value Pointer to the variable where the value will be copied
 * @return @ref RB_result_t
**/
RB_result_t RBPeek(uint32_t index, uint32_t *value);

/**
 * @brief Returns the number of values stored in the buffer
 * @return Number of values stored
**/
uint32_t RBCurrentSizeGet();

/**
 * @brief Returns the maximum number of values that can be stored in the buffer
 * @return Maximum size of the buffer
**/
uint32_t RBMaximumSizeGet();

/**
 * @brief Checks if the buffer is empty
 * @return TRUE if the buffer is empty
**/
RB_bool_t RBEmpty();

/**
 * @brief Checks if the buffer is full
 * @return TRUE if the buffer is full
**/
RB_bool_t RBFull();

/**
 * @brief Discard all stored values and reset all counters
**/
void RBClear(void);

#endif /* RINGBUFFER_H_ */
