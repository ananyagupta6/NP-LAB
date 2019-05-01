#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct users{
	char username[50];
	char password[50];
	int balance;
};
int main()
{
	int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[100],buff2[50],buff1[50];
	struct users u[3];
	strcpy(u[0].username,"ananyagupta6");
	strcpy(u[1].username,"ananyagupta");
	strcpy(u[2].username,"ananyaaa");
	strcpy(u[0].password,"def");
	strcpy(u[1].password,"ghi");
	strcpy(u[2].password,"jkl");
	u[0].balance=500;
	u[1].balance=100;
	u[2].balance=1000;
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
	printf("\nSocket binded.\n");

	r=listen(s,1);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening. Waiting for connections..\n");
	len=sizeof(client);

	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.\n");

	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}
	recb=recv(ns,buff1,sizeof(buff1),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}
	int flag=0;
	for(int i=0;i<3;i++)
	{
		if(strcmp(u[i].username,buff)==0)
			flag=i+1;
	}
	int j=0;
	while(buff1[j]!='\0')
	{
		buff1[j]=buff1[j]+3;
		j++;
	}
	if(flag>0)
	{
		if(strcmp(u[flag-1].password,buff1)==0)
			strcpy(buff,"Authentication succeeded!");
		else
			strcpy(buff,"Incorrect password");
	}
	else
	{
		strcpy(buff,"Incorrect username");
	}
	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
	if(strcmp(buff,"Authentication succeeded!")!=0)
	{
		close(ns);
		close(s);
		exit(0);
	}
	strcpy(buff,"1.Debit  2.Credit  3.View balance  4.Exit  Enter your choice?");
	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}

	char ch=0;
	while(ch!=4)
	{
		recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}
	ch=buff[0];
	char amt;
	switch(ch)
	{
		case 1: amt=buff[1];
		u[flag-1].balance-=amt;
		printf("\nAmount debited!\n");
		break;

		case 2: amt=buff[1];
		u[flag-1].balance+=amt;
		printf("\nAmount credited!\n");
		break;

		case 3: printf("\nBalance is: %d\n", u[flag-1].balance);
		break;

		case 4: break;
	}
	}
	close(ns);
	close(s);
}