  /* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 Huazhong University of Science and Technology, Dian Group
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Pengyu Liu <eic_lpy@hust.edu.cn>
 *         Hao Yin <haoyin@uw.edu>

 TODO
 no tener en cuenta los primeros segundos de la simulacion
 bit de retransmision en cabecera del paquete para diferenciarlo

 */

#include "ns3/core-module.h"
#include "ns3/ns3-ai-module.h"
#include "ns3/log.h"
#include "ns3/wifi-phy.h"
#include "ns3/command-line.h"
#include "ns3/double.h"
#include "ns3/uinteger.h"
#include "ns3/config.h"
#include "ns3/boolean.h"
#include "ns3/string.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/mobility-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/mobility-model.h"
#include "ns3/packet-socket-helper.h"
#include "ns3/packet-socket-address.h"
#include "ns3/athstats-helper.h"
#include "ns3/log.h"
#include <string>  // Required for std::string
#include <iostream>
#include "ns3/buildings-helper.h"
#include "ns3/hybrid-buildings-propagation-loss-model.h"
#include <sstream>
#include "ns3/packet-sink-helper.h"

#include <map>


#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/ipv4.h"
#include "ns3/trace-helper.h"
#include "ns3/csma-helper.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-flow-classifier.h"
#include "ns3/table-based-error-rate-model.h"

using namespace std;
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ns3ai_data_collection");

int devrx_packets = 0;
int devtxAP_packets = 0;
int devrxAP_packets = 0;
int devtx_packets = 0;
int phyrx0k_packets = 0;
int phyrxerrortrace_packets = 0;
int phytx_packets = 0;
uint32_t retransmissionCount = 0;


bool g_verbose = false;


//añadir nº estaciones, tamaño red
bool useARF=false;
std::string  transmisionRate = "5Mbps";
double inicioScript = 0;
double finScript = 2;
double rxNoise = 10;





void MyPacketReceiveCallback(std::string context, ns3::Ptr<const ns3::Packet> packet, uint16_t channelFreq, ns3::WifiTxVector txVector, ns3::MpduInfo aMpdu, uint16_t staId) {
    ns3::WifiMacHeader macHeader;
    if (packet->PeekHeader(macHeader)) {
//std::cout << " ABECERA " << macHeader << ""<<std::endl;

        if (macHeader.IsRetry()) {
        	retransmissionCount ++;
        }
    }
}

void DropCallback(std::string context, Ptr<const Packet> packet) {



	WifiMacHeader macHeader;

		    if (packet->PeekHeader(macHeader)) {

		        if (macHeader.IsRetry()) {
		            retransmissionCount++;
		        }
		    }

}

void
DevTxTrace (std::string context, Ptr<const Packet> p)
{


  devtx_packets++;

  if (g_verbose)
  {
    std::cout << " TX p: " << *p << ""<<std::endl;
    std::cout << " CONTEXT:" << context;
  }
}

void
DevRxTrace (std::string context, Ptr<const Packet> p)
{
  devrx_packets++;
  

  if (g_verbose)
  {
    std::cout << " RX p: " << *p << std::endl;
  }
}


void
DevTxTraceAP (std::string context, Ptr<const Packet> p)
{

  devtxAP_packets++;

  if (g_verbose)
  {
    std::cout << " TXAp p: " << *p << ""<<std::endl;
  }
}
void
DevRxTraceAP (std::string context, Ptr<const Packet> p)
{
  devrxAP_packets++;

  if (g_verbose)
  {
    std::cout << " RXAp p: " << *p << std::endl;
  }
}


void
PhyRxOkTrace (std::string context, Ptr<const Packet> packet, double snr, WifiMode mode, WifiPreamble preamble)
{

  
  if (g_verbose)
  {
    std::cout << "PHYRXOK mode=" << mode << " snr=" << snr << " " << *packet <<  std::endl;
  }
}
void
PhyRxErrorTrace (std::string context, Ptr<const Packet> packet, double snr)
{
    phyrxerrortrace_packets++;

  if (g_verbose)
  {
    std::cout << "PHYRXERROR snr=" << snr << " " << *packet << std::endl;
        std::cout << "ERROR EN TRAZA "<<std::endl;

  }
}

void
PhyTxTrace (std::string context, Ptr<const Packet> packet, WifiMode mode, WifiPreamble preamble, uint8_t txPower)
{


    phytx_packets++;

  //std::cout << "HEADER:=" <<  macHeader << std::endl;

  // std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  //  std::cout << "PHYTX mode=" <<  mode << std::endl;
  //   std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  //   std::cout << "PAQUETE:" << *packet << std::endl;
  //   std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  //   // std::cout << "WIFIMODE:" << mode << std::endl;
  //   std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  //   std::cout << "PREAMBLE:" << preamble << std::endl;
    
}


// void
// PhyTxTracenNetDevice (std::string context, Ptr< const Packet > packet, uint16_t channelFreqMhz, WifiTxVector txVector, MpduInfo aMpdu, uint16_t staId){

//      // std::cout << " PAQUETE:" << *packet << std::endl;


// }

// void
// snifferTx (std::string context, const Ptr< const Packet > packet, uint16_t channelFreqMhz, WifiTxVector txVector, MpduInfo aMpdu, uint16_t staId){

//       std::cout << "TX Vector:" << txVector << " PAQUETE:" << *packet << "MpduInfo:"<< aMpdu << std::endl;

// }



static void
SetPosition (Ptr<Node> node, Vector position)
{
  Ptr<MobilityModel> mobility = node->GetObject<MobilityModel> ();
  mobility->SetPosition (position);
}

static Vector
GetPosition (Ptr<Node> node)
{
  Ptr<MobilityModel> mobility = node->GetObject<MobilityModel> ();
  return mobility->GetPosition ();
}

static void
AdvancePosition (Ptr<Node> node)
{
  Vector pos = GetPosition (node);
  pos.x += 5.0;
  if (pos.x >= 210.0)
  {
    return;
  }
  SetPosition (node, pos);

  Simulator::Schedule (Seconds (1.0), &AdvancePosition, node);
}

YansWifiPhyHelper
WiFiPhyConfig ()
{
  //NS_LOG_INFO ("Configuring physical layer.");
  // Configure Wi-Fi for AP and stations
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  channel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  // channel.AddPropagationLoss ("ns3::LogDistancePropagationLossModel", "Exponent",
  //                             DoubleValue (3.5));
  // channel.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5.15e9),
  //                             "SystemLoss", DoubleValue (1), "MinLoss", DoubleValue (0));

  YansWifiPhyHelper phy;
  phy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
  phy.SetChannel (channel.Create ());
  phy.SetErrorRateModel ("ns3::TableBasedErrorRateModel");
  phy.Set ("TxGain", DoubleValue (1.0));
  phy.Set ("RxGain", DoubleValue (1.0));
  phy.Set ("TxPowerLevels", UintegerValue (1));
  double txPower = 15.0; // dbm 
  phy.Set ("TxPowerEnd", DoubleValue (txPower));
  phy.Set ("TxPowerStart", DoubleValue (txPower));
  phy.Set ("RxNoiseFigure", DoubleValue (rxNoise)); //mas importante
  phy.Set ("ChannelNumber", UintegerValue (46));
  phy.Set ("ChannelWidth", UintegerValue (40));
  phy.Set ("MaxSupportedTxSpatialStreams", UintegerValue (1));
  phy.Set ("MaxSupportedRxSpatialStreams", UintegerValue (1));
  //phy.Set ("NumberOfAntennas", UintegerValue (2));
  return phy;
}

void
showStadistics(){

    std::cout << "devrx_packets: " << devrx_packets << " " << std::endl;
    std::cout << "devtx-packets: " << devtx_packets << " "  << std::endl;
    std::cout << "phyrx0k_packets: " << phyrx0k_packets << " " << std::endl;
    std::cout << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << " "  << std::endl;
    std::cout << "phytx_packets: " << phytx_packets << " "  << std::endl;

}

static void
printPositionNodes(ns3::Ptr<ns3::ListPositionAllocator> listNodes) 
{
    for (uint32_t i = 0; i < listNodes->GetSize(); i++) 
    {
        ns3::Vector position = listNodes->GetNext();
        std::cout << "Nodo " << i << ": (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
    }
}


MobilityHelper
MobilityConfig ()
{
  NS_LOG_INFO ("Configuring mobility.");
  MobilityHelper mobility;
  //double distanceToRx = 300; // meters

  // Ptr<RandomDiscPositionAllocator> positionAlloc = CreateObject<RandomDiscPositionAllocator> ();
  // positionAlloc->SetX (0);
  // positionAlloc->SetY (0);
  // positionAlloc->SetZ (0);
  // Ptr<RandomVariableStream> rho = CreateObject<UniformRandomVariable> ();
  // rho->SetAttribute ("Min", DoubleValue (0));
  // rho->SetAttribute ("Max", DoubleValue(distanceToRx));
  // positionAlloc->SetRho (rho);
  //positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  //positionAlloc->Add (Vector (distanceToRx, 0.0, 0.0));

  mobility.SetPositionAllocator (
      "ns3::RandomDiscPositionAllocator", "X", StringValue ("0.0"), "Y", StringValue ("0.0"), "Z",
      StringValue ("0.0"), "Rho",
      StringValue ("ns3::UniformRandomVariable[Min=5|Max=30]")); //min and max in meters
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  return mobility;
}


/**
 * \brief Shared memory to store a and b.
 *
 * This struct is the environment (in this example, contain 'a' and 'b')
 * shared between ns-3 and python with the same shared memory
 * using the ns3-ai model.
 */
struct Env
{
    int devrx_packets;
    int devtxAP_packets;
    int devrxAP_packets;
    int devtx_packets;
    int phyrx0k_packets;
    int phyrxerrortrace_packets;
    int phytx_packets;
}Packed;

/**
 * \brief Shared memory to store action c.
 *
 * This struct is the result (in this example, contain 'c')
 * calculated by python and put back to ns-3 with the shared memory.
 */
struct Act
{
    int c;
}Packed;

/**
 * \brief A class to calculate COLLECTOR (a plus b).
 *
 * This class shared memory with python by the same id,
 * and got two variable a and b, and then put them into the shared memory
 * using python to calculate c=a+b, and got c from python.
 */
class COLLECTOR : public Ns3AIRL<Env, Act>
{
public:
    COLLECTOR(uint16_t id);
    int Func(int devrx_packets,
    int devtxAP_packets,
    int devrxAP_packets,
    int devtx_packets,
    int phyrx0k_packets,
    int phyrxerrortrace_packets,
    int phytx_packets);
};

/**
 * \brief Link the shared memory with the id and set the operation lock
 *
 * \param[in] id  shared memory id, should be the same in python and ns-3
 */
COLLECTOR::COLLECTOR(uint16_t id) : Ns3AIRL<Env, Act>(id) {
    SetCond(2, 0);      ///< Set the operation lock (even for ns-3 and odd for python).
}


int COLLECTOR::Func(int devrx_packets,
    int devtxAP_packets,
    int devrxAP_packets,
    int devtx_packets,
    int phyrx0k_packets,
    int phyrxerrortrace_packets,
    int phytx_packets
                    )
{
    auto env = EnvSetterCond();     ///< Acquire the Env memory for writing
    //NS_LOG_DEBUG ("Env acquired, a is " << env->a << ", b is " << env->b);
    // env->a = a;
    // env->b = b;

    env->devrx_packets =devrx_packets;
    env->devtxAP_packets= devtxAP_packets;
    env->devrxAP_packets =devrxAP_packets;
    env->devtx_packets = devtx_packets;
    env->phyrx0k_packets = phyrx0k_packets;
    env->phyrxerrortrace_packets =phyrxerrortrace_packets;
    env->phytx_packets = phytx_packets;

    SetCompleted();                 ///< Release the memory and update conters
    NS_LOG_DEBUG ("Ver:" << (int)SharedMemoryPool::Get()->GetMemoryVersion(m_id));
    auto act = ActionGetterCond();  ///< Acquire the Act memory for reading
    int ret = act->c;
    std::cout << "Simulacion parada:  " << ret;
    
    GetCompleted();                 ///< Release the memory, roll back memory version and update conters
    NS_LOG_DEBUG ("Ver:" << (int)SharedMemoryPool::Get()->GetMemoryVersion(m_id));
    return ret;
}

int main(int argc, char *argv[])
{
    int memblock_key = 2333;        ///< memory block key, need to keep the same in the python script
    CommandLine cmd;
    // cmd.AddValue ("a","the value of a",a);
    // cmd.AddValue ("b","the value of b",b);
    cmd.AddValue ("key","memory block key",memblock_key);
    cmd.AddValue ("verbose", "Print trace information if true", g_verbose);
    cmd.AddValue ("finScript", "Establece el final del script", finScript);


    COLLECTOR collector(memblock_key);
      


    cmd.Parse (argc, argv);
  


  Packet::EnablePrinting ();

  WifiHelper wifi;
  //Use "g-2.4GHz" standard or "a-5GHz" standard


  wifi.SetStandard (ns3::WIFI_STANDARD_80211ac);


  if(useARF==true){
  //Use of ARF
  wifi.SetRemoteStationManager ("ns3::ArfWifiManager"); 

  //wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager","DataMode", StringValue("VhtMcs9")); 
  }
  

  MobilityHelper mobility;
  NodeContainer stas;
  NodeContainer ap;
  NetDeviceContainer staDevs;
  PacketSocketHelper packetSocket;


  //Position of the nodes
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0, 0, 0));  // Añade una pos para el primer nodo
  positionAlloc->Add (Vector (19, 0, 0));  // Añade una pos para el segundo nodo
  //positionAlloc->Add (Vector (0, 0.0, 0));  // Añade una pos para el tercer nodo 

  mobility.SetPositionAllocator (positionAlloc);

  //Crear una lista nueva donde sepa donde esta cada nodo
  stas.Create (1);
  ap.Create (1);

  // give packet socket powers to nodes.
  packetSocket.Install (stas);
  packetSocket.Install (ap);

  WifiMacHelper wifiMac;
  YansWifiPhyHelper wifiPhy;
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiPhy = WiFiPhyConfig();

  // //define propagation loss
  // wifiChannel.AddPropagationLoss ("ns3::HybridBuildingsPropagationLossModel");

  // wifiPhy.SetChannel (wifiChannel.Create ());
  Ssid ssid = Ssid ("wifi-default");
  // // setup stas.
   wifiMac.SetType ("ns3::StaWifiMac",
                    "ActiveProbing", BooleanValue (true),
                    "Ssid", SsidValue (ssid));
   staDevs = wifi.Install (wifiPhy, wifiMac, stas);
  //setup ap.
   wifiMac.SetType ("ns3::ApWifiMac",
                    "Ssid", SsidValue (ssid),"QosSupported",BooleanValue (true));

  
  wifi.Install (wifiPhy, wifiMac, ap);


  // Config::Set ("/NodeList/1/DeviceList/*/$ns3::WifiNetDevice/RemoteStationManager/"
  //              "$ns3::MinstrelHtWifiManager/UseVhtOnly",
  //              BooleanValue (true));
  


  //Set deadline and size of the queues (Default is 0.5 seconds)
  QueueSize size ("40Mp");

  Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/DeviceList/*/$ns3::WifiNetDevice/Mac/"
               "$ns3::ApWifiMac/Txop/$ns3::Txop/Queue/$ns3::WifiMacQueue/MaxDelay",
               TimeValue (Seconds (2)));

  //Set drop policy (default DropNewest)
  Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/DeviceList/*/$ns3::WifiNetDevice/Mac/"
               "$ns3::ApWifiMac/Txop/$ns3::Txop/Queue/$ns3::WifiMacQueue/DropPolicy",
               EnumValue (WifiMacQueue::DROP_OLDEST));

  Config::Set ("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/DeviceList/*/$ns3::WifiNetDevice/Mac/"
               "$ns3::ApWifiMac/Txop/$ns3::Txop/Queue/$ns3::WifiMacQueue/MaxSize",
               QueueSizeValue (size));
  



  // mobility.
  mobility.Install (stas);
  mobility.Install (ap);

  //obstacles
  BuildingsHelper::Install (stas);
  BuildingsHelper::Install (ap);


  // Simulator::Schedule (Seconds (1.0), &AdvancePosition, stas.Get (0));
  // Simulator::Schedule (Seconds (1.0), &AdvancePosition, stas.Get (1));



  //Conexion primera estacion
  PacketSocketAddress socket;


  socket.SetSingleDevice (staDevs.Get (0)->GetIfIndex ());
  //socket.SetPhysicalAddress (staDevs.Get (1)->GetAddress ());
  socket.SetPhysicalAddress (ap.Get (0)->GetDevice (0)->GetAddress ());  // Cambiado para apuntar al AP
  socket.SetProtocol (1);

  OnOffHelper onoff ("ns3::PacketSocketFactory", Address (socket));
  onoff.SetConstantRate (DataRate (transmisionRate));


   for (uint32_t i = 0; i < 3; ++i) {

    //Cambio de tasa de transmisión después de 10 segundos
   Simulator::Schedule (Seconds (0.1 * i), [&onoff,&collector]() {
    //showStadistics();
      
      collector.Func(devrx_packets,devtxAP_packets,devrxAP_packets,devtx_packets,phyrx0k_packets,phyrxerrortrace_packets,phytx_packets);

     //onoff.SetConstantRate (DataRate ("10Mbps"));
     
   });
  }
   

    

  // //Cambio de tasa de transmisión después de 20 segundos
  // Simulator::Schedule (Seconds (4.0), [&onoff]() {
  // onoff.SetConstantRate (DataRate ("4Mbps"));
  // });

  ApplicationContainer apps = onoff.Install (stas.Get (0));
  apps.Start (Seconds (inicioScript));
  apps.Stop (Seconds (finScript));
  

  Simulator::Stop (Seconds (finScript));

  Config::Connect ("/NodeList/0/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTrace));
  Config::Connect ("/NodeList/0/DeviceList/*/Mac/MacRx", MakeCallback (&DevRxTrace));
  //Config::Connect("/NodeList/*/DeviceList/*/Phy/MacTxDrop", MakeCallback(&CountRetransmissions));


  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTraceAP));
  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacRx", MakeCallback (&DevRxTraceAP));

  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxOk", MakeCallback (&PhyRxOkTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxError", MakeCallback (&PhyRxErrorTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/Phy/*/Tx", MakeCallback (&PhyTxTrace));


  Config::Connect("/NodeList/0/DeviceList/*/$ns3::WifiNetDevice/Phy/PhyTxEnd", MakeCallback(&DropCallback));



  ns3::Config::Connect("/NodeList/*/DeviceList/*/Phy/MonitorSnifferTx", ns3::MakeCallback(&MyPacketReceiveCallback));




  //NS_LOG_UNCOND ("Simulación iniciada"); // Agregar registro al inicio de la simulación


  Simulator::Run ();
printPositionNodes(positionAlloc);
std::cout << "Transmision rate: " << transmisionRate<< " " <<" RxNOise: " << rxNoise << " ARF: "<<  useARF <<" Incio script: "<< inicioScript << " Fin script: "<< finScript << std::endl;
    std::cout << "devrx_packets estacion: " << devrx_packets << " " << std::endl;
    std::cout << "devtx-packets estacion: " << devtx_packets << " "  << std::endl;

    std::cout << "devrx_packets punto acceso: " << devrxAP_packets << " " << std::endl;
    std::cout << "devtx-packets punto acceso: " << devtxAP_packets << " "  << std::endl;

    std::cout << "phyrx0k_packets: " << phyrx0k_packets << " " << std::endl;
    std::cout << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << " "  << std::endl;
    std::cout << "phytx_packets: " << phytx_packets << " "  << std::endl;
    std::cout << "RETRANSMISIONES: " << retransmissionCount << " "  << std::endl;



  //std::cout <<  "resultado suma total:" << "=" << collector.Func(devrx_packets,devtxAP_packets,devrxAP_packets,devtx_packets,phyrx0k_packets,phyrxerrortrace_packets,phytx_packets,phystate_packets) << std::endl;
  Simulator::Destroy ();
  collector.SetFinish();

  return 0;
  
}
