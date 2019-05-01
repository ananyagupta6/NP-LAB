#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct student{
	char regno[10];
	char name[10];
	char subjects[10][10];
	char marks[10][10];
	char add[20];
	char sem[5];
	char department[10];
	char section[5];
};
struct subject{
	char code[10];
	char sub_name[10];
	char dept[10];
};
int main()
{
	int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[100];

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
	struct student stu[2];
	struct subject sub[4];
	strcpy(stu[0].regno,"160956");
	strcpy(stu[1].regno,"160954");
	strcpy(stu[0].name,"ananya");
	strcpy(stu[1].name,"alex");
	strcpy(stu[0].add,"manipal");
	strcpy(stu[1].add,"manipal");
	strcpy(stu[0].sem,"4");
	strcpy(stu[1].sem,"2");
	strcpy(stu[0].department,"ICT");
	strcpy(stu[1].department,"CSE");
	strcpy(stu[0].section,"A");
	strcpy(stu[1].section,"B");
	strcpy(sub[0].code,"ICT123");
	strcpy(sub[1].code,"ICT234");
	strcpy(sub[2].code,"HUM089");
	strcpy(sub[3].code,"CSE198");
	strcpy(sub[0].sub_name,"OOPS");
	strcpy(sub[1].sub_name,"DS");
	strcpy(sub[2].sub_name,"EEFM");
	strcpy(sub[3].sub_name,"COD");
	strcpy(sub[0].dept,"ICT");
	strcpy(sub[1].dept,"ICT");
	strcpy(sub[2].dept,"HUMANTITY");
	strcpy(sub[3].dept,"CSE");
	strcpy(stu[0].subjects[0],"ICT123");
	strcpy(stu[0].subjects[1],"ICT234");
	strcpy(stu[1].subjects[0],"CSE198");
	strcpy(stu[0].marks[0],"15");
	strcpy(stu[0].marks[1],"15");
	strcpy(stu[1].marks[0],"12");
	while(1){
	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
	int n,i=0,j=0;
	char temp[50];
	int ch=buff[0];
	n=buff[1];
	for(i=0;i<n;i++)
	{
		temp[j]=buff[i+2];
		j++;
	}
	temp[j]='\0';
	if(ch==4)
		break;
	int pid=fork();
	if(pid==0)
	{
		//child 1 and ch=1
		if(ch==1)
		{
			if(strcmp(stu[0].regno,temp)==0)
			{
				strcpy(buff,"");
				strcpy(buff,"Name of student is: ");
				strcat(buff,stu[0].name);
				strcat(buff," Adress is: ");
				strcat(buff,stu[0].add);
				strcat(buff," PID is: 0");
			}
			else
			{
				strcpy(buff,"");
				strcpy(buff,"Name of student is: ");
				strcat(buff,stu[1].name);
				strcat(buff," Adress is: ");
				strcat(buff,stu[1].add);
				strcat(buff," PID is: 0");
			}

	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
		}
		else
		{
			int p=fork();
			if(p==0)
			{
				//child 2 and ch=2
				if(ch==2)
				{
					if(strcmp(stu[0].name,temp)==0)
					{
						strcpy(buff,"");
						strcpy(buff,"Dept sem section courses are: ");
						strcat(buff,stu[0].department);
						strcat(buff," ");
						strcat(buff,stu[0].sem);
						strcat(buff," ");
						strcat(buff,stu[0].section);
						strcat(buff,"  ");
						strcat(buff,stu[0].subjects[0]);
						strcat(buff," ");
						strcat(buff,stu[0].subjects[1]);
						strcat(buff," PID is: ");
						strcat(buff,"0");
					}
					else
					{
						strcpy(buff,"");
						strcpy(buff,"Dept sem section courses are: ");
						strcat(buff,stu[1].department);
						strcat(buff,"  ");
						strcat(buff,stu[1].sem);
						strcat(buff,"  ");
						strcat(buff,stu[1].section);
						strcat(buff,"  ");
						strcat(buff,stu[1].subjects[0]);
						strcat(buff," PID is: ");
						strcat(buff,"0");
					}

	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
				}
				else
				{
					int pd=fork();
					if(pd==0)
					{
						//child 3 and ch=3
						if(strcmp(stu[0].subjects[0],temp)==0)
						{
							strcpy(buff,"");
							strcpy(buff,"Marks are: ");
							strcat(buff,stu[0].marks[0]);
							strcat(buff," PID is: 0");
						}
						else if(strcmp(stu[0].subjects[1],temp)==0)
						{
							strcpy(buff,"");
							strcpy(buff,"Marks are: ");
							strcat(buff,stu[0].marks[1]);
							strcat(buff," PID is: 0");
						}
						else
						{
							strcpy(buff,"");
							strcpy(buff,"Marks are: ");
							strcat(buff,stu[1].marks[0]);
							strcat(buff," PID is: 0");
						}

	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
		printf("\nMessage Sending Failed");
		close(s);
		close(ns);
		exit(0);
	}
						exit(0);
					}

				}
				exit(0);
			}
		}
	exit(0);
	}
}

	close(ns);
	close(s);
}