import random
import os

def generate_random_list(size):
    # Genera una lista de tamaño 'size' con números aleatorios.
    return [random.randint(1, 1000) for _ in range(size)]

def generate_sorted_list(size):
    # Genera una lista de tamaño 'size' ordenada de forma ascendente.
    return list(range(1, size + 1))

def generate_reversed_list(size):
    # Genera una lista de tamaño 'size' ordenada de forma descendente.
    return list(range(size, 0, -1))

def generate_partially_sorted_list(size, disorder_factor=0.2):
    # Genera una lista parcialmente ordenada.
    # El factor de desorden indica el porcentaje de elementos que pueden estar desordenados.
    # Por ejemplo, si el factor de desorden es 0.2, el 20% de los elementos estarán desordenados.
    ordered_part = list(range(1, size + 1))
    disordered_part_size = int(size * disorder_factor)
    random.shuffle(ordered_part)
    return ordered_part[:disordered_part_size] + ordered_part[disordered_part_size:]

def save_to_file(data, filename):
    # Guarda la lista en un archivo dentro de la carpeta 'listas'.
    os.makedirs('listas', exist_ok=True)  # Crear la carpeta 'listas' si no existe
    filepath = os.path.join('listas', filename)
    with open(filepath, 'w') as file:
        file.write(" ".join(map(str, data)) + "\n")

# Tamaños de las listas a generar.
sizes = [10, 100, 1000, 10000] 

for size in sizes:
    # Generando listas
    random_data = generate_random_list(size)
    sorted_data = generate_sorted_list(size)
    reversed_data = generate_reversed_list(size)
    partially_sorted_data = generate_partially_sorted_list(size)

    # Guardando en archivos .txt los diferentes tipos de listas
    save_to_file(random_data, f"random_data_{size}.txt")
    save_to_file(sorted_data, f"sorted_data_{size}.txt")
    save_to_file(reversed_data, f"reversed_data_{size}.txt")
    save_to_file(partially_sorted_data, f"partially_sorted_data_{size}.txt")

print("Datasheets generados y guardados en archivos .txt dentro de la carpeta 'listas'")
