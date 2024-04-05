/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006,2007 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#include "ns3/command-line.h"
#include "ns3/wifi-mac-header.h"

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




using namespace ns3;
using namespace std;


NS_LOG_COMPONENT_DEFINE ("WifiScriptExample"); // Definir el componente de registro

int devrx_packets = 0;
int devtxAP_packets = 0;
int devrxAP_packets = 0;
int devtx_packets = 0;
int phyrx0k_packets = 0;
int phyrxerrortrace_packets = 0;
int phytx_packets = 0;
int retryCount = 0;


bool g_verbose = false;


//añadir nº estaciones, tamaño red
bool useARF=true;
std::string  transmisionRate = "1Mbps";
double inicioScript = 0;
double finScript = 3;
double rxNoise = 5;




void
DevTxTrace (std::string context, Ptr<const Packet> p) {
    devtx_packets++;
    if (g_verbose) {
    std::cout << " TX p: " << *p << std::endl;
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
    phyrx0k_packets++;

   if (g_verbose) 
    {
      std::cout << "PHYRXOK mode=" << mode << " snr=" << snr << " " << *packet << std::endl;
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

  if (!g_verbose)
    {
      std::cout << "PHYTX mode=" << mode << " " << *packet << std::endl;
    }
}


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




int main (int argc, char *argv[])
{
  //DEfault values

  // Establecer el nivel de registro predeterminado para mostrar mensajes
  LogComponentEnable ("WifiScriptExample", LOG_LEVEL_ALL);

  CommandLine cmd (__FILE__);
  cmd.AddValue ("verbose", "Print trace information if true", g_verbose);
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
  positionAlloc->Add (Vector (1, 0, 0));  // Añade una pos para el segundo nodo
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

  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTraceAP));
  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacRx", MakeCallback (&DevRxTraceAP));

  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxOk", MakeCallback (&PhyRxOkTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxError", MakeCallback (&PhyRxErrorTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/Tx", MakeCallback (&PhyTxTrace));

  // "/NodeList/[i]/DeviceList/[i]/$ns3::WaveNetDevice/PhyEntities/[i]



  AthstatsHelper athstats;
  athstats.EnableAthstats ("athstats-sta", stas);
  athstats.EnableAthstats ("athstats-ap", ap);

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
    std::cout << "retransmissions: " << retryCount << " " << std::endl;






// Agregar registro al final de la simulación

  //NS_LOG_UNCOND ("Simulación finalizada"); // Agregar registro al final de la simulación

  Simulator::Destroy ();

  return 0;


}

/*
Estos callbacks en el script de ejemplo "wifi-ap" de ns-3 están diseñados para rastrear eventos específicos en la capa MAC y la capa PHY de un dispositivo Wi-Fi. Veamos lo que hace cada uno de estos callbacks:

DevTxTrace:

Se activa cuando un paquete es transmitido por el dispositivo (en la capa MAC).
Incrementa el contador devtx_packets.

DevRxTrace:

Se activa cuando un paquete es recibido por el dispositivo (en la capa MAC).
Incrementa el contador devrx_packets.

PhyRxOkTrace:
Se activa cuando la capa PHY recibe un paquete correctamente.
Incrementa el contador phyrx0k_packets.
Si g_verbose es verdadera, imprime el modo Wi-Fi utilizado (mode), la relación señal a ruido (snr), y otros detalles del paquete.

PhyRxErrorTrace:
Se activa cuando ocurre un error en la recepción de un paquete en la capa PHY.
Incrementa el contador phyrxerrortrace_packets.
Si g_verbose es verdadera, imprime la relación señal a ruido (snr), detalles del paquete y un mensaje adicional "ERROR EN TRAZA".

PhyTxTrace:
Se activa cuando la capa PHY comienza a transmitir un paquete.
Incrementa el contador phytx_packets.
Si g_verbose es verdadera, imprime el modo Wi-Fi utilizado (mode) y detalles del paquete transmitido.


PhyStateTrace:
Se activa para rastrear los cambios de estado en la capa PHY (por ejemplo, cambio de estado a IDLE, TX, RX, etc.).
Incrementa el contador phystate_packets.
Si g_verbose es verdadera, imprime el nuevo estado (state), el tiempo de inicio del estado (start), y la duración del estado (duration).
Estos callbacks son extremadamente útiles para el diagnóstico y análisis del comportamiento de las comunicaciones Wi-Fi en el simulador. La variable g_verbose permite a los usuarios activar o desactivar la salida detallada, lo que es útil para no saturar la consola con mensajes si sólo se está interesado en las estadísticas y no en los detalles de cada paquete.
*/





