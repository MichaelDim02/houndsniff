#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "upp.h"

bool hasUpper(char ch[600]);

bool
hasUpper(char ch[600]) {
	
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
