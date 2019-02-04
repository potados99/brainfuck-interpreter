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
    bf_run(hello_world, (int)strlen(hello_world), 0);
    puts("");
    
    return 0;
}
