import matplotlib.pyplot as plt
import csv
import os
import numpy as np
import math
import sys

# Funcion que crea una utilizando la informacion de un archivo csv pasado por parametro en la consola
def crear_grafica(archivo):

    archivo2 = archivo.split('/')

    # Crea la carpeta Graficas si no existe
    if not os.path.exists("Graficas"):
        os.makedirs("Graficas")

    # Crea el nombre del archivo
    nombre_archivo_original = "Graficas/" + archivo2[1].split(".")[0] + "_img_original.png"
    nombre_archivo_nuevo = "Graficas/" + archivo2[1].split(".")[0] + "_img_nuevo.png"

    # Crea el titulo de la grafica
    if 'secuencial' in nombre_archivo_original:
        titulo_original = 'Histograma Original Secuencial'
        titulo_nuevo = 'Histograma Nuevo Secuencial'
    else:
        titulo_original = 'Histograma Original Parallel'
        titulo_nuevo = 'Histograma Nuevo Parallel'

    # Crea el eje x con valores desde 0 hasta 256
    x = np.arange(0, 256, 1)

    # Crea los ejes
    y = []
    z = []

    # Se lee el archivo csv
    try:
        with open(archivo, 'r') as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            # Se crea una lista con los datos del archivo
            datos = []
            for row in reader:
                datos.append(row)
        # Se crea una lista con los valores de y, historgama original
        for i in range(len(datos)):
            y.append(float(datos[i][1]))

        # Se crea una lista con los valores de z, histograma nuevo
        for i in range(len(datos)):
            z.append(float(datos[i][2]))

        # ax.plot(x, y, label='y')
        # ax.plot(x, z, label='z')

        # Se crea la grafica del histograma original
        fig, ax = plt.subplots()
        ax.set_xlabel('Valores de pixeles')
        ax.set_ylabel('Cantidad de valores de pixeles')
        ax.set_title(titulo_original)
        # plt.bar(x, y, label='y')
        plt.bar(x, y)
        plt.savefig(nombre_archivo_original)
        # plt.show()

        # Se crea la grafica del histograma nuevo
        fig, ax = plt.subplots()
        ax.set_xlabel('Valores de pixeles')
        ax.set_ylabel('Cantidad de valores de pixeles')
        ax.set_title(titulo_nuevo)
        # plt.bar(x, z, label='z')
        plt.bar(x, z)
        plt.savefig(nombre_archivo_nuevo)
        # plt.show()

        print("\nImagenes creadas correctamente :D\n")

    except FileNotFoundError:
        print("No se encontro el archivo")

if '__main__' == __name__:
    crear_grafica(sys.argv[1])