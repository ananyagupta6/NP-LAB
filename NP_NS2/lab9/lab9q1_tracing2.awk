BEGIN {
sendLine = 0;
recvLine = 0;
fowardLine = 0;
sent=0
}
{
event=$1
if(event=="r" && $4=="AGT"){
sent++
}
}
END{
printf "Packets that reached destination: %d",sent;
}