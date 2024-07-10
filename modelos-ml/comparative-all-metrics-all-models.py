import os
import pandas as pd
import matplotlib.pyplot as plt

def load_all_csv(directory):
    data_frames = []
    for subdir, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.csv'):
                file_path = os.path.join(subdir, file)
                df = pd.read_csv(file_path)
                data_frames.append(df)
    return pd.concat(data_frames, ignore_index=True)

def load_selected_models(paths, selected_models):
    data = {}
    for model, path in paths.items():
        if model in selected_models:
            data[model] = load_all_csv(path)
    return data

extract_paths = {
    'knn': '../results-knn', 
    'noknn': '../results-noknn-aux', 
    'rf': '/home/pgz/Escritorio/simulador/simulador-ns3/results-random-forest',
    'knn_ratio': '/home/pgz/Escritorio/simulador/simulador-ns3/results-knn-ratio',
    'rf_ratio': '/home/pgz/Escritorio/simulador/simulador-ns3/results-random-forest-ratio'
}

selected_models = ['rf_ratio','noknn']

data = load_selected_models(extract_paths, selected_models)

any_model_key = next(iter(data))
metrics = ['goodThroughput', 'retransmissionsPerPacket']

output_directory = '/home/pgz/Escritorio/simulador/simulador-ns3/kNN/graficas-models'
os.makedirs(output_directory, exist_ok=True)

for metric in metrics:
    plt.figure(figsize=(12, 8))
    
    for model, df in data.items():
        avg_data = df.groupby('num_stas')[metric].mean().reset_index()
        label = {
            'knn': 'Con KNN',
            'noknn': 'ARF por defecto',
            'rf': 'Random Forest',
            'knn_ratio': 'KNN Ratio',
            'rf_ratio': 'Random Forest Ratio'
        }[model]
        marker = {
            'knn': 'o',
            'noknn': 'x',
            'rf': 's',
            'knn_ratio': '^',
            'rf_ratio': 'v'
        }[model]
        color = 'orange' if model == 'noknn' else None
        plt.plot(avg_data['num_stas'], avg_data[metric], label=label, marker=marker, color=color)
    
    plt.xlabel('Number Of Stations', fontsize=28) 
    ylabel = metric
    if metric == "goodThroughput":
        ylabel = "Goodput in Mbps"
        plt.ylim(0, 4)  
    if metric == "retransmissionsPerPacket":
        ylabel = "Retransmissions Per Packet"

    plt.ylabel(ylabel, fontsize=28) 
    plt.xticks(fontsize=22)
    plt.yticks(fontsize=22)

    handles, labels = plt.gca().get_legend_handles_labels()
    for i in range(len(labels)):
        plt.legend(handles, labels, fontsize=24)  # Increase size for specific labels

    plt.grid(True)
    output_path = os.path.join(output_directory, f'{metric}_comparative.png')
    plt.savefig(output_path)
    plt.close()
