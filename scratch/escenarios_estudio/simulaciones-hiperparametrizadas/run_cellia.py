import random
import os
from ctypes import *
import pandas as pd
import matplotlib.pyplot as plt
from py_interface import *
import argparse

parser = argparse.ArgumentParser(description="Script for ns-3 AI integration")
parser.add_argument('--w', type=int, required=True, help="Width parameter")
parser.add_argument('--num_stas', type=int, required=True, help="Number of stations")
parser.add_argument('--tam_red', type=int, required=True, help="Size of the network")
parser.add_argument('--seedValue', type=int, required=True, help="Seed value for random number generator")

args = parser.parse_args()

class Env(Structure):
    _pack_ = 1
    _fields_ = [
        ('devrx_packets', c_int),
        ('devtxAP_packets', c_int),
        ('devrxAP_packets', c_int),
        ('devtx_packets', c_int),
        ('phyrx0k_packets', c_int),
        ('phyrxerrortrace_packets', c_int),
        ('phytx_packets', c_int),
        ('retransmissions', c_int),
        ('throughput', c_double),
        ('goodThroughput', c_double),
    ]


class Act(Structure):
    _pack_ = 1
    _fields_ = [
        ('c', c_int)
    ]

columns = ['devrx_packets', 'devtxAP_packets', 'devrxAP_packets', 'devtx_packets', 
           'phyrx0k_packets', 'phyrxerrortrace_packets', 'phytx_packets','retransmissions',
           'throughput','goodThroughput','retansmissionsPerPacket', 'w']

mempool_key = 1234                                          
mem_size = 4096                                             
memblock_key = 2333                                         

paquete = 732

lista_dataframes = []

exp = Experiment(mempool_key, mem_size, "sim_hyperparams.cc", "./")     

try:
    dataframe = pd.DataFrame(columns=columns)

    ns3Settings = {
        'useARF': True,
        "w": args.w,
        "numStas": args.num_stas,
        "tam_red": args.tam_red,
        "seedValue": args.seedValue
    }
    
    exp.reset()                                             
    rl = Ns3AIRL(memblock_key, Env, Act)                    
    setting = ns3Settings

    pro = exp.run(setting=ns3Settings, show_output=True)    
    while not rl.isFinish():
        with rl as data:
            if data is None:
                break
            

            row_data = [data.env.devrx_packets, data.env.devtxAP_packets, data.env.devrxAP_packets, 
                        data.env.devtx_packets, data.env.phyrx0k_packets, data.env.phyrxerrortrace_packets, 
                        data.env.phytx_packets, data.env.retransmissions, data.env.throughput, data.env.goodThroughput]
            
            if data.env.phytx_packets != 0:
                retransmission_per_packet = data.env.retransmissions / data.env.phytx_packets
            else:
                retransmission_per_packet = 0
            
            row_data.append(retransmission_per_packet)
            row_data.append(args.w)  # Añadir el valor de 'w'
            dataframe.loc[len(dataframe)] = row_data
            
    pro.wait()  # Wait for the ns-3 to stop

    folder_path = f"dataset-cellia/tam_red_{ns3Settings['tam_red']}/w_{ns3Settings['w']}/num_stas_{ns3Settings['numStas']}"
    os.makedirs(folder_path, exist_ok=True)

    filename = f"{folder_path}/ns3ai-cellia_stats_seed_{ns3Settings['seedValue']}.csv"
    dataframe.to_csv(filename, index=True, decimal='.')
    print(f"Datos guardados en {filename}")    
  
except Exception as e:
    print('Something wrong')
    print(e)
finally:
    del exp
