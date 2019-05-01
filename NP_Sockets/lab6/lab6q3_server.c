#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.");

	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.");

	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
	printf("\nFile name Recieved: ");
	printf("%s\n", buff);

	//fork and perform file operations
	int pid;
	pid=fork();
	if(pid==0)
	{
		//child
		FILE *fptr;
		FILE *ptr;
	char temp[512];
	if((fptr=fopen(buff,"r"))==NULL)
	{
		close(s);
		exit(0);
	}
	if((ptr=fopen("temp1.txt","w"))==NULL)
	{
		close(s);
		exit(0);
	}
	while((fgets(temp,512,fptr))!=NULL)
	{
		int i=0;
		while(temp[i]!='\0')
		{
			temp[i]=temp[i]-32;
			i++;
		}
		fputs(temp,ptr);
	}
	if(fptr)
	{
		fclose(fptr);
	}
	if(ptr)
	{
		fclose(ptr);
	}
	printf("\nChild operation: \n");
	FILE *fp;
	if((fp=fopen("temp1.txt","r"))==NULL)
	{
		close(s);
		exit(0);
	}
	while((fgets(temp,512,fp))!=NULL)
	{
		printf("%s\n", temp);
	}
	if(fp)
	{
		fclose(fp);
	}
	exit(0);
	}
	else
	{
		//parent
		FILE *fptr2;
		FILE *ptr2;
	char temp2[512];
	if((fptr2=fopen(buff,"r"))==NULL)
	{
		close(s);
		exit(0);
	}
	if((ptr2=fopen("temp2.txt","w"))==NULL)
	{
		close(s);
		exit(0);
	}
	int arr[50];
	while((fgets(temp2,512,fptr2))!=NULL)
	{
		int i=0;
		while(temp2[i]!='\0')
		{
			if(temp2[i]=='a')
				temp2[i]='1';
			else
				temp2[i]='5';
			i++;
		}
		fputs(temp2,ptr2);
	}
	if(fptr2)
	{
		fclose(fptr2);
	}
	if(ptr2)
	{
		fclose(ptr2);
	}
	printf("\nParent operation: \n");
	FILE *fp2;
	if((fp2=fopen("temp2.txt","r"))==NULL)
	{
		close(s);
		exit(0);
	}
	while((fgets(temp2,512,fp2))!=NULL)
	{
		printf("%s\n", temp2);
	}
	if(fp2)
	{
		fclose(fp2);
	}
	}

	//remove(buff);
	//remove("temp1.txt");
	//rename("temp2.txt",buff);
	strcpy(buff,"DONE!");
	sntb=send(s,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}
	close(ns);
	close(s);
}