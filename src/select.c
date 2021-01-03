#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "select.h"

/* houndsniff
 *
 * this is basically where the program
 * indexes through the database and picks
 * out the rows with desired values
 */

void list(void);
int matchcmp(const void *, const void *);
void sel(int length, const char *charset);

/* Notes:
   1. The popularity integer determines how the results are sorted
   2. It is determined by the number web search results compared
      to other hashing algorithms with the same characteristics.

   charsets:
   a = String is made only of numbers & lowercase letters
   b = string includes a '$'
   c = string includes a '/'
   d = string begins with '$0$'
   e = string includes uppercase letters */

#define NHASHES (int)(sizeof(hashes) / sizeof(hashes[0])) /* array size */
static const struct {
    char *name;
    short length;
    char charset;
    char popularity;
} hashes[] = {
	{"MD5",                     32,  'a', 100},
	{"SHA1",                    40,  'a', 85},
	{"SHA256",                  64,  'a', 87},
	{"SHA224",                  56,  'a', 79},
	{"SHA384",                  96,  'a', 58},
	{"SHA512",                  128, 'a', 70},
	{"RIPEMD160 ",              40,  'a', 38},
	{"MD4",                     32,  'a', 40},
	{"MD2",                     32,  'a', 35},
	{"CRC32b",                  8,   'a', 10},
	{"ADLER32",                 8,   'a', 8},
	{"CRYPT16",                 24,  'c', 10},
	{"LanManager Hash",         32,  'a', 25},
	{"Windows NT-Hash",         32,  'a', 20},
	{"MSSQL 2000",              94,  'd', 20},
	{"MSSQL 2005",              54,  'd', 20},
	{"MySQL 3.2.3",             16,  'a', 20},
	{"DES Crypt",               13,  'e', 20},
	{"FreeBSD nthash",          36,  'b', 20},
	{"CRC32",                   8,   'a', 19},
	{"HAVAL128,5",              32,  'a', 28},
	{"HAVAL128,4",              32,  'a', 26},
	{"HAVAL128,3",              32,  'a', 27},
	{"HAVAL256,5",              64,  'a', 20},
	{"HAVAL224,5",              56,  'a', 21},
	{"HAVAL192,5",              48,  'a', 27},
	{"HAVAL160,5",              40,  'a', 22},
	{"HAVAL224,4",              56,  'a', 25},
	{"HAVAL192,4",              48,  'a', 26},
	{"HAVAL160,4",              40,  'a', 21},
	{"HAVAL256,3",              64,  'a', 18},
	{"HAVAL224,3",              56,  'a', 20},
	{"HAVAL192,3",              48,  'a', 25},
	{"HAVAL160,3",              40,  'a', 22},
	{"Whirpool",                128, 'a', 50},
	{"GOST Hash",               64,  'a', 10},
	{"Snefru-128",              64,  'a', 5},
	{"RIPEMD128",               32,  'a', 9},
	{"RIPEMD256",               64,  'a', 9},
	{"RIPEMD320",               80,  'a', 8},
	{"Tiger128,3",              32,  'a', 5},
	{"Tiger160,3",              40,  'a', 5},
	{"Tiger192,3",              48,  'a', 6},
	{"Tiger128,4",              32,  'a', 7},
	{"Tiger160,4",              40,  'a', 7},
	{"Tiger192,4",              48,  'a', 5},
	{"CRC16",                   4,   'a', 50},
	{"DomainCachedCredentials", 32,  'a', 10},
	{"MD5 (half)",              16,  'a', 10},
	{"MD4 HMAC",                32,  'a', 7},
	{"MD5 HMAC",                32,  'a', 12},
};

void
sel(int length, const char *charset)
{
	int i;
	int nmatch = 0;
	int matches[NHASHES];

	for (i = 0; i < NHASHES; i++) {
		if (hashes[i].length == length && hashes[i].charset == *charset) {
			matches[nmatch++] = i;
		}
	}

	qsort(matches, nmatch, sizeof(*matches), matchcmp);

	printf("Possible results:\n\n");
	for (i = 0; i < nmatch; i++) {
		printf("[%d] %s\n", i + 1, hashes[matches[i]].name);
	}
}

/* comparison function for qsort() */
int
matchcmp(const void *p0, const void *p1)
{
	int m0 = *(int *)p0;
	int m1 = *(int *)p1;
	return hashes[m1].popularity - hashes[m0].popularity;
}

void
list(void)
{
	int i;
	printf("\nHoundsniff supports:\n\n");
	for (i = 0; i < NHASHES; i++) {
		puts(hashes[i].name);
	}

	/* hashes from definite(); */
        printf( "Wordpress hash \n"
	"MD5 crypt(3)   \n"
	"SHA256 crypt(3)\n"
	"SHA512 crypt(3)\n"
	"Base64         \n"
	"ARP1           \n"
	"phpBB          \n"
	"SHA1 Django    \n"
	"MD5 Joomla (pass:salt)\n");
}
