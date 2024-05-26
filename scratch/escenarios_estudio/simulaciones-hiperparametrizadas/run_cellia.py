# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-
# Copyright (c) 2020 Huazhong University of Science and Technology, Dian Group
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: Pengyu Liu <eic_lpy@hust.edu.cn>
#         Hao Yin <haoyin@uw.edu>

# An example for the ns3-ai model to illustrate the data exchange
# between python-based AI frameworks and ns-3.
#
# In this example, we have two variable a and b in ns-3,
# and then put them into the shared memory using python to calculate
#
#       c = a + b
#
# Finally, we put back c to the ns-3.

import random
import os
from ctypes import *
import pandas as pd
import matplotlib.pyplot as plt
from py_interface import *
import argparse

# Define the parser and arguments
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

# The result (in this example, contain 'c') calculated by python
# and put back to ns-3 with the shared memory.
class Act(Structure):
    _pack_ = 1
    _fields_ = [
        ('c', c_int)
    ]

columns = ['devrx_packets', 'devtxAP_packets', 'devrxAP_packets', 'devtx_packets', 
           'phyrx0k_packets', 'phyrxerrortrace_packets', 'phytx_packets','retransmissions','throughput','goodThroughput','retansmissionsPerPacket']

mempool_key = 1234                                          # memory pool key, arbitrary integer large than 1000
mem_size = 4096                                             # memory pool size in bytes
memblock_key = 2333                                         # memory block key, need to keep the same in the ns-3 script

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
    
    exp.reset()                                             # Reset the environment
    rl = Ns3AIRL(memblock_key, Env, Act)                    # Link the shared memory block with ns-3 script
    setting = ns3Settings

    pro = exp.run(setting=ns3Settings, show_output=True)    # Set and run the ns-3 script (sim.cc)
    while not rl.isFinish():
        with rl as data:
            if data is None:
                break
            # AI algorithms here and put the data back to the action
            #data.act.c = 99

            # Agregamos datos al dataframe
            row_data = [data.env.devrx_packets, data.env.devtxAP_packets, data.env.devrxAP_packets, 
                        data.env.devtx_packets, data.env.phyrx0k_packets, data.env.phyrxerrortrace_packets, 
                        data.env.phytx_packets, data.env.retransmissions, data.env.throughput, data.env.goodThroughput]
            
            # Calcular retransmissionPerPacket
            if data.env.phytx_packets != 0:
                retransmission_per_packet = data.env.retransmissions / data.env.phytx_packets
            else:
                retransmission_per_packet = 0
            
            row_data.append(retransmission_per_packet)
            dataframe.loc[len(dataframe)] = row_data
            
    pro.wait()  # Wait for the ns-3 to stop

    # Crear la estructura de carpetas
    folder_path = f"dataset-cellia/tam_red_{ns3Settings['tam_red']}/w_{ns3Settings['w']}/num_stas_{ns3Settings['numStas']}"
    os.makedirs(folder_path, exist_ok=True)

    # Save DataFrame to CSV
    filename = f"{folder_path}/ns3ai-cellia_stats_seed_{ns3Settings['seedValue']}.csv"
    dataframe.to_csv(filename, index=True, decimal='.')
    print(f"Datos guardados en {filename}")    
  
except Exception as e:
    print('Something wrong')
    print(e)
finally:
    del exp
