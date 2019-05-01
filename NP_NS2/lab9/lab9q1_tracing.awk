BEGIN {
sendLine = 0;
recvLine = 0;
fowardLine = 0;
sent=0
}
$0 ~/^s.* AGT/ {
sendLine ++ ;
}
$0 ~/^r.* AGT/ {
recvLine ++ ;
}
$0 ~/^f.* RTR/ {
fowardLine++;
}
END{
printf "Ratio:%.4f,f:%d, sent %d, recvd %d\n",(recvLine/sendLine),forwardLine, sendLine, recvLine;
}