#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "select.h"

/*
 * Houndsniff
 * hash identification
 *
 * by Michael Constantine Dimopoulos et al
 */

#define VERSION "1.9"
 
static int
hasUpper(char ch[])
{
	int len = strlen(ch);
	int i;
	
	for (i=0; i<len; i++) {
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

/* This is the first test;
 * here we identify the hash
 * based on *definite* characteristics
 */
void
definite(char string[], int length)
{
	char *def = "[" RED "+" RESET "] Definite identification";

	if (string[0]=='$' && string[1]=='P' && string[2]=='$')
		printf("%s Wordpress hash\n", def);
	else if (string[0]=='$' && string[1]=='1' && string[2]=='$')
		printf("%s MD5 crypt(3)\n", def);
	else if (string[0]=='$' && string[1]=='5' && string[2]=='$')
		printf("%s SHA256 crypt(3)\n", def);
	else if (string[0]=='$' && string[1]=='6' && string[2]=='$')
		printf("%s SHA512 crypt(3)\n", def);
	else if (string[length-1]=='=') 
		printf("%s Base64 or Base32\n", def);
	else if (string[0]=='$' && string[1]=='a' && string[2]=='p'
		&& string[3]=='r' && string[4]=='1' && string[5]=='$')
		printf("%s APR1\n", def);
	else if (string[0]=='$' && string[1]=='H' && string[2]=='$') 
		printf("%s phpBB\n", def);
	else if (string[0]=='s' && string[1]=='h' && string[2]=='a' &&
		string[3]=='1' && string[4]=='$')
		printf("%s SHA1 Django\n", def);
	else if (length==65 && string[32]==':')
		printf("%s MD5 Joomla (pass:salt)\n", def);
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
	printf( "Houndsniff is  a hash recognition tool.\n"
		"It works by extracting some info about	\n"
		"the hash and comparing it to info about\n"
		"other hashes in a local database. Then,\n"
		"it prints the matches sorted by  their \n"
		"popularity, which is determined by web	\n"
		"search result numbers in comparison to	\n"
		"other hashes with the same features	\n\n"

		"If your hash includes a dollar sign ($)\n"
		"make sure you place it in between quotes.\n\n"

		"By Michael Constantine Dimopoulos et al\n"
		"Contributors:"
		"Christopher Wellons, Martin K.\n"
		"tuu & fizzie on ##c@freenode\n\n"

		"-l to list supported hashing algorithms\n"
		"-s for an interactive shell\n"
		"-h to display this panel and exit\n"
		"\nUsage: Usage: %s [HASH] [-h] [-l] [-s]\n",
		exename);
}

void
driver(char *hash)
{
	int len = strlen(hash);
	const char* chars = charset(hash);
	printf("Hash: " RED "%s" RESET "\n", hash);
	printf("Length: " RED "%d" RESET "\n",len);
	printf("Charset: " RED "%s" RESET "\n\n", chars);
	sel(len, chars);
	definite(hash, len);
	printf("\n");
}

void
main(int argc, char* argv[])
{
	banner();

	if(argc==1) {
		printf("Usage: %s [HASH] [-h] [-l] [-s]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0){
		help(argv[0]);
	} else if(strcmp(argv[1], "-l")==0) {
		list();
	} else if(strcmp(argv[1], "-s")==0) {
		using_history();
		while(1) {
			char *hash;
			hash = readline("houndsniff > ");
			rl_bind_key('\t', rl_complete);
			
			if (!hash) break;
			
			add_history(hash);
			driver(hash);
			printf("--------------------------\n");
			free(hash);
		}
	} else {
		driver(argv[1]);
	}
	exit(EXIT_SUCCESS);
}
