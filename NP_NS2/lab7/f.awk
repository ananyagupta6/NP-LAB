BEGIN {
recvdSize = 0
startTime = 400
stopTime = 0
n=0
}
    
{
if($1=="+" && $3==0 && $4==1)
n++;

}
END {
printf("Number of packets sent: %d",n)
 }