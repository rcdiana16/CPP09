/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:30:00 by diana             #+#    #+#             */
/*   Updated: 2026/02/07 16:10:29 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

/*
** Clase RPN (Reverse Polish Notation):
** Evalúa expresiones matemáticas en notación polaca inversa
**
** ¿Qué es RPN?
** Notación normal (infija):    3 + 4
** Notación polaca inversa:     3 4 +
** 
** Ventaja: No necesita paréntesis ni precedencia de operadores
**
** Contenedor STL usado: std::stack<int>
** - LIFO (Last In, First Out): último en entrar, primero en salir
** - Perfecto para RPN: apilar números, desapilar para operar
** - Operaciones: push(), pop(), top()
**
** Ejemplo de evaluación:
** Expresión: "8 9 * 9 - 9 - 9 - 4 - 1 +"
** 1. Push 8, Push 9
** 2. Pop 9, Pop 8, calcular 8*9=72, Push 72
** 3. Push 9
** 4. Pop 9, Pop 72, calcular 72-9=63, Push 63
** ... y así sucesivamente
*/
class RPN
{
private:
    // Stack para almacenar números durante la evaluación
    // std::stack es un adaptador de contenedor (usa deque por defecto)
    // LIFO: perfecto para algoritmos de evaluación de expresiones
    std::stack<int> _stack;
    
    // Verifica si un carácter es un operador válido (+, -, *, /)
    bool isOperator(char c) const;
    
    // Verifica si un string es un número válido de un dígito (0-9)
    bool isNumber(const std::string& token) const;
    
    // Realiza la operación entre dos operandos
    // Lanza excepción si hay división por cero
    int performOperation(int a, int b, char op) const;

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    
    // Evalúa una expresión RPN y retorna el resultado
    // Formato: "número número operador número operador ..."
    // Ejemplo: "8 9 * 9 - 9 - 9 - 4 - 1 +" = 42
    // Lanza excepción si la expresión es inválida
    int evaluate(const std::string& expression);
};

#endif
