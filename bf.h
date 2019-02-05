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
#include <stdlib.h>
#include <string.h>

#define instruction(_fmt, ...) printf(_fmt, ##__VA_ARGS__)

void bf_run(const char * source, int length, int verbose);
void bf_run_file(const char * filename);

#endif /* bf_h */
