/**
	Note that Students should find the necessity, 
	e.g., functions and the structures 
	of each header file and add it as a comment 
	after the header file
*/
#include <stdio.h> /* <Write the necessity> */
#include <stdlib.h>
#include <time.h> /* <Write the necessity> */
#include <string.h> /* <Write the necessity> */
#include <errno.h> /* <Write the necessity> */
#include <netdb.h> /* <Write the necessity> */
#include <sys/uio.h> /* <Write the necessity> */
#include <arpa/inet.h> /* <Write the necessity> */
#include <netinet/in.h> /* <Write the necessity> */
#include <sys/types.h> /* <Write the necessity> */
#include <sys/socket.h> /* <Write the necessity> */

#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52001  // replace this with your assigned port number
#define	SA	struct sockaddr


FILE *fptr;  
char str1[100];
char port[100];
char method[2];
char file[100];
char Content[1000];
char fileContent[1000];
char directory[10];
char get[2] = "GET";
char newString[10][1000]; 
int i,j,ctr, t; 
uint8_t	buff[MAXLINE+1];
