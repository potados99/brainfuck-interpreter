//
//  bf.c
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#include "bf.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>

static inline void bf_execute_current_instruction(struct bf_context *context) {
#ifdef VERBOSE
    long inst_ptr_offset = context->inst_ptr - context->src;
#endif
    long data_ptr_offset = context->data_ptr - context->mem;
    
    int depth;
    long new_offset;
    
    switch (*(context->inst_ptr)) {
        case '>': {
            assert(data_ptr_offset < BF_MEM_SIZE);
            
            ++(context->data_ptr);
            
            debug_print("<+%ld>:\tADD\tar, 1\t\t(%ld)\n", inst_ptr_offset, data_ptr_offset + 1);
            
            break;
        }
            
        case '<': {
            assert(data_ptr_offset > 0);
            
            --(context->data_ptr);
            
            debug_print("<+%ld>:\tADD\tar, -1\t\t(%ld)\n", inst_ptr_offset, data_ptr_offset - 1);
            
            break;
        }
            
        case '+': {
            ++(*context->data_ptr);
            
            debug_print("<+%ld>:\tADD\t*ar, 1\t\t(%ld, %d)\n", inst_ptr_offset, data_ptr_offset, *context->data_ptr);
            
            break;
        }
            
        case '-': {
            --(*context->data_ptr);
            
            debug_print("<+%ld>:\tADD\t*ar, -1\t\t(%ld, %d)\n", inst_ptr_offset, data_ptr_offset, *context->data_ptr);
            
            break;
        }
            
        case '.': {
            putc(*context->data_ptr, stdout);
            
            debug_print("<+%ld>:\tPRT\t*(ar+%ld)\t\t(%d:%c)\n", inst_ptr_offset, data_ptr_offset, *context->data_ptr, *context->data_ptr);
            
            break;
        }
            
        case ',': {
            break;
        }
            
        case '[': {
            if (*context->data_ptr) {
                debug_print("<+%ld>:\tNOP\n", inst_ptr_offset);
                break;
            }
            
            depth = 1;
            
            while (depth) {
                new_offset = context->inst_ptr - context->src;
                
                assert(new_offset < context->src_len);
                
                ++(context->inst_ptr);
                
                if (*context->inst_ptr == ']') {
                    --depth;
                } else if (*context->inst_ptr == '[') {
                    ++depth;
                }
            }
            
            debug_print("<+%ld>:\tJMP\t\t\t\t<+%ld>\n", inst_ptr_offset, new_offset);
        }
            
        case ']': {
            if (!(*context->data_ptr)) {
                debug_print("<+%ld>:\tNOP\n", inst_ptr_offset);
                break;
            }
            
            depth = 1;
            
            while (depth) {
                new_offset = context->inst_ptr - context->src;
                
                assert(new_offset > 0);
                
                --(context->inst_ptr);
                
                if (*context->inst_ptr == '[') {
                    --depth;
                } else if (*context->inst_ptr == ']') {
                    ++depth;
                }
            }
            
            debug_print("<+%ld>:\tJMP\t\t\t\t<+%ld>\n", inst_ptr_offset, new_offset);
        }
    }
}

int bf_run(struct bf_context *context) {
    while (context->inst_ptr - context->src < context->src_len) {
        bf_execute_current_instruction(context);
        
        ++(context->inst_ptr);
    }
    
    return 0;
}


