/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:53:22 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 14:22:58 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>  // Para std::sort (usado en casos pequeños)

// ============================================================================
// ORTHODOX CANONICAL FORM
// ============================================================================

/*
** Constructor por defecto
** No necesitamos inicializar nada porque no tenemos atributos
*/
PmergeMe::PmergeMe() {}

/*
** Constructor de copia
** No hay nada que copiar porque no tenemos atributos
*/
PmergeMe::PmergeMe(const PmergeMe& other)
{
    (void)other;  // Evitar warning de parámetro no usado
}

/*
** Operador de asignación
** No hay nada que asignar porque no tenemos atributos
*/
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void)other;  // Evitar warning de parámetro no usado
    return *this;
}

/*
** Destructor
** No hay nada que destruir porque no tenemos memoria dinámica
*/
PmergeMe::~PmergeMe() {}

// ============================================================================
// FUNCIONES PARA std::vector
// ============================================================================

/*
** FUNCIÓN: binaryInsertVector
** 
** Inserta un número en un vector YA ORDENADO usando búsqueda binaria
** 
** ¿Cómo funciona la búsqueda binaria?
** En lugar de buscar posición por posición (lento), dividimos a la mitad
** 
** EJEMPLO: Insertar 3 en [1, 2, 5, 8, 9]
** 
** Paso 1: Buscar posición
**   left = 0, right = 4 (índices)
**   mid = (0 + 4) / 2 = 2
**   vec[2] = 5
**   ¿3 < 5? SÍ → buscar en mitad izquierda
** 
** Paso 2:
**   left = 0, right = 1
**   mid = (0 + 1) / 2 = 0
**   vec[0] = 1
**   ¿3 < 1? NO → buscar en mitad derecha
** 
** Paso 3:
**   left = 1, right = 1
**   mid = (1 + 1) / 2 = 1
**   vec[1] = 2
**   ¿3 < 2? NO → buscar en mitad derecha
** 
** Paso 4:
**   left = 2, right = 1
**   left > right → PARAR
**   Insertar en posición left (2)
** 
** Resultado: [1, 2, 3, 5, 8, 9]
*/
void PmergeMe::binaryInsertVector(std::vector<int>& vec, int value)
{
    // Caso especial: vector vacío
    if (vec.empty())
    {
        vec.push_back(value);
        return;
    }
    
    // Búsqueda binaria para encontrar la posición correcta
    int left = 0;
    int right = vec.size() - 1;
    
    // Mientras haya rango para buscar
    while (left <= right)
    {
        // Calcular punto medio
        int mid = left + (right - left) / 2;
        
        // Si el valor es menor que el del medio, buscar en mitad izquierda
        if (value < vec[mid])
            right = mid - 1;
        // Si no, buscar en mitad derecha
        else
            left = mid + 1;
    }
    
    // Insertar en la posición encontrada (left)
    // insert(posición, valor) inserta ANTES de la posición
    vec.insert(vec.begin() + left, value);
}

/*
** FUNCIÓN: sortVector
** 
** Ordena un vector usando el algoritmo Ford-Johnson (Merge-Insert Sort)
** 
** ALGORITMO SIMPLIFICADO (para entender fácil):
** 
** 1. Si el vector tiene 1 o 0 elementos → ya está ordenado
** 2. Si tiene 2 elementos → ordenarlos directamente
** 3. Si tiene más:
**    a) Emparejar números de 2 en 2
**    b) Ordenar cada pareja (mayor primero)
**    c) Ordenar recursivamente los mayores
**    d) Insertar los menores usando búsqueda binaria
** 
** EJEMPLO VISUAL: [5, 2, 8, 1, 9, 3]
** 
** Paso 1: Emparejar
**   Parejas: [5,2] [8,1] [9,3]
** 
** Paso 2: Ordenar cada pareja (mayor primero)
**   [5,2] [8,1] [9,3] (ya están ordenadas)
** 
** Paso 3: Extraer mayores y ordenarlos recursivamente
**   Mayores: [5, 8, 9]
**   Ordenar recursivamente → [5, 8, 9] (ya están ordenados)
** 
** Paso 4: Insertar menores con búsqueda binaria
**   Cadena: [5, 8, 9]
**   Insertar 2: [2, 5, 8, 9]
**   Insertar 1: [1, 2, 5, 8, 9]
**   Insertar 3: [1, 2, 3, 5, 8, 9]
** 
** RESULTADO: [1, 2, 3, 5, 8, 9] ✓
*/
void PmergeMe::sortVector(std::vector<int>& vec)
{
    // CASO BASE 1: Vector vacío o con 1 elemento → ya está ordenado
    if (vec.size() <= 1)
        return;
    
    // CASO BASE 2: Vector con 2 elementos → ordenar directamente
    if (vec.size() == 2)
    {
        if (vec[0] > vec[1])
            std::swap(vec[0], vec[1]);
        return;
    }
    
    // CASO BASE 3: Vector pequeño (≤ 20 elementos) → usar std::sort
    // Para vectores pequeños, std::sort es más eficiente
    if (vec.size() <= 20)
    {
        std::sort(vec.begin(), vec.end());
        return;
    }
    
    // ========================================================================
    // ALGORITMO FORD-JOHNSON PARA VECTORES GRANDES
    // ========================================================================
    
    // PASO 1: Guardar si hay un elemento impar (sin pareja)
    int straggler = -1;  // -1 significa "no hay elemento impar"
    bool hasStraggler = (vec.size() % 2 != 0);//aqui es donde garantizamos que sea par el vector.size()
    
    if (hasStraggler)
    {
        straggler = vec.back();  // Guardar el último elemento
        vec.pop_back();          // Quitarlo del vector
    }
    
    // PASO 2: Crear parejas y ordenar cada pareja (mayor primero)
    // Ejemplo: [5, 2, 8, 1] → parejas: [5,2] [8,1]
    //se crean temporalmente estos dos vectores para la separacion y luego juntar ordenadamente.
    std::vector<int> larger;   // Números mayores de cada pareja
    std::vector<int> smaller;  // Números menores de cada pareja
    
    //empieza en el indice 0 - avanza de 2 en dos (xk estamos trabajando en parejas) - seasume que vec.size es par 
    for (size_t i = 0; i < vec.size(); i += 2)
    {
        int a = vec[i];//primer # de la pareja
        int b = vec[i + 1];//segundo # de la pareja
        
        // Ordenar la pareja: el mayor va a 'larger', el menor a 'smaller'
        if (a > b)
        {
            larger.push_back(a);
            smaller.push_back(b);
        }
        else
        {
            larger.push_back(b);
            smaller.push_back(a);
        }
    }
    
    // PASO 3: Ordenar recursivamente los números mayores
    // Esto crea la "cadena principal" ordenada
    sortVector(larger);
    
    // PASO 4: Insertar los números menores usando búsqueda binaria
    // Insertamos en orden para mantener el vector ordenado
    for (size_t i = 0; i < smaller.size(); ++i)
    {
        binaryInsertVector(larger, smaller[i]);
    }
    
    // PASO 5: Si había un elemento impar, insertarlo también
    if (hasStraggler)
    {
        binaryInsertVector(larger, straggler);
    }
    
    // PASO 6: Copiar el resultado ordenado de vuelta al vector original
    vec = larger;
}

// ============================================================================
// FUNCIONES PARA std::deque
// ============================================================================

/*
** FUNCIÓN: binaryInsertDeque
** 
** Exactamente igual que binaryInsertVector pero para std::deque
** La lógica es idéntica, solo cambia el tipo de contenedor
*/
void PmergeMe::binaryInsertDeque(std::deque<int>& deq, int value)
{
    if (deq.empty())
    {
        deq.push_back(value);
        return;
    }
    
    int left = 0;
    int right = deq.size() - 1;
    
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        
        if (value < deq[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    
    deq.insert(deq.begin() + left, value);
}

/*
** FUNCIÓN: sortDeque
** 
** Exactamente igual que sortVector pero para std::deque
** La lógica es idéntica, solo cambia el tipo de contenedor
** 
** Esto nos permite comparar el rendimiento de vector vs deque
** con el mismo algoritmo
*/
void PmergeMe::sortDeque(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return;
    
    if (deq.size() == 2)
    {
        if (deq[0] > deq[1])
            std::swap(deq[0], deq[1]);
        return;
    }
    
    if (deq.size() <= 20)
    {
        std::sort(deq.begin(), deq.end());
        return;
    }
    
    int straggler = -1;
    bool hasStraggler = (deq.size() % 2 != 0);
    
    if (hasStraggler)
    {
        straggler = deq.back();
        deq.pop_back();
    }
    
    std::deque<int> larger;
    std::deque<int> smaller;
    
    for (size_t i = 0; i < deq.size(); i += 2)
    {
        int a = deq[i];
        int b = deq[i + 1];
        
        if (a > b)
        {
            larger.push_back(a);
            smaller.push_back(b);
        }
        else
        {
            larger.push_back(b);
            smaller.push_back(a);
        }
    }
    
    sortDeque(larger);
    
    for (size_t i = 0; i < smaller.size(); ++i)
    {
        binaryInsertDeque(larger, smaller[i]);
    }
    
    if (hasStraggler)
    {
        binaryInsertDeque(larger, straggler);
    }
    
    deq = larger;
}
