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
	char arr[50];
	int arr1[50],arr2[50];
    recb=recv(ns,arr,sizeof(arr),0);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
	}	
	printf("\n\nArray of numbers received!\n");
	int ch=1,n,num=1;
	while(ch!=5)
	{
		recb=recv(ns,buff,sizeof(buff),0);
		if(recb==-1)
		{
		printf("\nMessage Recieving Failed");		
		close(s);
		close(ns);
		exit(0);
		}	
		n=buff[0];
		ch=buff[1];
		if(ch!=5)
			printf("\nProcessing request..\n");
		int l=0,k=0,x;
		switch(ch)
		{
			case 1: num=buff[2];
					for(x=0;x<n;x++)
					{
						if(arr[x]==num)
							break;
					}
					printf("\nProcessing done!");
					if(x==n)
						printf("\nElement does not exist!");
					else
						printf("\nElement exists at %d position.",x+1);
					printf("\n\n");
					break;
			case 2: for(int i=0;i<n-1;i++)
					{
						for(int j=0;j<n-i-1;j++)
							{
								if(arr[j]>arr[j+1])
								{
									int temp=arr[j];
									arr[j]=arr[j+1];
									arr[j+1]=temp;
								}
							}
					}
					printf("\nProcessing done!");
					printf("\nSorted array is: \n");
					for(int i=0;i<n;i++)
						printf("%d  ",arr[i]);
					printf("\n\n");
					break;
			case 3: for(int i=0;i<n-1;i++)
					{
						for(int j=0;j<n-i-1;j++)
							{
								if(arr[j]<arr[j+1])
								{
									int temp=arr[j];
									arr[j]=arr[j+1];
									arr[j+1]=temp;
								}
							}
					}
					printf("\nProcessing done!");
					printf("\nSorted array is: \n");
					for(int i=0;i<n;i++)
						printf("%d  ",arr[i]);
					printf("\n\n");
					break;
			case 4: printf("\nProcessing done!");
			printf("\nEven array is: \n");
					for(int i=0;i<n;i++)
					{
						if(arr[i]%2==0)
							printf("%d ",arr[i]);
					}
					printf("\n\nOdd array is: \n");
					for(int i=0;i<n;i++)
					{
						if(arr[i]%2!=0)
							printf("%d ",arr[i]);
					}
					printf("\n\n");
					break;
			case 5: break;
			default: break;
		}
	}
	close(ns);
	close(s);
}