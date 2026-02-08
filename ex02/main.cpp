/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:03:36 by diana             #+#    #+#             */
/*   Updated: 2026/02/08 16:24:48 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>  
#include <iomanip>      

/*
** Programa: PmergeMe
** 
** Uso: ./PmergeMe <números positivos>
** 
** Ejemplo: ./PmergeMe 3 5 9 7 4
** 
** Funcionalidad:
** 1. Lee números de la línea de comandos
** 2. Valida que sean números positivos
** 3. Ordena usando Ford-Johnson con std::vector
** 4. Ordena usando Ford-Johnson con std::deque
** 5. Compara los tiempos de ejecución
** 
** Contenedores STL usados: std::vector y std::deque
*/

/*
** FUNCIÓN: getTimeInMicroseconds
** 
** Obtiene el tiempo actual en microsegundos
** 
** ¿Qué es un microsegundo?
** 1 segundo = 1,000,000 microsegundos
** 1 microsegundo = 0.000001 segundos
** 
** Usamos gettimeofday() que es compatible con C++98
** (clock() no es suficientemente preciso para este ejercicio)
*/
double getTimeInMicroseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    // Convertir a microsegundos
    // tv.tv_sec = segundos
    // tv.tv_usec = microsegundos
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

/*
** FUNCIÓN: isValidNumber
** 
** Verifica si un string es un número positivo válido
** 
** Reglas:
** - Solo dígitos (0-9)
** - No puede empezar con 0 (excepto si es solo "0")
** - Debe ser positivo
** - No puede ser demasiado grande (debe caber en int)
*/
bool isValidNumber(const std::string& str)
{
    // String vacío → inválido
    if (str.empty())
        return false;
    
    // Verificar que solo tenga dígitos
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    
    // Convertir a long para verificar rango
    char* endptr;
    long num = std::strtol(str.c_str(), &endptr, 10);
    
    // Verificar que la conversión fue completa y el número es positivo
    // y cabe en un int
    return (*endptr == '\0' && num >= 0 && num <= 2147483647);
}

/*
** FUNCIÓN: printNumbers
** 
** Imprime una secuencia de números
** Si hay más de 5 números, muestra solo los primeros 5 y agrega [...]
** 
** Ejemplo:
** [3, 5, 9, 7, 4] → "3 5 9 7 4"
** [1, 2, 3, 4, 5, 6, 7, 8] → "1 2 3 4 5 [...]"
*/
void printNumbers(const std::vector<int>& vec)
{
    size_t limit = (vec.size() > 5) ? 5 : vec.size();
    
    for (size_t i = 0; i < limit; ++i)
    {
        std::cout << vec[i];
        if (i < limit - 1)
            std::cout << " ";
    }
    
    if (vec.size() > 5)
        std::cout << " [...]";
}

/*
** FUNCIÓN PRINCIPAL: main
** 
** Flujo del programa:
** 1. Validar argumentos
** 2. Parsear y validar números
** 3. Crear dos copias (vector y deque)
** 4. Mostrar "Before"
** 5. Ordenar con vector y medir tiempo
** 6. Ordenar con deque y medir tiempo
** 7. Mostrar "After"
** 8. Mostrar tiempos
*/
int main(int argc, char** argv)
{
    // ========================================================================
    // PASO 1: Validar que hay argumentos
    // ========================================================================
    
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    // ========================================================================
    // PASO 2: Parsear y validar números
    // ========================================================================
    
    std::vector<int> numbers;  // Aquí guardamos los números válidos
    
    // Recorrer cada argumento (empezando desde argv[1])
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        
        // Validar que sea un número positivo
        if (!isValidNumber(arg))
        {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        
        // Convertir a int y agregar al vector
        int num = std::atoi(arg.c_str());
        numbers.push_back(num);
    }
    
    // ========================================================================
    // PASO 3: Crear dos copias (una para vector, otra para deque)
    // ========================================================================
    
    // Copia para std::vector (ya la tenemos en 'numbers')
    std::vector<int> vec = numbers;
    
    // Copia para std::deque
    std::deque<int> deq;
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        deq.push_back(numbers[i]);
    }
    
    // ========================================================================
    // PASO 4: Mostrar números ANTES de ordenar
    // ========================================================================
    
    std::cout << "Before: ";
    printNumbers(numbers);
    std::cout << std::endl;
    
    // ========================================================================
    // PASO 5: Ordenar con std::vector y medir tiempo
    // ========================================================================
    
    PmergeMe sorter;  // Crear objeto PmergeMe
    
    // Tomar tiempo ANTES de ordenar
    double startVector = getTimeInMicroseconds();
    
    // Ordenar usando vector
    sorter.sortVector(vec);
    
    // Tomar tiempo DESPUÉS de ordenar
    double endVector = getTimeInMicroseconds();
    
    // Calcular tiempo transcurrido en microsegundos
    double timeVector = endVector - startVector;
    
    // ========================================================================
    // PASO 6: Ordenar con std::deque y medir tiempo
    // ========================================================================
    
    // Tomar tiempo ANTES de ordenar
    double startDeque = getTimeInMicroseconds();
    
    // Ordenar usando deque
    sorter.sortDeque(deq);
    
    // Tomar tiempo DESPUÉS de ordenar
    double endDeque = getTimeInMicroseconds();
    
    // Calcular tiempo transcurrido en microsegundos
    double timeDeque = endDeque - startDeque;
    
    // ========================================================================
    // PASO 7: Mostrar números DESPUÉS de ordenar
    // ========================================================================
    
    std::cout << "After: ";
    printNumbers(vec);  // Mostrar el vector ordenado
    std::cout << std::endl;
    
    // ========================================================================
    // PASO 8: Mostrar tiempos de ejecución
    // ========================================================================
    
    // Configurar precisión decimal (5 dígitos después del punto)
    std::cout << std::fixed << std::setprecision(5);
    
    // Mostrar tiempo de std::vector
    std::cout << "Time to process a range of " << numbers.size() 
              << " elements with std::vector : " 
              << timeVector << " us" << std::endl;
    
    // Mostrar tiempo de std::deque
    std::cout << "Time to process a range of " << numbers.size() 
              << " elements with std::deque : " 
              << timeDeque << " us" << std::endl;
    
    return 0;
}
