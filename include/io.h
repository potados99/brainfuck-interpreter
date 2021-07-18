//
//  io.h
//  brainfuck-interpreter
//
//  Created by Potados on 2021/07/18.
//  Copyright © 2021 potados. All rights reserved.
//

#ifndef io_h
#define io_h

#include <stdio.h>

#ifdef VERBOSE
#define debug_print(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__);
#else
#define debug_print(fmt, ...) NULL;
#endif

/**
 * String callback.
 * A string and its length is passed.
 */
typedef int (*str_callback)(const char *, int);

/**
 * Handle user input from stream and launch callback.
 * Default EOF handling is:
 *  stop reading & run callback & return RET_SIG_EOF.
 *
 * @param from          Input stream.
 * @param about         Number of bytes to read.
 * @param until         Read until this character. (not included.)
 * @param stop_on       Immediately return stop_with when this character is came.
 * @param stop_with     Signal to return when stop_on came.
 * @param and_then      Callback to launch when input completed.
 *
 * @return              Result of the callback. If reading fails, program will stop.
 */
int io_with_input(FILE          *from,
                 int            about,
                 char           until,
                 char           stop_on,
                 int            stop_with,
                 str_callback   and_then);

/**
 * Open and read file, and launch callback.
 *
 * @param filename      Input filename.
 * @param callback      Callback to launch when input completed.
 *
 * @return              Result of the callback. If reading fails, program will stop.
 */
int io_with_file(const char * filename, str_callback callback);

#endif /* io_h */
