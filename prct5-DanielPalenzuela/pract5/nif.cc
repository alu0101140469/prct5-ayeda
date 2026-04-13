/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file nif.cc
 * @brief Implementación de la clase nif.
 */

#include "nif.h"

#include <iostream>

/**
 * @brief Constructor por defecto.
 */
nif::nif() {
  number_ = 10000000L + std::rand() % 90000000L;
}

/**
 * @brief Constructor a partir de un número.
 * @param number Número para inicializar el nif. Si no es válido, se asigna un número aleatorio.
 */
nif::nif(const long number) : number_(isValid(number) ? number : 10000000L) {}

/**
 * @brief Conversión a long.
 * @return El número representado por el nif.
 */
nif::operator long() const {
  return number_;
}

/**
 * @brief Operador de igualdad.
 * @param other Otro nif para comparar.
 * @return true si los nifs son iguales, false en caso contrario.
 */
bool nif::operator==(const nif& other) const {
  return number_ == other.number_;
}

/**
 * @brief Operador de desigualdad.
 * @param other Otro nif para comparar.
 * @return true si los nifs son diferentes, false en caso contrario.
 */
bool nif::operator!=(const nif& other) const {
  return number_ != other.number_;
}

/**
 * @brief Operador de menor que.
 * @param other Otro nif para comparar.
 * @return true si el nif es menor que el otro, false en caso contrario.
 */
bool nif::operator<(const nif& other) const {
  return number_ < other.number_;
}

/**
 * @brief Operador de mayor que.
 * @param other Otro nif para comparar.
 * @return true si el nif es mayor que el otro, false en caso contrario.
 */
bool nif::operator>(const nif& other) const {
  return number_ > other.number_;
}

/**
 * @brief Verifica si un número es un nif válido.
 * @param number Número a verificar.
 * @return true si el número es un nif válido, false en caso contrario.
 */
bool nif::isValid(const long number) {
  return number >= 10000000L && number <= 99999999L; // Un nif válido debe ser un número de 8 dígitos (la L es para indicar que es tipo long)
}

/**
 * @brief Escribe un nif en un flujo de salida.
 * @param os Flujo de salida.
 * @param value Valor a escribir.
 * @return Flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const nif& value) {
  os << static_cast<long>(value);
  return os;
}