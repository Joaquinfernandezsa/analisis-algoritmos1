#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <string>
#include <map>

// Función para fusionar dos subvectores
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    
    // Copiar los datos a los vectores temporales L y R
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    
    int i = 0; // Índice inicial para el subvector L
    int j = 0; // Índice inicial para el subvector R
    int k = left; // Índice inicial para el subvector fusionado
    
    // Fusionar los vectores temporales de vuelta al arreglo original
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    
    // Copiar los elementos restantes de L, si los hay
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    
    // Copiar los elementos restantes de R, si los hay
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Función recursiva para realizar Merge Sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Ordenar la primera mitad
        mergeSort(arr, left, mid);
        
        // Ordenar la segunda mitad
        mergeSort(arr, mid + 1, right);
        
        // Fusionar las dos mitades ordenadas
        merge(arr, left, mid, right);
    }
}

// Función para leer datos desde un archivo
std::vector<int> readDataFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    std::vector<int> data;
    int number;
    
    if (infile.is_open()) {
        std::string line;
        std::getline(infile, line);
        std::istringstream iss(line);
        while (iss >> number) {
            data.push_back(number);
        }
        infile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
    }
    
    return data;
}

int main() {
    // Lista de archivos a leer
    std::vector<std::string> files = {
        "listas/random_data_10.txt",
        "listas/random_data_100.txt",
        "listas/random_data_1000.txt",
        "listas/random_data_10000.txt",
        "listas/sorted_data_10.txt",
        "listas/sorted_data_100.txt",
        "listas/sorted_data_1000.txt",
        "listas/sorted_data_10000.txt",
        "listas/reversed_data_10.txt",
        "listas/reversed_data_100.txt",
        "listas/reversed_data_1000.txt",
        "listas/reversed_data_10000.txt",
        "listas/partially_sorted_data_10.txt",
        "listas/partially_sorted_data_100.txt",
        "listas/partially_sorted_data_1000.txt",
        "listas/partially_sorted_data_10000.txt"
    };
    
    // Map para almacenar los tiempos de ordenamiento
    std::map<std::string, double> sortingTimes;
    
    for (const auto& file : files) {
        std::vector<int> data = readDataFromFile(file);
        
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(data, 0, data.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> duration = end - start;
        double milliseconds = duration.count() * 1000.0; // Convertir a milisegundos
        
        sortingTimes[file] = milliseconds;
        
        std::cout << "Archivo: " << file << " - Tiempo de ordenamiento: " << milliseconds << " milisegundos" << std::endl;
    }

    return 0;
}
