#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>  // Biblioteca para medir el tiempo

std::vector<std::vector<int>> leer_matriz(std::ifstream& archivo, int filas, int columnas) {
    std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas));
    std::string linea;

    for (int i = 0; i < filas; ++i) {
        std::getline(archivo, linea);
        std::istringstream ss(linea);
        for (int j = 0; j < columnas; ++j) {
            ss >> matriz[i][j];
        }
    }
    return matriz;
}

std::vector<std::vector<int>> multiplicar_matrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

void guardar_matriz_en_txt(const std::vector<std::vector<int>>& matriz, const std::string& nombre_archivo) {
    std::string ruta = "matrices/matrices_resultantes/" + nombre_archivo;  // Ruta a la subcarpeta
    std::ofstream archivo(ruta);
    if (archivo.is_open()) {
        int filas = matriz.size();
        int columnas = matriz[0].size();
        archivo << "Matriz resultante (" << filas << "x" << columnas << "):\n";
        for (const auto& fila : matriz) {
            for (int valor : fila) {
                archivo << valor << " ";
            }
            archivo << "\n";
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo crear el archivo " << ruta << ".\n";
    }
}

void procesar_archivo(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        std::cerr << "No se puede abrir el archivo " << nombre_archivo << ".\n";
        return;
    }

    int filas, columnas;
    std::string linea;

    // Leer la primera matriz
    std::getline(archivo, linea);
    sscanf(linea.c_str(), "Matriz 1 (%dx%d):", &filas, &columnas);
    std::vector<std::vector<int>> matriz1 = leer_matriz(archivo, filas, columnas);

    // Leer la segunda matriz
    std::getline(archivo, linea);  // Saltar la línea en blanco
    std::getline(archivo, linea);
    sscanf(linea.c_str(), "Matriz 2 (%dx%d):", &filas, &columnas);
    std::vector<std::vector<int>> matriz2 = leer_matriz(archivo, filas, columnas);

    // Medir el tiempo de ejecución de la multiplicación
    auto inicio = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> matriz_resultante = multiplicar_matrices(matriz1, matriz2);

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    
    std::cout << "Tiempo de ejecucion para " << nombre_archivo << ": " << duracion.count() << " segundos.\n";

    // Guardar la matriz resultante en un archivo
    std::string nombre_resultado = "matriz_resultante_tradicional" + std::to_string(filas) + "x" + std::to_string(columnas) + ".txt";
    guardar_matriz_en_txt(matriz_resultante, nombre_resultado);

    archivo.close();
}

int main() {
    procesar_archivo("matrices/matriz_100x100_y_100x100.txt");
    procesar_archivo("matrices/matriz_100x200_y_200x150.txt");
    procesar_archivo("matrices/matriz_200x300_y_300x250.txt");
    procesar_archivo("matrices/matriz_300x300_y_300x300.txt");
    procesar_archivo("matrices/matriz_300x400_y_400x350.txt");
    procesar_archivo("matrices/matriz_500x500_y_500x500.txt");
    procesar_archivo("matrices/matriz_700x700_y_700x700.txt");
    procesar_archivo("matrices/matriz_300x700_y_700x550.txt");
    procesar_archivo("matrices/matriz_200x1000_y_1000x200.txt");
    procesar_archivo("matrices/matriz_1000x1000_y_1000x1000.txt");
    return 0;
}
