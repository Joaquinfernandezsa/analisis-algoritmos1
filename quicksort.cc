#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <string>
#include <map>

// Función para realizar el particionamiento
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Elegir el último elemento como pivote
    int i = low - 1; // Índice del elemento más pequeño, inicialmente el primer elemento del arreglo
    
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Función recursiva para realizar Quick Sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Ordenar los elementos antes y después de la partición
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
        quickSort(data, 0, data.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> duration = end - start;
        double milliseconds = duration.count() * 1000.0; // Convertir a milisegundos
        
        sortingTimes[file] = milliseconds;
        
        std::cout << "Archivo: " << file << " - Tiempo de ordenamiento: " << milliseconds << " milisegundos" << std::endl;
    }

    return 0;
}
