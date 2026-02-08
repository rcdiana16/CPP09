/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:30:00 by diana             #+#    #+#             */
/*   Updated: 2026/02/07 16:37:16 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cctype>      

RPN::RPN() {}
RPN::RPN(const RPN& other) : _stack(other._stack) {}
//Orthodox Canonical Form - Operador de asignación
// Asigna el contenido de otro objeto a este

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}
RPN::~RPN() {}

/*
** Verifica si un carácter es un operador válido
** Operadores permitidos: + - * /
*/
bool RPN::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/*
** Verifica si un token es un número válido de un dígito (0-9)
** El subject especifica que los números son menores a 10
*/
bool RPN::isNumber(const std::string& token) const
{
    // Debe ser exactamente 1 carácter Y debe ser un dígito
    return (token.length() == 1 && std::isdigit(token[0]));
}

/*
** Realiza la operación aritmética entre dos operandos
** 
** IMPORTANTE: El orden importa en RPN
** Si tenemos en el stack: [... a b] y operador '-'
** Debemos calcular: a - b (NO b - a)
** 
** Por eso:
** - Primero pop() saca 'b' (el último)
** - Segundo pop() saca 'a' (el penúltimo)
** - Calculamos: a operador b
*/
int RPN::performOperation(int a, int b, char op) const
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Error: division by zero");
            return a / b;
        default:
            throw std::runtime_error("Error: invalid operator");
    }
}

/*
** FUNCIÓN PRINCIPAL: evaluate
** 
** Evalúa una expresión en notación polaca inversa (RPN)
** 
** ALGORITMO RPN:
** 1. Leer token por token (separados por espacios)
** 2. Si es número: PUSH al stack
** 3. Si es operador:
**    a) POP dos números del stack
**    b) Aplicar operación
**    c) PUSH resultado al stack
** 4. Al final, debe quedar exactamente 1 número en el stack (el resultado)
**
** EJEMPLO: "8 9 * 9 - 9 - 9 - 4 - 1 +"
** 
** Token | Acción           | Stack después
** ------|------------------|---------------
** 8     | push(8)          | [8]
** 9     | push(9)          | [8, 9]
** *     | pop 9, pop 8     | []
**       | 8*9=72, push(72) | [72]
** 9     | push(9)          | [72, 9]
** -     | pop 9, pop 72    | []
**       | 72-9=63, push(63)| [63]
** 9     | push(9)          | [63, 9]
** -     | pop 9, pop 63    | []
**       | 63-9=54, push(54)| [54]
** 9     | push(9)          | [54, 9]
** -     | pop 9, pop 54    | []
**       | 54-9=45, push(45)| [45]
** 4     | push(4)          | [45, 4]
** -     | pop 4, pop 45    | []
**       | 45-4=41, push(41)| [41]
** 1     | push(1)          | [41, 1]
** +     | pop 1, pop 41    | []
**       | 41+1=42, push(42)| [42]
** 
** Resultado final: 42
*/
int RPN::evaluate(const std::string& expression)
{
    // Limpiar el stack antes de evaluar (por si se reutiliza el objeto)
    while (!_stack.empty())
        _stack.pop();
    
    // Usar istringstream para dividir la expresión en tokens (palabras) - Los tokens están separados por espacios
    // iss es el nombre de la variable que contiene la expresion(el texto que se va a leer) separada en tokens
    // xk lo utilizamos? Para poder hacer esto mentalmente: “Dame la siguiente palabra“Ahora la siguiente”Sin tener que partir el string a mano
    std::istringstream iss(expression);
    std::string token;
    
    // Leer token por token ">>" es el operador de extracción de stream " -“Mientras pueda sacar algo de iss y meterlo en token, sigue.-
    //iss es una bolsa de canicas, token es tu mano, El >> significa: “Dame una canica de la bolsa y ponla en mi mano”
    while (iss >> token)
    {
        // CASO 1: El token es un número (0-9)
        if (isNumber(token))
        {
            // Convertir char a int: '5' - '0' = 5
            int num = token[0] - '0';
            
            // PUSH: Apilar el número en el stack
            _stack.push(num);
        }
        // CASO 2: El token es un operador (+, -, *, /)
        else if (token.length() == 1 && isOperator(token[0]))
        {
            // Verificar que hay al menos 2 números en el stack
            if (_stack.size() < 2)
                throw std::runtime_error("Error: insufficient operands");
            
            // POP: Sacar los dos últimos números del stack
            // IMPORTANTE: El orden importa
            int b = _stack.top();  // Segundo operando (último en entrar)
            _stack.pop();
            
            int a = _stack.top();  // Primer operando (penúltimo en entrar)
            _stack.pop();
            
            // Realizar la operación: a operador b
            int result = performOperation(a, b, token[0]);
            
            // PUSH: Apilar el resultado
            _stack.push(result);
        }
        // CASO 3: Token inválido (ni número ni operador)
        else
        {
            throw std::runtime_error("Error: invalid token");
        }
    }
    
    // Al final, el stack debe tener exactamente 1 elemento (el resultado)
    if (_stack.size() != 1)
        throw std::runtime_error("Error: invalid expression");
    
    // Retornar el resultado final
    return _stack.top();
}
