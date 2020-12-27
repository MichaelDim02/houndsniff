#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "select.h"

/*
 * Houndsniff
 * hash identification program in C
 * by Michael Constantine Dimopoulos (Kerberos) 
 */

char version[4] = "1.3";
 
/* has uppercase letters */
bool
hasUpper(char ch[])
{
	bool hup = false;

	int len = strlen(ch);
	int i;
	
	for (i=0; i<len; i++) {
		if (ch[i] >= 'A' && ch[i] <= 'Z') {
			hup = true;
			break;
		}  /*else if (ch[i] >= 'a' && ch[i] <= 'z') {*/
	} 
	return hup;
}

void
banner()
{ 
	printf("          __\n");
	printf("(\\,------'()'--o  Sniff..\n");
	printf(" l_ ) _    /-''    Sniff...\n");
	printf(" /_)_) /_)_)\n\n");
	/*https://www.asciiart.eu/animals/dogs*/
	
	printf("Houndsniff - Hash Identification Program - Version %s\nBy MCD Sep 2020\n\n",version);
}

/* This function prints out the supported hashes
 * The reason I used a text file is because
 * 1. it's easier 
 * 2. it's simpler and
 * 3. I can add comments etc.
 */

void
list_(void)
{
	printf("\nHoundsniff supports:\n\n");
	int c;
	FILE *file;
	file = fopen("list.txt", "r");

	if (file) {
		while ((c = getc(file)) != EOF)
			putchar(c);
    		fclose(file);
	}

}

/* This is the first test;
 * here we identify the hash
 * based on *definite* characteristics
 */
void
definite(char string[], int length)
{
	if (string[0]=='$' && string[1]=='P' && string[2]=='$'){
		printf("[+] Definite identification: Wordpress hash\n");
		exit(0);
	} else if (string[0]=='$' && string[1]=='1' && string[2]=='$'){
		printf("[+] Definite identification: MD5 crypt(3)\n");
		exit(0);
	} else if (string[0]=='$' && string[1]=='5' && string[2]=='$'){
		printf("[+] Definite identification: SHA256 crypt(3)\n");
		exit(0);
	} else if (string[0]=='$' && string[1]=='6' && string[2]=='$'){
		printf("[+] Definite identification: SHA512 crypt(3)\n");
		exit(0);
	} else if (string[length-1]=='=') {
		printf("[+] Definite identification: Base64\n");
		exit(0);
	} else if (string[0]=='$' && string[1]=='a' && string[2]=='p' && string[3]=='r' && string[4]=='1' && string[5]=='$'){
		printf("[+] Definite identification: APR1\n");
		exit(0);
	} else if (string[0]=='$' && string[1]=='H' && string[2]=='$') {
		printf("[+] Definite identification: phpBB\n");
		exit(0);
	} else if (string[0]=='s' && string[1]=='h' && string[2]=='a' && string[3]=='1' && string[4]=='$'){
		printf("[+] Definite identification: SHA1 Django\n");
		exit(0);
	} else if (strlen(string)>31 && string[32]==':' && length==65) {
		printf("[+] Definite identification: MD5 Joomla (pass:salt)\n");
		exit(0);
	}
}

/* this function determines charset (used later for identification)*/
const char*
charset(char string[])
{
	if (strchr(string, '$') != NULL)
		return "b";	
	else if (strchr(string, '/') != NULL)
		return "c";
	else if (string[0]=='0' && string[1]=='x' && string[2]=='0')
		return "d";
	else if (hasUpper(string)==true)
		return "e";
	else
		return "a";
}

void
help(void)
{
	printf("Houndsniff is  a hash recognition  program\n");
	printf("It works  by  extracting some  info  about\n");
	printf("the  hash  and comparing it to  info about\n");
	printf("other  hashes in an SQLite  database. Then,\n");
	printf("it prints the matches sorted by popularity.\n");
	printf("Their  popularity  is  determined  by  web\n");
	printf("search  result  numbers  in  comparison to\n");
	printf("to other  hashes  with  the  same features\n\n");
	printf("If your hash includes a dollar sign ($), make\nsure you place it in between quotes.\n\n");
	printf("Send missing hashes at houndsniff@protonmail.com\n\n");
	printf("-h to display this panel and exit\n");
	printf("-l to list supported hashing algorithms\n");
	printf("\nUsage: hound [HASH]\n");
}

int
main(int argc, char* argv[])
{
	banner();

	if(argc>1){
		if(strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0){
			help();
		} else if(strcmp(argv[1], "-l")==0) {
			list_();
		} else {
			int len = strlen(argv[1]);
			printf("Hash: %s\n", argv[1]);
			printf("Length: %d\n",len);
			const char* chars = charset(argv[1]);
			printf("Charset: %s\n\n", chars);
			sel(len, chars);
			definite(argv[1], len);
		}
	} else {
		printf("Usage: %s [HASH] or -h for help\n", argv[0]);
	}
	return 0;
}
