//
//  bf.h
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#ifndef bf_h
#define bf_h

#include <stdio.h>
#include <string.h>

#define instruction(_fmt, ...) printf(_fmt, ##__VA_ARGS__)

void bf_run(const char * file, int size, int verbose);

#endif /* bf_h */
