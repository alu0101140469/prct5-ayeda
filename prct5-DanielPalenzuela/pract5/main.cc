/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file main.cc
 * @brief Programa principal de la práctica 5 algoritmos de ordenación.
 * Ejecutar ejemplo: ./algordenacion -size 5 -ord s -init random -trace n
 */

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "SortMethod.h"
#include "nif.h"

namespace {

/**
 * @brief Imprime la información de uso del programa.
 * @param prog_name Nombre del programa.
 */
void PrintUsage(const char* prog_name) {
  std::cout << "Modo de ejecución: " << prog_name
            << " -size <s> -ord <m> -init <manual|random|file> [fichero] -trace <y|n>\n\n"
            << "Metodos de ordenacion:\n"
            << "  s  Seleccion\n"
            << "  b  Burbuja\n"
            << "  m  MergeSort\n"
            << "  h  HeapSort\n"
            << "  i  Incrementos decrecientes\n\n"
            << "Opciones extra:\n"
            << "  -alpha <a>   Factor alfa para incrementos decrecientes (0 < a < 1)\n";
}

/**
 * @brief Convierte una cadena a minúsculas.
 * @param text Cadena a convertir.
 * @return Cadena convertida a minúsculas.
 */
std::string ToLower(std::string text) {
  for (char& ch : text) {
    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
  }
  return text;
}

/**
 * @brief Rellena una secuencia con valores introducidos por pantalla.
 * @param seq Secuencia a rellenar.
 */
void FillManual(staticSequence<nif>& seq) {
  const unsigned n = seq.capacity();
  for (unsigned i = 0; i < n; ++i) {
    long value = 0;
    std::cout << "Introduce el valor " << (i + 1) << " de " << n << " (8 digitos): ";
    std::cin >> value;
    if (value < 10000000L || value > 99999999L) {
      std::cout << "El valor debe tener 8 digitos. Vuelve a introducir el numero." << std::endl;
      --i;
      continue;
    }
    seq.insert(nif(value));
  }
}

/**
 * @brief Rellena una secuencia con valores aleatorios.
 * @param seq Secuencia a rellenar.
 */
void FillRandom(staticSequence<nif>& seq) {
  const unsigned n = seq.capacity();
  for (unsigned i = 0; i < n; ++i) {
    seq.insert(nif());
  }
}

/**
 * @brief Rellena una secuencia con valores leídos desde un fichero.
 * @param seq Secuencia a rellenar.
 * @param file_name Nombre del fichero de entrada.
 * @return true si se ha rellenado correctamente, false si ha ocurrido un error.
 */
bool FillFromFile(staticSequence<nif>& seq, const std::string& file_name) {
  std::ifstream input(file_name);
  if (!input) {
    std::cerr << "No se ha podido abrir el fichero de entrada: " << file_name << std::endl;
    return false;
  }

  const unsigned n = seq.capacity();
  unsigned count = 0;
  long value = 0;

  while (count < n && input >> value) {
    if (value < 10000000L || value > 99999999L) {
      std::cerr << "Valor invalido en el fichero: " << value << std::endl;
      return false;
    }
    if (!seq.insert(nif(value))) {
      std::cerr << "No se ha podido insertar el valor leido desde fichero." << std::endl;
      return false;
    }
    ++count;
  }

  if (count < n) {
    std::cerr << "El fichero no contiene suficientes valores para completar la secuencia." << std::endl;
    return false;
  }

  return true;
}

}

/**
 * @brief Función principal del programa.
 */
int main(int argc, char* argv[]) {

  // Comprobar si se ha solicitado la ayuda
  if (argc == 2 && std::string(argv[1]) == "--help") {
    PrintUsage(argv[0]);
    return 0;
  }

  // Variables para almacenar los parámetros de entrada
  unsigned size = 0;
  char ord = '\0';
  std::string init_mode;
  std::string file_name;
  bool trace = false;
  double alpha = 0.5;

  // Procesar los argumentos de entrada
  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (arg == "-size" && i + 1 < argc) { // Tamaño de la secuencia a ordenar
      try {
        size = static_cast<unsigned>(std::stoul(argv[++i]));
      } catch (...) {
        std::cerr << "Valor invalido para -size." << std::endl;
        return 1;
      }
    } else if (arg == "-ord" && i + 1 < argc) { // Método de ordenación a utilizar
      std::string code = ToLower(argv[++i]);
      ord = code.empty() ? '\0' : code[0];
    } else if (arg == "-init" && i + 1 < argc) { // Método de inicialización de la secuencia
      init_mode = ToLower(argv[++i]);
      if (init_mode == "file" && i + 1 < argc) { // Se espera un argumento adicional con el nombre del fichero
        file_name = argv[++i];
      }
    } else if (arg == "-trace" && i + 1 < argc) { // Si mostrar información de seguimiento durante la ordenación
      trace = (ToLower(argv[++i]) == "y");
    } else if (arg == "-alpha" && i + 1 < argc) { // Parámetro para el algoritmo de ordenación por incrementos decrecientes
      try {
        alpha = std::stod(argv[++i]); // Convertir el argumento a un número de punto flotante
      } catch (...) {
        std::cerr << "Valor invalido para -alpha." << std::endl; // Si la conversión falla, mostrar un mensaje de error
        return 1;
      }
    } else {
      std::cerr << "Argumento no reconocido: " << arg << std::endl;
      PrintUsage(argv[0]);
      return 1;
    }
  }

  // Validar los parámetros de entrada
  if (size == 0 || ord == '\0' || init_mode.empty()) {
    PrintUsage(argv[0]);
    return 1;
  }

  if (init_mode != "manual" && init_mode != "random" && init_mode != "file") {
    std::cerr << "Modo de inicializacion invalido." << std::endl;
    PrintUsage(argv[0]);
    return 1;
  }

  if (ord == 'i' && !(alpha > 0.0 && alpha < 1.0)) {
    std::cerr << "El valor de alfa debe cumplir 0 < alfa < 1." << std::endl;
    return 1;
  }

  std::srand(static_cast<unsigned>(std::time(nullptr))); // Inicializar la semilla para la generación de números aleatorios

  staticSequence<nif> sequence(size); // Crear una secuencia con la capacidad especificada

  // Rellenar la secuencia según el método de inicialización seleccionado
  if (init_mode == "manual") {
    FillManual(sequence);
  } else if (init_mode == "random") {
    FillRandom(sequence);
  } else {
    if (!FillFromFile(sequence, file_name)) {
      return 1;
    }
  }

  // Mostrar la secuencia inicial antes de ordenar
  std::cout << "Secuencia inicial:" << std::endl;
  printSequence(sequence, sequence.size());

  std::unique_ptr<SortMethod<nif>> method; // Puntero para almacenar el método de ordenación seleccionado

  // Crear una instancia del método de ordenación seleccionado
  switch (ord) {
    case 's':
      method = std::make_unique<SelectionSortMethod<nif>>(sequence, trace);
      break;
    case 'b':
      method = std::make_unique<BubbleSortMethod<nif>>(sequence, trace);
      break;
    case 'm':
      method = std::make_unique<MergeSortMethod<nif>>(sequence, trace);
      break;
    case 'h':
      method = std::make_unique<HeapSortMethod<nif>>(sequence, trace);
      break;
    case 'i':
      method = std::make_unique<DecreasingIncrementSortMethod<nif>>(sequence, alpha, trace);
      break;
    default:
      std::cerr << "Codigo de ordenacion invalido." << std::endl;
      PrintUsage(argv[0]);
      return 1;
  }

  method->Sort(); // Ordenar la secuencia utilizando el método seleccionado

  // Mostrar la secuencia ordenada después de aplicar el algoritmo de ordenación
  std::cout << "Secuencia ordenada:" << std::endl;
  printSequence(method->GetSequence(), method->GetSequence().size());

  return 0;
}