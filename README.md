OVERWIEW
==========================================================================
This folder contains the ring buffer lib, executable and test source codes.

The ring buffer library implements a simple FIFO ring buffer.

These are the files located on it:
 +ringbuffer.c/.h - Source code of the ring buffer library
 +main.c          - Source code of a command line program
 +tests.c         - Source code to the test the ring buffer library
 +Makefile        - Needed to compile the code

COMPILE
=============================================================================
Just type:
  $make all

The compilation will generate the following final files:
 -bin/ringbuffer.a - static library to be linked
 -bin/ringbuff     - command line executable to use the ring buffer
 -bin/ringtest     - executable file that runs unit tests of the ring buffer library
 
EXECUTING ringtests
=============================================================================
Run "./ringtests" from the bin directory. The program will start automatically performing
all defined tests. These are very simple tests which cover the basic functionality of
the ringbuffer. The tests are:
-testPushPop: Test the correct insertion and extraction of values
-testPushLimits: Test insertion limitation
-testPopLimits: Test extraction limitation
-testCurrentSize: Check current size validity
-testEmptyFullFlags: Check full and empty flags validity
-testOverflow: Test insertion and extraction with buffer overflow
-testPeek: Test peek functionality

We could also test variables boundaries.

EXECUTING ringbuff
=============================================================================
Run "./ringbuff" from the bin directory. You can insert values and extract them by
using the following commands:
 u [x] - push a value x
 o     - pop the next value
 e [x] - peek a value at position x
 q     - quit
 h     - show this help

