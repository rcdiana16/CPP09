/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:08:33 by diana             #+#    #+#             */
/*   Updated: 2026/02/07 11:28:33 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>   // std::cout, std::cerr
#include <fstream>    // std::ifstream para lectura de archivos
#include <sstream>    // std::stringstream (no usado pero disponible)
#include <cstdlib>    // std::atoi, std::strtod

//Inicializa un objeto BitcoinExchange vacío El std::map _database se inicializa automáticamente vacío

BitcoinExchange::BitcoinExchange() {}

// Crea una copia profunda del objeto std::map tiene su propio constructor de copia que copia todos los elementos

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

// Asigna el contenido de otro objeto a este Patrón: 1) Verificar auto-asignación, 2) Copiar datos, 3) Retornar *this

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)  // Protección contra auto-asignación (a = a)
        _database = other._database;  // std::map tiene operator= propio
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/*
** Valida formato de fecha: YYYY-MM-DD
** Verifica:
** 1. Longitud exacta de 10 caracteres
** 2. Guiones en posiciones correctas (4 y 7)
** 3. Solo dígitos en posiciones numéricas
** 4. Rangos válidos: año (1000-9999), mes (1-12), día (1-31)
*/
bool BitcoinExchange::isValidDate(const std::string& date) const
{
    // Formato: YYYY-MM-DD = 10 caracteres
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    // Verificar que solo haya dígitos (excepto en posiciones de guiones)
    for (size_t i = 0; i < date.length(); ++i)
    {
        if (i != 4 && i != 7 && !std::isdigit(date[i]))
            return false;
    }
    
    // Extraer y validar rangos de año, mes y día
    int year = std::atoi(date.substr(0, 4).c_str());   // Posiciones 0-3
    int month = std::atoi(date.substr(5, 2).c_str());  // Posiciones 5-6
    int day = std::atoi(date.substr(8, 2).c_str());    // Posiciones 8-9
    
    // Validación básica de rangos (no valida días por mes específico)
    return (year >= 1000 && year <= 9999 && month >= 1 && month <= 12 && day >= 1 && day <= 31);
}

/*
** Valida que el valor sea un número válido entre 0 y 1000
** Usa strtod() que es C++98 compatible (std::stod es C++11)
** endptr apunta al primer carácter no convertido:
** - Si *endptr == '\0', toda la cadena fue convertida correctamente
*/
bool BitcoinExchange::isValidValue(const std::string& value) const
{
    if (value.empty())
        return false;
    
    char* endptr;
    double val = std::strtod(value.c_str(), &endptr);
    
    // Verificar: conversión completa Y rango [0, 1000]
    return (*endptr == '\0' && val >= 0 && val <= 1000);
}

// Convierte string a double usando strtod() (C++98) NULL como segundo parámetro ignora el puntero de error
// Funciona incluso con números como "123.45", "0.1", "1000"
// Todo lo que lees con std::getline() y substr() son strings, no números. y cuando el usuario va a decir tengo
// 3 bitcoins en esta fecha no podemos multiplicar un string "3" por el valor del dia para dar el resultado final
//por eso se tiene que convertir a double para poder hacer operaciones matemáticas
// tambien porque tenemos que validar que lo que introduce el usuario sea un numero y no puedo comparar si el string "982" es menor que el limite de 1000 
// tambien otra razon es para soportar decimales... si nos dicen tengo 1.2 bitcoins entonces necesito convertir 1.2 a numero para poder multiplicarlo

double BitcoinExchange::stringToDouble(const std::string& str) const
{
    return std::strtod(str.c_str(), NULL);
}

/*
** FUNCIÓN: loadDatabase
** 
** PROPÓSITO: Cargar el archivo CSV con precios históricos de Bitcoin en nuestro std::map _database
** 
** FORMATO DEL ARCHIVO data.csv:
** date,exchange_rate          <- Primera línea (header) que ignoramos
** 2009-01-02,0                <- Línea de datos: fecha,precio
** 2009-01-05,0
** 2011-01-03,0.3
** 2011-01-09,0.32
** ...
** 
** RESULTADO FINAL EN _database (std::map):
** _database["2009-01-02"] = 0.0
** _database["2009-01-05"] = 0.0
** _database["2011-01-03"] = 0.3
** _database["2011-01-09"] = 0.32
** ...
** 
** El std::map mantiene AUTOMÁTICAMENTE el orden por clave (fecha)
** Esto es CRUCIAL para poder usar lower_bound() después
*/
bool BitcoinExchange::loadDatabase(const std::string& filename)
{
    // PASO 1: Abrir el archivo CSV
    // En C++98 necesitamos .c_str() para convertir std::string a const char*
    std::ifstream file(filename.c_str());
    
    // PASO 2: Verificar que el archivo se abrió correctamente
    if (!file.is_open())
        return false;  // Si falla, retornar false
    
    std::string line;  // Variable para almacenar cada línea leída
    
    // PASO 3: Saltar la primera línea (header: "date,exchange_rate")
    // No nos interesa procesar el header, solo los datos
    std::getline(file, line);
    
    // PASO 4: Leer el archivo línea por línea hasta el final
    // std::getline() lee una línea completa y retorna false cuando llega al final
    while (std::getline(file, line))
    {
        // Ahora 'line' contiene algo como: "2011-01-03,0.3"
        
        // PASO 5: Buscar la posición de la coma (separador CSV)
        // find() retorna la posición del primer ',' encontrado
        // Si no encuentra ',', retorna std::string::npos
        size_t pos = line.find(',');
        
        // PASO 6: Verificar que encontramos la coma
        if (pos != std::string::npos)
        {
            // PASO 7: Dividir la línea en dos partes usando la posición de la coma
            
            // Extraer la FECHA (todo lo que está ANTES de la coma)
            // Ejemplo: si line = "2011-01-03,0.3" y pos = 10
            // substr(0, 10) extrae desde posición 0, 10 caracteres: "2011-01-03"
            std::string date = line.substr(0, pos);
            
            // Extraer el PRECIO (todo lo que está DESPUÉS de la coma)
            // substr(pos + 1) extrae desde posición 11 hasta el final: "0.3"
            std::string price = line.substr(pos + 1);
            
            // PASO 8: Insertar en el std::map _database
            // Sintaxis: _database[clave] = valor
            // - Clave: fecha (string) -> "2011-01-03"
            // - Valor: precio convertido a double -> 0.3
            // 
            // IMPORTANTE: operator[] del map hace dos cosas:
            // 1. Si la clave NO existe: la crea y asigna el valor
            // 2. Si la clave YA existe: sobrescribe el valor anterior
            // 
            // stringToDouble(price) convierte "0.3" (string) -> 0.3 (double)
            _database[date] = stringToDouble(price);
            
            // Después de esta línea, nuestro map tiene un nuevo par:
            // clave="2011-01-03", valor=0.3
            // 
            // El std::map AUTOMÁTICAMENTE mantiene las claves ordenadas
            // No necesitamos hacer nada extra para ordenar
        }
        // Si no hay coma en la línea, simplemente la ignoramos y continuamos
    }
    
    // PASO 9: Retornar true indicando que la carga fue exitosa
    return true;
    
    // Al salir de esta función, _database contiene TODOS los pares fecha->precio
    // ordenados automáticamente por fecha (orden alfabético de strings)
    // Ejemplo de cómo queda _database internamente:
    // {
    //   "2009-01-02" -> 0.0,
    //   "2009-01-05" -> 0.0,
    //   "2011-01-03" -> 0.3,
    //   "2011-01-09" -> 0.32,
    //   "2012-01-11" -> 7.1,
    //   ...
    // }
}

/*
** Obtiene el precio de bitcoin para una fecha específica
** Si la fecha exacta no existe, retorna el precio de la fecha más cercana ANTERIOR
** 
** lower_bound(date) retorna un iterador al primer elemento >= date
** - Si encuentra fecha exacta: retorna iterador a esa fecha
** - Si no existe: retorna iterador a la siguiente fecha mayor
** 
** Lógica:
** 1. Si it != begin() Y (it == end() O it->first != date)
**    -> Decrementar para obtener fecha anterior
** 2. Retornar el precio de esa fecha
*/
double BitcoinExchange::getExchangeRate(const std::string& date) const
{
    // lower_bound: primer elemento con clave >= date
    std::map<std::string, double>::const_iterator it = _database.lower_bound(date);
    
    // Si no es el primer elemento Y (llegó al final O no es fecha exacta)
    // -> retroceder al elemento anterior (fecha más cercana menor)
    if (it != _database.begin() && (it == _database.end() || it->first != date))
        --it;
    
    // Retornar precio, o 0.0 si el map está vacío
    return (it != _database.end()) ? it->second : 0.0;
}

/*
** Procesa el archivo de input línea por línea
** Formato esperado: date | value
** Ejemplo: 2011-01-03 | 3
** 
** Para cada línea:
** 1. Validar formato (debe tener " | ")
** 2. Validar fecha
** 3. Validar valor (0-1000)
** 4. Calcular: value * exchange_rate
** 5. Mostrar resultado o error apropiado
*/
void BitcoinExchange::processInput(const std::string& filename) const
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line);  // Saltar header ("date | value")
    
    // Procesar cada línea del input
    while (std::getline(file, line))
    {
        // Buscar separador " | " (3 caracteres: espacio-pipe-espacio)
        size_t pos = line.find(" | ");
        if (pos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;  // Saltar a siguiente línea
        }
        
        // Extraer fecha y valor
        std::string date = line.substr(0, pos);          // Antes de " | "
        std::string valueStr = line.substr(pos + 3);     // Después de " | " (+3 por longitud)
        
        // Validar formato de fecha
        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        
        // Validar rango de valor
        if (!isValidValue(valueStr))
        {
            double val = stringToDouble(valueStr);
            // Mensaje de error específico según el tipo de error
            if (val < 0)
                std::cerr << "Error: not a positive number." << std::endl;
            else  // val > 1000 o formato inválido
                std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        
        // Calcular resultado: cantidad * precio_en_fecha
        double value = stringToDouble(valueStr);
        double rate = getExchangeRate(date);  // Obtiene precio (usa lower_bound)
        
        // Formato de salida: date => value = result
        std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
    }
}