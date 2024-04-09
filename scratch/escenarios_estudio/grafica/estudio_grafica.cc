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
#include "ns3/random-walk-2d-mobility-model.h"  // Incluye la definición del modelo de movilidad
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
#include <fstream> // Para trabajar con archivos
#include <vector>
#include <numeric> // Para std::accumulate


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
int retransmissionCount = 0;

//calculo throughput
uint64_t totalBytesPhy = 0;
Time startTime = Seconds (5); // Empezar después de 5 segundos para evitar el periodo de estabilización
Time interval = Seconds (1); // Calcular el throughput cada segundo
std::vector<double> throughputValues;
double meanThroughputValue = 0;

//calculo transmission rate
uint64_t totalDataRate = 0; // Acumula las velocidades de transmisión
uint32_t totalPacketsTransmitted = 0; // Contador de paquetes transmitidos
std::vector<double> averageTransmissionRateValues;


bool g_verbose = false;
bool keepEvidences = false;



//añadir nº estaciones, tamaño red
bool useARF=false;
double inicioScript = 0;
double finScript = 30;
int posX = 80;
int paquetesPorSegundo = 732; //6Mbps por defecto
uint32_t numNodos = 100;
double rxNoise = 21;
uint32_t i = 0;

void
DevTxTrace (std::string context, Ptr<const Packet> p)
{

    //std::cout << "Paquete enviado desde: " << context << std::endl;


  devtx_packets++;

  if (g_verbose)
  {
    std::cout << " TX p: " << *p << ""<<std::endl;
    std::cout << " CONTEXT:" << context;
  }
}

void PrintNodePositions(NodeContainer *nodes) {
    std::cout << "ENTRO " << std::endl;
    for (NodeContainer::Iterator i = nodes->Begin(); i != nodes->End(); ++i) {
        Ptr<Node> node = (*i);
        Ptr<MobilityModel> mobility = node->GetObject<MobilityModel>();
        Vector pos = mobility->GetPosition();
        std::cout << "Nodo " << node->GetId() << ": Posición = (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
    }
}



struct LayerParams {
	MobilityHelper* mobility;
      YansWifiPhyHelper* wifiPhy;
      WifiMacHelper* wifiMac;
      Ipv4Address destinationAddress;
      uint16_t destinationPort;
  };

//TODO meter más ruido para mover la gráfica hacia la izquierda
//TODO Añadir hiperparametro para añadir la cantidad de estaciones dinámicamente con schedule aleatorio entre 0 y 0.3. 
void AddStation (NodeContainer *nodeContainer, InternetStackHelper *internetStack, WifiHelper *wifi, LayerParams* params, Ipv4AddressHelper *address, OnOffHelper *onOff) {
    Ptr<Node> node = CreateObject<Node>();
    nodeContainer->Add(node);


    if (g_verbose) {
        std::cout << "Node added with ID: " << node->GetId() << ". Total in dynamicStas: " << nodeContainer->GetN() << std::endl;
    }

    // Mobility configuration
    params->mobility->SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                              "Mode", StringValue("Time"),
                              "Time", TimeValue(Seconds(1.0)),
                              "Speed", StringValue("ns3::ConstantRandomVariable[Constant=1.111]"), // 4 km/h in m/s
                              "Bounds", RectangleValue(Rectangle(-100, 100, -100, 100)));
    params->mobility->Install(node);

    if (g_verbose) {
        std::cout << "Mobility model set for node " << node->GetId() << std::endl;
    }

    internetStack->Install(node);

    if (g_verbose) {
        std::cout << "Internet stack installed on node " << node->GetId() << std::endl;
    }

    NetDeviceContainer staDev = wifi->Install(*params->wifiPhy, *params->wifiMac, node);
    Ipv4InterfaceContainer staInterface = address->Assign(staDev);

    if (g_verbose) {
        std::cout << "WiFi device installed and IP address assigned: " << staInterface.GetAddress(0) << std::endl;
    }

    std::ostringstream oss;
    oss << "/NodeList/" << node->GetId() << "/DeviceList/*/Mac/MacTx";
    Config::Connect(oss.str(), MakeCallback(&DevTxTrace));

    if (g_verbose) {
        std::cout << "Callback configured for node " << node->GetId() << std::endl;
    }

    ApplicationContainer apps = onOff->Install(node);

//    std::cout << "node container print en iteracion: " << i << std::endl;
//    i++;
//    PrintNodePositions(*nodeContainer);
//    std::cout << "------------------------------------------------------------------------"<< std::endl;

    // Assuming app start and stop times are set outside this snippet
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
	totalPacketsTransmitted++;

	 uint64_t dataRate = mode.GetDataRate(40);

	totalDataRate += dataRate; // Acumula la tasa de datos de este paquete
  
  if (g_verbose)
  {
    std::cout << "PHYRXOK mode=" << mode<< " snr=" << snr << " " << *packet <<  std::endl;
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
PhyTxTrace (std::string context, Ptr<const Packet> packet) //,WifiMode mode, WifiPreamble preamble, uint8_t txPower)
{
//    totalTransmissionRate += mode.GetDataRate(); // Sumar la velocidad de transmisión en Mbps

	totalBytesPhy += packet->GetSize ();

    phytx_packets++;
    ns3::WifiMacHeader macHeader;
    if (packet->PeekHeader(macHeader)) {
    // std::cout << "CABECERA " << macHeader << ""<<std::endl;

        if (macHeader.IsRetry()) {
        	retransmissionCount ++;
        }
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
  double txPower = 25.0; // dbm
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
    int retransmissionsCount;
    double meanThroughputValue;
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
    int phytx_packets,
	int retransmissionsCount,
	double meanThroughputValue);
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
    int phytx_packets,
	int retransmissionsCount,
	double meanThroughputValue)

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
//    env->phytx_packets = phytx_packets;
    env->retransmissionsCount = retransmissionsCount;
    env->meanThroughputValue = meanThroughputValue;

    SetCompleted();                 ///< Release the memory and update conters
    NS_LOG_DEBUG ("Ver:" << (int)SharedMemoryPool::Get()->GetMemoryVersion(m_id));
    auto act = ActionGetterCond();  ///< Acquire the Act memory for reading
    int ret = act->c;
    std::cout << "Simulacion parada:  " << ret;
    
    GetCompleted();                 ///< Release the memory, roll back memory version and update conters
    NS_LOG_DEBUG ("Ver:" << (int)SharedMemoryPool::Get()->GetMemoryVersion(m_id));
    return ret;
}

void CalculateThroughput () {

  double throughputMbpsPhy = (totalBytesPhy * 8.0) / (interval.GetSeconds () * 1e6); // Convertir a Mbps

  if(g_verbose){
	  std::cout << "Throughput phy: " << throughputMbpsPhy << " Mbps" << std::endl;

  }
  totalBytesPhy = 0; // Reiniciar para el próximo intervalo
  throughputValues.push_back(throughputMbpsPhy);


  // Verificar si aún estamos dentro del tiempo de simulación total
    if (Simulator::Now().GetSeconds() + interval.GetSeconds() < finScript) {
      Simulator::Schedule(interval, &CalculateThroughput); // Programar el próximo cálculo
    }
}
void CalculateTransmissionRate(){

    if (totalPacketsTransmitted > 0) { // Evitar división por cero

    	double averageTransmissionRate = (totalDataRate / totalPacketsTransmitted) / 1e6;

    	averageTransmissionRateValues.push_back(averageTransmissionRate);
    	  if(g_verbose){
    	        std::cout << "Average Transmission Rate: " << averageTransmissionRate << " Mbps" << std::endl;

    	  }

    } else {
        std::cout << "No packets transmitted in this interval." << std::endl;
    }

    // Reiniciar variables para el próximo intervalo
    totalDataRate = 0;
    totalPacketsTransmitted = 0;

    // Programar el próximo cálculo si aún no se alcanza el tiempo final de la simulación
    if (Simulator::Now().GetSeconds() < finScript - 1) { // Asume que `totalTime` es la duración total de tu simulación
        Simulator::Schedule(Seconds(1.0), &CalculateTransmissionRate);
    }
}

std::string calculateMCS(int paquetesPorSegundo) {
    const uint32_t packetSize = 1024; // Tamaño del paquete en bytes
    const uint32_t bitsPorByte = 8;
    // Calcular la tasa de datos en bits por segundo
    uint64_t tasaDeDatos = static_cast<uint64_t>(paquetesPorSegundo) * packetSize * bitsPorByte;

    if (tasaDeDatos <= 6000000) {
        if(g_verbose) std::cout << "ErpOfdmRate6Mbps" << std::endl;

        return "ErpOfdmRate6Mbps";
    } else if (tasaDeDatos <= 9000000) {
        if(g_verbose) std::cout << "ErpOfdmRate9Mbps" << std::endl;

        return "ErpOfdmRate9Mbps";
    } else if (tasaDeDatos <= 12000000) {
        if(g_verbose) std::cout << "ErpOfdmRate12Mbps" << std::endl;

        return "ErpOfdmRate12Mbps";
    } else if (tasaDeDatos <= 18000000) {
        if(g_verbose) std::cout << "ErpOfdmRate18Mbps" << std::endl;

        return "ErpOfdmRate18Mbps";
    } else if (tasaDeDatos <= 24000000) {
        if(g_verbose) std::cout << "ErpOfdmRate24Mbps" << std::endl;

        return "ErpOfdmRate24Mbps";
    } else if (tasaDeDatos <= 36000000) {
        if(g_verbose) std::cout << "ErpOfdmRate36Mbps" << std::endl;

        return "ErpOfdmRate36Mbps";
    } else if (tasaDeDatos <= 48000000) {
        if(g_verbose) std::cout << "ErpOfdmRate48Mbps" << std::endl;

        return "ErpOfdmRate48Mbps";
    } else {

        if(g_verbose) std::cout << "ErpOfdmRate54Mbps" << std::endl;

        return "ErpOfdmRate54Mbps"; // Suponemos que cualquier tasa de datos más alta se ajustará a 54Mbps
    }
}

int main(int argc, char *argv[])
{
//	// Activar el log del componente OnOffApplication con nivel de detalle INFO
//	LogComponentEnable("OnOffApplication", LOG_LEVEL_INFO);
//
//	// Activar el log del componente PacketSink con nivel de detalle INFO
//	LogComponentEnable("PacketSink", LOG_LEVEL_INFO);

//	LogComponentEnable("OnOffApplication", LOG_LEVEL_INFO);
//	LogComponentEnable("Ipv4L3Protocol", LOG_LEVEL_INFO);

    int memblock_key = 2333;        ///< memory block key, need to keep the same in the python script
    CommandLine cmd;
    // cmd.AddValue ("a","the value of a",a);
    // cmd.AddValue ("b","the value of b",b);
    cmd.AddValue ("key","memory block key",memblock_key);
    cmd.AddValue ("verbose", "Print trace information if true", g_verbose);
    cmd.AddValue ("finScript", "Establece el final del script", finScript);
    cmd.AddValue ("keep_evidences", "Establece si se guardan evidencias de la simulacion", keepEvidences);
    cmd.AddValue ("posX", "Establece posicion ejeX del nodo estático", posX);
    cmd.AddValue ("paquetes", "Establece los paquetes que se van a transmitir", paquetesPorSegundo);

    COLLECTOR collector(memblock_key);
      


    cmd.Parse (argc, argv);

//    AsciiTraceHelper asciiTraceHelper;
//
//       // Enable logging for specific components
//       LogComponentEnable("OnOffApplication", LOG_LEVEL_INFO);
//       LogComponentEnable("WifiMac", LOG_LEVEL_ALL);


  Packet::EnablePrinting ();

  WifiHelper wifi;
  //Use "g-2.4GHz" standard or "a-5GHz" standard



//  ErpOfdmRate6Mbps
//   ErpOfdmRate9Mbps
//   ErpOfdmRate12Mbps
//   ErpOfdmRate18Mbps
//   ErpOfdmRate24Mbps
//   ErpOfdmRate36Mbps
//   ErpOfdmRate48Mbps
//   ErpOfdmRate54Mbps

  wifi.SetStandard (ns3::WIFI_STANDARD_80211g);
  wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                     "DataMode", StringValue(calculateMCS(paquetesPorSegundo)),
                                     "ControlMode", StringValue(calculateMCS(paquetesPorSegundo)));



  if(useARF==true){
  //Use of ARF
  wifi.SetRemoteStationManager ("ns3::ArfWifiManager");
	  //wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");


//  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager","DataMode", StringValue("VhtMcs9"));
  }
  

  MobilityHelper mobilityStatic;
  MobilityHelper mobilityDynamic;
  NodeContainer nodes;
  NodeContainer staticStas;
  NodeContainer dynamicStas;

  NodeContainer ap;
  NetDeviceContainer staDevs;
  NetDeviceContainer apDev;
  InternetStackHelper IPstack;



  Ipv4AddressHelper addresses;

  // PacketSocketHelper packetSocket;


  //Position of the nodes
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0, 0, 0));  // Añade una pos para el primer nodo// este es el punto de acceso
  positionAlloc->Add (Vector (posX, 0, 0));  // Estacion fija a 5m
  //positionAlloc->Add (Vector (20, 0.0, 0));  // Añade una pos para el tercer nodo

  mobilityStatic.SetPositionAllocator (positionAlloc);


  //Crear una lista nueva donde sepa donde esta cada nodo
  nodes.Create (numNodos);
  ap = NodeContainer(nodes.Get (0));
  staticStas = NodeContainer(nodes.Get (1));

  // give packet socket powers to nodes.
  // packetSocket.Install (stas);
  // packetSocket.Install (ap);

  WifiMacHelper wifiMac;
  YansWifiPhyHelper wifiPhy;
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiPhy = WiFiPhyConfig();

  // //define propagation loss
  // wifiChannel.AddPropagationLoss ("ns3::HybridBuildingsPropagationLossModel");

  // wifiPhy.SetChannel (wifiChannel.Create ());
  Ssid ssid = Ssid ("wifi-default");

  //setup ap.
   wifiMac.SetType ("ns3::ApWifiMac",
                     "Ssid", SsidValue (ssid),"QosSupported",BooleanValue (true));


   addresses.SetBase ("10.1.1.0", "255.255.255.0");

   apDev = wifi.Install (wifiPhy, wifiMac, ap);

  // // setup stas.
  wifiMac.SetType ("ns3::StaWifiMac",
                    "ActiveProbing", BooleanValue (true),
                    "Ssid", SsidValue (ssid));
  staDevs = wifi.Install (wifiPhy, wifiMac, staticStas);



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
  

  // mobilityStatic.
  mobilityStatic.Install (ap);
  mobilityStatic.Install (staticStas);

  //obstacles
  BuildingsHelper::Install (ap);
  BuildingsHelper::Install (staticStas);



  // Simulator::Schedule (Seconds (1.0), &AdvancePosition, stas.Get (0));
  // Simulator::Schedule (Seconds (1.0), &AdvancePosition, stas.Get (1));



  // //Conexion primera estacistason
  // PacketSocketAddress socket;


  // socket.SetSingleDevice (staDevs.Get (0)->GetIfIndex ());
  // //socket.SetPhysicalAddress (staDevs.Get (1)->GetAddress ());
  // socket.SetPhysicalAddress (apDev.Get(0)->GetAddress ());  // Cambiado para apuntar al AP
  // // socket.SetProtocol (1);

  //--------------------------------------------
  //-- Configure IP stack
  //--------------------------------------------
  // No le habías puesto IP a ninguna interfaz, no se estaba transmitiendo ningún paquete IP.
  IPstack.Install (nodes);


  //assign directions to the STAs
  Ipv4InterfaceContainer apInterface = addresses.Assign (apDev);
  Ipv4InterfaceContainer staticStasInterfaces = addresses.Assign (staDevs);

  // Get source address
  auto ipv4_ap = ap.Get (0)->GetObject<Ipv4> ();
  auto ipv4_staticSta = staticStas.Get (0)->GetObject<Ipv4> (); //Get ip objetct from transmiter 1
  auto source_staticSta = ipv4_staticSta->GetAddress (1, 0).GetLocal ();


//    for (uint32_t i = 0; i < staticStas.GetN(); i++) {
//		std::cout << "num stas: " << staticStas.GetN() << std::endl;
//
//		auto ipv4_sta = staticStas.Get(i)->GetObject<Ipv4>();
//		auto source = ipv4_sta->GetAddress(1, 0).GetLocal();
//		std::cout << "source address i: " << source << std::endl;
//
//	}

//
//  auto ipv4_sta2 = stas.Get (1)->GetObject<Ipv4> (); //Get ip objetct from transmiter 2
//  auto source_2 = ipv4_sta2->GetAddress (1, 0).GetLocal ();


  auto destination = ipv4_ap->GetAddress (1, 0).GetLocal ();
  std::cout << "static sta:: " << source_staticSta << std::endl;

  std::cout << "destination address: " << destination << std::endl;



  //Create router nodes, initialize routing database and set up the routing tables in the nodes.

  //--------------------------------------------
  //-- Sender
  //--------------------------------------------  
  uint16_t port = 6600;
  InetSocketAddress dest_socket (destination, port);
  // Tu onoff no estaba configurado correctamente, no sabía donde enviar, no había protocolo IP
  OnOffHelper onoff ("ns3::UdpSocketFactory", dest_socket);
  //Configure attributes
  // onoff.SetAttribute ("PacketSize", UintegerValue (packet_size));
  onoff.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onoff.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));

  // Configurar la tasa de datos y el tamaño del paquete al máximo que pueda admitir el MCS (54Mbps)
  uint32_t packetSize = 1024; // Tamaño del paquete en bytes
  uint32_t packetsPerSecond = paquetesPorSegundo;
  DataRate dataRate(packetSize * 8 * packetsPerSecond);

  onoff.SetAttribute ("DataRate", DataRateValue (dataRate));
  AddressValue remoteAddress (dest_socket);
  onoff.SetAttribute ("Remote", remoteAddress);
  // onoff.SetAttribute ("EnableSeqTsSizeHeader", BooleanValue (true)); //header to store some info

  //--------------------------------------------
  //-- Receiver
  //--------------------------------------------  
  // No tenías a nadie recibiendo en el otro extremo, necesitas sí o sí un sink. Esto ya lo habíamos mencionado.
  PacketSinkHelper sink ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));
  auto receiver = sink.Install (ap.Get (0));
  // Ptr<PacketSink> pktSink = StaticCast<PacketSink> (receiver.Get (0));
  receiver.Start (Seconds (inicioScript));
  receiver.Stop (Seconds (finScript));



  //COMUNICACION CON NS3AI
 for (uint32_t i = 0; i < 1; ++i) {

    //TODO Parar cada x segundos (0.1) para recopilar datos 
    Simulator::Schedule (Seconds (29.9), [&onoff,&collector]() {
    //showStadistics();

   double sumaValoresThroughput = std::accumulate(throughputValues.begin(), throughputValues.end(), 0.0);
   double meanThroughputValue = sumaValoresThroughput / throughputValues.size();

    collector.Func(devrx_packets,devtxAP_packets,devrxAP_packets,devtx_packets,phyrx0k_packets,phyrxerrortrace_packets,phytx_packets,retransmissionCount,meanThroughputValue);

   //onoff.SetConstantRate (DataRate ("10Mbps"));

  });
 }
   


  // //Cambio de tasa de transmisión después de 20 segundos
  // Simulator::Schedule (Seconds (4.0), [&onoff]() {
  // onoff.SetConstantRate (DataRate ("4Mbps"));
  // });

  ApplicationContainer apps;

//  apps = onoff.Install (stas.Get (0));
//  apps = onoff.Install (stas.Get (1));

  for (NodeContainer::Iterator i = staticStas.Begin(); i != staticStas.End(); ++i) {

      apps.Add(onoff.Install(*i));
  }


//  LayerParams* params = new LayerParams{
//          &mobilityDynamic, &wifiPhy, &wifiMac, destination, port
//      };


//  for (uint32_t i = 0; i < 28; i += 2) {
//      Simulator::Schedule(Seconds(i * 1.0), &AddStation, &dynamicStas, &IPstack, &wifi, params, &addresses, &onoff);
//      Simulator::Schedule(Seconds(i * 1.0+0.5), &AddStation, &dynamicStas, &IPstack, &wifi, params, &addresses, &onoff);
//
//  }
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

//  PrintNodePositions(dynamicStas);

  apps.Start (Seconds (inicioScript));
  apps.Stop (Seconds (finScript));
  

  Simulator::Schedule (startTime, &CalculateThroughput);
  Simulator::Schedule(Seconds(5.0), &CalculateTransmissionRate);
  Simulator::Schedule(Seconds(29.9), &PrintNodePositions, &dynamicStas);

  Simulator::Stop (Seconds (finScript));

  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTrace));
  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacRx", MakeCallback (&DevRxTrace));
  //Config::Connect("/NodeList/*/DeviceList/*/Phy/MacTxDrop", MakeCallback(&CountRetransmissions));


  Config::Connect ("/NodeList/0/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTraceAP));
  Config::Connect ("/NodeList/0/DeviceList/*/Mac/MacRx", MakeCallback (&DevRxTraceAP));

  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxOk", MakeCallback (&PhyRxOkTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxError", MakeCallback (&PhyRxErrorTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/PhyTxEnd", MakeCallback (&PhyTxTrace));





  // Config::Connect("/NodeList/0/DeviceList/*/$ns3::WifiNetDevice/Phy/PhyTxEnd", MakeCallback(&DropCallback));



  // ns3::Config::Connect("/NodeList/*/DeviceList/*/Phy/MonitorSnifferTx", ns3::MakeCallback(&MyPacketReceiveCallback));




  //NS_LOG_UNCOND ("Simulación iniciada"); // Agregar registro al inicio de la simulación

  //EScritura de resultados obtenidos en un archivo
  std::string rutaRelativa = "./scratch/escenarios_estudio/simulaciones/";
  std::ostringstream fileName;
  fileName << rutaRelativa << "TransmisionRate_" << dataRate.GetBitRate()
           << "_RxNoise_" << rxNoise
           << "_ARF_" << useARF
           << "_InicioScript_" << inicioScript
           << "_FinScript_" << finScript << ".txt";





  wifiPhy.EnablePcap ("Ap", apDev.Get(0), true);
  Simulator::Run ();
  std::cout << "Transmision rate: " << dataRate.GetBitRate()<< " " <<" RxNOise: " << rxNoise << " ARF: "<<  useARF <<" Incio script: "<< inicioScript << " Fin script: "<< finScript << std::endl;
  std::cout << "devrx_packets estacion: " << devrx_packets << " " << std::endl;
  std::cout << "devtx-packets estacion: " << devtx_packets << " "  << std::endl;

  std::cout << "MCS: " << calculateMCS(paquetesPorSegundo) << " "  << std::endl;
  std::cout << "MCS: " << calculateMCS(paquetesPorSegundo) << " "  << std::endl;

  std::cout << "devrx_ackets punto acceso: " << devrxAP_packets << " " << std::endl;
  std::cout << "devtx-packets punto acceso: " << devtxAP_packets << " "  << std::endl;

  std::cout << "phyrx0k_packets: " << phyrx0k_packets << " " << std::endl;
  std::cout << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << " "  << std::endl;
  std::cout << "phytx_packets: " << phytx_packets << " "  << std::endl;
  std::cout << "RETRANSMISIONES: " << retransmissionCount << " "  << std::endl;

  if(g_verbose){
	  for (size_t i = 0; i < throughputValues.size(); ++i) {
	     std::cout << "THROPUGHPUT ->Intervalo: " << i + 1 << ": " << throughputValues[i] << " Mbps" << std::endl;
	   }

	  for (size_t i = 0; i < averageTransmissionRateValues.size(); ++i) {
	       std::cout << "TRANSMISSION RATE ->Intervalo: " << i + 1 << ": " << averageTransmissionRateValues[i] << " Mbps" << std::endl;
	     }
  }

  if(keepEvidences){
	  // Abriendo el archivo para escritura
	    std::ofstream outFile;
	    outFile.open(fileName.str());

	    // Asegurándose de que el archivo se abrió correctamente
	    if (!outFile.is_open()) {
	        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
	         // O maneja el error como prefieras
	    }

	    outFile << "devrx_packets estacion: " << devrx_packets << std::endl;
	    outFile << "devtx-packets estacion: " << devtx_packets << std::endl;
	    outFile << "devrx_packets punto acceso: " << devrxAP_packets << " " << std::endl;
	    outFile << "devtx-packets punto acceso: " << devtxAP_packets << " "  << std::endl;

	    outFile << "phyrx0k_packets: " << phyrx0k_packets << " " << std::endl;
	    outFile << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << " "  << std::endl;
	    outFile << "phytx_packets: " << phytx_packets << " "  << std::endl;
	    outFile << "RETRANSMISIONES: " << retransmissionCount << " "  << std::endl;
	    outFile.close();
  }



  //std::cout <<  "resultado suma total:" << "=" << collector.Func(devrx_packets,devtxAP_packets,devrxAP_packets,devtx_packets,phyrx0k_packets,phyrxerrortrace_packets,phytx_packets,phystate_packets) << std::endl;
//  PrintNodePositions(dynamicStas);

  Simulator::Destroy ();

  collector.SetFinish();

  return 0;
  
}
