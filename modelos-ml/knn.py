import pandas as pd
import os
import glob
import logging
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.neighbors import KNeighborsRegressor
from sklearn.metrics import mean_squared_error
import joblib
import matplotlib.pyplot as plt

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger()

# Ruta donde están almacenados los archivos CSV
path = '/home/pgz/Escritorio/simulador/simulador-ns3/combined-dataset' 

# Obtenemos archivos CSV en el directorio y sus subdirectorios
logger.info('Buscando archivos CSV...')
all_files = glob.glob(os.path.join(path, "**/*.csv"), recursive=True)
logger.info(f"Cantidad de archivos CSV encontrados: {len(all_files)}")

# Cargamos todos los archivos CSV y concatenarlos en un solo DataFrame, omitiendo las primeras 50 filas de cada archivo que se corresponden a los primeros 5 segundos de simulacion
logger.info('Cargando archivos CSV...')
df_list = [pd.read_csv(file, skiprows=range(1, 51)) for file in all_files] #ignoramos las 50 primeras filas que se corresponden a los primeros 0.5 segundos de simulacion
full_data = pd.concat(df_list, ignore_index=True)

# Eliminamos variables que no tienen correlación con el goodput
full_data.drop(columns=['devrx_packets','devtxAP_packets'], inplace=True)

# Seleccionamos las columnas a normalizar, excluyendo los hiperparámetros y la var objetivo
columns_to_normalize = full_data.columns.difference(['w', 'c', 'tam_red', 'num_stas', 'goodThroughput'])

# Normalizamos los datos
logger.info('Normalizando datos...')
scaler = StandardScaler()
full_data[columns_to_normalize] = scaler.fit_transform(full_data[columns_to_normalize])

# Separamos características y etiqueta
logger.info('Separando características y etiqueta...')
X = full_data.drop(columns=['goodThroughput'])  # goodThroughput es la variable objetivo
y = full_data['goodThroughput']

# Dividimos los datos en conjunto de entrenamiento y conjunto de prueba
logger.info('Dividiendo los datos en conjunto de entrenamiento y prueba...')
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Definimos los parámetros para GridSearchCV
param_grid = {'n_neighbors': range(1, 21)}
logger.info('Buscando el mejor valor de k usando validación cruzada...')
grid_search = GridSearchCV(KNeighborsRegressor(), param_grid, cv=5, scoring='neg_mean_squared_error')
grid_search.fit(X_train, y_train)

# Obtenemos el mejor valor de k
best_k = grid_search.best_params_['n_neighbors']
logger.info(f'El mejor valor de k encontrado es: {best_k}')

# Entrenamos el modelo con el mejor valor de k
logger.info(f'Creando y entrenando el modelo kNN con k={best_k}...')
knn = KNeighborsRegressor(n_neighbors=best_k)
knn.fit(X_train, y_train)

# Evaluamos el rendimiento del modelo
y_pred = knn.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
logger.info(f"Mean Squared Error: {mse}")

# Guardamos el modelo y el scaler
model_filename = 'knn_model_aux.joblib'
scaler_filename = 'scaler_aux.joblib'
joblib.dump(knn, model_filename)
joblib.dump(scaler, scaler_filename)
logger.info(f'Modelo guardado en {model_filename} y scaler guardado en {scaler_filename}')

# Graficamos los resultados de la validación cruzada
results = pd.DataFrame(grid_search.cv_results_)
plt.figure(figsize=(12, 8))
plt.plot(results['param_n_neighbors'], -results['mean_test_score'], marker='o')
plt.xlabel('Número de vecinos (k)', fontsize=28)
plt.ylabel('Mean Squared Error', fontsize=28)
plt.xticks(fontsize=22)
plt.yticks(fontsize=22)
#plt.title('Resultados de la Validación Cruzada para kNN')
plt.grid(True)
plt.show()
