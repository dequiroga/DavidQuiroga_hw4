#Genera las graficas de los datos que se obtienen de GraphicPoint.c

import numpy as np 
import matplotlib.pyplot as plt

mapa=np.loadtxt('map_data.txt')
#Arreglo de 500(Latitud)x744(longitud) con el mapa de la tierra, 0 si es mar y 1 si es tierra

PN=np.loadtxt('coordNemo.csv', delimiter=',')

R=PN[2]
lng=PN[1]
lat=PN[0]


fig=plt.figure()
ax=fig.add_subplot(111)

#Punto Nemo
ax.scatter(lng,lat, c='red')

#Mapa
ax.imshow(mapa, cmap='Greens', extent=[-180,180,-90,90])

#Circulo
circulo=plt.Circle((lng,lat), R, color='red', fill=False)
ax.add_artist(circulo)

plt.savefig('PuntoNemo.pdf')
plt.close()





