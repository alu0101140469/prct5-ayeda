/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file nif.h
 * @brief Definición del tipo nif utilizado como clave en los algoritmos.
 */

#ifndef NIF_H
#define NIF_H

#include <cstdlib>
#include <iosfwd>

/**
 * @brief Tipo que representa la parte numérica de un NIF.
 */
class nif {
 public:
  /** 
   * @brief Constructor por defecto. 
   */
  nif();

  /**
   * @brief Constructor a partir de un número.
   * @param number Número para inicializar el nif. Si no es válido, se asigna un número aleatorio.
   */
  explicit nif(const long number);

  /**
   * @brief Conversión a long.
   * @return El número representado por el nif.
   */
  operator long() const;

  /**
   * @brief Operador de igualdad.
   * @param other Otro nif para comparar.
   * @return true si los nifs son iguales, false en caso contrario.
   */
  bool operator==(const nif& other) const;

  /**
   * @brief Operador de desigualdad.
   * @param other Otro nif para comparar.
   * @return true si los nifs son diferentes, false en caso contrario.
   */
  bool operator!=(const nif& other) const;

  /**
   * @brief Operador de menor que.
   * @param other Otro nif para comparar.
   * @return true si el nif es menor que el otro, false en caso contrario.
   */
  bool operator<(const nif& other) const;

  /**
   * @brief Operador de mayor que.
   * @param other Otro nif para comparar.
   * @return true si el nif es mayor que el otro, false en caso contrario.
   */
  bool operator>(const nif& other) const;

 private:
  static bool isValid(const long number); // Verifica si un número es un nif válido
  long number_; // Número que representa el nif
};

/**
 * @brief Escribe un nif en un flujo de salida.
 * @param os Flujo de salida.
 * @param value Valor a escribir.
 * @return Flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const nif& value);

#endif