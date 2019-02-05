//
//  io.h
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#ifndef _shell_h
#define _shell_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

typedef int (*str_callback)(const char *, int);

/**
 * Handle user input from stream and launch callback.
 * Optimized for terminal input, line by line. (use fgets.)
 *
 * @param stream        Input stream.
 * @param delim         Read until this character. (not included.)
 * @param exit          Exit when this character is came.
 * @param callback      Callback to launch when input completed.
 *
 * @return              Zero on normal, negative on error, positive on exit.
 */
RET io_for_input(FILE * stream, char delim, char exit, str_callback callback);

/**
 * Open and read file, and launch callback.
 *
 * @param filename      Input filename.
 * @param callback      Callback to launch when input completed.
 *
 * @return              Zero on normal, negative on error.
 */
RET io_for_file(const char * filename, str_callback callback);


#endif /* _shell_h */
