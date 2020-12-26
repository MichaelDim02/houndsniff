/*
 * HOUNDSNIFF by Michael C. Dim. (Kerberos)
 *        hash identification program
 *
 *        select.h
 */

#ifndef SELECT_H
#define SELECT_H

int callback(void *, int, char **, char **);
int sel(int length, const char *charset);

#endif
