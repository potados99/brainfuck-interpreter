//
//  main.c
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bf.h"
#include "io.h"

const char * hello_world = "+[-[<<[+[--->]-[<<<]]]>>>-]>-.---.>..>.<<<<-.<+.>>>>>.>.<<.<-.";

int interpret_brainfuck(const char *source, int len) {
    struct bf_context context = {
        .src = source,
        .src_len = len,
        .mem = {0, },
        .data_ptr = context.mem,
        .inst_ptr = context.src
    };
    
    return bf_run(&context);
}

int main_file(int argc, const char * argv[]) {
    return io_with_file(argv[1], interpret_brainfuck);
}

int main_terminal(int argc, const char * argv[]) {
    printf("Brainfuck interpreter v0.0.1\n");
    printf("Copyright 2019 Potados.\n");
    
    printf("\n>> ");
    
    int result = 0;
    
    for(;;) {
        result = io_with_input(stdin, 128, '\n', 'q', 1, interpret_brainfuck);
        
        if (result == 0) {
            printf("\n>> ");
            continue;
        } else {
            puts("");
            return 0;
        }
    }
}

int main_redirection(int argc, const char *argv[]) {
    return io_with_input(stdin, 1024, EOF, 0, 0, interpret_brainfuck);
}

int main(int argc, const char * argv[]) {
    if (argc > 1)
        return main_file(argc, argv);
    else if (isatty(fileno(stdin)))
        return main_terminal(argc, argv);
    else
        return main_redirection(argc, argv);
}



