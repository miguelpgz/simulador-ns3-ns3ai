import random
from ctypes import *
import pandas as pd
import matplotlib.pyplot as plt
import itertools
import os

from py_interface import *


# La clase `Env` define las métricas que se compartirán entre ns-3 y Python.
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
        ('w', c_int),
        ('c', c_int),
        ('avg_datarate', c_double),
        ('ocupacion', c_double),
        ('throughput', c_double),
        ('goodThroughput', c_double),

        ('devtx_packetsStaticSta', c_int),
        ('phytx_packetsStaticSta', c_int),
        ('retransmissionsStaticSta', c_int),
        ('avg_datarateStaticSta', c_double),
        ('ocupacionStaticSta', c_double),
        ('throughputStaticSta', c_double),
        ('goodThroughputStaticSta', c_double),


    ]

# La clase `Act` define la acción que se calculará en Python y se devolverá a ns-3.
class Act(Structure):
    _pack_ = 1
    _fields_ = [
         ('predicted_w', c_int),
        ('predicted_c', c_int)
    ]

# Columnas del DataFrame
columns = ['devrx_packets', 'devtxAP_packets', 'devrxAP_packets', 'devtx_packets', 
           'phyrx0k_packets', 'phyrxerrortrace_packets', 'phytx_packets', 'retransmissions','avg_datarate','ocupacion',
           'throughput', 'goodThroughput', 'retransmissionsPerPacket', 'w','c','tam_red','num_stas']


columnsStaticSta = ['devtx_packetsStaticSta','phytx_packetsStaticSta','retransmissionsStaticSta','avg_datarateStaticSta','ocupacionStaticSta','throughputStaticSta','goodThroughputStaticSta','retransmissionsPerPacket','w','c','tam_red','num_stas']

# Hiperparámetros
tam_red_values = [40,70,100]
wc_values = [(2, 10), (3, 9), (4, 8), (5, 7), (6, 6)]
num_stas_values =  [14]
seed_values = [6,7,8,9,10]



# Claves de memoria compartida
mempool_key = 1234
mem_size = 4096
memblock_key = 2333

# Función para ejecutar una combinación de hiperparámetros
def run_simulation(tam_red, w, c, num_stas, seed):
    ns3Settings = {
        'finScript': 30,
        'verbose': False,
        'numStas': num_stas,
        'w': w,
        'c':c,
        'tam_red': tam_red,
        'seedValue': seed,
        'verbose': False,
        'useARF': True,
    }

    exp = Experiment(mempool_key, mem_size, "sim_hyperparams.cc", "./")
    try:
        dataframe = pd.DataFrame(columns=columns)
        dataframeStaticSta = pd.DataFrame(columns=columnsStaticSta)
        exp.reset()  # Reset the environment
        rl = Ns3AIRL(memblock_key, Env, Act)  # Link the shared memory block with ns-3 script
        pro = exp.run(setting=ns3Settings, show_output=True)  # Set and run the ns-3 script
        while not rl.isFinish():
            with rl as data:
                if data is None:
                    break
                # Extract data from the shared memory
                row_data = [data.env.devrx_packets, data.env.devtxAP_packets, data.env.devrxAP_packets, 
                            data.env.devtx_packets, data.env.phyrx0k_packets, data.env.phyrxerrortrace_packets, 
                            data.env.phytx_packets, data.env.retransmissions, data.env.avg_datarate,data.env.ocupacion,data.env.throughput, 
                            data.env.goodThroughput]

                row_data_staticSta = [data.env.devtx_packetsStaticSta, data.env.phytx_packetsStaticSta, data.env.retransmissionsStaticSta, data.env.avg_datarateStaticSta, data.env.ocupacionStaticSta, data.env.throughputStaticSta, data.env.goodThroughputStaticSta]

                # Calculate retransmissions per packet
                if data.env.phytx_packets != 0:
                    retransmission_per_packet = data.env.retransmissions / data.env.phytx_packets
                else:
                    retransmission_per_packet = 0

                if data.env.phytx_packetsStaticSta != 0:
                    retransmission_per_packet_static_sta = data.env.retransmissionsStaticSta / data.env.phytx_packetsStaticSta
                else:
                    retransmission_per_packet_static_sta = 0
                
                row_data_staticSta.append(retransmission_per_packet_static_sta)
                row_data_staticSta.append(w)  # Add the value of 'w' to the row data for the static sta
                row_data_staticSta.append(c)
                row_data_staticSta.append(tam_red)
                row_data_staticSta.append(num_stas+1)

                row_data.append(retransmission_per_packet)
                row_data.append(w)  # Add the value of 'w' to the row data
                row_data.append(c)
                row_data.append(tam_red)
                row_data.append(num_stas+1)

                dataframe.loc[len(dataframe)] = row_data
                dataframeStaticSta.loc[len(dataframeStaticSta)] = row_data_staticSta


        pro.wait()  # Wait for ns-3 to stop
        
        for column in columns:
            sum_value = dataframe[column].sum()
            print(f"La suma de la columna {column} es: {sum_value}")
#
        # Crear la estructura de carpetas
        folder_path = f"dataset2-final/tam_red_{tam_red}/num_stas_{num_stas+1}/wc_{w}_{c}/seed_{seed}"

        folder_path_static_sta = f"results-staticSta/tam_red_{tam_red}/num_stas_{num_stas+1}/wc_{w}_{c}/seed_{seed}"

        os.makedirs(folder_path, exist_ok=True)
        os.makedirs(folder_path_static_sta, exist_ok=True)


        # Save DataFrame to CSV
        filename = f"{folder_path}/ns3ai_stats_seed_{seed}.csv"
        filenameStaticSta = f"{folder_path_static_sta}/ns3ai_stats_static_sta_seed_{seed}.csv"


        dataframe.to_csv(filename, index=False, decimal='.')
        dataframeStaticSta.to_csv(filenameStaticSta, index=False, decimal='.')

        print(f"Datos guardados en {filename}")

    except Exception as e:
        print('Algo salió mal')
        print(e)
    finally:
        del exp

# Crear combinaciones de hiperparámetros y ejecutar simulaciones
combinations = list(itertools.product(tam_red_values, wc_values, num_stas_values, seed_values))

for combo in combinations:
    tam_red, (w, c), num_stas, seed = combo
    run_simulation(tam_red, w, c, num_stas, seed)

