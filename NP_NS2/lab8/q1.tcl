set val(chan)           Channel/WirelessChannel    ;#Channel Type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq
set val(nn)             2                          ;# number of mobilenodes
set val(rp)             AODV                       ;# routing protocol
#set val(rp)             DSR                       ;# routing protocol
set val(x)		500
set val(y)		500

# Initialize Global Variables
set ns_		[new Simulator]
set tracefd     [open wireless_mitf.tr w]
$ns_ trace-all $tracefd

set namtrace [open wireless_mitf.nam w]
$ns_ namtrace-all-wireless $namtrace $val(x) $val(y)

# set up topography object
set topo       [new Topography]

$topo load_flatgrid $val(x) $val(y)

# Create God
create-god $val(nn)

# New API to config node: 
# 1. Create channel (or multiple-channels);
# 2. Specify channel in node-config (instead of channelType);
# 3. Create nodes for simulations.

# Create channel #1 and #2
set chan_1_ [new $val(chan)]
set chan_2_ [new $val(chan)]

# Create node(0) "attached" to channel #1

# configure node, please note the change below.
$ns_ node-config -adhocRouting $val(rp) \
		-llType $val(ll) \
		-macType $val(mac) \
		-ifqType $val(ifq) \
		-ifqLen $val(ifqlen) \
		-antType $val(ant) \
		-propType $val(prop) \
		-phyType $val(netif) \
		-topoInstance $topo \
		-agentTrace ON \
		-routerTrace ON \
		-macTrace ON \
		-movementTrace OFF \
		-channel $chan_1_ 

set node_(0) [$ns_ node]

# node_(1) can also be created with the same configuration, or with a different
# channel specified.
# Uncomment below two lines will create node_(1) with a different channel.
#  $ns_ node-config \
#		 -channel $chan_2_ 

# set node_(1) [$ns_ node]
# set node_(2) [$ns_ node]
set node_(1) [$ns_ node]


$node_(0) random-motion 0
# $node_(1) random-motion 0
# $node_(2) random-motion 0
$node_(1) random-motion 0

for {set i 0} {$i < $val(nn)} {incr i} {
	$ns_ initial_node_pos $node_($i) 20
}

#
# Provide initial (X,Y, for now Z=0) co-ordinates for mobilenodes
#
$node_(0) set X_ 1.0
$node_(0) set Y_ 1.0
$node_(0) set Z_ 0.0

# $node_(1) set X_ 80.0
# $node_(1) set Y_ 50.0
# $node_(1) set Z_ 0.0

# $node_(2) set X_ 50.0
# $node_(2) set Y_ 20.0
# $node_(2) set Z_ 0.0

$node_(1) set X_ 100.0
$node_(1) set Y_ 100.0
$node_(1) set Z_ 0.0


$node_(0) radius 2
$node_(1) radius 2

$ns_ at 3.0 "$node_(0) setdest 400.0 400.0 50.0"
$ns_ at 3.0 "$node_(1) setdest 1.0 1.0 50.0"

# Node_(1) then starts to move away from node_(0)
#$ns_ at 20.0 "$node_(1) setdest 490.0 480.0 30.0" 

# Setup traffic flow between nodes
# TCP connections between node_(0) and node_(1)

set tcp [new Agent/TCP]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns_ attach-agent $node_(0) $tcp
$ns_ attach-agent $node_(1) $sink
$ns_ connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns_ at 3.0 "$ftp start" 

#
# Tell nodes when the simulation ends
#
# for {set i 0} {$i < $val(nn) } {incr i} {
#     $ns_ at 30.0 "$node_($i) reset";
# }
$ns_ at 30.0 "stop"
$ns_ at 30.01 "puts \"NS EXITING...\" ; $ns_ halt"
proc stop {} {
    global ns_ tracefd
    $ns_ flush-trace
    close $tracefd
    exec nam wireless_mitf.nam
    exit 0
}

puts "Starting Simulation..."
$ns_ run
