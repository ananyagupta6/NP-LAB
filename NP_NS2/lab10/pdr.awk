BEGIN {
        sendLine = 0;
        recvLine = 0;
        fowardLine = 0;
}
 
$0 ~/^s.* AGT/ {
        sendLine ++ ;
}
 
$0 ~/^r.* AGT/ {
        recvLine ++ ;
}
 
$0 ~/^f.* RTR/ {
        fowardLine ++ ;
}
 
END {
        printf "s:%d r:%d, r/s Ratio:%.4f, f:%d \n", sendLine, recvLine, (recvLine/sendLine),fowardLine;
}
 
