//
//  io.c
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#include "io.h"

RET io_for_input(FILE * stream, char delim, char exit, str_callback callback) {
    verify(stream, RET_WRONG_PARAM, "stream is null.");
    verify(callback, RET_WRONG_PARAM, "callback is null.");
    
    char total_buf[1024]    = {0, };
    int total_len           = 0;
    
    char current_char       = 0;
    char * p                = total_buf;
    
    int got_eof             = 0;
    
    while ((current_char = fgetc(stream))) {
        if (current_char == EOF) {
            got_eof = 1;
            break;
        }
        else if (current_char == delim) {
            break;
        }
        else if ((exit != '\0') && (current_char == exit)) {
            return RET_SIG_EXIT;
        }
        else {
            *p++ = current_char;
        }
    }
    
    total_buf[(total_len = (int)(p - total_buf))] = '\0'; /* just for safety. */
    
    int callback_result = callback(total_buf, total_len);

    if (got_eof) return RET_SIG_EOF;
    else
        if (callback_result < 0) error(RET_ACTION_FAIL, "callback failed.");
        else return callback_result;
}

RET io_for_file(const char * filename, str_callback callback) {
    verify(filename, RET_WRONG_PARAM, "filename is null.");
    verify(callback, RET_WRONG_PARAM, "callback is null.");

    FILE *file;
    file = fopen(filename, "rt");
    verify(file, RET_ACTION_FAIL, "fopen failed.");
    
    int result = io_for_input(file, EOF, 0, callback);
    
    fclose(file);
    
    if (result < 0) error(RET_ACTION_FAIL, "io_for_input failed.");
    else return result;
}

