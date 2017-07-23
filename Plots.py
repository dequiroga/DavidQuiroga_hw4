#Genera las graficas de los datos que se obtienen de GraphicPoint.c

import numpy as np 
import matplotlib.pyplot as plt

mapa=np.loadtxt('map_data.txt')
#Arreglo de 500(Latitud)x744(longitud) con el mapa de la tierra, 0 si es mar y 1 si es tierra

plt.imshow(mapa, cmap='Greens')
plt.show()
