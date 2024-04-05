import pandas as pd

df = pd.DataFrame(columns=['A', 'B'])
df = df.append({'A': 1, 'B': 2}, ignore_index=True)
print(df)
