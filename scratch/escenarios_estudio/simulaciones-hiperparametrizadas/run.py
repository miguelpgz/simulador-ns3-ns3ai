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
from ctypes import *
import pandas as pd
import matplotlib.pyplot as plt

from py_interface import *


# The environment (in this example, contain 'a' and 'b')
# shared between ns-3 and python with the same shared memory
# using the ns3-ai model.

def calculo_stats(dataframe):
    #lista_devtx = dataframe['phytx_packets'].tolist()
    paquetes_totales = dataframe.sum().sum() 
    print("Mbps comunicacion:" , ((paquetes_totales*512)/0.4) / 1000 )



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
        ('meanThroughputValue', c_double),

        
    ]

# The result (in this example, contain 'c') calculated by python
# and put back to ns-3 with the shared memory.
class Act(Structure):
    _pack_ = 1
    _fields_ = [
        ('c', c_int)
    ]

columns = ['devrx_packets', 'devtxAP_packets', 'devrxAP_packets', 'devtx_packets', 
           'phyrx0k_packets', 'phyrxerrortrace_packets', 'phytx_packets','retransmissions','meanThroughputValue']



ns3Settings = {'finScript': 30, "verbose":False, 'posX': 0}

mempool_key = 1234                                          # memory pool key, arbitrary integer large than 1000
mem_size = 4096                                             # memory pool size in bytes
memblock_key = 2333                                         # memory block key, need to keep the same in the ns-3 script

distances = [0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125]
paquetes = [732,1098,1464,2197,2929,4394,5859,6591]

etiquetas = [
    "ErpOfdmRate6Mbps",
    "ErpOfdmRate9Mbps",
    "ErpOfdmRate12Mbps",
    "ErpOfdmRate18Mbps",
    "ErpOfdmRate24Mbps",
    "ErpOfdmRate36Mbps",
    "ErpOfdmRate48Mbps",
    "ErpOfdmRate54Mbps"
]

lista_dataframes = []

exp = Experiment(mempool_key, mem_size, "sim_hyperparams.cc", "./")     

try:
    for paquete in paquetes:
        dataframe = pd.DataFrame(columns=columns)
        ns3Settings['paquetes'] = paquete
        for distance in distances:
            ns3Settings['posX'] = distance
            exp.reset()                                             # Reset the environment
            rl = Ns3AIRL(memblock_key, Env, Act)                    # Link the shared memory block with ns-3 script
            setting=ns3Settings

            pro = exp.run(setting=ns3Settings, show_output=True)    # Set and run the ns-3 script (sim.cc)
            while not rl.isFinish():
                with rl as data:
                    if data == None:
                        break
                    # AI algorithms here and put the data back to the action
                    #data.act.c = 99

                    # Agregamos datos al dataframe
                    row_data = [data.env.devrx_packets, data.env.devtxAP_packets, data.env.devrxAP_packets, 
                                data.env.devtx_packets, data.env.phyrx0k_packets, data.env.phyrxerrortrace_packets, 
                                data.env.phytx_packets,data.env.retransmissions, data.env.meanThroughputValue]
                    #dataframe = dataframe.append(pd.Series(row_data, index=dataframe.columns), ignore_index=True)
                    dataframe.loc[len(dataframe)] = row_data
            
            
            pro.wait()  # Wait the ns-3 to stop
        print(dataframe)
            #calculo_stats(dataframe)
        lista_dataframes.append(dataframe)


    plt.figure(figsize=(10, 6))

    for i in range(len(lista_dataframes)):
        plt.plot(distances, lista_dataframes[i]["meanThroughputValue"], marker='o', label=etiquetas[i])
        plt.legend()

    plt.title('Mean Throughput Value vs Distance')
    plt.xlabel('Distance (m)')
    plt.ylabel('Mean Throughput Value (Mbps)')
    plt.grid(True)
    plt.show()

except Exception as e:
    print('Something wrong')
    print(e)
finally:
    del exp



