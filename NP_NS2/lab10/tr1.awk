BEGIN{
f1 = 0;
n1 = 0;
f2=0;
n2=0;
st1=400;
s1=0;
r1 = 0;

st2=400;
s2=0;
r2 = 0;

f3 =0;
n3=0;
st3=0;
s3=0;
r3=0;



}
{
action = $1;
time = $2;
from = $3;
to = $4;
type = $5;
pktsize = $6;
flow_id = $8;
src = $9;
dst = $10;
seq_no = $11;
packet_id = $12;


if(from==0 && to==1 && action == "+")
{
 if(time<st1)
{
      st1 = time;
}
 f1++;
}
if(from==0 && to==1 &&  action == "r")
{
if(time>s1)
{
s1 = time;
}
r1 += pktsize;
}
if(from==0 && to==1 &&  action == "d")
{

n1++;
}


if(from==1 && to==2 && action == "+")
{
 if(time<st2)
{
      st2 = time;
}
 f2++;
}


if(from==1 && to==2 &&  action == "r")
{
if(time>s2)
{
s2 = time;
}
r2 += pktsize;
}

if(from==1 && to==2 && action == "d")
{
 n2++;
}

if(from==0 && action == "+")
{
if(time<st3)
{
st3 = time;
}
n3++;
}

if(to==2 && action == "r")
{
 if(time>s3)
{
 s3=time;
}
r3+=pktsize;
}


}
END{
printf("Average Throughput[kbps](0-1) = %.2f",(r1/(s1-st1))*(8/1000));
printf("Average Throughput[kbps](1-2) = %.2f",(r2/(s2-st2))*(8/1000));
printf("Average Throughput[kbps](0-3) = %.2f",(r3/(s3-st3))*(8/1000));
print "packet loss from 0-2 = " n2/f2;
}
