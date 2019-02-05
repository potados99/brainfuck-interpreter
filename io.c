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
    
    char line_buf[256]      = {0, };
    int line_len            = 0;
    
    char * lp = line_buf;
    int got_delim = 0;
    
    while (fgets(line_buf, sizeof(line_buf) - 1, stream)) {
        line_len = (int)strlen(line_buf); /* including '\n' at the end. */
        lp = line_buf;
        got_delim = 0;

        // line filter.
        if (line_len == 1)
            printf("empty line.\n");
        else if ((exit) && (line_len == 2) && (line_buf[0] == exit))
            return RET_SIG_EXIT; /* in case of ("\n%c\n", exit). */
        
        // substring and concat.
        while((*lp = ((got_delim = (*lp == delim)) ? '\0' : *lp))) { ++lp; }
        strcat(total_buf, line_buf);
        
        if (got_delim) break;
        
        memset(line_buf, 0, sizeof(line_buf));
    }
    
    total_len = (int)strlen(total_buf); /* already null-terminated. */
    
    int callback_result = callback(total_buf, total_len);
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

