/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file SortFunctions.h
 * @brief Plantillas de funciones con los algoritmos de ordenación.
 */

#ifndef SORTFUNCTIONS_H
#define SORTFUNCTIONS_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "staticSequence.h"

/**
 * @brief Imprime una secuencia por pantalla.
 * @tparam Key Tipo de dato.
 * @param seq Secuencia.
 * @param size Número de elementos a mostrar.
 */
template <class Key>
inline void printSequence(const staticSequence<Key>& seq, const unsigned size) {
  for (unsigned i = 0; i < size; ++i) {
    std::cout << seq[i];
    if (i + 1 < size) std::cout << ' ';
  }
  std::cout << std::endl;
}

/**
 * @brief Ordenación por selección.
 * @param seq Secuencia a ordenar.
 * @param size Número de elementos a ordenar.
 * @param trace Indica si se debe mostrar información de seguimiento.
 */
template <class Key>
inline void selectionSort(staticSequence<Key>& seq, const unsigned size, const bool trace) {
  if (size < 2) return; // No es necesario ordenar secuencias de 0 o 1 elementos
  for (unsigned i = 0; i + 1 < size; ++i) {
    unsigned min_index = i; // Índice del elemento mínimo encontrado
    for (unsigned j = i + 1; j < size; ++j) {
      if (seq[j] < seq[min_index]) min_index = j; // Actualizar el índice del mínimo si se encuentra un elemento menor
    }
    if (min_index != i) std::swap(seq[i], seq[min_index]); // Intercambiar el elemento actual con el mínimo encontrado
    if (trace) printSequence(seq, size); // Mostrar la secuencia después de cada paso si se activa
  }
}

/**
 * @brief Ordenación por burbuja.
 * @param seq Secuencia a ordenar.
 * @param size Número de elementos a ordenar.
 * @param trace Indica si se debe mostrar información de seguimiento.
 */
template <class Key>
inline void bubbleSort(staticSequence<Key>& seq, const unsigned size, const bool trace) {
  if (size < 2) return; // No es necesario ordenar secuencias de 0 o 1 elementos
  for (unsigned pass = 0; pass + 1 < size; ++pass) {
    bool swapped = false; // Indica si se ha realizado algún intercambio en esta pasada
    for (unsigned i = 0; i + 1 < size - pass; ++i) {
      if (seq[i + 1] < seq[i]) { 
        std::swap(seq[i], seq[i + 1]); // Si el elemento siguiente es menor que el actual, intercambiarlos
        swapped = true;
      }
    }
    if (trace) printSequence(seq, size); // Mostrar la secuencia después de cada paso si se activa
    if (!swapped) break; // Si no se ha realizado ningún intercambio, la secuencia ya está ordenada y finaliza
  }
}

/**
 * @brief Fusiona dos rangos ordenados.
 * @param seq Secuencia a ordenar.
 * @param ini Índice inicial del primer rango.
 * @param mid Índice medio que separa los dos rangos.
 * @param fin Índice final del segundo rango.
 */
template <class Key>
inline void mergeRanges(staticSequence<Key>& seq, const unsigned ini, const unsigned mid, const unsigned fin) {
  std::vector<Key> aux; // Vector auxiliar para almacenar la fusión de los dos rangos
  aux.reserve(fin - ini); // Reservar espacio para evitar realocaciones durante la fusión

  unsigned left = ini; // Índice para recorrer el primer rango
  unsigned right = mid; // Índice para recorrer el segundo rango

  while (left < mid && right < fin) {
    if (!(seq[right] < seq[left])) {
      aux.push_back(seq[left]); // Si el elemento del primer rango es menor o igual que el del segundo, agregarlo al vector auxiliar
      ++left;
    } else {
      aux.push_back(seq[right]); // Si el elemento del segundo rango es menor que el del primero, agregarlo al vector auxiliar
      ++right;
    }
  }

  while (left < mid) aux.push_back(seq[left++]); // Agregar los elementos restantes del primer rango si los hay
  while (right < fin) aux.push_back(seq[right++]); // Agregar los elementos restantes del segundo rango si los hay

  for (unsigned i = 0; i < aux.size(); ++i) {
    seq[ini + i] = aux[i]; // Copiar los elementos fusionados de vuelta a la secuencia original
  }
}

/**
 * @brief Parte recursiva de MergeSort.
 * @param seq Secuencia a ordenar.
 * @param ini Índice inicial del rango a ordenar.
 * @param fin Índice final del rango a ordenar.
 * @param trace Indica si se debe mostrar información de seguimiento.
 */
template <class Key>
inline void mergeSortRec(staticSequence<Key>& seq, const unsigned ini, const unsigned fin, const bool trace) {
  if (fin - ini <= 1) return; // Un rango de 0 o 1 elementos ya está ordenado
  const unsigned mid = ini + (fin - ini) / 2; // Calcular el índice medio para dividir el rango en dos partes
  mergeSortRec(seq, ini, mid, trace); // Ordenar recursivamente el primer rango
  mergeSortRec(seq, mid, fin, trace); // Ordenar recursivamente el segundo rango
  mergeRanges(seq, ini, mid, fin); // Fusionar los dos rangos ordenados
  if (trace) printSequence(seq, seq.size()); // Mostrar la secuencia después de cada paso si se activa
}

/**
 * @brief Ordenación MergeSort.
 * @param seq Secuencia a ordenar.
 * @param size Número de elementos a ordenar.
 * @param trace Indica si se debe mostrar información de seguimiento.
 */
template <class Key>
inline void mergeSort(staticSequence<Key>& seq, const unsigned size, const bool trace) {
  if (size < 2) return; // No es necesario ordenar secuencias de 0 o 1 elementos
  mergeSortRec(seq, 0, size, trace); // Iniciar la parte recursiva de MergeSort con el rango completo de la secuencia
}

/**
 * @brief Ajusta un nodo de un heap máximo.
 * @param seq Secuencia a ordenar.
 * @param heap_size Tamaño del heap.
 * @param root Índice del nodo a ajustar.
 */
template <class Key>
inline void siftDown(staticSequence<Key>& seq, const unsigned heap_size, unsigned root) {
  while (true) {
    const unsigned left = 2 * root + 1; // Índice del hijo izquierdo
    const unsigned right = left + 1; // Índice del hijo derecho
    unsigned largest = root; // Índice del nodo con el valor más grande entre el nodo actual y sus hijos

    // Si el hijo izquierdo es mayor que el nodo actual, actualizar el índice del nodo más grande
    if (left < heap_size && seq[largest] < seq[left]) largest = left; 
    // Si el hijo derecho es mayor que el nodo más grande encontrado hasta ahora, actualizar el índice del nodo más grande
    if (right < heap_size && seq[largest] < seq[right]) largest = right; 

    if (largest == root) break; // Si el nodo actual es el más grande, el heap ya está ajustado
    std::swap(seq[root], seq[largest]); // Intercambiar el nodo actual con el nodo más grande encontrado
    root = largest;
  }
}

/**
 * @brief Ordenación HeapSort.
 * @param seq Secuencia a ordenar.
 * @param size Número de elementos a ordenar.
 * @param trace Indica si se debe mostrar información de seguimiento.
 */
template <class Key>
inline void heapSort(staticSequence<Key>& seq, const unsigned size, const bool trace) {
  if (size < 2) return; // No es necesario ordenar secuencias de 0 o 1 elementos

  for (int i = static_cast<int>(size / 2) - 1; i >= 0; --i) {
    siftDown(seq, size, static_cast<unsigned>(i)); // Construir el heap máximo a partir de la secuencia
  }

  for (unsigned end = size - 1; end > 0; --end) {
    std::swap(seq[0], seq[end]); // Intercambiar el elemento máximo con el último elemento del rango no ordenado
    siftDown(seq, end, 0); // Ajustar el heap máximo para el rango reducido
    if (trace) printSequence(seq, size); // Mostrar la secuencia después de cada paso si se activa
  }
}

/**
 * @brief Ordenación por incrementos decrecientes.
 * @param seq Secuencia a ordenar.
 * @param size Número de elementos a ordenar.
 * @param alpha Parámetro para el algoritmo de incrementos decrecientes.
 * @param trace Indica si se debe mostrar información de seguimiento.
 */
template <class Key>
inline void decreasingIncrementSort(staticSequence<Key>& seq, const unsigned size, const double alpha, const bool trace) {
  if (size < 2) return; // No es necesario ordenar secuencias de 0 o 1 elementos

  unsigned gap = size; // Inicializar el gap con el tamaño de la secuencia
  do {
    gap = static_cast<unsigned>(std::floor(static_cast<double>(gap) * alpha)); // Calcular el nuevo gap multiplicando el gap actual por alpha
    if (gap < 1) gap = 1; // Asegurarse de que el gap no sea menor que 1

    // Realizar una inserción por gap para ordenar los elementos separados por el gap
    for (unsigned i = gap; i < size; ++i) {
      Key temp = seq[i]; // Guardar el elemento actual para insertarlo en su posición correcta dentro de los elementos separados por el gap
      int j = static_cast<int>(i); // Índice para recorrer los elementos separados por el gap hacia atrás
      while (j >= static_cast<int>(gap) && temp < seq[j - gap]) {
        seq[j] = seq[j - gap]; // Mover el elemento separado por el gap hacia adelante si es mayor que temp
        j -= static_cast<int>(gap);
      }
      seq[j] = temp; // Colocar temp en su posición correcta dentro de los elementos separados por el gap
    }

    if (trace) printSequence(seq, size); // Mostrar la secuencia después de cada paso si se activa
  } while (gap > 1); // Continuar reduciendo el gap hasta que sea 1, momento en el cual se realiza una inserción por gap final que ordena completamente la secuencia
}

#endif