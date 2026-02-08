/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:08:51 by diana             #+#    #+#             */
/*   Updated: 2026/02/07 09:09:01 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

/*
** Clase BitcoinExchange:
** Gestiona una base de datos de precios históricos de Bitcoin y calcula
** el valor de una cantidad de bitcoin en una fecha específica.
**
** Contenedor STL usado: std::map<std::string, double>
** - Clave: fecha en formato YYYY-MM-DD (string)
** - Valor: precio del bitcoin en esa fecha (double)
** - Ventaja: mantiene las fechas ordenadas automáticamente
** - Permite búsqueda eficiente con lower_bound() para encontrar fecha más cercana
*/
class BitcoinExchange
{
private:
    // Base de datos: mapa ordenado de fechas -> precios
    // std::map mantiene orden automático por clave (fecha)
    // Complejidad de búsqueda: O(log n)
    std::map<std::string, double> _database;
    
    // Valida formato de fecha: YYYY-MM-DD
    // Verifica que año, mes y día estén en rangos válidos
    bool isValidDate(const std::string& date) const;
    
    // Valida que el valor sea un número entre 0 y 1000
    bool isValidValue(const std::string& value) const;
    
    // Convierte string a double (C++98 compatible)
    // Usa strtod() en lugar de std::stod() (C++11)
    double stringToDouble(const std::string& str) const;

public:
    // Orthodox Canonical Form (OCF) - Obligatorio en módulos 02-09
    
    // 1. Constructor por defecto
    BitcoinExchange();
    
    // 2. Constructor de copia
    BitcoinExchange(const BitcoinExchange& other);
    
    // 3. Operador de asignación
    BitcoinExchange& operator=(const BitcoinExchange& other);
    
    // 4. Destructor
    ~BitcoinExchange();
    
    // Carga la base de datos desde archivo CSV
    // Formato esperado: date,exchange_rate
    // Retorna true si se cargó correctamente
    bool loadDatabase(const std::string& filename);
    
    // Procesa archivo de input con formato: date | value
    // Calcula y muestra el valor en bitcoin para cada línea
    void processInput(const std::string& filename) const;
    
    // Obtiene el precio de bitcoin para una fecha específica
    // Si la fecha no existe, retorna el precio de la fecha más cercana anterior
    // Usa lower_bound() del std::map para búsqueda eficiente
    double getExchangeRate(const std::string& date) const;
};

#endif