#include	"utils.h"

int
main(int argc, char **argv)
{
	int	sockfd, n, i, t, j, k, d;
	char	recvline[MAXLINE + 1];
	char	msgrcv[100];
	char	msgstr[100];
	char	msgstrm[50];
	char	msgstrh[50];
	char 	line[1000];
	char 	fileContent[1000];
	char 	ipaddress[20];
	char 	website[100];
	char 	wgetreq[100];
	
	char directory[10];
	struct sockaddr_in	servaddr;
	FILE *fptr;

	if (argc != 5) 
	{
		printf("Missing argument");
		return 1;
	}
	int port = atoi(argv[2]);
	if(port == 80 && strcmp(argv[3], "GET") == 0){
		
   		strcpy(directory, "pages/");
   		strcat(directory, argv[4]); 
   		sprintf(wgetreq ,"wget -O ""%s"" https://""%s""", directory, argv[1]);
   		system(wgetreq);
   		return 1;
			
	}else if(port == 80){
		printf("Please Enter the Right PORT Number! \n");
		return 1;
		
	}else if((strcmp(argv[3], "GET") != 0) && (strcmp(argv[3], "PUT") != 0 )){
		printf("Please Enter the Right Method! \n");
		return 1;

	}
	
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error");
		return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	bzero(msgstr, sizeof(msgstr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(port);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s", argv[1]);
		return 1;
	}

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) 
	{
		printf("connect error");
		return 1; 
	}
	
	strcpy(msgstr, argv[2]);
	strcpy(msgstrm, argv[3]);
	strcpy(msgstrh, argv[4]);
	
	strcat(msgstr, " ");
	strcat(msgstr, msgstrm);
	strcat(msgstr, " ");
	strcat(msgstr, msgstrh);
	strcpy(directory, "files/");
	if(strcmp(argv[3], "PUT") == 0){
		if ((fptr = fopen(strcat(directory, msgstrh), "r")) == NULL) {
				printf("cannot find %s\n", msgstrh);
				return 1;
				
		if (n < 0) 
		{
			printf("read error");
			return 1;
		}

		exit(0);
		
    		}
    		while (fgets(line, sizeof(line), fptr)) {
       	 	strcat(fileContent, line);
   		}
   	
   		strcat(msgstr, " ");
		strcat(msgstr, fileContent);
		fclose(fptr);
	}
	
	
	if ( write(sockfd, msgstr, strlen(msgstr)) != strlen(msgstr)) 
	{
		fprintf(stderr, "accept failed\n");
		exit (1);
	}
	
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) 
	{
		recvline[n] = 0;
	}
		for(i=0; i<=(strlen(recvline)); i++)
    		{		
    				
       	 			if(recvline[i]=='/')
        				{
        					if( i == 4)
        					{
        						msgrcv[i] = recvline[i];
        						continue;
        					
        					}
              					j=0;    //for next word, init index to 0
            					for(t=i+1;t<=(strlen(recvline));t++)
            					{
            						fileContent[j]=recvline[t];
            						j++;	
            					
            					}
        				
        					if(t > i)
        						break;
				
	        			}else{
	        				msgrcv[i] = recvline[i];
        				}
        				
        			
       	 }
	printf("%s\n", msgrcv);
	if(strcmp(msgrcv ,"HTTP/1.0 200 OK") == 0)
	{	
		strcpy(directory, "pages/");
		fptr = fopen(strcat(directory, argv[4]), "w+");
   		fprintf(fptr, fileContent);
   		fclose(fptr);
   	
   	}
   	
	exit(0);
}
