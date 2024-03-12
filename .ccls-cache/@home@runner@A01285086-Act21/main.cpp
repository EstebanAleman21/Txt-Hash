/**
 * @brief Programa que calcula el hash de un archivo dado.
 * @author Esteban Aleman Manzanilla A01285086 - Saul Roberto Orozco Villanazul A00831554
 * @date 11/03/2024
 *
 * Complejidad:
 * La complejidad temporal del algoritmo es O(n), donde n es el tamaño del archivo de entrada.
 * Esto se debe a que se recorre el archivo una vez para calcular el hash.
 *
 * La complejidad espacial es O(n), ya que se utiliza un vector para almacenar los datos del archivo.
 * Además, se utiliza otro vector para almacenar el hash calculado, cuyo tamaño es constante (n).
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * @brief Calcula el hash de un archivo.
 * @param fileName Nombre del archivo.
 * @param n Tamaño del hash (múltiplo de 4 entre 16 y 64).
 * @return Cadena que representa el hash del archivo.
 */
string HashFile(const string& fileName, int n) {
    ifstream file(fileName);

    if (!file) {
        cerr << "Error: No se pudo abrir el archivo " << fileName << endl;
        return "";
    }

    vector<char> fileData;
    char c;

    while (file.get(c)) {
        fileData.push_back(c);
    }

    file.close();

    if (fileData.empty()) {
        ostringstream oss;

        for (int i = 0; i < n; i += 4) {
            oss << "00000000";

            if (i + 4 < n) {
                oss << " - ";
            }
        }

        return oss.str();
    }

    int rows = (fileData.size() + n - 1) / n;
    vector<int> hashArray(n, 0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < n; j++) {
            int index = i * n + j;

            if (index < fileData.size()) {
                hashArray[j] += static_cast<int>(fileData[index]);
            } else {
                hashArray[j] += n;
            }

            hashArray[j] %= 256;
        }
    }

    ostringstream oss;

    for (int i = 0; i < n; i += 4) {
        oss << hex << setw(4) << setfill('0') << uppercase
            << (hashArray[i] << 24 | hashArray[i + 1] << 16 | hashArray[i + 2] << 8 | hashArray[i + 3]);

        if (i + 4 < n) {
            oss << " - ";
        }
    }

    string hashString = oss.str();
    return hashString;
}

/**
 * @brief Función principal del programa.
 * @return 0 si se ejecutó correctamente, 1 en caso de error.
 */
int main() {
    string fileName = "hash.txt";
    int n;

    cout << "Ingrese un valor para n (multiplo de 4, entre 16 y 64): ";
    cin >> n;

    if (n < 16 || n > 64 || n % 4 != 0) {
        cerr << "Error: El valor de n debe ser un multiplo de 4 entre 16 y 64." << endl;
        return 1;
    }

    string hash = HashFile(fileName, n);

    if (hash.empty()) {
        return 1;
    }

    cout << "El hash del archivo " << fileName << " es: " << hash << endl;
    return 0;
}

/*
Casos de prueba:

n = 16
Input: Hello, World!
Output esperado: El hash del archivo hash.txt es: 48656C6C - 6F2C2057 - 6F726C64 - 21101010

n = 20
Input: Lorem ipsum
Output esperado: El hash del archivo hash.txt es: 4C6F7265 - 6D206970 - 73756D14 - 14141414

n = 32
Input: Tecnologico de Monterrey
Output esperado: El hash del archivo hash.txt es: 54656368 - 6E6F6C6F - 67696320 - 64652073 - 6F6E7465 - 72726579 - 20202020 - 20202020

n = 64
Input: yjzqadkpcgsrmbx
Output esperado: El hash del archivo hash.txt es: 796A7A71 - 61646B70 - 63677372 - 6D62780A - 0A404040 - 40404040 - 40404040 - 40404040 - 40404040 - 40404040 - 40404040 - 40404040 - 40404040 - 40404040 - 40404040 - 40404040

n = 64
Input: (vacío)
Output esperado: El hash del archivo hash.txt es: 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000 - 00000000
*/