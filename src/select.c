#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "select.h"

/* this is basically where the program
   indexes through the database and pick
   out the rows with desired values */

int counter = 0;
int callback(void *, int, char **, char **);
int sel(int length, const char *charset);

int
sel(int length, const char *charset)
{
	sqlite3 *db;
	char *err_msg = 0;
	
	int rc = sqlite3_open("hashes", &db);
	char sql[1150], len[5], pt2[30], pt3[40];

	strcpy(sql,  "SELECT name FROM hashes WHERE length=");
	sprintf(len, "%d", length);
	strcpy(pt2, " AND charset='");
	strcpy(pt3, "' ORDER BY popularity DESC;");

	strcat(sql, len);
	strcat(sql, pt2);
	strcat(sql, charset);
	strcat(sql, pt3);
	rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
	sqlite3_close(db);
	
	return 0;
}

int
callback(void *unused, int argc, char **argv, char **azColName)
{
	counter++;
	int i;

	for (i = 0; i < argc; i++) {
		if (counter == 1)
			printf("Possible results:\n\n[%d] %s", counter, argv[i] ? argv[i] : "NULL");
		else
			printf("[%d] %s", counter, argv[i] ? argv[i] : "NULL");	
	} printf("\n");
	return 0;
}
