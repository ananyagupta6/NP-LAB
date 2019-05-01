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
int main()
{
	int s,r,recb,sntb,x;
	printf("INPUT port number: ");
	scanf("%d", &x);
	struct sockaddr_in server;
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
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");
	
	int ch=1;
	int a[50];
	char arr[50];
	int n;
	printf("\n\nEnter the number of elements: ");
	scanf("%d",&n);
	printf("\nEnter the numbers: ");
	int num=0;
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<n;i++)
		arr[i]=a[i];
	sntb=send(s,arr,sizeof(arr),0);
	if(sntb==-1)
	{
		close(s);
		printf("\nMessage Sending Failed");
		exit(0);
	}
	while(ch!=5)
	{
	printf("\n\n");
	printf("1.Search for a number\n2.Sort in ascending order\n3.Sort in descending order\n4.Split into even and odd arrays\n5.Exit\nEnter your choice: ");
	scanf("%d", &ch);
	switch(ch)
	{
		case 1: printf("\nEnter the number to be searched: ");
				scanf("%d",&num);
				buff[0]=n;
				buff[1]=ch;
				buff[2]=num;
				sntb=send(s,buff,sizeof(buff),0);
				if(sntb==-1)
				{
					close(s);
					printf("\nMessage Sending Failed");
					exit(0);
				}
				break;
		case 2: buff[0]=n;
				buff[1]=ch;
				sntb=send(s,buff,sizeof(buff),0);
				if(sntb==-1)
				{
					close(s);
					printf("\nMessage Sending Failed");
					exit(0);
				}
				break;
		case 3: buff[0]=n;
				buff[1]=ch;
				sntb=send(s,buff,sizeof(buff),0);
				if(sntb==-1)
				{
					close(s);
					printf("\nMessage Sending Failed");
					exit(0);
				}
				break;
		case 4: buff[0]=n;
				buff[1]=ch;
				sntb=send(s,buff,sizeof(buff),0);
				if(sntb==-1)
				{
					close(s);
					printf("\nMessage Sending Failed");
					exit(0);
				}
				break;
		case 5: buff[0]=n;
				buff[1]=ch;
				sntb=send(s,buff,sizeof(buff),0);
				if(sntb==-1)
				{
					close(s);
					printf("\nMessage Sending Failed");
					exit(0);
				}
				break;
		default: printf("\nInvalid choice. Try again!");

	}
}
	close(s);

}