/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file main.cc
 * @brief Programa principal de la práctica 5 algoritmos de ordenación.
 * Ejecutar ejemplo: ./algordenacion -size 5 -ord s -init random -trace n
 */

 /*
 MODIF: buscar cuantos niveles de log hay y pasarselo al programa. 
 La practica tiene un flag que dice si logear o no logear (trace). 
 Actualizar para que en vez de logear o no, logee en base a los niveles indicados.
 Es decir, en vez de si o no es un nivel.

 Ejemplos:
  ./algordenacion -size 5 -ord s -init random -log none
  ./algordenacion -size 5 -ord s -init random -log error
  ./algordenacion -size 5 -ord s -init random -log warn
  ./algordenacion -size 5 -ord s -init random -log info
  ./algordenacion -size 5 -ord s -init random -log debug
  ./algordenacion -size 5 -ord s -init random -log trace
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
            << " -size <s> -ord <m> -init <manual|random|file> [fichero] -log <none|error|warn|info|debug|trace>\n\n"
            << "Metodos de ordenacion:\n"
            << "  s  Seleccion\n"
            << "  b  Burbuja\n"
            << "  m  MergeSort\n"
            << "  h  HeapSort\n"
            << "  i  Incrementos decrecientes\n\n"
            << "Opciones extra:\n"
            << "  -alpha <a>   Factor alfa para incrementos decrecientes (0 < a < 1)\n"
            << "  -log <lvl>  Nivel de log: none, error, warn, info, debug, trace\n";
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

// modif
enum LogLevel {
  LOG_NONE  = 0,
  LOG_ERROR = 1,
  LOG_WARN  = 2,
  LOG_INFO  = 3,
  LOG_DEBUG = 4,
  LOG_TRACE = 5
};

inline bool ShouldLog(const int current_level, const LogLevel msg_level) {
  return current_level >= static_cast<int>(msg_level);
}

inline void LogMsg(const int current_level, const LogLevel msg_level, const std::string& msg) {
  if (!ShouldLog(current_level, msg_level)) return;

  std::ostream& out = (msg_level <= LOG_WARN) ? std::cerr : std::cout;

  switch (msg_level) {
    case LOG_ERROR: out << "[ERROR] "; break;
    case LOG_WARN:  out << "[WARN ] "; break;
    case LOG_INFO:  out << "[INFO ] "; break;
    case LOG_DEBUG: out << "[DEBUG] "; break;
    case LOG_TRACE: out << "[TRACE] "; break;
    default: break;
  }
  out << msg << std::endl;
}

inline std::string OrdToString(const char ord) {
  switch (ord) {
    case 's': return "Seleccion";
    case 'b': return "Burbuja";
    case 'm': return "MergeSort";
    case 'h': return "HeapSort";
    case 'i': return "Incrementos decrecientes";
    default: return "Desconocido";
  }
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
  //bool trace = false;
  int log_level = 0;
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
    //} else if (arg == "-trace" && i + 1 < argc) { // Si mostrar información de seguimiento durante la ordenación
    //  trace = (ToLower(argv[++i]) == "y");

    } else if (arg == "-log" && i + 1 < argc) {
      const std::string lvl = ToLower(argv[++i]);
      if (lvl == "none") log_level = 0;
      else if (lvl == "error") log_level = 1;
      else if (lvl == "warn" || lvl == "warning") log_level = 2;
      else if (lvl == "info") log_level = 3;
      else if (lvl == "debug") log_level = 4;
      else if (lvl == "trace") log_level = 5;
      else {
        std::cerr << "Nivel de log invalido: " << lvl << std::endl;
        return 1;
      }

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

  LogMsg(log_level, LOG_INFO, "Parametros: size=" + std::to_string(size) +
                              " ord=" + OrdToString(ord) +
                              " init=" + init_mode);

  if (ord == 'i') {
    LogMsg(log_level, LOG_INFO, "Parametro alpha=" + std::to_string(alpha));
  }

  std::srand(static_cast<unsigned>(std::time(nullptr))); // Inicializar la semilla para la generación de números aleatorios

  staticSequence<nif> sequence(size); // Crear una secuencia con la capacidad especificada

  // Rellenar la secuencia según el método de inicialización seleccionado
  if (init_mode == "file") {
    LogMsg(log_level, LOG_INFO, "Leyendo datos desde fichero: " + file_name);
  }

  if (init_mode == "manual") {
    FillManual(sequence);
  } else if (init_mode == "random") {
    FillRandom(sequence);
  } else {
    if (!FillFromFile(sequence, file_name)) {
      LogMsg(log_level, LOG_ERROR, "Fallo al inicializar la secuencia desde fichero.");
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
      method = std::make_unique<SelectionSortMethod<nif>>(sequence, log_level);
      break;
    case 'b':
      method = std::make_unique<BubbleSortMethod<nif>>(sequence, log_level);
      break;
    case 'm':
      method = std::make_unique<MergeSortMethod<nif>>(sequence, log_level);
      break;
    case 'h':
      method = std::make_unique<HeapSortMethod<nif>>(sequence, log_level);
      break;
    case 'i':
      method = std::make_unique<DecreasingIncrementSortMethod<nif>>(sequence, alpha, log_level);
      break;
    default:
      std::cerr << "Codigo de ordenacion invalido." << std::endl;
      PrintUsage(argv[0]);
      return 1;
  }

  LogMsg(log_level, LOG_INFO, "Iniciando ordenacion: " + OrdToString(ord));
  if (log_level >= LOG_DEBUG) {
    LogMsg(log_level, LOG_DEBUG, "Traza de ordenacion activada.");
  }

  method->Sort(); // Ordenar la secuencia utilizando el método seleccionado

  LogMsg(log_level, LOG_INFO, "Ordenacion finalizada.");

  // Mostrar la secuencia ordenada después de aplicar el algoritmo de ordenación
  std::cout << "Secuencia ordenada:" << std::endl;
  printSequence(method->GetSequence(), method->GetSequence().size());

  return 0;
}