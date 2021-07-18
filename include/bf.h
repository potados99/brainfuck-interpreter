//
//  bf.h
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#ifndef bf_h
#define bf_h

#define BF_MEM_SIZE 256

struct bf_context {
    const char *src;
    int src_len;
    
    char mem[BF_MEM_SIZE];
    char *data_ptr;        /* data pointer */
    const char *inst_ptr;        /* instruction pointer */
};

int bf_run(struct bf_context *context);

#endif /* bf_h */
