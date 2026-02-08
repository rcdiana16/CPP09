/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:37:45 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 14:23:22 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>   // Primer contenedor: std::vector
#include <deque>    // Segundo contenedor: std::deque
#include <string>   // Para manejar strings

/*
** Clase PmergeMe:
** Implementa el algoritmo Ford-Johnson (Merge-Insert Sort) para ordenar números
** 
** ¿Qué hace este programa?
** Ordena una secuencia de números usando el algoritmo Ford-Johnson
** y compara el rendimiento usando DOS contenedores diferentes
**
** CONTENEDORES STL USADOS (2 obligatorios):
** 
** 1. std::vector<int>
**    - Array dinámico
**    - Acceso rápido por índice: O(1)
**    - Inserción al final rápida: O(1)
**    - Inserción en medio lenta: O(n)
**    - Memoria contigua (todos los elementos juntos)
**
** 2. std::deque<int> (double-ended queue)
**    - Cola de doble extremo
**    - Acceso por índice: O(1)
**    - Inserción al inicio/final rápida: O(1)
**    - Inserción en medio: O(n)
**    - Memoria en bloques (no contigua)
**
** ALGORITMO FORD-JOHNSON (Merge-Insert Sort):
** 1. Emparejar números de 2 en 2
** 2. Ordenar cada pareja (mayor primero)
** 3. Ordenar las parejas por el número mayor
** 4. Crear cadena principal con los mayores
** 5. Insertar los menores usando búsqueda binaria
**
** Ejemplo:
** Input:  [5, 2, 8, 1, 9, 3]
** Parejas: [5,2] [8,1] [9,3]
** Cadena principal: [5, 8, 9]
** Insertar menores: [1, 2, 3, 5, 8, 9]
*/
class PmergeMe
{
private:
    // No necesitamos atributos privados porque trabajamos directamente
    // con los contenedores que se pasan como parámetros
    
    // ========================================================================
    // FUNCIONES AUXILIARES PARA std::vector
    // ========================================================================
    
    /*
    ** Inserta un número en un vector ordenado usando búsqueda binaria
    ** 
    ** ¿Qué es búsqueda binaria?
    ** En lugar de buscar uno por uno (lento), dividimos a la mitad cada vez
    ** 
    ** Ejemplo: Insertar 3 en [1, 2, 5, 8, 9]
    ** - Miro el del medio (5): ¿3 < 5? Sí → busco en [1, 2]
    ** - Miro el del medio (2): ¿3 < 2? No → insertar después de 2
    ** - Resultado: [1, 2, 3, 5, 8, 9]
    */
    void binaryInsertVector(std::vector<int>& vec, int value);
    
    // ========================================================================
    // FUNCIONES AUXILIARES PARA std::deque
    // ========================================================================
    
    /*
    ** Igual que binaryInsertVector pero para std::deque
    ** Misma lógica, diferente contenedor
    */
    void binaryInsertDeque(std::deque<int>& deq, int value);

public:
    // ========================================================================
    // ORTHODOX CANONICAL FORM (OCF) - Obligatorio en módulos 02-09
    // ========================================================================
    
    // 1. Constructor por defecto
    PmergeMe();
    
    // 2. Constructor de copia
    PmergeMe(const PmergeMe& other);
    
    // 3. Operador de asignación
    PmergeMe& operator=(const PmergeMe& other);
    
    // 4. Destructor
    ~PmergeMe();
    
    // ========================================================================
    // FUNCIONES PRINCIPALES DE ORDENAMIENTO
    // ========================================================================
    
    /*
    ** Ordena un std::vector usando el algoritmo Ford-Johnson
    ** 
    ** Pasos:
    ** 1. Si hay 1 o 0 elementos → ya está ordenado, retornar
    ** 2. Emparejar números de 2 en 2
    ** 3. Ordenar cada pareja (mayor primero)
    ** 4. Ordenar recursivamente las parejas
    ** 5. Crear cadena principal con los mayores
    ** 6. Insertar los menores con búsqueda binaria
    ** 
    ** Parámetro: vec - referencia al vector a ordenar (se modifica)
    */
    void sortVector(std::vector<int>& vec);
    
    /*
    ** Ordena un std::deque usando el algoritmo Ford-Johnson
    ** 
    ** Misma lógica que sortVector pero con std::deque
    ** Esto nos permite comparar el rendimiento de ambos contenedores
    ** 
    ** Parámetro: deq - referencia al deque a ordenar (se modifica)
    */
    void sortDeque(std::deque<int>& deq);
};

#endif
