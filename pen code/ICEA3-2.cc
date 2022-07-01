 #include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/wifi-module.h"      
#include "ns3/mobility-module.h"  
#include "ns3/constant-position-mobility-model.h"   
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/csma-module.h"

using namespace ns3;
int main (int argc,char *argv[]){
	
LogComponentEnable("UdpClient",LOG_LEVEL_INFO);
LogComponentEnable("UdpServer",LOG_LEVEL_INFO);
	
NodeContainer ptpNodes;
ptpNodes.Create(4);

NodeContainer apNode=ptpNodes.Get(1);

NodeContainer staNodes; 
staNodes.Create(1);

NodeContainer csmaNodes;
csmaNodes.Add(ptpNodes.Get(2));
csmaNodes.Create(3);

Vector temp0(30,20,0);
Ptr<Node> n0=ptpNodes.Get(0);
Ptr<ConstantPositionMobilityModel>p0=n0->GetObject<ConstantPositionMobilityModel>();
p0=CreateObject<ConstantPositionMobilityModel>();
n0->AggregateObject(p0);
p0->SetPosition(temp0);


Vector temp1(30,40,0);
Ptr<Node> n1=ptpNodes.Get(1);
Ptr<ConstantPositionMobilityModel>p1=n1->GetObject<ConstantPositionMobilityModel>();
p1=CreateObject<ConstantPositionMobilityModel>();
n1->AggregateObject(p1);
p1->SetPosition(temp1);


Vector temp2(40,40,0);
Ptr<Node> n2=ptpNodes.Get(2);
Ptr<ConstantPositionMobilityModel>p2=n2->GetObject<ConstantPositionMobilityModel>();
p2=CreateObject<ConstantPositionMobilityModel>();
n2->AggregateObject(p2);
p2->SetPosition(temp2);

Vector temp3(40,60,0);
Ptr<Node> n3=ptpNodes.Get(3);
Ptr<ConstantPositionMobilityModel>p3=n3->GetObject<ConstantPositionMobilityModel>();
p3=CreateObject<ConstantPositionMobilityModel>();
n3->AggregateObject(p3);
p3->SetPosition(temp3);

Vector temp4(10,60,0);
Ptr<Node> n4=staNodes.Get(0);
Ptr<ConstantPositionMobilityModel> p4=n4->GetObject<ConstantPositionMobilityModel>();
p4=CreateObject<ConstantPositionMobilityModel>();
n4->AggregateObject(p4);
p4->SetPosition(temp4);

Vector temp5(50,30,0);
Ptr<Node> n5=csmaNodes.Get(1);
Ptr<ConstantPositionMobilityModel> p5=n5->GetObject<ConstantPositionMobilityModel>();
p5=CreateObject<ConstantPositionMobilityModel>();
n5->AggregateObject(p5);
p5->SetPosition(temp5);

Vector temp6(50,40,0);
Ptr<Node> n6=csmaNodes.Get(2);
Ptr<ConstantPositionMobilityModel> p6=n6->GetObject<ConstantPositionMobilityModel>();
p6=CreateObject<ConstantPositionMobilityModel>();
n6->AggregateObject(p6);
p6->SetPosition(temp6);

Vector temp7(50,50,0);
Ptr<Node> n7=csmaNodes.Get(3);
Ptr<ConstantPositionMobilityModel> p7=n7->GetObject<ConstantPositionMobilityModel>();
p7=CreateObject<ConstantPositionMobilityModel>();
n7->AggregateObject(p7);
p7->SetPosition(temp7);
	
InternetStackHelper stack;
stack.Install(ptpNodes);
stack.Install(staNodes);
stack.Install(csmaNodes.Get(1));
stack.Install(csmaNodes.Get(2));
stack.Install(csmaNodes.Get(3));

PointToPointHelper ptp1,ptp2,ptp3;

ptp1.SetDeviceAttribute("DataRate",StringValue("10Mbps"));
ptp1.SetChannelAttribute("Delay",StringValue("2ms"));

ptp2.SetDeviceAttribute("DataRate",StringValue("10Mbps"));
ptp2.SetChannelAttribute("Delay",StringValue("2ms"));

ptp3.SetDeviceAttribute("DataRate",StringValue("10Mbps"));
ptp3.SetChannelAttribute("Delay",StringValue("1ms"));

CsmaHelper csma;
csma.SetChannelAttribute("DataRate",StringValue("100Mbps"));
csma.SetChannelAttribute("Delay",TimeValue(NanoSeconds(6560)));

NetDeviceContainer device1,device2,device3,csmaDevice;
device1=ptp1.Install(ptpNodes.Get(0),ptpNodes.Get(1));
device2=ptp2.Install(ptpNodes.Get(1),ptpNodes.Get(2));
device3=ptp3.Install(ptpNodes.Get(2),ptpNodes.Get(3));
csmaDevice=csma.Install(csmaNodes);

YansWifiChannelHelper channel=YansWifiChannelHelper::Default();
YansWifiPhyHelper phy=YansWifiPhyHelper::Default();
phy.SetChannel(channel.Create());

WifiHelper wifi;
wifi.SetRemoteStationManager("ns3::AarfWifiManager");
Ssid ssid=Ssid("ns-3-ssid"); 
   
WifiMacHelper mac;
mac.SetType("ns3::StaWifiMac","Ssid",SsidValue(ssid),"ActiveProbing",BooleanValue(false));    

NetDeviceContainer staDevices;
staDevices=wifi.Install(phy,mac,staNodes);

mac.SetType("ns3::ApWifiMac","Ssid",SsidValue(ssid)); 
 
NetDeviceContainer apDevice;
apDevice=wifi.Install(phy,mac,apNode);  

MobilityHelper mobility;
mobility.SetPositionAllocator("ns3::GridPositionAllocator",
"MinX",DoubleValue(0.0),
"MinY",DoubleValue(0.0),
"DeltaX",DoubleValue(40.0),
"DeltaY",DoubleValue(40.0),
"GridWidth",UintegerValue(3),
"LayoutType",StringValue("RowFirst"));
    
mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel","Bounds",RectangleValue(Rectangle(-50,1000,-50,1000)));
mobility.Install(staNodes);  

Ipv4AddressHelper address1,address2,address3,address4,address5;
address1.SetBase("192.168.2.8","255.255.255.248");
address2.SetBase("192.168.2.0","255.255.255.248");
address3.SetBase("192.168.1.128","255.255.255.128");
address4.SetBase("192.168.1.0","255.255.255.128");
address5.SetBase("192.168.2.16","255.255.255.248");

Ipv4InterfaceContainer wifiInterface;
address5.Assign(apDevice);
address5.Assign(staDevices);
Ipv4InterfaceContainer SA=address1.Assign(device1);
Ipv4InterfaceContainer AR=address2.Assign(device2);
Ipv4InterfaceContainer RD=address3.Assign(device3);

Ipv4InterfaceContainer csmaInterface=address4.Assign(csmaDevice);

Ipv4GlobalRoutingHelper::PopulateRoutingTables();


UdpServerHelper echoServer1(10);

ApplicationContainer serverApp1=echoServer1.Install(ptpNodes.Get(3));
serverApp1.Start(Seconds(1.0));
serverApp1.Stop(Seconds(10.0));

UdpClientHelper echoClient1(RD.GetAddress(1),10);
echoClient1.SetAttribute("MaxPackets",UintegerValue(10));
echoClient1.SetAttribute("Interval",TimeValue(Seconds(0.5)));
echoClient1.SetAttribute("PacketSize",UintegerValue(1024));

ApplicationContainer clientApp1=echoClient1.Install(csmaNodes.Get(1));
clientApp1.Start(Seconds(2.0));
clientApp1.Stop(Seconds(15.0));  

AnimationInterface anim("ICEA3-2.xml");

anim.UpdateNodeDescription(ptpNodes.Get(0),"Subscriber Station");
anim.UpdateNodeDescription(ptpNodes.Get(1),"Access point");
anim.UpdateNodeDescription(ptpNodes.Get(2),"Router");
anim.UpdateNodeDescription(ptpNodes.Get(3),"D");

anim.UpdateNodeDescription(staNodes.Get(0),"Laptop");
   
anim.UpdateNodeDescription(csmaNodes.Get(1),"A");
anim.UpdateNodeDescription(csmaNodes.Get(2),"B");
anim.UpdateNodeDescription(csmaNodes.Get(3),"C");

ptp1.EnablePcapAll("AP->Router");  

Simulator::Run();
Simulator::Destroy();
	
return 0;
}