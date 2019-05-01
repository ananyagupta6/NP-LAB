#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<netdb.h>
#include<errno.h>
int main()
{
	int s,r,recb,sntb,x;
	printf("INPUT port number: ");
	scanf("%d", &x);
	struct sockaddr_in server;
	char buff[100],buff1[50],buff2[50];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");

	printf("\nEnter username: ");
	scanf("%s",buff);

	sntb=send(s,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}

	printf("\nEnter password: ");
	scanf("%s",buff);

	sntb=send(s,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}

	recb=recv(s,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}

	printf("\n%s\n", buff);

	if(strcmp(buff,"Authentication succeeded!")!=0)
	{
		close(s);
		exit(0);
	}

	recb=recv(s,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}

	int ch=0;
	int amt;
	while(ch!=4){

	printf("\n%s\n", buff);
	
	scanf("%d",&ch);

	strcpy(buff1,"");
	
	switch(ch)
	{
		case 1:printf("\nEnter amount to be debited: \n");
		scanf("%d",&amt);
		buff1[0]=ch;
		buff1[1]=amt;
		break;

		case 2:printf("\nEnter amount to be credited: \n");
		scanf("%d",&amt);
		buff1[0]=ch;
		buff1[1]=amt;
		break;

		case 3: buff1[0]=ch;
		case 4: break;
	}

	sntb=send(s,buff1,sizeof(buff1),0);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}
}
	close(s);

}