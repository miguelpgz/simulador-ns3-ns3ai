
import random
from ctypes import *
import pandas as pd
import matplotlib.pyplot as plt
import joblib
import numpy as np
import logging
from sklearn.preprocessing import StandardScaler
from py_interface import *
import itertools
import os


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

class Act(Structure):
    _pack_ = 1
    _fields_ = [
        ('predicted_w', c_int),
        ('predicted_c', c_int)
    ]

columns = ['devrx_packets', 'devtxAP_packets', 'devrxAP_packets', 'devtx_packets', 
           'phyrx0k_packets', 'phyrxerrortrace_packets', 'phytx_packets', 'retransmissions','avg_datarate','ocupacion',
           'throughput', 'goodThroughput', 'retransmissionsPerPacket', 'w','c','tam_red','num_stas','goodput_retransmissions']


tam_red_values = [40,70,100]
num_stas_values =  [0,4,8,12,16,20,24,26,28]
seed_values = [111,222,333,444,666,777,888,999]

mempool_key = 1234
mem_size = 4096
memblock_key = 2333

paquete = 732
lista_dataframes = []

exp = Experiment(mempool_key, mem_size, "sim_hyperparams.cc", "./")


logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger()

# Cargar el modelo kNN y el scaler
model_filename = '/home/pgz/Escritorio/simulador/simulador-ns3/models/knn_model_ratio.joblib'
scaler_filename = '/home/pgz/Escritorio/simulador/simulador-ns3/models/scaler_ratio.joblib'
logger.info('Cargando el modelo y el scaler...')
knn = joblib.load(model_filename)
scaler = joblib.load(scaler_filename)

# Lista de valores de 'w' para probar en kNN y quedarnos con el mejor
wc_values = [(2, 10), (3, 9), (4, 8), (5, 7), (6, 6)]

def run_simulation(tam_red, num_stas, seed):
    ns3Settings = {
        'finScript': 30,
        'useKNN': True,
        'verbose': False,
        'numStas': num_stas,
        'tam_red': tam_red,
        'seedValue': seed,
        'useARF': True,
    }
    
    exp = Experiment(mempool_key, mem_size, "sim_hyperparams.cc", "./")

    try:
        dataframe = pd.DataFrame(columns=columns)
        exp.reset()
        rl = Ns3AIRL(memblock_key, Env, Act)
        pro = exp.run(setting=ns3Settings, show_output=True)

        while not rl.isFinish():
            with rl as data:
                if data is None:
                    break

                # Calcular retransmissionPerPacket
                if data.env.phytx_packets != 0:
                    retransmission_per_packet = data.env.retransmissions / data.env.phytx_packets
                else:
                    retransmission_per_packet = 0

                goodput_retransmissions_col = data.env.goodThroughput / (data.env.retransmissions + 1)

                # Recibir datos de ns3
                row_data = [
                    data.env.devrx_packets, data.env.devtxAP_packets, data.env.devrxAP_packets, 
                    data.env.devtx_packets, data.env.phyrx0k_packets, data.env.phyrxerrortrace_packets, 
                    data.env.phytx_packets, data.env.retransmissions, data.env.avg_datarate, data.env.ocupacion,data.env.throughput, data.env.goodThroughput,
                    retransmission_per_packet, data.env.w, data.env.c, ns3Settings['tam_red'], ns3Settings['numStas']+1, goodput_retransmissions_col
                ]


                #print(row_data)

              

                # Agregar fila al DataFrame
                dataframe.loc[len(dataframe)] = row_data

                # Crear un DataFrame con los datos recibidos
                data_df = pd.DataFrame([row_data], columns=columns)

                # Seleccionar las columnas que no queremos normalizar
                columns_to_normalize = data_df.columns.difference(['w','c','tam_red', 'num_stas','goodput_retransmissions'])

                # Normalizar los datos recibidos
                data_df[columns_to_normalize] = scaler.transform(data_df[columns_to_normalize])

                # Crear una lista para almacenar los goodput predichos
                predicted_goodputs = []

                # Predecir el goodput para cada valor de w
                for w, c in wc_values:
                    data_df['w'] = w
                    data_df['c'] = c
                    # X_new = data_df.drop(columns=['goodThroughput'])
                    X_new = data_df.drop(columns=['goodput_retransmissions'])
                    
                    predicted_goodput = knn.predict(X_new)
                    predicted_goodputs.append((predicted_goodput[0], w, c))


               # Calcular la tupla (w, c) que maximiza el goodput
                max_goodput, optimal_w, optimal_c = max(predicted_goodputs, key=lambda x: x[0])

                # Enviar el valor óptimo de w a ns3
                data.act.predicted_w = optimal_w
                data.act.predicted_c = optimal_c


        pro.wait()

        folder_path = f"results-knn-ratio/tam_red_{tam_red}/num_stas_{num_stas+1}"
        os.makedirs(folder_path, exist_ok=True)

        filename = f"{folder_path}/ns3ai_stats_seed_{seed}.csv"
        dataframe.to_csv(filename, index=False, decimal='.')
        print(f"Datos guardados en {filename}")


    except Exception as e:
        logger.error('Something went wrong')
        logger.error(e)
    finally:
        del exp

combinations = list(itertools.product(tam_red_values, num_stas_values, seed_values))

for combo in combinations:
    tam_red, num_stas, seed = combo
    run_simulation(tam_red, num_stas, seed)

