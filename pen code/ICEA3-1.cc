#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/csma-module.h"
#include "ns3/drop-tail-queue.h"
#include "ns3/constant-position-mobility-model.h"

using namespace ns3;

int main(int argc,char *argv[])
{

LogComponentEnable("UdpEchoClientApplication",LOG_LEVEL_INFO);
LogComponentEnable("UdpEchoServerApplication",LOG_LEVEL_INFO);


NodeContainer ptpNodes;
ptpNodes.Create(4);

NodeContainer topCsmaNodes;
topCsmaNodes.Create(3);
topCsmaNodes.Add(ptpNodes.Get(1));

NodeContainer bottomCsmaNodes;
bottomCsmaNodes.Add(ptpNodes.Get(2));
bottomCsmaNodes.Create(3);




//set node positions
Vector temp0(5,0,0);
Ptr<Node> n0=topCsmaNodes.Get(0);
Ptr<ConstantPositionMobilityModel> p0=n0-> GetObject<ConstantPositionMobilityModel>();
p0=CreateObject<ConstantPositionMobilityModel>();
n0->AggregateObject(p0);
p0->SetPosition(temp0);


Vector temp1(10,5,0);
Ptr<Node> n1=topCsmaNodes.Get(1);
Ptr<ConstantPositionMobilityModel>p1=n1-> GetObject<ConstantPositionMobilityModel>();
p1=CreateObject<ConstantPositionMobilityModel>();
n1->AggregateObject(p1);
p1->SetPosition(temp1);


Vector temp2(15,10,0);
Ptr<Node> n2=topCsmaNodes.Get(2);
Ptr<ConstantPositionMobilityModel>p2=n2-> GetObject<ConstantPositionMobilityModel>();
p2=CreateObject<ConstantPositionMobilityModel>();
n2->AggregateObject(p2);
p2->SetPosition(temp2);

Vector temp3(20,10,0);
Ptr<Node> n3=ptpNodes.Get(1);
Ptr<ConstantPositionMobilityModel>p3=n3-> GetObject<ConstantPositionMobilityModel>();
p3=CreateObject<ConstantPositionMobilityModel>();
n3->AggregateObject(p3);
p3->SetPosition(temp3);

Vector temp4(15,15,0);
Ptr<Node> n4=ptpNodes.Get(0);
Ptr<ConstantPositionMobilityModel>p4=n4-> GetObject<ConstantPositionMobilityModel>();
p4=CreateObject<ConstantPositionMobilityModel>();
n4->AggregateObject(p4);
p4->SetPosition(temp4);

Vector temp5(25,10,0);
Ptr<Node> n5=ptpNodes.Get(2);
Ptr<ConstantPositionMobilityModel>p5=n5-> GetObject<ConstantPositionMobilityModel>();
p5=CreateObject<ConstantPositionMobilityModel>();
n5->AggregateObject(p5);
p5->SetPosition(temp5);

Vector temp6(35,0,0);
Ptr<Node> n6=ptpNodes.Get(3);
Ptr<ConstantPositionMobilityModel>p6=n6-> GetObject<ConstantPositionMobilityModel>();
p6=CreateObject<ConstantPositionMobilityModel>();
n6->AggregateObject(p6);
p6->SetPosition(temp6);

Vector temp7(20,20,0);
Ptr<Node> n7=bottomCsmaNodes.Get(1);
Ptr<ConstantPositionMobilityModel>p7=n7-> GetObject<ConstantPositionMobilityModel>();
p7=CreateObject<ConstantPositionMobilityModel>();
n7->AggregateObject(p7);
p7->SetPosition(temp7);

Vector temp8(25,20,0);
Ptr<Node> n8=bottomCsmaNodes.Get(2);
Ptr<ConstantPositionMobilityModel>p8=n8-> GetObject<ConstantPositionMobilityModel>();
p8=CreateObject<ConstantPositionMobilityModel>();
n8->AggregateObject(p8);
p8->SetPosition(temp8);


Vector temp9(30,20,0);
Ptr<Node> n9=bottomCsmaNodes.Get(3);
Ptr<ConstantPositionMobilityModel>p9=n9-> GetObject<ConstantPositionMobilityModel>();
p9=CreateObject<ConstantPositionMobilityModel>();
n9->AggregateObject(p9);
p9->SetPosition(temp9);


PointToPointHelper ptp1;
ptp1.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
ptp1.SetChannelAttribute("Delay",StringValue("2ms"));

PointToPointHelper ptp2;
ptp2.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
ptp2.SetChannelAttribute("Delay",StringValue("2ms"));

PointToPointHelper ptp3;
ptp3.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
ptp3.SetChannelAttribute("Delay",StringValue("2ms"));

CsmaHelper csma1;
csma1.SetChannelAttribute("DataRate",StringValue("100Mbps"));
csma1.SetChannelAttribute("Delay",TimeValue(NanoSeconds(6560)));

CsmaHelper csma2;
csma2.SetChannelAttribute("DataRate",StringValue("100Mbps"));
csma2.SetChannelAttribute("Delay",TimeValue(NanoSeconds(6560)));

//Install Protocol
InternetStackHelper stack;
stack.Install(topCsmaNodes);
stack.Install(bottomCsmaNodes);
stack.Install(ptpNodes.Get(0));
stack.Install(ptpNodes.Get(3));


//connect point to point cable with our nodes
NetDeviceContainer ptpDevice1,ptpDevice2,ptpDevice3,csmaDevice1,csmaDevice2;
ptpDevice1=ptp1.Install(ptpNodes.Get(0),ptpNodes.Get(1));
ptpDevice2=ptp2.Install(ptpNodes.Get(1),ptpNodes.Get(2));
ptpDevice3=ptp3.Install(ptpNodes.Get(2),ptpNodes.Get(3));
csmaDevice1 =csma1.Install(topCsmaNodes);
csmaDevice2 =csma2.Install(bottomCsmaNodes);



//Creating Ip Adrress
Ipv4AddressHelper address1;
address1.SetBase("192.168.1.0","255.255.255.0");

Ipv4AddressHelper address2;
address2.SetBase("192.168.2.0","255.255.255.0");

Ipv4AddressHelper address3;
address3.SetBase("192.168.3.0","255.255.255.0");

Ipv4AddressHelper address4;
address4.SetBase("192.168.4.0","255.255.255.0");

Ipv4AddressHelper address5;
address5.SetBase("192.168.5.0","255.255.255.0");

Ipv4GlobalRoutingHelper::PopulateRoutingTables();

//Assign Ip Address 
Ipv4InterfaceContainer csmaInterface1=address1.Assign(csmaDevice1);
Ipv4InterfaceContainer csmaInterface2=address2.Assign(csmaDevice2);
Ipv4InterfaceContainer ptpInterface1=address4.Assign(ptpDevice1);
Ipv4InterfaceContainer ptpInterface2=address3.Assign(ptpDevice2);
Ipv4InterfaceContainer ptpInterface3=address5.Assign(ptpDevice3);





//Create applications to monitor the packet transfer
UdpEchoServerHelper echoServer(9);
ApplicationContainer serverApp=echoServer.Install(ptpNodes.Get(1));
serverApp.Start(Seconds(1.0));
serverApp.Stop(Seconds(10.0));


UdpEchoClientHelper echoClient(ptpInterface2.GetAddress(0),9);
echoClient.SetAttribute("MaxPackets",UintegerValue(1));
echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
echoClient.SetAttribute("PacketSize",UintegerValue(1024));

ApplicationContainer clientApp=echoClient.Install(bottomCsmaNodes.Get(3));
clientApp.Start(Seconds(1.0));
clientApp.Stop(Seconds(10.0));



//TCP server
PacketSinkHelper sink("ns3::TcpSocketFactory",Address(InetSocketAddress(Ipv4Address::GetAny(),10)));
ApplicationContainer tcpserver=sink.Install(ptpNodes.Get(0));
tcpserver.Start(Seconds(1.0));
tcpserver.Stop(Seconds(10.0));

//TCP client
OnOffHelper onOff("ns3::TcpSocketFactory",Address(InetSocketAddress(Ipv4Address(ptpInterface1.GetAddress(0)),10)));
onOff.SetAttribute("OnTime",StringValue("ns3::ConstantRandomVariable[Constant=1]"));
onOff.SetAttribute("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
onOff.SetAttribute("DataRate",StringValue("2Mbps"));
onOff.SetAttribute("PacketSize",UintegerValue(1024));

ApplicationContainer tcpclient=onOff.Install(ptpNodes.Get(3));
tcpclient.Start(Seconds(1.0));
tcpclient.Stop(Seconds(10.0));

//UDP server
UdpServerHelper udpServer(11);
ApplicationContainer server=udpServer.Install(ptpNodes.Get(1));
server.Start(Seconds(1.0));
server.Stop(Seconds(1.0));

//UDP client
UdpClientHelper UdpClient(ptpInterface2.GetAddress(0),11);
UdpClient.SetAttribute("MaxPackets",UintegerValue(2));
UdpClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
UdpClient.SetAttribute("PacketSize",UintegerValue(512));

ApplicationContainer client=UdpClient.Install(topCsmaNodes.Get(0));
client.Start(Seconds(1.0));
client.Stop(Seconds(10.0));



AnimationInterface anim("ICEA3-1.xml");

anim.UpdateNodeDescription(4,"A-UDP Client");
anim.UpdateNodeDescription(1,"R-UDP Echo Server");
anim.UpdateNodeDescription(0,"I-TCP Server");
anim.UpdateNodeDescription(5,"B");
anim.UpdateNodeDescription(2,"H-UDP Server");
anim.UpdateNodeDescription(6,"C");
anim.UpdateNodeDescription(3,"G-TCP Client");
anim.UpdateNodeDescription(7,"D");
anim.UpdateNodeDescription(8,"E");
anim.UpdateNodeDescription(9,"F-UDP Echo Client");

Simulator::Run();
Simulator::Destroy();

return 0;
}
