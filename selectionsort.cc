#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <string>
#include <map>

//Función para ordenar un vector de enteros usando el algoritmo Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

//Función para leer los datos de un archivo y almacenarlos en un vector
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
        
        // Medir el tiempo de ordenamiento
        auto start = std::chrono::high_resolution_clock::now();
        selectionSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> duration = end - start;
        double milliseconds = duration.count() * 1000.0; // Convertir a milisegundos
        
        sortingTimes[file] = milliseconds;
        
        std::cout << "Archivo: " << file << " - Tiempo de ordenamiento: " << milliseconds << " milisegundos" << std::endl;
    }
    
    return 0;
}
