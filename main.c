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

const char * hello_world = "+[-[<<[+[--->]-[<<<]]]>>>-]>-.---.>..>.<<<<-.<+.>>>>>.>.<<.<-.";

int main(int argc, const char * argv[]) {
    if (argc > 1) {
        // file argument
        bf_run_file(argv[1]);
        
        return 0;
    }
    
    int terminal = isatty(fileno(stdin));
    
    char buf[512] = {0, };
    int str_len = 0;
    
    // redirection or pipe
    if (! terminal) {
        char combined[1024] = {0, };
        
        while(fgets(buf, sizeof(buf) - 1, stdin)) {
            strcat(combined, buf);
        }
        
        str_len = (int)strlen(combined);
        combined[str_len - 1] = '\0'; /* last character. */

        bf_run(combined, str_len, 0);
        
        return 0;
    }

    printf("Brainfuck interpreter v0.0.1\n");
    printf("Copyright 2019 Potados.\n");
    
    // terminal
    while(1) {
        rewind(stdin);
        
        printf("\n>>> ");
        if (fgets(buf, sizeof(buf) - 1, stdin) == NULL) {
            printf("fgets error.\n");
            continue;
        }
        
        rewind(stdin);
        
        str_len = (int)strlen(buf);
        
        if (str_len == 1) {
            printf("parse error.\n");
            continue;;
        }
        
        buf[str_len - 1] = '\0'; /* last character. */

        if (strcmp(buf, "q") == 0 || strcmp(buf, "quit") == 0) {
            return 0;
        }
        
        bf_run(buf, str_len, 0);
    }
    
    return 0;
}

