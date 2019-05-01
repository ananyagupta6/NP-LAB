# Define options
    set val(chan)        Channel/WirelessChannel;# channel type
    set val(prop)       Propagation/TwoRayGround;# radio-propagation model
    set val(netif)       Phy/WirelessPhy ;# network interface type
    set val(mac)         Mac/802_11 ;# MAC type
    set val(ifq)       Queue/DropTail/PriQueue ;# interface queue type
    set val(ll)        LL ;# link layer type
    set val(ant)        Antenna/OmniAntenna ;# antenna model
    set val(ifqlen)     50 ;# max packet in ifq
    set val(nn)         15 ;# number of mobilenodes
    set val(rp)        DSDV ;# routing protocol
    set val(x)        1000 ;# X dimension of topography
    set val(y)        1000 ;# Y dimension of topography
    set val(stop)      100 ;# time of simulation end


set ns              [new Simulator]
#creating trace file and nam file
set tracefd       [open wireless2.tr w]
set windowVsTime2 [open win.tr w]
set namtrace      [open wirelessf.nam w]  

$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

# set up topography object
set topo       [new Topography]

$topo load_flatgrid $val(x) $val(y)

create-god $val(nn)

# configure the nodes
        $ns node-config -adhocRouting $val(rp) \
                   -llType $val(ll) \
                   -macType $val(mac) \
                   -ifqType $val(ifq) \
                   -ifqLen $val(ifqlen) \
                   -antType $val(ant) \
                   -propType $val(prop) \
                   -phyType $val(netif) \
                   -channelType $val(chan) \
                   -topoInstance $topo \
                   -agentTrace ON \
                   -routerTrace ON \
                   -macTrace OFF \
                   -movementTrace ON
                   
      for {
set i 0
} {
$i < $val(nn)
} {
 incr i
} {

            set node_($i) [$ns node]    
      
}


# Provide initial location of mobilenodes
$node_(0) set X_ 0.0
$node_(0) set Y_ 127.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 5.0
$node_(1) set Y_ 5.0
$node_(1) set Z_ 0.0

$node_(2) set X_ 150.0
$node_(2) set Y_ 5.0
$node_(2) set Z_ 0.0

$node_(3) set X_ 300.0
$node_(3) set Y_ 5.0
$node_(3) set Z_ 0.0

$node_(4) set X_ 450.0
$node_(4) set Y_ 5.0
$node_(4) set Z_ 0.0

$node_(5) set X_ 600.0
$node_(5) set Y_ 5.0
$node_(5) set Z_ 0.0

$node_(6) set X_ 750.0
$node_(6) set Y_ 5.0
$node_(6) set Z_ 0.0

$node_(7) set X_ 900.0
$node_(7) set Y_ 5.0
$node_(7) set Z_ 0.0

$node_(8) set X_ 5.0
$node_(8) set Y_ 250.0
$node_(8) set Z_ 0.0

$node_(9) set X_ 150.0
$node_(9) set Y_ 250.0
$node_(9) set Z_ 0.0

$node_(10) set X_ 300.0
$node_(10) set Y_ 250.0
$node_(10) set Z_ 0.0

$node_(11) set X_ 450.0
$node_(11) set Y_ 250.0
$node_(11) set Z_ 0.0

$node_(12) set X_ 600.0
$node_(12) set Y_ 250.0
$node_(12) set Z_ 0.0

$node_(13) set X_ 750.0
$node_(13) set Y_ 250.0
$node_(13) set Z_ 0.0

$node_(14) set X_ 900.0
$node_(14) set Y_ 250.0
$node_(14) set Z_ 0.0



#$ns at 15.0 "$node_(1) setdest 45.0 285.0 5.0"
#$ns at 19.0 "$node_(2) setdest 480.0 300.0 5.0"


# Set a TCP connection between node_(1) and node_(4)
set tcp [new Agent/TCP/Newreno]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns attach-agent $node_(0) $tcp
$ns attach-agent $node_(4) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at 10.0 "$ftp start"


# Generation of movements
$ns at 10.0 "$node_(0) setdest 400.0 127.0 5.0"

set udp1 [new Agent/UDP]
$ns attach-agent $node_(0) $udp1
set null1 [new Agent/Null]
$ns attach-agent $node_(11) $null1
$ns connect $udp1 $null1
$udp1 set fid_ 2
#Setup a CBR over UDP connection
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set type_ CBR
$ns at 30 "$cbr1 start"


#set tcp [new Agent/TCP/Newreno]
#$tcp set class_ 2
#set sink [new Agent/TCPSink]
#$ns attach-agent $node_(1) $tcp
#$ns attach-agent $node_(2) $sink
#$ns connect $tcp $sink
#set ftp [new Application/FTP]
#$ftp attach-agent $tcp
#$ns at 10.0 "$ftp start"

# Printing the window size
proc plotWindow {
tcpSource file
} {

global ns
set time 0.01
set now [$ns now]
set cwnd [$tcpSource set cwnd_]
puts $file "$now $cwnd"
$ns at [expr $now+$time] "plotWindow $tcpSource $file"
}
$ns at 10.0 "plotWindow $tcp $windowVsTime2"

# Define node initial position in nam
for {
set i 0
} {
$i < $val(nn)
} {
 incr i
} {

# 30 defines the node size for nam
$ns initial_node_pos $node_($i) 30

}

# Telling nodes when the simulation ends
for {
set i 0
} {
$i < $val(nn)
} {
 incr i
} {

    $ns at $val(stop) "$node_($i) reset";

}

# ending nam and the simulation
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 100.01 "puts \"end simulation\" ; $ns halt"
proc stop {

} {

    global ns tracefd namtrace
    $ns flush-trace
    close $tracefd
    close $namtrace
exec nam wirelessf.nam &

#exec xgraph wireless1.tr &
exit 0

}

$ns run
