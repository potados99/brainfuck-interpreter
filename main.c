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

#include "bf.h"

const char * hello_world = "+[-[<<[+[--->]-[<<<]]]>>>-]>-.---.>..>.<<<<-.<+.>>>>>.>.<<.<-.";

int main(int argc, const char * argv[]) {
    if (argc > 1) {
        bf_run(argv[1], (int)strlen(argv[1]), 0);
    }

    char buf[512] = {0, };


    while() {
    rewind(stdin);
    if (fgets(buffer, _BUFFER_SIZE - 1, stdin) == NULL) {
        return NULL;
    }
    rewind(stdin);

    if (strlen(buffer) == 1) {
        return NULL;
    }
    }

    bf_run(hello_world, (int)strlen(hello_world), 0);
    puts("");



    return 0;
}
