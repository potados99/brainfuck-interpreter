//
//  bf.c
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#include "bf.h"

RET bf_run(const char * source, int length, int verbose) {
    static unsigned char mem[256] = {0, };
    static unsigned char * ar = mem;        /* address register */
    static long temp_ar = 0;

    char * ip = (char *)source;             /* instruction pointer */
    long temp_ip = 0;

    unsigned long depth = 0;
    
    while (ip - source < length) {
        
        temp_ip = ip - source;
        temp_ar = ar - mem;
        
        switch (*ip) {
            case '>':
                if (temp_ar == sizeof(mem) - 1)
                    error(RET_MEM_VIOLATION, "access denied at %ld.", temp_ar + 1);
                
                ++ar;
                
                if (verbose)
                    instruction("<+%ld>:\tADD\tar, 1\t\t(%ld)\n", temp_ip, temp_ar + 1);
                break;
                
            case '<':
                if (temp_ar == 0)
                    error(RET_MEM_VIOLATION, "access denied at %ld.", temp_ar - 1);
                
                --ar;
                
                if (verbose)
                    instruction("<+%ld>:\tADD\tar, -1\t\t(%ld)\n", temp_ip, temp_ar - 1);
                break;
                
            case '+':
                ++(*ar);
                if (verbose)
                    instruction("<+%ld>:\tADD\t*ar, 1\t\t(%ld, %d)\n", temp_ip, temp_ar, *ar);
                break;
                
            case '-':
                --(*ar);
                if (verbose)
                    instruction("<+%ld>:\tADD\t*ar, -1\t\t(%ld, %d)\n", temp_ip, temp_ar, *ar);
                break;
                
            case '.':
                if (verbose)
                    instruction("<+%ld>:\tPRT\t*(ar+%ld)\t\t(%d:%c)\n",
                                temp_ip, temp_ar, *ar, *ar);
                else
                    putc(*ar, stdout);

                break;
                
            case ',':
                // not yet.
                break;
                
            case '[':                
                if (*ar) {
                    if (verbose)
                        instruction("<+%ld>:\tNOP\n", temp_ip);
                    break;
                }
                
                depth = 1;
                
                while (depth) {
                    if (ip - source == length)
                        error(RET_ACTION_FAIL, "expected ].");
                    
                    ++ip;
                    
                    if (*ip == ']') --depth;
                    else if (*ip == '[') ++depth;
                }
                if (verbose)
                    instruction("<+%ld>:\tJMP\t\t\t\t<+%ld>\n", temp_ip, ip - source);

                continue;
                
            case ']':
                if (! *ar) {
                    if (verbose)
                        instruction("<+%ld>:\tNOP\n", temp_ip);
                    break;
                }

                depth = 1;
                
                while (depth) {
                    if (ip - source == 0)
                        error(RET_ACTION_FAIL, "expected [.");
                    
                    --ip;

                    if (*ip == '[') --depth;
                    else if (*ip == ']') ++depth;
                }
                if (verbose)
                    instruction("<+%ld>:\tJMP\t\t\t\t<+%ld>\n", temp_ip, ip - source);

                continue;

            default:
                break;
                
        } /* end of switch */
        
        ++ip;
    }
    
    return RET_OK;
}
