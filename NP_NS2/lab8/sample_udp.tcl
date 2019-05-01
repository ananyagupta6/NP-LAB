# simple-wireless.tcl
# A simple example for wireless simulation
#
#===================================================================
#===
# Define options
#
#===================================================================
#===
set val(chan) Channel/WirelessChannel ;# channel type
set val(prop) Propagation/TwoRayGround ;# radio-propagation model
set val(netif) Phy/WirelessPhy ;# network interface type
set val(mac) Mac/802_11 ;# MAC type
set val(ifq) Queue/DropTail/PriQueue ;# interface queue type
set val(ll) LL ;# link layer type
set val(ant) Antenna/OmniAntenna ;# antenna model
set val(ifqlen) 50 ;# max packet in ifq
set val(nn) 3 ;# number of mobilenodes
set val(rp) AODV ;# routing protocol
#
#===================================================================
#===
# Main Program
#
#===================================================================
#===

#
# Initialize Global Variables
#
set ns_ [new Simulator]
set tracefd [open simple.tr w]
$ns_ trace-all $tracefd
set namtrace [open out.nam w]
$ns_ namtrace-all-wireless $namtrace 500 500
# set up topography object
set topo [new Topography]
$topo load_flatgrid 500 500
#
# Create God
#
create-god $val(nn)
#
# Create the specified number of mobilenodes [$val(nn)] and "attach" them
# to the channel.
# Here 3 nodes are created : node(0) and node(1) and node(2)
# configure node
$ns_ node-config -adhocRouting $val(rp) \
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
-movementTrace OFF
for {set i 0} {$i < $val(nn) } {incr i} {
set node_($i) [$ns_ node]
$node_($i) random-motion 0 ;# disable random motion
}
#
# Provide initial (X,Y, for now Z=0) co-ordinates for mobilenodes
#
$node_(0) set X_ 5.0
$node_(0) set Y_ 2.0
$node_(0) set Z_ 0.0
$node_(1) set X_ 39.0
$node_(1) set Y_ 38.0
$node_(1) set Z_ 0.0
$node_(2) set X_ 35.5
$node_(2) set Y_ 34.0
$node_(2) set Z_ 0.0

#
# Now produce some simple node movements
# Node_(1) starts to move towards node_(0)
#
$ns_ at 10.0 "$node_(1) setdest 60.0 18.0 1.0"
$ns_ at 10.0 "$node_(0) setdest 20.0 18.0 1.0"
$ns_ at 10.0 "$node_(2) setdest 100.0 18.0 1.0"
# Node_(1) then starts to move away from node_(0)
#$ns_ at 100.0 "$node_(1) setdest 490.0 480.0 15.0"
# Setup traffic flow between nodes
# TCP connections between node_(0) and node_(1)
set udp [new Agent/UDP]
set sink [new Agent/Null]
$ns_ attach-agent $node_(0) $udp
$ns_ attach-agent $node_(2) $sink
$ns_ connect $udp $sink
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$ns_ at 5.0 "$cbr start"
$ns_ at 50.0 "$cbr stop"
# Tell nodes when the simulation ends
#
for {set i 0} {$i < $val(nn) } {incr i} {
$ns_ at 150.0 "$node_($i) reset";
}
$ns_ at 150.0 "stop"
$ns_ at 150.01 "puts \"NS EXITING...\" ; $ns_ halt"
proc stop {} {
global ns_ tracefd
$ns_ flush-trace
close $tracefd
exec nam out.nam &
}
puts "Starting Simulation..."
$ns_ run