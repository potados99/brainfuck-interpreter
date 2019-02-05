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

int interpret_brainfuck(const char * source, int len) {
    printf("\nSTART\n%s\nEND(%d)\n", source, len);
    return 0;
}

int main_file(int argc, const char * argv[]) {
    int result = io_for_file(argv[1], interpret_brainfuck);
    
    if (result < 0) {
        // error.
        error(RET_ACTION_FAIL, "io_for_file failed.");
    }
    else if (result > 0) {
        // signal.
        return RET_SIG_EXIT;
    }
    else {
        // ok.
        return RET_OK;
    }
    
    return 0;
}

int main_terminal(int argc, const char * argv[]) {
    printf("Brainfuck interpreter v0.0.1\n");
    printf("Copyright 2019 Potados.\n");
    
    printf("\n>> ");
    
    int result = 0;
    
    for(;;) {
        result = io_for_input(stdin, '\n', 'q', interpret_brainfuck);
         
        if (result < 0) {
            // error.
            error(RET_ACTION_FAIL, "io_for_input failed.");
        }
        else if (result > 0) {
            // signal.
            return RET_SIG_EXIT;
        }
        else {
            // ok.
            printf("\n>> ");
            continue;
        }
    }
}

int main_redirection(int argc, const char *argv[]) {
    int result = io_for_input(stdin, EOF, 0, interpret_brainfuck);
    
    if (result < 0) {
        // error.
        error(RET_ACTION_FAIL, "io_for_input failed.");
    }
    else if (result > 0) {
        // signal.
        return RET_SIG_EXIT;
    }
    else {
        // ok.
        return RET_OK;
    }
}

int main(int argc, const char * argv[]) {
    if (argc > 1)
        return main_file(argc, argv);
    else if (isatty(fileno(stdin)))
        return main_terminal(argc, argv);
    else
        return main_redirection(argc, argv);
}

