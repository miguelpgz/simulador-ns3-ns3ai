import pandas as pd
import numpy as np
import os
import glob
import logging
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, RandomizedSearchCV
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error
import joblib
import matplotlib.pyplot as plt
from scipy.stats import randint

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger()

# Ruta donde están almacenados los archivos CSV
path = '/home/pgz/Escritorio/simulador/simulador-ns3/combined-dataset'

# Obtenemos archivos CSV en el directorio y sus subdirectorios
logger.info('Buscando archivos CSV...')
all_files = glob.glob(os.path.join(path, "**/*.csv"), recursive=True)
logger.info(f"Cantidad de archivos CSV encontrados: {len(all_files)}")

# Cargamos todos los archivos CSV y los concatenamos en un solo DataFrame, omitiendo las primeras 50 filas de cada archivo que se corresponden a los primeros 0.5 segundos de simulación
logger.info('Cargando archivos CSV...')
df_list = [pd.read_csv(file, skiprows=range(1, 51)) for file in all_files]
full_data = pd.concat(df_list, ignore_index=True)

# Eliminamos variables que no tienen correlación con el goodput
full_data.drop(columns=['devrx_packets', 'devtxAP_packets'], inplace=True)

# Seleccionamos las columnas a normalizar, excluyendo los hiperparámetros y la variable objetivo
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

# Definimos los parámetros para RandomizedSearchCV
param_dist = {
    'n_estimators': randint(50, 200),
    'max_depth': [10, 20, None],
    'min_samples_split': randint(2, 10),
    'min_samples_leaf': randint(1, 4)
}

n_iter = 10
logger.info('Buscando los mejores hiperparámetros usando búsqueda aleatoria...')
random_search = RandomizedSearchCV(
    RandomForestRegressor(),
    param_distributions=param_dist,
    n_iter=n_iter,  # Número de combinaciones aleatorias a probar
    cv=5,  # Número de pliegues de validación cruzada
    scoring='neg_mean_squared_error',
    n_jobs=-1,  # Usar dos núcleos
    random_state=42,
    verbose=0  # Nivel de detalle en los logs
)

# Ajustar el modelo y registrar los intentos
random_search.fit(X_train, y_train)

# Obtenemos los mejores hiperparámetros
best_params = random_search.best_params_
logger.info(f'Los mejores hiperparámetros encontrados son: {best_params}')

# Entrenamos el modelo con los mejores hiperparámetros
logger.info(f'Creando y entrenando el modelo RandomForest con los mejores hiperparámetros...')
rf = RandomForestRegressor(**best_params)
rf.fit(X_train, y_train)

# Evaluamos el rendimiento del modelo
y_pred = rf.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
logger.info(f"Mean Squared Error: {mse}")

# Guardamos el modelo y el scaler
model_filename = 'random_forest_model_aux.joblib'
scaler_filename = 'scaler_aux.joblib'
joblib.dump(rf, model_filename)
joblib.dump(scaler, scaler_filename)
logger.info(f'Modelo guardado en {model_filename} y scaler guardado en {scaler_filename}')

# Graficamos los resultados de la validación cruzada
results = pd.DataFrame(random_search.cv_results_)
plt.figure(figsize=(10, 6))
for param, values in param_dist.items():
    plt.plot(results[f'param_{param}'], -results['mean_test_score'], marker='o', label=param)
plt.xlabel('Hiperparámetros')
plt.ylabel('Mean Squared Error (negativo)')
plt.title('Resultados de la Búsqueda Aleatoria para RandomForest')
plt.legend()
plt.grid(True)
plt.show()
