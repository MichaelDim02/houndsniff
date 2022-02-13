/*
 *             houndsniff
 *    hash identification program.
 *
 *  by Michael Constantine Dimopoulos
 *  https://mcdim.xyz  <mk@mcdim.xyz>
 *
 *  select.h
 *
 */

#ifndef SELECT_H
#define SELECT_H

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
void list(void);
void sel(int length, const char *charset, int clean_out);
char *replace(char *str);

#endif
