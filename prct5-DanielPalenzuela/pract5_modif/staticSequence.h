/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file staticSequence.h
 * @brief Implementación de una secuencia estática de tamaño fijo.
 */

#ifndef STATICSEQUENCE_H
#define STATICSEQUENCE_H

#include <stdexcept>
#include <vector>
#include <ostream>

#include "Sequence.h"

/**
 * @brief Secuencia estática con capacidad fija.
 * @tparam Key Tipo de dato almacenado.
 */
template <class Key>
class staticSequence : public Sequence<Key> {
 public:
  /**
   * @brief Constructor.
   * @param size Capacidad máxima de la secuencia.
   */
  explicit staticSequence(const unsigned size = 0)
      : data_(size), max_size_(size), used_(0) {}

  /**
   * @brief Indica si la secuencia está llena.
   * @return true si está llena, false en caso contrario.
   */
  bool isFull() const { return used_ >= max_size_; }

  /**
   * @brief Devuelve el número de elementos almacenados.
   * @return Tamaño actual.
   */
  unsigned size() const { return used_; }

  /**
   * @brief Devuelve la capacidad máxima.
   * @return Capacidad.
   */
  unsigned capacity() const { return max_size_; }

  /**
   * @brief Busca un elemento en la secuencia.
   * @param key Elemento a buscar.
   * @return true si se encuentra, false en caso contrario.
   */
  bool search(const Key& key) const override {
    for (unsigned i = 0; i < used_; ++i) {
      if (data_[i] == key) return true;
    }
    return false;
  }

  /**
   * @brief Inserta un elemento al final de la secuencia.
   * @param key Elemento a insertar.
   * @return true si se ha insertado correctamente, false si la secuencia está llena.
   */
  bool insert(const Key& key) override {
    if (isFull()) return false;
    data_[used_++] = key;
    return true;
  }

  /**
   * @brief Acceso a un elemento por índice (lectura).
   * @param index Índice del elemento.
   * @return Elemento en la posición dada.
   */
  Key operator[](const unsigned index) const override {
    if (index >= used_) throw std::out_of_range("staticSequence: índice fuera de rango");
    return data_[index];
  }

  /**
   * @brief Acceso a un elemento por índice (escritura).
   * @param index Índice del elemento.
   * @return Referencia al elemento en la posición dada.
   */
  Key& operator[](const unsigned index) override {
    if (index >= used_) throw std::out_of_range("staticSequence: índice fuera de rango");
    return data_[index];
  }

 private:
  std::vector<Key> data_; // Almacenamiento de los elementos
  unsigned max_size_; // Capacidad máxima de la secuencia
  unsigned used_; // Número de elementos actualmente almacenados
};

/**
 * @brief Imprime una secuencia estática.
 * @tparam Key Tipo almacenado.
 * @param os Flujo de salida.
 * @param seq Secuencia a imprimir.
 * @return Flujo de salida.
 */
template <class Key>
std::ostream& operator<<(std::ostream& os, const staticSequence<Key>& seq) {
  for (unsigned i = 0; i < seq.size(); ++i) {
    os << seq[i];
    if (i + 1 < seq.size()) os << ' ';
  }
  return os;
}

#endif