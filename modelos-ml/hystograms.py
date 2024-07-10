import os
import pandas as pd
import matplotlib.pyplot as plt

def load_data_from_subfolders(base_folder_path):
    all_data = []
    for root, _, files in os.walk(base_folder_path):
        for file in files:
            if file.endswith('.csv'):
                file_path = os.path.join(root, file)
                data = pd.read_csv(file_path)
                all_data.append(data)
    if all_data:
        return pd.concat(all_data, ignore_index=True)
    else:
        return pd.DataFrame()  

base_path = '../results-knn-ratio'  # Cambiar esto a la ruta donde están las carpetas
tam_red_40_path = os.path.join(base_path, 'tam_red_40')
tam_red_70_path = os.path.join(base_path, 'tam_red_70')
tam_red_100_path = os.path.join(base_path, 'tam_red_100')

data_tam_red_40 = load_data_from_subfolders(tam_red_40_path)
data_tam_red_70 = load_data_from_subfolders(tam_red_70_path)
data_tam_red_100 = load_data_from_subfolders(tam_red_100_path)

if not data_tam_red_40.empty:
    data_tam_red_40['tam_red'] = 40
if not data_tam_red_70.empty:
    data_tam_red_70['tam_red'] = 70
if not data_tam_red_100.empty:
    data_tam_red_100['tam_red'] = 100

dataframes = [df for df in [data_tam_red_40, data_tam_red_70, data_tam_red_100] if not df.empty]

if not dataframes:
    print("No hay datos para concatenar. Verifica el contenido de las carpetas.")
else:
    all_data = pd.concat(dataframes, ignore_index=True)

    wc_values = [(2, 10), (3, 9), (4, 8), (5, 7), (6, 6)]

    frequency_data = []

    for size in [40, 70, 100]:
        size_data = all_data[all_data['tam_red'] == size]
        for w, c in wc_values:
            count = len(size_data[(size_data['w'] == w) & (size_data['c'] == c)])
            frequency_data.append({'tam_red': size, 'w': w, 'c': c, 'count': count})

    frequency_df = pd.DataFrame(frequency_data)

    print(frequency_df)

    for size in [40, 70, 100]:
        plt.figure(figsize=(10, 6))
        subset = frequency_df[frequency_df['tam_red'] == size]
        plt.bar([f'({row.w},{row.c})' for idx, row in subset.iterrows()], subset['count'], edgecolor='black')
        print("size:")
        print(size)
        plt.xlabel('Tuplas (W, C)', fontsize=22)
        plt.xticks(fontsize=20)
        plt.yticks(fontsize=20)
        plt.ylabel('Frecuencia', fontsize=22)
        plt.grid(True)
        plt.show()
