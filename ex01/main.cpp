/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:30:00 by diana             #+#    #+#             */
/*   Updated: 2026/02/07 14:30:00 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

/*
** Programa: RPN (Reverse Polish Notation)
** 
** Uso: ./RPN "expresión"
** 
** Funcionalidad:
** Evalúa expresiones matemáticas en notación polaca inversa
** 
** Ejemplos:
** ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"  → 42
** ./RPN "7 7 * 7 -"                  → 42
** ./RPN "1 2 * 2 / 2 * 2 4 - +"      → 0
** 
** Contenedor STL usado: std::stack
** - Estructura LIFO (Last In, First Out)
** - Ideal para algoritmos de evaluación de expresiones
** - Operaciones principales: push(), pop(), top()
** 
** Algoritmo:
** 1. Si es número → push al stack
** 2. Si es operador → pop 2 números, operar, push resultado
** 3. Al final → debe quedar 1 número (el resultado)
*/
int main(int argc, char** argv)
{
    // Validar número de argumentos
    // Debe ser exactamente 2: ./RPN "expresión"
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    // Crear objeto RPN (usa constructor por defecto)
    RPN rpn;
    
    // Try-catch para manejar errores de evaluación
    // La función evaluate() lanza excepciones si hay errores
    try
    {
        // Evaluar la expresión RPN
        int result = rpn.evaluate(argv[1]);
        
        // Imprimir resultado
        std::cout << result << std::endl;
    }
    catch (const std::exception& e)
    {
        // Capturar cualquier error y mostrar mensaje
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
