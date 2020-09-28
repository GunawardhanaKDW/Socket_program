#include	"utils.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int			listenfd, connfd,n;
	socklen_t		len;
	pid_t			childpid;
	struct sockaddr_in	servaddr, cliaddr;
	char			buff[MAXLINE], msgrcv[100], msgsnd[1000], recvline[MAXLINE + 1];;
	const char	*ptr;
	int port = atoi(argv[1]);	

	// socket creation
	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		fprintf(stderr, "socket creation failed\n");
		exit (1);
	}

	bzero(&servaddr, sizeof(servaddr));
	bzero(msgrcv, sizeof(msgrcv));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(port); /* daytime server */

	if ( (bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0) 
	{
		fprintf(stderr, "bind failed\n");
		exit (1);
	}
		

	if ( listen(listenfd, LISTENQ) < 0) 
	{
		fprintf(stderr, "listen failed\n");
		exit (1);
	}

	for ( ; ; ) 
	{
		len = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &len)) < 0 ) 	
		{
			fprintf(stderr, "accept failed\n");
			exit (1);
		}

		if( (ptr = inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff))) == NULL) 
		{
			fprintf(stderr, "inet_ntop error \n");
			exit (1);
		}
		
		if((childpid=fork()) == 0){
			close(listenfd);
			runC(connfd);
			exit(0);
		}else{
			close(connfd);
		}
		
	}
	
}
void runC(int connfd){

	char	buff[MAXLINE], msgrcv[MAXLINE], msgsnd[1000], recvline[MAXLINE + 1];;
	int n;
	char* ptr;
	char fileOpen[20];
	char type[3];
	
	
	bzero(msgrcv, sizeof(msgrcv));	//Message Reading
	n = read(connfd, msgrcv, MAXLINE);	//Message Received
    	
    	for(int d = 0;d < 4;d++ ){		//Get message type ex:- HTTP 
		type[d] = msgrcv[d+16]; 		
		
	}

    	// If HTTP request
 	if(strcmp(type, "HTTP") == 0){
 		
		for(int k = 0;k < 20;k++){ 	//Remove the trailing chars
			fileOpen[k] = msgrcv[k];
		
		}
		
		if((ptr = strstr(fileOpen, "index")) != NULL){
			GET("index.html", connfd);
			
		}else if((ptr = strstr(fileOpen, "hello")) != NULL){
			GET("hello.html", connfd);
			
		}else if((ptr = strstr(fileOpen, "sliit")) != NULL){
			GET("sliit.html", connfd);
			
		}else{
			snprintf((char*)buff, sizeof(buff), "HTTP/1.0 404 Not Found/404 Not Found");
			if ( write(connfd, (char*)buff, strlen((char*)buff)) != strlen((char*)buff)) 
			{
			fprintf(stderr, "accept failed\n");
			
			}
			exit(1);
       	
			
		}
 	
 	}else{	
 	
 		strcpy(str1,msgrcv);
 	
		j=0; ctr=0; t =0;
    		for(i=0;i<=(strlen(str1));i++)
    		{
       	 		if(str1[i]==' '||str1[i]=='\0')
        			{
          				newString[ctr][j]='\0';
            				ctr++;  
            				j=0;    
            				if(ctr == 3)
            				{
            					for(t=i+1;t<=(strlen(str1));t++)
            					{
            						newString[ctr][j]=str1[t];
            						j++;	
            						
            					}
        				}
        				if(t > i)
        					break;
	
	        		}else{
	        			newString[ctr][j]=str1[i];
	            			j++;
        		
       	 		}
        	
            			
    		}
    	
    		strcpy(port,newString[0]);
    		strcpy(method,newString[1]);
    		strcpy(file,newString[2]);
    		strcpy(Content,newString[3]);
    				
		if(strcmp(method, "GET") == 0 ){
			GET(file, connfd);
		
		}else if(strcmp(method, "PUT") == 0 ){
			PUT(file, connfd, newString[3]);
			
		
		}else{
			printf("----error-----");
		}
	
	}
	
	//Message sent
	if ( close(connfd) == -1) 
	{
		fprintf(stderr, "accept failed\n");
		exit (1);
	}

}

void GET(char fileName[10], int connfd ){
	
	char line[1000];
	char fileContent[1000];
    	char sendline[MAXLINE + 1];
	size_t characters;
	size_t bufsize = 100;
	char pages[2][20] = {{"hello.html"}, {"index.html"}, {"sliit.html"}};
	size_t nn;
	char a[20];
	strcpy(directory, "pages/");
    	
	if(strcmp(fileName, pages[0]) == 0 ){
		if ((fptr = fopen(strcat(directory, pages[0]), "r")) == NULL) {
        	printf("Error! opening file");
       	 exit(1);
    		}
	
	}else if(strcmp(fileName, "index.html") == 0 ){
		if ((fptr = fopen(strcat(directory, pages[1]), "r")) == NULL) {
        	printf("Error! opening file");
       	 exit(1);
    		}
	
	}else if(strcmp(fileName, "sliit.html") == 0 ){
		if ((fptr = fopen(strcat(directory, pages[2]), "r")) == NULL) {
        	printf("Error! opening file");
        	exit(1);
    		}
	}else{
		snprintf((char*)buff, sizeof(buff), "HTTP/1.0 404 Not Found/404 Not Found");
		if ( write(connfd, (char*)buff, strlen((char*)buff)) != strlen((char*)buff)) 
		{
		fprintf(stderr, "accept failed\n");
		exit (1);
		}
	}
    	// reads text until newline is encountered
    	while (fgets(line, sizeof(line), fptr)) {
        	strcat(fileContent, line);
		
   	}
	fclose(fptr);
   	
    	snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK/""%s""", fileContent);
        	
        if ( write(connfd, (char*)buff, strlen((char*)buff)) != strlen((char*)buff)) 
	{
		fprintf(stderr, "accept failed\n");
		exit (1);
	}	

}

void PUT(char fileName[10], int connfd, char Content[1000]){ 	
   	strcpy(directory, "files/");
	fptr = fopen(strcat(directory, fileName), "w+");
   	fprintf(fptr, Content);
   	fclose(fptr);
   	
   	snprintf((char*)buff, sizeof(buff), "Your requested file ""%s"" is saved", fileName);
        	
        if ( write(connfd, (char*)buff, strlen((char*)buff)) != strlen((char*)buff)) 
	{
		fprintf(stderr, "accept failed\n");
		exit (1);
	}
	
    
}
	
	

