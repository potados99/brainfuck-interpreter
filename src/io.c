//
//  io.c
//  brainfuck-interpreter
//
//  Created by Potados on 2021/07/18.
//  Copyright © 2021 potados. All rights reserved.
//

#include "io.h"

#include <err.h>
#include <assert.h>
#include <stdbool.h>

#define BUF_SIZE 1024

int io_with_input(FILE          *from,
                 int            about,
                 char           until,
                 char           stop_on,
                 int            stop_with,
                 str_callback   and_then) {

    assert(from);
    assert(and_then);
    assert(about <= BUF_SIZE);
    
    char file_buf[BUF_SIZE] = {0, };
    char *p = file_buf;

    int current_char = 0;
        
    while ((current_char = fgetc(from))) {
        bool reached_end = current_char == until;
        bool reached_eof = current_char == EOF;
        bool reached_limit = (int)(p - file_buf) >= about;
        bool reached_terminal = current_char == stop_on;
        
        if (reached_end || reached_eof || reached_limit) {
            break;
        }
        
        if (reached_terminal) {
            return stop_with;
        }
        
        *(p++) = current_char;
    }
    
    int total_len = (int)(p - file_buf);
    
    file_buf[total_len] = '\0'; /* just for safety. */
    
    int callback_result = and_then(file_buf, total_len);
    
    return callback_result;
}

int io_with_file(const char * filename, str_callback callback) {
    assert(filename);
    assert(callback);

    FILE *file = fopen(filename, "rt");
    assert(file);
        
    // read forever until EOF, no exit signal.
    int result = io_with_input(file, BUF_SIZE, EOF, 0, 0, callback);
    
    fclose(file);
    
    return result;
}
