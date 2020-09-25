#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "upp.h"
#include "select.h"

void banner(float vesion){ 
	printf("          __               \n");
	printf("(\\,------'()'--o  Sniff..\n");
	printf(" l_ )  _   /-''    Sniff...\n");
	printf("  /_)_) /_)_)\n\n");
	
	//https://www.asciiart.eu/animals/dogs
	
	printf("Houndsniff - Hash Identification Program - Version %.1f\nBy MCD\n\n",vesion);
}

void list_() {
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

void definite(char string[1000], int length){
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
	}
}

const char* charset(char string[1000]){
	const char* result;
	if (strchr(string, '$') != NULL){
		return "b";	
	} else if (strchr(string, '/') != NULL){
		return "c";
	} else if (string[0]=='0' && string[1]=='x' && string[2]=='0'){
		return "d";
	} else if (hasUpper(string)==true) {
		return "e";
	} else {
		return "a";
	}
}

void help(){
	printf("Houndsniff is a hash recognition program\n");
	printf("It works by extracting some info about the\n");
	printf("the hash and comparing it to info about\n");
	printf("other hashes in an SQLite database. Then,\n");
	printf("it prints the matches sorted by popularity.\n");
	printf("Their popularity is determined by Google\n");
	printf("search result numbers in comparison to\n");
	printf("to other hashes with the same characteristcs\n\n");
	printf("If your hash includes a dollar sign ($), make\nsure you place it in between quotes.\n\n");
	printf("Send missing hashes at houndsniff@protonmail.com\n\n");
	printf("-h to display this panel and exit\n");
	printf("-l to list supported hashing algorithms\n");
	printf("\nUsage: hound [HASH]\n");
}
int main(int argc, char* argv[]) {
	float version = 1.0;
	banner(version);
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
		printf("Usage: hound [HASH] or -h for help\n");
	}
	return 0;
}
