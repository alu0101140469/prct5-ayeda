/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file SortMethod.h
 * @brief Jerarquía de clases para representar los diferentes métodos de ordenación.
 */

#ifndef SORTMETHOD_H
#define SORTMETHOD_H

#include "SortFunctions.h"

/**
 * @brief Clase base abstracta para algoritmos de ordenación.
 * @tparam Key Tipo de dato de la secuencia.
 */
template <class Key>
class SortMethod {
 public:
  /**
   * @brief Constructor.
   * @param seq Secuencia a ordenar.
   * @param trace Indica si se debe mostrar información de seguimiento.
   */
  //explicit SortMethod(const staticSequence<Key>& seq, const bool trace = false)
  //  : sequence_(seq), trace_(trace) {}
  explicit SortMethod(const staticSequence<Key>& seq, const int log_level = 0)
    : sequence_(seq), log_level_(log_level) {}

  /**
   * @brief Destructor.
   */
  virtual ~SortMethod() = default;

  /**
   * @brief Ordena la secuencia.
   */
  virtual void Sort() = 0;

  /**
   * @brief Devuelve la secuencia ordenada.
   * @return Secuencia ordenada.
   */
  const staticSequence<Key>& GetSequence() const {
    return sequence_;
  }

 protected:
  staticSequence<Key> sequence_; // Secuencia a ordenar
  //bool trace_; // Indica si se debe mostrar información de seguimiento
  int log_level_;
};


/**
 * @brief Clase para el algoritmo de ordenación por selección.
 * @tparam Key Tipo de dato de la secuencia.
 */
template <class Key>
class SelectionSortMethod : public SortMethod<Key> {
 public:
  /**
   * @brief Constructor.
   * @param seq Secuencia a ordenar.
   * @param trace Indica si se debe mostrar información de seguimiento.
   */
  //explicit SelectionSortMethod(staticSequence<Key>& seq, const bool trace = false)
  //    : SortMethod<Key>(seq, trace) {}
  explicit SelectionSortMethod(staticSequence<Key>& seq, const int log_level = 0)
    : SortMethod<Key>(seq, log_level) {}

  /**
   * @brief Ordena la secuencia utilizando el algoritmo de selección.
   */
  void Sort() override {
    //selectionSort(this->sequence_, this->sequence_.size(), this->trace_);
    selectionSort(this->sequence_, this->sequence_.size(), this->log_level_);
  }
};


/**
 * @brief Clase para el algoritmo de ordenación por burbuja.
 * @tparam Key Tipo de dato de la secuencia.
 */
template <class Key>
class BubbleSortMethod : public SortMethod<Key> {
 public:
  /**
   * @brief Constructor.
   * @param seq Secuencia a ordenar.
   * @param trace Indica si se debe mostrar información de seguimiento.
   */
  //explicit BubbleSortMethod(staticSequence<Key>& seq, const bool trace = false)
  //    : SortMethod<Key>(seq, trace) {}
  explicit BubbleSortMethod(staticSequence<Key>& seq, const int log_level = 0)
      : SortMethod<Key>(seq, log_level) {}

  /**
   * @brief Ordena la secuencia utilizando el algoritmo de burbuja.
   */
  void Sort() override {
    //bubbleSort(this->sequence_, this->sequence_.size(), this->trace_);
    bubbleSort(this->sequence_, this->sequence_.size(), this->log_level_);
  }
};


/**
 * @brief Clase para el algoritmo de ordenación MergeSort.
 * @tparam Key Tipo de dato de la secuencia.
 */
template <class Key>
class MergeSortMethod : public SortMethod<Key> {
 public:
  /**
   * @brief Constructor.
   * @param seq Secuencia a ordenar.
   * @param trace Indica si se debe mostrar información de seguimiento.
   */
  //explicit MergeSortMethod(staticSequence<Key>& seq, const bool trace = false)
  //    : SortMethod<Key>(seq, trace) {}
  explicit MergeSortMethod(staticSequence<Key>& seq, const int log_level = 0)
      : SortMethod<Key>(seq, log_level) {}

  /**
   * @brief Ordena la secuencia utilizando el algoritmo MergeSort.
   */
  void Sort() override {
    //mergeSort(this->sequence_, this->sequence_.size(), this->trace_);
    mergeSort(this->sequence_, this->sequence_.size(), this->log_level_);
  }
};


/**
 * @brief Clase para el algoritmo de ordenación HeapSort.
 * @tparam Key Tipo de dato de la secuencia.
 */
template <class Key>
class HeapSortMethod : public SortMethod<Key> {
 public:
  /**
   * @brief Constructor.
   * @param seq Secuencia a ordenar.
   * @param trace Indica si se debe mostrar información de seguimiento.
   */
  //explicit HeapSortMethod(staticSequence<Key>& seq, const bool trace = false)
  //    : SortMethod<Key>(seq, trace) {}
  explicit HeapSortMethod(staticSequence<Key>& seq, const int log_level = 0)
      : SortMethod<Key>(seq, log_level) {}

  /**
   * @brief Ordena la secuencia utilizando el algoritmo HeapSort.
   */
  void Sort() override {
    //heapSort(this->sequence_, this->sequence_.size(), this->trace_);
    heapSort(this->sequence_, this->sequence_.size(), this->log_level_);
  }
};


/**
 * @brief Clase para el algoritmo de ordenación por incrementos decrecientes.
 * @tparam Key Tipo de dato de la secuencia.
 */
template <class Key>
class DecreasingIncrementSortMethod : public SortMethod<Key> {
 public:
  /**
   * @brief Constructor.
   * @param seq Secuencia a ordenar.
   * @param alpha Parámetro para el algoritmo de incrementos decrecientes.
   * @param trace Indica si se debe mostrar información de seguimiento.
   */
  //(staticSequence<Key>& seq, const double alpha, const bool trace = false)
  //    : SortMethod<Key>(seq, trace), alpha_(alpha) {}
  DecreasingIncrementSortMethod(staticSequence<Key>& seq, const double alpha, const int log_level = 0)
      : SortMethod<Key>(seq, log_level), alpha_(alpha) {}

  /**
   * @brief Ordena la secuencia utilizando el algoritmo de incrementos decrecientes.
   */
  void Sort() override {
    //decreasingIncrementSort(this->sequence_, this->sequence_.size(), alpha_, this->trace_);
    decreasingIncrementSort(this->sequence_, this->sequence_.size(), alpha_, this->log_level_);
  }

 private:
  double alpha_; // Parámetro para el algoritmo de incrementos decrecientes
};

#endif