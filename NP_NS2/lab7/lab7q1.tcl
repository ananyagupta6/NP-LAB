#Create a simulator object
set ns [new Simulator]
#Define different colors for data flows (for NAM)
$ns color 1 Blue
$ns color 2 Red
#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf
set nt [open out2.tr w]
$ns trace-all $nt
#Define a 'finish' procedure 
proc finish {} {							
global ns nf
$ns flush-trace
#Close the NAM trace file
close $nf
#Execute NAM on the trace file
exec nam out.nam &
exit 0
}
#Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
#Create links between the nodes
$ns duplex-link $n0 $n4 2Mb 10ms DropTail
$ns duplex-link $n1 $n4 2Mb 10ms DropTail
$ns duplex-link $n4 $n3 1.7Mb 20ms DropTail
$ns duplex-link $n4 $n2 1.7Mb 20ms DropTail
#Set Queue Size of link (n2-n3) to 10
$ns queue-limit $n4 $n3 10
$ns queue-limit $n4 $n2 10
#Give node position (for NAM)
$ns duplex-link-op $n0 $n4 orient right-down
$ns duplex-link-op $n2 $n4 orient right-up
$ns duplex-link-op $n1 $n4 orient left-down
$ns duplex-link-op $n3 $n4 orient left-up
#Monitor the queue for link (n2-n3). (for NAM)
$ns duplex-link-op $n4 $n3 queuePos 0.5
$ns duplex-link-op $n4 $n2 queuePos 0.5

#Setup a UDP connection
set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp $null
$udp set fid_ 2
#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false

#Setup a UDP connection
set udp2 [new Agent/UDP]
$ns attach-agent $n1 $udp2
set null2 [new Agent/Null]
$ns attach-agent $n2 $null2
$ns connect $udp2 $null2
$udp2 set fid_ 1
#Setup a CBR over UDP connection
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp2
$cbr2 set type_ CBR
$cbr2 set packet_size_ 1000
$cbr2 set rate_ 1mb
$cbr2 set random_ false

#Schedule events for the CBR and FTP agents
$ns at 0.1 "$cbr start"
$ns at 1.0 "$cbr2 start"
$ns at 9.0 "$cbr stop"
$ns at 10.0 "$cbr2 stop"
#Detach tcp and sink agents (not really necessary) 
#$ns at 4.5 "$ns detach-agent $n0 $tcp ; $ns detach-agent $n3 $sink"
#Call the finish procedure after 5 seconds of simulation time
$ns at 10.0 "finish"
#Print CBR packet size and interval
#puts "CBR packet size = [$cbr set packet_size_]"
#puts "CBR interval = [$cbr set interval_]"
#Run the simulation
$ns run
