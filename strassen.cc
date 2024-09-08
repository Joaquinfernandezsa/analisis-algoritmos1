#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>  // Biblioteca para medir el tiempo

// Función para sumar matrices
std::vector<std::vector<int>> sumar_matrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar matrices
std::vector<std::vector<int>> restar_matrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Algoritmo de Strassen
std::vector<std::vector<int>> strassen(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        std::vector<std::vector<int>> C(1, std::vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    std::vector<std::vector<int>> A11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A22(newSize, std::vector<int>(newSize));

    std::vector<std::vector<int>> B11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B22(newSize, std::vector<int>(newSize));

    // Dividir las matrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular las siete multiplicaciones de Strassen
    std::vector<std::vector<int>> M1 = strassen(sumar_matrices(A11, A22), sumar_matrices(B11, B22));
    std::vector<std::vector<int>> M2 = strassen(sumar_matrices(A21, A22), B11);
    std::vector<std::vector<int>> M3 = strassen(A11, restar_matrices(B12, B22));
    std::vector<std::vector<int>> M4 = strassen(A22, restar_matrices(B21, B11));
    std::vector<std::vector<int>> M5 = strassen(sumar_matrices(A11, A12), B22);
    std::vector<std::vector<int>> M6 = strassen(restar_matrices(A21, A11), sumar_matrices(B11, B12));
    std::vector<std::vector<int>> M7 = strassen(restar_matrices(A12, A22), sumar_matrices(B21, B22));

    // Combinar los resultados en la matriz resultante C
    std::vector<std::vector<int>> C(n, std::vector<int>(n));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C[i][j + newSize] = M3[i][j] + M5[i][j];
            C[i + newSize][j] = M2[i][j] + M4[i][j];
            C[i + newSize][j + newSize] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    return C;
}

// Función para leer la matriz desde archivo
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

// Función para guardar la matriz resultante en archivo
void guardar_matriz_en_txt(const std::vector<std::vector<int>>& matriz, const std::string& nombre_archivo) {
    std::string ruta = "matrices/matrices_resultantes/" + nombre_archivo;
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

// Procesar archivo
void procesar_archivo(const std::string& nombre_archivo) {
    std::ifstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        std::cerr << "No se puede abrir el archivo " << nombre_archivo << ".\n";
        return;
    }

    int filas, columnas;
    std::string linea;

    std::getline(archivo, linea);
    sscanf(linea.c_str(), "Matriz 1 (%dx%d):", &filas, &columnas);
    std::vector<std::vector<int>> matriz1 = leer_matriz(archivo, filas, columnas);

    std::getline(archivo, linea);  // Saltar la línea en blanco
    std::getline(archivo, linea);
    sscanf(linea.c_str(), "Matriz 2 (%dx%d):", &filas, &columnas);
    std::vector<std::vector<int>> matriz2 = leer_matriz(archivo, filas, columnas);

    auto inicio = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> matriz_resultante = strassen(matriz1, matriz2);

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;

    std::cout << "Tiempo de ejecucion para " << nombre_archivo << ": " << duracion.count() << " segundos.\n";

    std::string nombre_resultado = "matriz_resultante_strassen" + std::to_string(filas) + "x" + std::to_string(columnas) + ".txt";
    guardar_matriz_en_txt(matriz_resultante, nombre_resultado);

    archivo.close();
}

int main() {
    procesar_archivo("matrices/matriz_100x100_y_100x100.txt");
    procesar_archivo("matrices/matriz_100x200_y_200x150.txt");
    procesar_archivo("matrices/matriz_200x300_y_300x250.txt");
    procesar_archivo("matrices/matriz_256x256_y_256x256.txt");
    procesar_archivo("matrices/matriz_300x300_y_300x300.txt");
    procesar_archivo("matrices/matriz_300x400_y_400x350.txt");
    procesar_archivo("matrices/matriz_500x500_y_500x500.txt");
    procesar_archivo("matrices/matriz_512x512_y_512x512.txt");
    procesar_archivo("matrices/matriz_700x700_y_700x700.txt");
    procesar_archivo("matrices/matriz_300x700_y_700x550.txt");
    procesar_archivo("matrices/matriz_200x1000_y_1000x200.txt");
    procesar_archivo("matrices/matriz_1000x1000_y_1000x1000.txt");
    procesar_archivo("matrices/matriz_1023x1023_y_1023x1023.txt");
    return 0;
}

