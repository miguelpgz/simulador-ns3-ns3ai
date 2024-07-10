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
int phytx_packets_PhyTxTrace = 0;
int retransmissionCount = 0;

//calculo throughput
uint64_t totalBytesPhy = 0;
Time startTime = Seconds (5); // Empezar después de 5 segundos para evitar el periodo de estabilización
Time interval = Seconds (1); // Calcular el throughput cada segundo
std::vector<double> throughputValues;
double meanThroughputValue = 0;

//calculo transmission rate
uint64_t totalDataRate = 0; // Acumula las velocidades de transmisión
uint32_t totalGoodPacketsTransmitted = 0; // Contador de paquetes transmitidos
std::vector<double> averageGoodTransmissionRateValues;


bool g_verbose = false;
bool keepEvidences = false;



//añadir nº estaciones, tamaño red
bool useARF=false;
double inicioScript = 0;
double finScript = 30;
int posX = 80;
int paquetesPorSegundo = 732; //6Mbps por defecto
uint32_t numNodos = 100;
double rxNoise = 19;
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
    WifiMacHeader macHeader;
    if (packet->PeekHeader(macHeader)) {
        if (macHeader.IsData()) {  // Verifica si el paquete es de datos
            phyrx0k_packets++;
            totalGoodPacketsTransmitted++;

            uint64_t dataRate = mode.GetDataRate(40);
            totalDataRate += dataRate; // Acumula la tasa de datos de este paquete

            if (g_verbose) {
                std::cout << "PHYRXOK mode=" << mode << " snr=" << snr << " data packet " << *packet << std::endl;
            }
        } else {
            if (g_verbose) {
                std::cout << "Ignored control packet " << *packet << std::endl;
            }
        }
    } else {
        std::cerr << "Failed to retrieve MAC header." << std::endl;
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
PhyTxTrace (std::string context, Ptr<const Packet> packet) 
{

	totalBytesPhy += packet->GetSize ();

    phytx_packets_PhyTxTrace++;
    ns3::WifiMacHeader macHeader;
    if (packet->PeekHeader(macHeader)) {
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
 YansWifiChannelHelper channel;

 channel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");

 channel.AddPropagationLoss("ns3::ThreeLogDistancePropagationLossModel",
                            "ReferenceLoss", DoubleValue(40.045997),
                            "Distance1", DoubleValue(20.0),
                            "Distance2", DoubleValue(90.0),
                            "Exponent0", DoubleValue(3.5),
                            "Exponent1", DoubleValue(2.5),
                            "Exponent2", DoubleValue(2.0));



  YansWifiPhyHelper phy;
  phy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
  phy.SetChannel (channel.Create ());
  phy.SetErrorRateModel ("ns3::TableBasedErrorRateModel");
  phy.Set ("TxGain", DoubleValue (1.0));
  phy.Set ("RxGain", DoubleValue (1.0));
  phy.Set ("TxPowerLevels", UintegerValue (1));
  double txPower = 23.0; // dbm
  phy.Set ("TxPowerEnd", DoubleValue (txPower));
  phy.Set ("TxPowerStart", DoubleValue (txPower));
  phy.Set ("RxNoiseFigure", DoubleValue (rxNoise)); //mas importante
  phy.Set ("ChannelNumber", UintegerValue (46));
  phy.Set ("ChannelWidth", UintegerValue (40));
  phy.Set ("MaxSupportedTxSpatialStreams", UintegerValue (1));
  phy.Set ("MaxSupportedRxSpatialStreams", UintegerValue (1));
  return phy;
}




void
showStadistics(){

    std::cout << "devrx_packets: " << devrx_packets << " " << std::endl;
    std::cout << "devtx-packets: " << devtx_packets << " "  << std::endl;
    std::cout << "phyrx0k_packets: " << phyrx0k_packets << " " << std::endl;
    std::cout << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << " "  << std::endl;
    std::cout << "phytx_packets: " << phytx_packets_PhyTxTrace << " "  << std::endl;

}



MobilityHelper
MobilityConfig ()
{
  NS_LOG_INFO ("Configuring mobility.");
  MobilityHelper mobility;

  mobility.SetPositionAllocator (
      "ns3::RandomDiscPositionAllocator", "X", StringValue ("0.0"), "Y", StringValue ("0.0"), "Z",
      StringValue ("0.0"), "Rho",
      StringValue ("ns3::UniformRandomVariable[Min=5|Max=30]")); //min and max in meters
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  return mobility;
}

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



struct Act
{
    int c;
}Packed;


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
    auto env = EnvSetterCond();  


    env->devrx_packets =devrx_packets;
    env->devtxAP_packets= devtxAP_packets;
    env->devrxAP_packets =devrxAP_packets;
    env->devtx_packets = devtx_packets;
    env->phyrx0k_packets = phyrx0k_packets;
    env->phyrxerrortrace_packets =phyrxerrortrace_packets;
    env->retransmissionsCount = retransmissionsCount;
    env->meanThroughputValue = meanThroughputValue;

    SetCompleted();                
    NS_LOG_DEBUG ("Ver:" << (int)SharedMemoryPool::Get()->GetMemoryVersion(m_id));
    auto act = ActionGetterCond();  
    int ret = act->c;
    std::cout << "Simulacion parada:  " << ret;
    
    GetCompleted();                
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


    if (Simulator::Now().GetSeconds() + interval.GetSeconds() < finScript) {
      Simulator::Schedule(interval, &CalculateThroughput); // Programar el próximo cálculo
    }
}
void CalculateTransmissionRate_and_ocupacion(){

    if (totalGoodPacketsTransmitted > 0) { // Evitar división por cero

    	double averageTransmissionRate = (totalDataRate / totalGoodPacketsTransmitted) / 1e6;

    	averageGoodTransmissionRateValues.push_back(averageTransmissionRate);
    	  if(g_verbose){
    	        std::cout << "Average Transmission Rate: " << averageTransmissionRate << " Mbps" << std::endl;

    	  }

    } else {
        std::cout << "No packets transmitted in this interval." << std::endl;
    }

    totalDataRate = 0;
    totalGoodPacketsTransmitted = 0;

    if (Simulator::Now().GetSeconds() < finScript - 1) { // Asume que `totalTime` es la duración total de tu simulación
        Simulator::Schedule(Seconds(1.0), &CalculateTransmissionRate_and_ocupacion);
    }
}

std::string calculateMCS_noschedule(int paquetesPorSegundo) {
    const uint32_t packetSize = 1024; // Tamaño del paquete en bytes
    const uint32_t bitsPorByte = 8;
    // Calcular la tasa de datos en bits por segundo
    uint64_t tasaDeDatos = static_cast<uint64_t>(paquetesPorSegundo) * packetSize * bitsPorByte;

    if (tasaDeDatos <= 6000000) {
        if(g_verbose) std::cout << "OfdmRate6Mbps" << std::endl;

        return "OfdmRate6Mbps";
    } else if (tasaDeDatos <= 9000000) {
        if(g_verbose) std::cout << "OfdmRate9Mbps" << std::endl;

        return "OfdmRate9Mbps";
    } else if (tasaDeDatos <= 12000000) {
        if(g_verbose) std::cout << "OfdmRate12Mbps" << std::endl;

        return "OfdmRate12Mbps";
    } else if (tasaDeDatos <= 18000000) {
        if(g_verbose) std::cout << "OfdmRate18Mbps" << std::endl;

        return "OfdmRate18Mbps";
    } else if (tasaDeDatos <= 24000000) {
        if(g_verbose) std::cout << "OfdmRate24Mbps" << std::endl;

        return "OfdmRate24Mbps";
    } else if (tasaDeDatos <= 36000000) {
        if(g_verbose) std::cout << "OfdmRate36Mbps" << std::endl;

        return "OfdmRate36Mbps";
    } else if (tasaDeDatos <= 48000000) {
        if(g_verbose) std::cout << "OfdmRate48Mbps" << std::endl;

        return "OfdmRate48Mbps";
    } else {

        if(g_verbose) std::cout << "OfdmRate54Mbps" << std::endl;

        return "OfdmRate54Mbps"; // Suponemos que cualquier tasa de datos más alta se ajustará a 54Mbps
    }
}

int main(int argc, char *argv[])
{


    int memblock_key = 2333;        
    CommandLine cmd;
    cmd.AddValue ("key","memory block key",memblock_key);
    cmd.AddValue ("verbose", "Print trace information if true", g_verbose);
    cmd.AddValue ("finScript", "Establece el final del script", finScript);
    cmd.AddValue ("keep_evidences", "Establece si se guardan evidencias de la simulacion", keepEvidences);
    cmd.AddValue ("posX", "Establece posicion ejeX del nodo estático", posX);
    cmd.AddValue ("paquetes", "Establece los paquetes que se van a transmitir", paquetesPorSegundo);

    COLLECTOR collector(memblock_key);
      


    cmd.Parse (argc, argv);




  Packet::EnablePrinting ();

  WifiHelper wifi;

  wifi.SetStandard (ns3::WIFI_STANDARD_80211a);



  if(useARF==true){
  //Use of ARF
  wifi.SetRemoteStationManager ("ns3::ArfWifiManager");

  }
  else{
	  wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
	                                      "DataMode", StringValue(calculateMCS_noschedule(paquetesPorSegundo)),
	                                      "ControlMode", StringValue(calculateMCS_noschedule(paquetesPorSegundo)));

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



  //Position of the nodes
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0, 0, 0));  // Añade una pos para el primer nodo// este es el punto de acceso
  positionAlloc->Add (Vector (posX, 0, 0));  // Estacion fija a 5m

  mobilityStatic.SetPositionAllocator (positionAlloc);


  //Crear una lista nueva donde sepa donde esta cada nodo
  nodes.Create (numNodos);
  ap = NodeContainer(nodes.Get (0));
  staticStas = NodeContainer(nodes.Get (1));


  WifiMacHelper wifiMac;
  YansWifiPhyHelper wifiPhy;
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiPhy = WiFiPhyConfig();

  Ssid ssid = Ssid ("wifi-default");

  //setup ap.
   wifiMac.SetType ("ns3::ApWifiMac",
                     "Ssid", SsidValue (ssid),"QosSupported",BooleanValue (true));


   addresses.SetBase ("10.1.1.0", "255.255.255.0");

   apDev = wifi.Install (wifiPhy, wifiMac, ap);

  //setup stas.
  wifiMac.SetType ("ns3::StaWifiMac",
                    "ActiveProbing", BooleanValue (true),
                    "Ssid", SsidValue (ssid));
  staDevs = wifi.Install (wifiPhy, wifiMac, staticStas);


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
  


  mobilityStatic.Install (ap);
  mobilityStatic.Install (staticStas);

  //obstacles
  BuildingsHelper::Install (ap);
  BuildingsHelper::Install (staticStas);

  IPstack.Install (nodes);


  Ipv4InterfaceContainer apInterface = addresses.Assign (apDev);
  Ipv4InterfaceContainer staticStasInterfaces = addresses.Assign (staDevs);

  auto ipv4_ap = ap.Get (0)->GetObject<Ipv4> ();
  auto ipv4_staticSta = staticStas.Get (0)->GetObject<Ipv4> (); //Get ip objetct from transmiter 1
  auto source_staticSta = ipv4_staticSta->GetAddress (1, 0).GetLocal ();


  auto destination = ipv4_ap->GetAddress (1, 0).GetLocal ();
  std::cout << "static sta:: " << source_staticSta << std::endl;

  std::cout << "destination address: " << destination << std::endl;





  //Sender
  uint16_t port = 6600;
  InetSocketAddress dest_socket (destination, port);
  OnOffHelper onoff ("ns3::UdpSocketFactory", dest_socket);
  onoff.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onoff.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));

  uint32_t packetSize = 1024; // Tamaño del paquete en bytes
  uint32_t packetsPerSecond = paquetesPorSegundo;
  DataRate dataRate(packetSize * 8 * packetsPerSecond);

  onoff.SetAttribute ("DataRate", DataRateValue (dataRate));
  AddressValue remoteAddress (dest_socket);
  onoff.SetAttribute ("Remote", remoteAddress);


  PacketSinkHelper sink ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));
  auto receiver = sink.Install (ap.Get (0));
  receiver.Start (Seconds (inicioScript));
  receiver.Stop (Seconds (finScript));



  //COMUNICACION CON NS3AI
 for (uint32_t i = 0; i < 1; ++i) {

    //TODO Parar cada x segundos (0.1) para recopilar datos
    Simulator::Schedule (Seconds (29.9), [&onoff,&collector]() {

   double sumaValoresThroughput = std::accumulate(throughputValues.begin(), throughputValues.end(), 0.0);
   double meanThroughputValue = sumaValoresThroughput / throughputValues.size();

   collector.Func(devrx_packets,devtxAP_packets,devrxAP_packets,devtx_packets,phyrx0k_packets,phyrxerrortrace_packets,phytx_packets_PhyTxTrace,retransmissionCount,meanThroughputValue);
  });
 }

  ApplicationContainer apps;

  for (NodeContainer::Iterator i = staticStas.Begin(); i != staticStas.End(); ++i) {

      apps.Add(onoff.Install(*i));
  }

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  apps.Start (Seconds (inicioScript));
  apps.Stop (Seconds (finScript));
  

  Simulator::Schedule (startTime, &CalculateThroughput);
  Simulator::Schedule(Seconds(5.0), &CalculateTransmissionRate_and_ocupacion);
  Simulator::Schedule(Seconds(29.9), &PrintNodePositions, &dynamicStas);

  Simulator::Stop (Seconds (finScript));

  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTrace));
  Config::Connect ("/NodeList/1/DeviceList/*/Mac/MacRx", MakeCallback (&DevRxTrace));

  Config::Connect ("/NodeList/0/DeviceList/*/Mac/MacTx", MakeCallback (&DevTxTraceAP));
  Config::Connect ("/NodeList/0/DeviceList/*/Mac/MacRx", MakeCallback (&DevRxTraceAP));

  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxOk", MakeCallback (&PhyRxOkTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/Phy/State/RxError", MakeCallback (&PhyRxErrorTrace));
  Config::Connect ("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/PhyTxEnd", MakeCallback (&PhyTxTrace));

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

  std::cout << "MCS: " << calculateMCS_noschedule(paquetesPorSegundo) << " "  << std::endl;
  std::cout << "MCS: " << calculateMCS_noschedule(paquetesPorSegundo) << " "  << std::endl;

  std::cout << "devrx_ackets punto acceso: " << devrxAP_packets << " " << std::endl;
  std::cout << "devtx-packets punto acceso: " << devtxAP_packets << " "  << std::endl;

  std::cout << "phyrx0k_packets: " << phyrx0k_packets << " " << std::endl;
  std::cout << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << " "  << std::endl;
  std::cout << "phytx_packets: " << phytx_packets_PhyTxTrace << " "  << std::endl;
  std::cout << "RETRANSMISIONES: " << retransmissionCount << " "  << std::endl;

  if(g_verbose){
	  for (size_t i = 0; i < throughputValues.size(); ++i) {
	     std::cout << "THROPUGHPUT ->Intervalo: " << i + 1 << ": " << throughputValues[i] << " Mbps" << std::endl;
	   }

	  for (size_t i = 0; i < averageGoodTransmissionRateValues.size(); ++i) {
	       std::cout << "TRANSMISSION RATE ->Intervalo: " << i + 1 << ": " << averageGoodTransmissionRateValues[i] << " Mbps" << std::endl;
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
	    outFile << "phytx_packets: " << phytx_packets_PhyTxTrace << " "  << std::endl;
	    outFile << "RETRANSMISIONES: " << retransmissionCount << " "  << std::endl;
	    outFile.close();
  }

  Simulator::Destroy ();

  collector.SetFinish();

  return 0;
  
}
