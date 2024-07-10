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
 * Author: Miguel Paños >
 *
 *
 ** Based on the work of: Pengyu Liu <eic_lpy@hust.edu.cn>
 *         Hao Yin <haoyin@uw.edu>
 *

 */

#include "ns3/core-module.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/random-walk-2d-mobility-model.h"
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
#include <string>
#include <iostream>
#include "ns3/buildings-helper.h"
#include "ns3/hybrid-buildings-propagation-loss-model.h"
#include <sstream>
#include "ns3/packet-sink-helper.h"
#include <fstream>
#include <vector>
#include <numeric>
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
#include "ns3/random-variable-stream.h"

using namespace std;
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ns3ai_data_collection");

int devrx_packets = 0;
int devtxAP_packets = 0;
int devrxAP_packets = 0;
int devtx_packets = 0;
int devtx_packets_static_sta = 0;
int devtx_packets_dataRate = 0;
int devtx_packets_dataRate_static_sta = 0;
double phyTx_packetsSniffer = 0;
double phyTx_packetsSnifferStaticSta = 0;
double all_phytx_packets_SnifferTx = 0;
double all_phytx_packets_SnifferTxStaticSta = 0;

int phyrx0k_packets = 0;
double snifferRxPackets = 0;

int phyrxerrortrace_packets = 0;
int phytx_packets_PhyTxTrace = 0;
int retransmissionCount = 0;
double snifferRetransmissionCountStaticSta = 0;
double all_snifferRetransmissionCount = 0;
double all_snifferRetransmissionCountStaticSta = 0;
int all_phytx_retransmissionCount = 0;

double rates = 0;
double ratesStaticSta = 0;
int w = 2;
int c = 10;
int new_w = w;
int new_c = c;

uint64_t totalBytesPhy = 0;
uint64_t totalBytesPhyOnlyStaticSta = 0;

uint64_t totalBytesSnifferTx = 0;

uint64_t totalGoodBytesPhy = 0;
uint64_t totalGoodBytesPhyOnlyStaticSta = 0;

Time startTime = Seconds(5);
Time interval = Seconds(0.1);
std::vector<double> throughputValues;
std::vector<double> averageOcupacionValues;

std::vector<double> goodThroughputValues;

double meanThroughputValue = 0;

uint64_t totalDataRate = 0;
uint64_t totalGoodDataRate = 0;

uint32_t totalGoodPacketsTransmitted = 0;
std::vector<double> averageGoodTransmissionRateValues;
std::vector<double> averageSnifferTransmissionRateValues;

bool g_verbose = false;
bool keepEvidences = false;

int numStas = 0;
int paquetSize = 1024;
bool useARF = false;
bool useMLmodel = false;
double inicioScript = 0;
double finScript = 30;
int posX = 5;
int paquetesPorSegundo = 732;
uint32_t numNodos = 2;
double rxNoise = 19;
int seedValue = 1;
int tamano_red = 95;
double retransmissionsPerPacket = 0;
double totalTransmissionTime = 0;
uint32_t i = 0;

#include "ns3/arf-wifi-manager.h"

void DevTxTrace(std::string context, Ptr<const Packet> p)
{
  devtx_packets++;
  devtx_packets_dataRate++;
  if (g_verbose)
  {
    std::cout << "TX p: " << *p << std::endl;
    std::cout << "CONTEXT:" << context;
  }
}

void DevTxTraceOnlyStaticSta(std::string context, Ptr<const Packet> p)
{
  devtx_packets_static_sta++;
  devtx_packets_dataRate_static_sta++;
  if (g_verbose)
  {
    std::cout << "TX p: " << *p << std::endl;
    std::cout << "CONTEXT:" << context;
  }
}

void SnifferTxTrace(std::string context, Ptr<const Packet> packet, uint16_t channelFreqMhz, WifiTxVector txVector, MpduInfo aMpdu, uint16_t staId)
{
  totalBytesPhy += packet->GetSize();
  phyTx_packetsSniffer++;
  ns3::WifiMacHeader macHeader;
  if (packet->PeekHeader(macHeader))
  {
    if (macHeader.IsData())
    {
      all_phytx_packets_SnifferTx++;
    }
    rates += txVector.GetMode().GetDataRate(txVector) / 1e+6;
    if (macHeader.IsRetry())
    {
      all_snifferRetransmissionCount++;
    }
  }
}

void SnifferTxTraceOnlyStaticSta(std::string context, Ptr<const Packet> packet, uint16_t channelFreqMhz, WifiTxVector txVector, MpduInfo aMpdu, uint16_t staId)
{
  totalBytesPhyOnlyStaticSta += packet->GetSize();
  phyTx_packetsSnifferStaticSta++;
  ns3::WifiMacHeader macHeader;
  if (packet->PeekHeader(macHeader))
  {
    if (macHeader.IsData())
    {
      all_phytx_packets_SnifferTxStaticSta++;
    }
    ratesStaticSta += txVector.GetMode().GetDataRate(txVector) / 1e+6;
    if (macHeader.IsRetry())
    {
      snifferRetransmissionCountStaticSta++;
      all_snifferRetransmissionCountStaticSta++;
    }
  }
}

void PrintNodePositions(NodeContainer *nodes)
{
  std::cout << "ENTRO" << std::endl;
  for (NodeContainer::Iterator i = nodes->Begin(); i != nodes->End(); ++i)
  {
    Ptr<Node> node = (*i);
    Ptr<MobilityModel> mobility = node->GetObject<MobilityModel>();
    Vector pos = mobility->GetPosition();
    std::cout << "Nodo " << node->GetId() << ": Posición = (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
  }
}

struct LayerParams
{
  MobilityHelper *mobility;
  YansWifiPhyHelper *wifiPhy;
  WifiMacHelper *wifiMac;
  Ipv4Address destinationAddress;
  uint16_t destinationPort;
};

void AddStation(NodeContainer *nodeContainer, InternetStackHelper *internetStack, WifiHelper *wifi, LayerParams *params, Ipv4AddressHelper *address, OnOffHelper *onOff)
{
  Ptr<Node> node = CreateObject<Node>();
  nodeContainer->Add(node);
  if (g_verbose)
  {
    std::cout << "Node added with ID: " << node->GetId() << ". Total in dynamicStas: " << nodeContainer->GetN() << std::endl;
  }
  params->mobility->SetPositionAllocator("ns3::RandomRectanglePositionAllocator",
                                         "X", StringValue("ns3::UniformRandomVariable[Min=" + std::to_string(-tamano_red) + "|Max=" + std::to_string(tamano_red) + "]"),
                                         "Y", StringValue("ns3::UniformRandomVariable[Min=" + std::to_string(-tamano_red) + "|Max=" + std::to_string(tamano_red) + "]"));
  params->mobility->SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                                     "Mode", StringValue("Time"),
                                     "Time", TimeValue(Seconds(1.0)),
                                     "Speed", StringValue("ns3::ConstantRandomVariable[Constant=1.111]"),
                                     "Bounds", RectangleValue(Rectangle(-100, 100, -100, 100)));
  params->mobility->Install(node);
  if (g_verbose)
  {
    std::cout << "Mobility model set for node " << node->GetId() << std::endl;
  }
  Ptr<MobilityModel> mobilityModel = node->GetObject<MobilityModel>();
  Vector position = mobilityModel->GetPosition();
  std::cout << "Current position of node " << node->GetId() << ": (" << position.x << ", " << position.y << ")" << std::endl;
  internetStack->Install(node);
  if (g_verbose)
  {
    std::cout << "Internet stack installed on node " << node->GetId() << std::endl;
  }
  NetDeviceContainer staDev = wifi->Install(*params->wifiPhy, *params->wifiMac, node);
  Ipv4InterfaceContainer staInterface = address->Assign(staDev);
  if (g_verbose)
  {
    std::cout << "WiFi device installed and IP address assigned: " << staInterface.GetAddress(0) << std::endl;
  }
  std::ostringstream oss;
  std::ostringstream oss3;
  oss << "/NodeList/" << node->GetId() << "/DeviceList/*/Mac/MacTx";
  oss3 << "/NodeList/" << node->GetId() << "/DeviceList/*/Phy/MonitorSnifferTx";
  Config::Connect(oss.str(), MakeCallback(&DevTxTrace));
  Config::Connect(oss3.str(), MakeCallback(&SnifferTxTrace));
  if (g_verbose)
  {
    std::cout << "Callback configured for node " << node->GetId() << std::endl;
  }
  ApplicationContainer apps = onOff->Install(node);
}

void DevRxTrace(std::string context, Ptr<const Packet> p)
{
  devrx_packets++;
  if (g_verbose)
  {
    std::cout << "RX p: " << *p << std::endl;
  }
}

void DevTxTraceAP(std::string context, Ptr<const Packet> p)
{
  devtxAP_packets++;
  if (g_verbose)
  {
    std::cout << "TXAp p: " << *p << std::endl;
  }
}

void DevRxTraceAP(std::string context, Ptr<const Packet> p)
{
  devrxAP_packets++;
  if (g_verbose)
  {
    std::cout << "RXAp p: " << *p << std::endl;
  }
}

std::ofstream outFile;

void PhyRxOkTrace(std::string context, Ptr<const Packet> packet, double snr, WifiMode mode, WifiPreamble preamble)
{
  Mac48Address node1StaticSta("00:00:00:00:00:02");
  WifiMacHeader macHeader;
  phyrx0k_packets++;
  if (packet->PeekHeader(macHeader))
  {
    if (macHeader.IsData())
    {
      totalGoodBytesPhy += packet->GetSize();
      if (macHeader.GetAddr2() == node1StaticSta)
      {
        totalGoodBytesPhyOnlyStaticSta += packet->GetSize();
      }
      totalGoodPacketsTransmitted++;
      if (g_verbose)
      {
        std::cout << "PHYRXOK mode=" << mode << " snr=" << snr << " data packet " << *packet << std::endl;
      }
    }
    else
    {
      if (g_verbose)
      {
        std::cout << "Ignored control packet " << *packet << std::endl;
      }
    }
  }
  else
  {
    std::cerr << "Failed to retrieve MAC header." << std::endl;
  }
}

void PhyRxErrorTrace(std::string context, Ptr<const Packet> packet, double snr)
{
  phyrxerrortrace_packets++;
  if (g_verbose)
  {
    std::cout << "PHYRXERROR snr=" << snr << " " << *packet << std::endl;
    std::cout << "ERROR EN TRAZA" << std::endl;
  }
}

static void SetPosition(Ptr<Node> node, Vector position)
{
  Ptr<MobilityModel> mobility = node->GetObject<MobilityModel>();
  mobility->SetPosition(position);
}

static Vector GetPosition(Ptr<Node> node)
{
  Ptr<MobilityModel> mobility = node->GetObject<MobilityModel>();
  return mobility->GetPosition();
}

static void AdvancePosition(Ptr<Node> node)
{
  Vector pos = GetPosition(node);
  pos.x += 5.0;
  if (pos.x >= 210.0)
  {
    return;
  }
  SetPosition(node, pos);
  Simulator::Schedule(Seconds(1.0), &AdvancePosition, node);
}

YansWifiPhyHelper WiFiPhyConfig()
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
  phy.SetPcapDataLinkType(WifiPhyHelper::DLT_IEEE802_11_RADIO);
  phy.SetChannel(channel.Create());
  phy.SetErrorRateModel("ns3::TableBasedErrorRateModel");
  phy.Set("TxGain", DoubleValue(1.0));
  phy.Set("RxGain", DoubleValue(1.0));
  phy.Set("TxPowerLevels", UintegerValue(1));
  double txPower = 23.0;
  phy.Set("TxPowerEnd", DoubleValue(txPower));
  phy.Set("TxPowerStart", DoubleValue(txPower));
  phy.Set("RxNoiseFigure", DoubleValue(rxNoise));
  phy.Set("ChannelNumber", UintegerValue(46));
  phy.Set("ChannelWidth", UintegerValue(40));
  phy.Set("MaxSupportedTxSpatialStreams", UintegerValue(1));
  phy.Set("MaxSupportedRxSpatialStreams", UintegerValue(1));
  return phy;
}

void showStadistics()
{
  std::cout << "devrx_packets: " << devrx_packets << std::endl;
  std::cout << "devtx-packets: " << devtx_packets << std::endl;
  std::cout << "phyrx0k_packets: " << phyrx0k_packets << std::endl;
  std::cout << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << std::endl;
  std::cout << "phytx_packets: " << phytx_packets_PhyTxTrace << std::endl;
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
  int w;
  int c;
  double avg_datarate;
  double ocupacion;
  double throughput;
  double goodThroughput;
  int devtx_packets_staticSta;
  int phytx_packets_staticSta;
  int retransmissionsCountStaticSta;
  double avg_datarateStaticSta;
  double ocupacionStaticSta;
  double throughputStaticSta;
  double goodThroughputStaticSta;
} Packed;

struct Act
{
  int predicted_w;
  int predicted_c;
} Packed;

struct Predictions
{
  int w;
  int c;
};

class COLLECTOR : public Ns3AIRL<Env, Act>
{
public:
  COLLECTOR(uint16_t id);
  Predictions Func(int devrx_packets,
                   int devtxAP_packets,
                   int devrxAP_packets,
                   int devtx_packets,
                   int phyrx0k_packets,
                   int phyrxerrortrace_packets,
                   int phytx_packets,
                   int retransmissionsCount,
                   int w,
                   int c,
                   double avg_datarate,
                   double ocupacion,
                   double throughput,
                   double goodThroughput,
                   int devtx_packets_staticSta,
                   int phytx_packets_staticSta,
                   int retransmissionsCountStaticSta,
                   double avg_datarateStaticSta,
                   double ocupacionStaticSta,
                   double throughputStaticSta,
                   double goodThroughputStaticSta);
};

COLLECTOR::COLLECTOR(uint16_t id) : Ns3AIRL<Env, Act>(id)
{
  SetCond(2, 0);
}

Predictions COLLECTOR::Func(int devrx_packets,
                            int devtxAP_packets,
                            int devrxAP_packets,
                            int devtx_packets,
                            int phyrx0k_packets,
                            int phyrxerrortrace_packets,
                            int phytx_packets,
                            int retransmissionsCount,
                            int w,
                            int c,
                            double avg_datarate,
                            double ocupacion,
                            double throughput,
                            double goodThroughput,
                            int devtx_packets_staticSta,
                            int phytx_packets_staticSta,
                            int retransmissionsCountStaticSta,
                            double avg_datarateStaticSta,
                            double ocupacionStaticSta,
                            double throughputStaticSta,
                            double goodThroughputStaticSta)
{
  auto env = EnvSetterCond();
  env->devrx_packets = devrx_packets;
  env->devtxAP_packets = devtxAP_packets;
  env->devrxAP_packets = devrxAP_packets;
  env->devtx_packets = devtx_packets;
  env->phyrx0k_packets = phyrx0k_packets;
  env->phyrxerrortrace_packets = phyrxerrortrace_packets;
  env->phytx_packets = phytx_packets;
  env->retransmissionsCount = retransmissionsCount;
  env->w = w;
  env->c = c;
  env->avg_datarate = avg_datarate;
  env->ocupacion = ocupacion;
  env->throughput = throughput;
  env->goodThroughput = goodThroughput;
  env->devtx_packets_staticSta = devtx_packets_staticSta;
  env->phytx_packets_staticSta = phytx_packets_staticSta;
  env->retransmissionsCountStaticSta = retransmissionsCountStaticSta;
  env->avg_datarateStaticSta = avg_datarateStaticSta;
  env->ocupacionStaticSta = ocupacionStaticSta;
  env->throughputStaticSta = throughputStaticSta;
  env->goodThroughputStaticSta = goodThroughputStaticSta;

  SetCompleted();
  auto act = ActionGetterCond();
  Predictions preds;
  preds.c = act->predicted_c;
  preds.w = act->predicted_w;
  GetCompleted();
  return preds;
}

struct Throughputs
{
  double throughput;
  double goodThroughput;
};
//Throughputs para todas las estaciones
Throughputs CalculateThroughput()
{
  double throughputMbpsPhy = (totalBytesPhy * 8.0) / (interval.GetSeconds() * 1e6);
  double goodThroughputMbpsPhy = (totalGoodBytesPhy * 8.0) / (interval.GetSeconds() * 1e6);

  if (g_verbose)
  {
    std::cout << "Throughput phy: " << throughputMbpsPhy << " Mbps" << std::endl;
    std::cout << "Good throughput phy: " << goodThroughputMbpsPhy << " Mbps" << std::endl;
  }

  totalBytesPhy = 0;
  totalGoodBytesPhy = 0;

  throughputValues.push_back(throughputMbpsPhy);
  goodThroughputValues.push_back(goodThroughputMbpsPhy);

  Throughputs result;
  result.throughput = throughputMbpsPhy;
  result.goodThroughput = goodThroughputMbpsPhy;
  return result;
}

//Throughputs solo para la estacion estatica cerca del AP
Throughputs CalculateThroughputStaticSta()
{
  double throughputMbpsPhy = (totalBytesPhyOnlyStaticSta * 8.0) / (interval.GetSeconds() * 1e6);
  double goodThroughputMbpsPhy = (totalGoodBytesPhyOnlyStaticSta * 8.0) / (interval.GetSeconds() * 1e6);

  if (g_verbose)
  {
    std::cout << "Throughput phy static sta: " << throughputMbpsPhy << " Mbps" << std::endl;
    std::cout << "Good throughput phy static sta: " << goodThroughputMbpsPhy << " Mbps" << std::endl;
  }
  totalBytesPhyOnlyStaticSta = 0;
  totalGoodBytesPhyOnlyStaticSta = 0;

  Throughputs result;
  result.throughput = throughputMbpsPhy;
  result.goodThroughput = goodThroughputMbpsPhy;
  return result;
}

double CalculateOcupacion(int devtx_packets, double average_dataRate)
{
  double bits_paquete = paquetSize * 8;
  double bits_average_dataRate = average_dataRate * 1e+6;
  double ocupacion_1_paquete = bits_paquete / bits_average_dataRate;

  double ocupacion_all_paquetes = ((ocupacion_1_paquete * devtx_packets) / interval.GetSeconds());

  return ocupacion_all_paquetes;
}

struct DatarRate_ocupacion
{
  double avg_datarate;
  double avg_ocupacion;
};
//Calcula el datarate y la ocupacion del canal
DatarRate_ocupacion CalculateTransmissionRate_and_ocupacion()
{
  DatarRate_ocupacion results;

  if (phyTx_packetsSniffer > 0)
  {
    double averageTransmissionRateSniffer = (rates / (phyTx_packetsSniffer));
    results.avg_datarate = averageTransmissionRateSniffer;
    results.avg_ocupacion = CalculateOcupacion(devtx_packets_dataRate, averageTransmissionRateSniffer);

    averageSnifferTransmissionRateValues.push_back(averageTransmissionRateSniffer);
    averageOcupacionValues.push_back(results.avg_ocupacion);

    rates = 0;
    phyTx_packetsSniffer = 0;
    devtx_packets_dataRate = 0;

    return results;

    if (g_verbose)
    {
      std::cout << "Average Transmission Rate: " << results.avg_datarate << " Mbps" << std::endl;
    }
  }
  else
  {
    std::cout << "No good packets transmitted in this interval." << std::endl;

    results.avg_datarate = 0;
    results.avg_ocupacion = 0;
    rates = 0;
    phyTx_packetsSniffer = 0;
    devtx_packets_dataRate = 0;
    return results;
  }
}
//Calcula el datarate y la ocupacion del canal solo para la estacion estatica
DatarRate_ocupacion CalculateTransmissionRate_and_ocupacion_for_StaticSta()
{
  DatarRate_ocupacion results;

  if (phyTx_packetsSnifferStaticSta > 0)
  {
    double averageTransmissionRateSniffer = (ratesStaticSta / (phyTx_packetsSnifferStaticSta));
    results.avg_datarate = averageTransmissionRateSniffer;
    results.avg_ocupacion = CalculateOcupacion(devtx_packets_dataRate_static_sta, averageTransmissionRateSniffer);

    averageSnifferTransmissionRateValues.push_back(averageTransmissionRateSniffer);

    ratesStaticSta = 0;
    phyTx_packetsSnifferStaticSta = 0;
    snifferRetransmissionCountStaticSta = 0;
    devtx_packets_dataRate_static_sta = 0;

    return results;
  }
  else
  {
    std::cout << "No good packets transmitted in this interval." << std::endl;
    results.avg_datarate = 0;
    results.avg_ocupacion = 0;
    ratesStaticSta = 0;
    phyTx_packetsSnifferStaticSta = 0;
    snifferRetransmissionCountStaticSta = 0;
    devtx_packets_dataRate_static_sta = 0;
    return results;
  }
}
//Se usa para calcular el MCS que se está usando en función del datarate. No se usa en este caso
std::string calculateMCS(int paquetesPorSegundo) {
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
  //Parametros de entrada del script
  cmd.AddValue("key", "memory block key", memblock_key);
  cmd.AddValue("verbose", "Print trace information if true", g_verbose);
  cmd.AddValue("finScript", "Establece el final del script", finScript);
  cmd.AddValue("keep_evidences", "Establece si se guardan evidencias de la simulacion", keepEvidences);
  cmd.AddValue("posX", "Establece posicion ejeX del nodo estático", posX);
  cmd.AddValue("paquetes", "Establece los paquetes que se van a transmitir", paquetesPorSegundo);
  cmd.AddValue("numStas", "Establece las estaciones que se van a añadir", numStas);
  cmd.AddValue("useARF", "Establece si se va a usar ARF", useARF);
  cmd.AddValue("useMLmodel", "Establece si se va a usar o no el modelo de ML para apoyar a ARF", useMLmodel);
  cmd.AddValue("seedValue", "Establece la semilla de generación para la simulación", seedValue);
  cmd.AddValue("tam_red", "Establece el tamanio de la red", tamano_red);
  cmd.AddValue("w", "Establece los ACKs consecutivos que faltan para bajar la velocidad.", w);
  cmd.AddValue("c", "Establece los ACKs consecutivos que deben llegar para subir la velocidad", c);

  COLLECTOR collector(memblock_key);

  cmd.Parse(argc, argv);

  RngSeedManager::SetSeed(seedValue);

  Packet::EnablePrinting();

  WifiHelper wifi;
  wifi.SetStandard(ns3::WIFI_STANDARD_80211a);

  if (useARF == true)
  {
    std::cout << "valor w: " << w << std::endl;
    wifi.SetRemoteStationManager("ns3::ArfWifiManager",
                                 "WThreshold", UintegerValue(w),
                                 "SuccessThreshold", UintegerValue(c));
  }
  else
  {
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                 "DataMode", StringValue(calculateMCS(paquetesPorSegundo)),
                                 "ControlMode", StringValue(calculateMCS(paquetesPorSegundo)));
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

  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
  positionAlloc->Add(Vector(0, 0, 0));
  positionAlloc->Add(Vector(posX, 0, 0));

  mobilityStatic.SetPositionAllocator(positionAlloc);

  nodes.Create(numNodos);
  ap = NodeContainer(nodes.Get(0));
  staticStas = NodeContainer(nodes.Get(1));

  WifiMacHelper wifiMac;
  YansWifiPhyHelper wifiPhy;
  wifiPhy = WiFiPhyConfig();

  Ssid ssid = Ssid("wifi-default");

  wifiMac.SetType("ns3::ApWifiMac",
                  "Ssid", SsidValue(ssid), "QosSupported", BooleanValue(true));

  addresses.SetBase("10.1.1.0", "255.255.255.0");

  apDev = wifi.Install(wifiPhy, wifiMac, ap);

  wifiMac.SetType("ns3::StaWifiMac",
                  "ActiveProbing", BooleanValue(true),
                  "Ssid", SsidValue(ssid));
  staDevs = wifi.Install(wifiPhy, wifiMac, staticStas);

  QueueSize size("40Mp");

  Config::Set("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/DeviceList/*/$ns3::WifiNetDevice/Mac/"
              "$ns3::ApWifiMac/Txop/$ns3::Txop/Queue/$ns3::WifiMacQueue/MaxDelay",
              TimeValue(Seconds(2)));

  Config::Set("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/DeviceList/*/$ns3::WifiNetDevice/Mac/"
              "$ns3::ApWifiMac/Txop/$ns3::Txop/Queue/$ns3::WifiMacQueue/DropPolicy",
              EnumValue(WifiMacQueue::DROP_OLDEST));

  Config::Set("/$ns3::NodeListPriv/NodeList/0/$ns3::Node/DeviceList/*/$ns3::WifiNetDevice/Mac/"
              "$ns3::ApWifiMac/Txop/$ns3::Txop/Queue/$ns3::WifiMacQueue/MaxSize",
              QueueSizeValue(size));

  mobilityStatic.Install(ap);
  mobilityStatic.Install(staticStas);

  BuildingsHelper::Install(ap);
  BuildingsHelper::Install(staticStas);

  IPstack.Install(nodes);

  Ipv4InterfaceContainer apInterface = addresses.Assign(apDev);
  Ipv4InterfaceContainer staticStasInterfaces = addresses.Assign(staDevs);

  auto ipv4_ap = ap.Get(0)->GetObject<Ipv4>();

  auto ipv4_staticSta = staticStas.Get(0)->GetObject<Ipv4>();
  auto source_staticSta = ipv4_staticSta->GetAddress(1, 0).GetLocal();

  auto destination = ipv4_ap->GetAddress(1, 0).GetLocal();
  std::cout << "static sta 1: " << source_staticSta << std::endl;

  std::cout << "destination address: " << destination << std::endl;

  uint16_t port = 6600;
  InetSocketAddress dest_socket(destination, port);
  OnOffHelper onoff("ns3::UdpSocketFactory", dest_socket);

  onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
  onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));

  Ptr<UniformRandomVariable> r = CreateObject<UniformRandomVariable>();
  r->SetAttribute("Min", DoubleValue(1.0));
  r->SetAttribute("Max", DoubleValue(2.0));

  onoff.SetAttribute("DataRate", DataRateValue(DataRate("400kbps")));
  onoff.SetAttribute("PacketSize", UintegerValue(paquetSize));
  onoff.SetAttribute("StartTime", TimeValue(Seconds(r->GetValue(1.0, 2.0))));
  AddressValue remoteAddress(dest_socket);
  onoff.SetAttribute("Remote", remoteAddress);

  PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));
  auto receiver = sink.Install(ap.Get(0));
  receiver.Start(Seconds(inicioScript));
  receiver.Stop(Seconds(finScript));


  //Comunicacion con NS3-AI
  for (int i = 0; i <= finScript * 10; i++)
  {
    Simulator::Schedule(Seconds(0.1 * i), [&onoff, &collector]() {
      Throughputs resultsThroughput = CalculateThroughput();
      Throughputs resultsThroughputStaticSta = CalculateThroughputStaticSta();

      DatarRate_ocupacion resultavgDataRateavgocupacion = CalculateTransmissionRate_and_ocupacion();
      DatarRate_ocupacion resultAvgDataRateOcupaciononlyStaticSta = CalculateTransmissionRate_and_ocupacion_for_StaticSta();

      if (useMLmodel)
      {
        Predictions preds;
        preds = collector.Func(devrx_packets, devtxAP_packets, devrxAP_packets, devtx_packets, phyrx0k_packets, phyrxerrortrace_packets, all_phytx_packets_SnifferTx, all_snifferRetransmissionCount, new_w, new_c, resultavgDataRateavgocupacion.avg_datarate, resultavgDataRateavgocupacion.avg_ocupacion, resultsThroughput.throughput, resultsThroughput.goodThroughput, devtx_packets_static_sta, all_phytx_packets_SnifferTxStaticSta, all_snifferRetransmissionCountStaticSta, resultAvgDataRateOcupaciononlyStaticSta.avg_datarate, resultAvgDataRateOcupaciononlyStaticSta.avg_ocupacion, resultsThroughputStaticSta.throughput, resultsThroughputStaticSta.goodThroughput);
        new_w = preds.w;
        new_c = preds.c;

        std::cout << "Nuevo valor de W predicho por el modelo:" << new_w << std::endl;
        std::cout << "Nuevo valor de C predicho por el modelo:" << new_c << std::endl;

        Config::Set("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/RemoteStationManager/WThreshold", UintegerValue(new_w));
        Config::Set("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/RemoteStationManager/SuccessThreshold", UintegerValue(new_c));
      }
      else
      {
        collector.Func(devrx_packets, devtxAP_packets, devrxAP_packets, devtx_packets, phyrx0k_packets, phyrxerrortrace_packets, all_phytx_packets_SnifferTx, all_snifferRetransmissionCount, new_w, new_c, resultavgDataRateavgocupacion.avg_datarate, resultavgDataRateavgocupacion.avg_ocupacion, resultsThroughput.throughput, resultsThroughput.goodThroughput, devtx_packets_static_sta, all_phytx_packets_SnifferTxStaticSta, all_snifferRetransmissionCountStaticSta, resultAvgDataRateOcupaciononlyStaticSta.avg_datarate, resultAvgDataRateOcupaciononlyStaticSta.avg_ocupacion, resultsThroughputStaticSta.throughput, resultsThroughputStaticSta.goodThroughput);
      }

      devrx_packets = 0;
      devtxAP_packets = 0;
      devrxAP_packets = 0;
      devtx_packets = 0;
      devtx_packets_static_sta = 0;
      phyrx0k_packets = 0;
      phyrxerrortrace_packets = 0;
      all_phytx_packets_SnifferTx = 0;
      all_phytx_packets_SnifferTxStaticSta = 0;
      all_snifferRetransmissionCount = 0;
      all_snifferRetransmissionCountStaticSta = 0;
    });
  }

  ApplicationContainer apps;
  for (NodeContainer::Iterator i = staticStas.Begin(); i != staticStas.End(); ++i)
  {
    apps.Add(onoff.Install(*i));
  }

  LayerParams *params = new LayerParams{
      &mobilityDynamic, &wifiPhy, &wifiMac, destination, port};

  Ptr<UniformRandomVariable> var = CreateObject<UniformRandomVariable>();
  var->SetAttribute("Min", DoubleValue(0.0));
  var->SetAttribute("Max", DoubleValue(numStas * 0.3));

  for (int i = 0; i < numStas; i += 1)
  {
    Simulator::Schedule(Seconds(var->GetValue()), &AddStation, &dynamicStas, &IPstack, &wifi, params, &addresses, &onoff);
  }

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  apps.Start(Seconds(inicioScript));
  apps.Stop(Seconds(finScript));

  Simulator::Stop(Seconds(finScript));

  //Configuracion de los callbacks
  Config::Connect("/NodeList/1/DeviceList/*/Mac/MacRx", MakeCallback(&DevRxTrace));
  Config::Connect("/NodeList/1/DeviceList/*/Mac/MacTx", MakeCallback(&DevTxTrace));
  Config::Connect("/NodeList/1/DeviceList/*/Mac/MacTx", MakeCallback(&DevTxTraceOnlyStaticSta));
  Config::Connect("/NodeList/0/DeviceList/*/Mac/MacTx", MakeCallback(&DevTxTraceAP));
  Config::Connect("/NodeList/0/DeviceList/*/Mac/MacRx", MakeCallback(&DevRxTraceAP));
  Config::Connect("/NodeList/0/DeviceList/*/Phy/State/RxOk", MakeCallback(&PhyRxOkTrace));
  Config::Connect("/NodeList/0/DeviceList/*/Phy/State/RxError", MakeCallback(&PhyRxErrorTrace));
  Config::Connect("/NodeList/1/DeviceList/*/Phy/MonitorSnifferTx", MakeCallback(&SnifferTxTrace));
  Config::Connect("/NodeList/1/DeviceList/*/Phy/MonitorSnifferTx", MakeCallback(&SnifferTxTraceOnlyStaticSta));

  wifiPhy.EnablePcap("Ap", apDev.Get(0), true);

  Simulator::Run();

  std::cout << "devrx_packets estacion: " << devrx_packets << std::endl;
  std::cout << "devtx-packets estacion: " << devtx_packets << std::endl;
  std::cout << "devrx_ackets punto acceso: " << devrxAP_packets << std::endl;
  std::cout << "devtx-packets punto acceso: " << devtxAP_packets << std::endl;
  std::cout << "phyrx0k_packets: " << phyrx0k_packets << std::endl;
  std::cout << "phyrxerrortrace_packets: " << phyrxerrortrace_packets << std::endl;
  retransmissionsPerPacket = all_phytx_retransmissionCount / static_cast<double>(all_phytx_packets_SnifferTx);
  std::cout << "RETRANSMISIONES/PAQUETE: " << retransmissionsPerPacket << std::endl;
  std::cout << "TRANSMISIONES SNIFFERTX: " << all_phytx_packets_SnifferTx << std::endl;
  std::cout << "RETRANSMISIONES SNIFFERTX: " << all_snifferRetransmissionCount << std::endl;
  std::cout << "TRANSMISIONES STATIC STA: " << all_phytx_packets_SnifferTxStaticSta << std::endl;
  std::cout << "RETRANSMISIONES STATIC STA: " << all_snifferRetransmissionCountStaticSta << std::endl;
  std::cout << "devtx-packets estacion ESTATICA: " << devtx_packets_static_sta << std::endl;

  if (!g_verbose)
  {
    for (size_t i = 0; i < throughputValues.size(); ++i)
    {
      std::cout << "THROPUGHPUT ->Intervalo: " << i + 1 << ": " << throughputValues[i] << " Mbps" << std::endl;
    }
    for (size_t i = 0; i < goodThroughputValues.size(); ++i)
    {
      std::cout << "GOOD THROPUGHPUT ->Intervalo: " << i + 1 << ": " << goodThroughputValues[i] << " Mbps" << std::endl;
    }
    for (size_t i = 0; i < averageSnifferTransmissionRateValues.size(); ++i)
    {
      std::cout << "TRANSMISSION RATE SNIFFER ->Intervalo: " << i + 1 << ": " << averageSnifferTransmissionRateValues[i] << " Mbps" << std::endl;
    }
  }

  Simulator::Destroy();
  collector.SetFinish();
  return 0;
}
