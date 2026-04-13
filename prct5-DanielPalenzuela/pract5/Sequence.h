/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Sequence.h
 * @brief Definición de la clase base abstracta Sequence.
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H

/**
 * @brief Clase base abstracta para una secuencia genérica de elementos.
 * @tparam Key Tipo de dato almacenado en la secuencia.
 */
template <class Key>
class Sequence {
 public:
  /**
    * @brief Busca un elemento en la secuencia.
    * @param key Elemento a buscar.
    * @return true si se encuentra, false en caso contrario.
    */
  virtual bool search(const Key& key) const = 0;

  /**
   * @brief Inserta un elemento en la secuencia.
   * @param key Elemento a insertar.
   * @return true si se ha insertado correctamente, false si no se ha podido insertar.
   */
  virtual bool insert(const Key& key) = 0;

  /**
   * @brief Devuelve el elemento en la posición dada.
   * @param index Índice del elemento a devolver.
   * @return Elemento en la posición dada.
   */
  virtual Key operator[](const unsigned index) const = 0;

  /**
   * @brief Devuelve una referencia al elemento en la posición dada.
   * @param index Índice del elemento a devolver.
   * @return Referencia al elemento en la posición dada.
   */
  virtual Key& operator[](const unsigned index) = 0;
  
  /**
   * @brief Destructor de la clase.
   */
  virtual ~Sequence() = default;
};

#endif