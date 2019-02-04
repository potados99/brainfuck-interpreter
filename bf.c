//
//  bf.c
//  brainfuck-interpreter
//
//  Created by POTADOS on 05/02/2019.
//  Copyright © 2019 potados. All rights reserved.
//

#include "bf.h"

void bf_run(const char * file, int size, int verbose) {
    unsigned char mem[256] = {0, };
    
    char * ip = (char *)file;   /* instruction pointer */
    unsigned char * ar = mem;   /* address register */

    unsigned long depth = 0;
    long temp_ip = 0;
    long temp_ar = 0;
    
    while (ip - file < size) {
        
        temp_ip = ip - file;
        temp_ar = ar - mem;
        
        switch (*ip) {
            case '>':
                ++ar;
                if (verbose)
                    instruction("<+%ld>:\tADD\tar, 1\t\t(%ld)\n", temp_ip, temp_ar + 1);
                break;
                
            case '<':
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
                    printf("%c", *ar);

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
                    ++ip;
                    if (*ip == ']') --depth;
                    else if (*ip == '[') ++depth;
                }
                if (verbose)
                    instruction("<+%ld>:\tJMP\t\t\t\t<+%ld>\n", temp_ip, ip - file);

                continue;
                
            case ']':
                if (! *ar) {
                    if (verbose)
                        instruction("<+%ld>:\tNOP\n", temp_ip);
                    break;
                }
                

                depth = 1;
                while (depth) {
                    --ip;
                    if (*ip == '[') --depth;
                    else if (*ip == ']') ++depth;
                }
                if (verbose)
                    instruction("<+%ld>:\tJMP\t\t\t\t<+%ld>\n", temp_ip, ip - file);

                continue;

            default:
                break;
                
        } /* end of switch */
        
        ++ip;
    }
}
