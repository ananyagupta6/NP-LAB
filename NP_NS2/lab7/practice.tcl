set ns [new Simulator]
$ns color 1 Red
$ns color 2 Blue
set nf [open out.nam w]
$ns namtrace-all $nf
proc finish{} {
global ns nf
$ns flush-trace
close $nf
exec nam out.nam &
exit 0
}
set n0 [$ns node]
set n1[$ns node]
set n2[$ns node]
set n3[$ns node]
$ns dupex-link $n0 $n2 1Mb 10s DropTail
$ns dupex-link $n1 $n2 1Mb 10s DropTail
$ns dupex-link $n2 $n3 1Mb 10s DropTail
$ns queue-limit $n2 $n3 10
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n2 $n3 queuePos 0.5

set tcp [new Agent/TCP]
$tcp set class_ 1
$ns attach-agent $n0 $tcp
set sink [new Application/FTP]
$ns attach-agent $n3 $sink
$ns connect $tcp $sink
$tcp set fid_ 1


