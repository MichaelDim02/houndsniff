/*
 * Houndsniff - version 2.1
 *
 * by Michael Constantine Dimopoulos et al
 * https://mcdim.xyz <mk@mcdim.xyz> GNU GPLv3
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "select.h"

#define VERSION "2.1"

#define BUFFER_SIZE 1024

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
 
static int
hasUpper(char ch[])
{
	int len = strlen(ch);
	int i;
	
	for (i = 0; i < len; i++) {
		if (isupper(ch[i])) return 1;
	} 

	return 0;
}

void
banner()
{ 
	printf(	"          __			\n"
		"(\\,------'()'--o  Sniff..	\n"
		" \\_ )  _   /-''    Sniff...	\n"
		"  /_)_) /_)_)			\n\n");
	/*https://www.asciiart.eu/animals/dogs*/
	
	printf( "Houndsniff - Hash Identification Program - Version %s\n"
		"By Michael Constantine Dimopoulos et al <mk@mcdim.xyz>\n"
		"\n",VERSION);
}

static int
starts_with(const char *a, const char *b)
{
	if(strncmp(a, b, strlen(b)) == 0) return 1;
		return 0;
}

static void
dprint(char *name, int clean_out)
{
	if (!clean_out) {
		printf("[" RED "+" RESET "] Definite identification: "
	       RED "%s" RESET "\n", name);
	} else {
		printf("%s 100.00\n", replace(name));
	}
}


/* This is the first test;
 * here we identify the hash
 * based on *definite* characteristics
 */
void
definite(char string[], int length, int co)
{

	if (starts_with(string, "$P"))
		dprint("Wordpress hash", co);
	else if (starts_with(string, "$1$"))
		dprint("MD5 crypt(3)", co);
	else if (starts_with(string, "$5$"))
		dprint("SHA256 crypt(3)", co);
	else if (starts_with(string, "$6$"))
		dprint("SHA512 crypt(3)", co);
	else if (string[length-1]=='=') 
		dprint("Base64 or Base32", co);
	else if (starts_with(string, "$apr1$"))
		dprint("APR1", co);
	else if (starts_with(string, "$H$"))
		dprint("phpBB", co);
	else if (starts_with(string, "sha1$"))
		dprint("SHA1 Django", co);
	else if (length==65 && string[32]==':')
		dprint("MD5 Joomla (pass:salt)", co);
	else if (starts_with(string, "$2y$"))
		dprint("PHP password_hash", co);
}

/* this function determines charset*/
const char*
charset(char string[])
{
	if (strchr(string, '$') != NULL)
		return "b";	
	else if (strchr(string, '/') != NULL)
		return "c";
	else if (string[0]=='0' && string[1]=='x' && string[2]=='0')
		return "d";
	else if (hasUpper(string)==1)
		return "e";
	else
		return "a";
}

static void
help(char *exename)
{
	printf( "If your hash includes a dollar sign ($) or other\n"
		"special symbols, make sure you place it in between\n"
		"quotes.\n\n"

		"Contributors:\n"
		"Christopher Wellons, Martin K.\n"
		"tuu & fizzie on ##c@freenode\n\n"

		"  -i   use interactive shell\n"
		"  -s   use scripting mode\n"
		"  -l   list supported hashing algorithms\n"
		"  -h   display this panel and exit\n"
		"  -v   print version and exit\n"
		"\nUsage: Usage: %s [HASH] [-h|-v|-l] [-i] [-s]\n",
		exename);
}

void
driver(char *hash, int clean_out)
{
	int len = strlen(hash);
	const char* chars = charset(hash);

	if (!clean_out) {
		printf("Hash: " RED "%s" RESET "\n", hash);
		printf("Length: " RED "%d" RESET "\n",len);
		printf("Charset: " RED "%s" RESET "\n\n", chars);
	}

	sel(len, chars, clean_out);
	definite(hash, len, clean_out);

	printf("\n");
}

void
main(int argc, char* argv[])
{

	if (argc==1) {
		banner();
		printf("Usage: %s [HASH] [-h|-v|-l] [-i] [-s]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0){
		banner();
		help(argv[0]);
	} else if (strcmp(argv[1], "-l")==0) {
		banner();
		list();
	} else if (strcmp(argv[1], "-i")==0) {
		banner();
		using_history();
		while(1) {
			char *hash;
			hash = readline("houndsniff > ");
			rl_bind_key('\t', rl_complete);
			
			if (!hash) break;
			
			add_history(hash);
			driver(hash, 0);
			printf("--------------------------\n");
			free(hash);
		}
	} else if (strcmp(argv[1], "-s")==0) {
		char buffer[BUFFER_SIZE];
		while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			strtok(buffer, "\n");
			driver(buffer, 1);
		}

	} else if (strcmp(argv[1], "-v")==0) {
		printf("houndsniff-v%s\n", VERSION);      
	} else {
		banner();
		driver(argv[1], 0);
	}
	exit(EXIT_SUCCESS);
}
