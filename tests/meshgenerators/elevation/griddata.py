from scipy.interpolate import griddata
import pandas
import numpy as np

df = pandas.read_csv('mount_glory.txt')

print(df['z'].max(), df['z'].min())


N = 1000
x = np.linspace(df['x'].min(), df['x'].max(), N)
y = np.linspace(df['y'].min(), df['y'].max(), N)

print(x)
print(y)

data = griddata((df['x'], df['y']), df['z'], (x, y), method='nearest')
print(data.min(), data.max())
