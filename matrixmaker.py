import random
import os

# Función para generar una matriz de tamaño dado (filas x columnas)
def generar_matriz(filas, columnas):
    return [[random.randint(1, 500) for _ in range(columnas)] for _ in range(filas)]

# Función para guardar dos matrices en un archivo .txt en la carpeta 'matrices'
def guardar_dos_matrices_en_txt(matriz1, matriz2, nombre_archivo):
    # Asegurar que la carpeta 'matrices' exista
    os.makedirs('matrices', exist_ok=True)
    
    # Crear la ruta completa del archivo
    ruta_archivo = os.path.join('matrices', nombre_archivo)
    
    # Guardar el archivo en la carpeta 'matrices'
    with open(ruta_archivo, 'w') as archivo:
        # Guardar la primera matriz
        filas1, columnas1 = len(matriz1), len(matriz1[0])
        archivo.write(f"Matriz 1 ({filas1}x{columnas1}):\n")
        for fila in matriz1:
            archivo.write(' '.join(map(str, fila)) + '\n')
        archivo.write('\n')  # Línea en blanco entre matrices
        
        # Guardar la segunda matriz
        filas2, columnas2 = len(matriz2), len(matriz2[0])
        archivo.write(f"Matriz 2 ({filas2}x{columnas2}):\n")
        for fila in matriz2:
            archivo.write(' '.join(map(str, fila)) + '\n')

# Ejemplo de uso:
# Definir las dimensiones de las matrices a generar
dimensiones_matrices = [
    (100, 100, 100),  # Matriz 100x100 y 100x100 
    (300, 300, 300),  # Matriz 300x300 y 300x300 
    (500, 500, 500),  # Matriz 500x500 y 500x500 
    (100, 200, 150),  # Matriz 100x200 y 200x150 
    (200, 300, 250),  # Matriz 200x300 y 300x250 
    (256, 256, 256),  # Matriz 200x300 y 300x250 
    (300, 400, 350),  # Matriz 300x400 y 400x350 
    (512, 512, 512),  # Matriz 300x700 y 700x550  
    (700, 700, 700),  # Matriz 700x700 y 700x700
    (1000, 1000, 1000),  # Matriz 1000x1000 y 1000x1000 
    (1023, 1023, 1023),  # Matriz 1000x1000 y 1000x1000 
    (200, 1000, 200)  # Matriz 200x1000 y 1000x200 
]

# Generar y guardar dos matrices en cada archivo dentro de la carpeta 'matrices'
for i, (filas1, columnas1, columnas2) in enumerate(dimensiones_matrices, start=1):
    matriz1 = generar_matriz(filas1, columnas1)  # Matriz de tamaño filas1 x columnas1
    matriz2 = generar_matriz(columnas1, columnas2)  # Matriz de tamaño columnas1 x columnas2 (multiplicable)
    nombre_archivo = f'matriz_{filas1}x{columnas1}_y_{columnas1}x{columnas2}.txt'
    guardar_dos_matrices_en_txt(matriz1, matriz2, nombre_archivo)

print("Matrices generadas y guardadas en la carpeta 'matrices'")
