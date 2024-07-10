

import random
from ctypes import *
import pandas as pd
import matplotlib.pyplot as plt

from py_interface import *



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


class Act(Structure):
    _pack_ = 1
    _fields_ = [
        ('c', c_int)
    ]

columns = ['devrx_packets', 'devtxAP_packets', 'devrxAP_packets', 'devtx_packets', 
           'phyrx0k_packets', 'phyrxerrortrace_packets', 'phytx_packets','retransmissions','meanThroughputValue']



ns3Settings = {'finScript': 30, "verbose":False, 'posX': 0}

mempool_key = 1234                                          
mem_size = 4096                                             
memblock_key = 2333                                         

distances = [0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125]
paquetes = [732,1098,1464,2197,2929,4394,5859,6591]

etiquetas = [
    "OfdmRate6Mbps",
    "OfdmRate9Mbps",
    "OfdmRate12Mbps",
    "OfdmRate18Mbps",
    "OfdmRate24Mbps",
    "OfdmRate36Mbps",
    "OfdmRate48Mbps",
    "OfdmRate54Mbps"
]

lista_dataframes = []

exp = Experiment(mempool_key, mem_size, "estudio_grafica.cc", "./")     

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

                    # Agregamos datos al dataframe
                    row_data = [data.env.devrx_packets, data.env.devtxAP_packets, data.env.devrxAP_packets, 
                                data.env.devtx_packets, data.env.phyrx0k_packets, data.env.phyrxerrortrace_packets, 
                                data.env.phytx_packets,data.env.retransmissions, data.env.meanThroughputValue]
                    dataframe.loc[len(dataframe)] = row_data
            
            
            pro.wait()  # Wait the ns-3 to stop
        print(dataframe)
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




