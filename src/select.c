/*
 * Houndsniff - version 1.9
 *
 * by Michael Constantine
 * Dimopoulos et al
 * https://mcdim.xyz
 * <mk@mcdim.xyz>
 * GNU GPLv3
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "select.h"

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

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
    double likelihood;
} hashes[] = {
	{"CRC16",                   4,   'a', 100},

	{"CRC32b",                  8,   'a', 56.84},
	{"CRC32",                   8,   'a', 22.96},
	{"ADLER32",                 8,   'a', 21.43},

	{"MD5 (half)",              16,  'a', 79.15},
	{"MySQL 3.2.3",             16,  'a', 20.85},

	{"MD5",                     32,  'a', 44.1},
	{"LanManager Hash",         32,  'a', 25.67},
	{"Windows NT-Hash",         32,  'a', 5.93},
	{"RIPEMD128",               32,  'a', 4.81},
	{"MD4",                     32,  'a', 3.16},
	{"MD2",                     32,  'a', 2.56},
	{"Tiger128,4",              32,  'a', 2.13},
	{"Tiger128,3",              32,  'a', 2.13},
	{"HAVAL128,3",              32,  'a', 2.12},
	{"MD4 HMAC",                32,  'a', 1.90},
	{"HAVAL128,4",              32,  'a', 1.89},
	{"HAVAL128,5",              32,  'a', 1.88},
	{"DomainCachedCredentials", 32,  'a', 1.34},
	{"MD5 HMAC",                32,  'a', 0.33},

	{"SHA1",                    40,  'a', 45.86},
	{"HAVAL160,4",              40,  'a', 13.83},
	{"Tiger160,3",              40,  'a',  8.99},
	{"Tiger160,4",              40,  'a',  8.81},
	{"RIPEMD160 ",              40,  'a',  8.18},
	{"HAVAL160,3",              40,  'a',  8.08},
	{"HAVAL160,5",              40,  'a',  6.21},

	{"Tiger192,4",              48,  'a', 31.14},
	{"Tiger192,3",              48,  'a', 19.84},
	{"HAVAL192,5",              48,  'a', 18.29},
	{"HAVAL192,4",              48,  'a', 17.67},
	{"HAVAL192,3",              48,  'a', 13.05},

	{"SHA224",                  56,  'a', 27.79},
	{"HAVAL224,4",              56,  'a', 27.18},
	{"HAVAL224,3",              56,  'a', 22.81},
	{"HAVAL224,5",              56,  'a', 22.20},

	{"SHA256",                  64,  'a', 66.07},
	{"GOST Hash",               64,  'a', 8.32},
	{"Snefru-128",              64,  'a', 7.52},
	{"RIPEMD256",               64,  'a', 6.48},
	{"HAVAL256,5",              64,  'a', 5.81},
	{"HAVAL256,3",              64,  'a', 5.77},

	{"RIPEMD320",               80,  'a', 100},

	{"SHA384",                  96,  'a', 100},

	{"Whirpool",                128, 'a', 80.2},
	{"SHA512",                  128, 'a', 19.8},

	{"FreeBSD nthash",          36,  'b', 100},

	{"CRYPT16",                 24,  'c', 100},

	{"MSSQL 2005",              54,  'd', 70.16},
	{"MSSQL 2000",              94,  'd', 29.84},

	{"DES Crypt",               13,  'e', 100},
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
		printf("[" RED "%d" RESET "] %s - " RED "%.2f%" RESET "\n",
		       i + 1, hashes[matches[i]].name,
		       hashes[matches[i]].likelihood);
	}
}

/* comparison function for qsort() */
int
matchcmp(const void *p0, const void *p1)
{
	int m0 = *(int *)p0;
	int m1 = *(int *)p1;
	return hashes[m1].likelihood - hashes[m0].likelihood;
}

void
list(void)
{
	int i;
	printf("\nHoundsniff supports:\n\n");
	for (i = 0; i < NHASHES; i++) {
		puts(hashes[i].name);
	}

	/* hashes from main.c:definite(); */
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
