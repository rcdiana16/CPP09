/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diana <diana@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:09:10 by diana             #+#    #+#             */
/*   Updated: 2026/02/07 09:09:16 by diana            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

/*
** Programa: btc (Bitcoin Exchange)
** 
** Uso: ./btc <input_file>
** 
** Funcionalidad:
** 1. Carga base de datos de precios históricos desde "data.csv"
** 2. Lee archivo de input con formato: date | value
** 3. Para cada línea, calcula: value * precio_bitcoin_en_fecha
** 4. Si la fecha no existe, usa la fecha más cercana anterior
** 
** Contenedor STL usado: std::map (en BitcoinExchange)
** - Mantiene fechas ordenadas
** - Permite búsqueda eficiente con lower_bound()
*/
int main(int argc, char** argv)
{
    // Validar número de argumentos
    // Debe ser exactamente 2: ./btc <input_file>
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    
    // Crear objeto BitcoinExchange (usa constructor por defecto)
    BitcoinExchange btc;
    
    // Cargar base de datos CSV con precios históricos
    // El archivo "data.csv" debe estar en el mismo directorio
    // Formato: date,exchange_rate
    if (!btc.loadDatabase("data.csv"))
    {
        std::cerr << "Error: could not load database." << std::endl;
        return 1;
    }
    
    // Procesar archivo de input (argv[1])
    // Lee línea por línea, valida y calcula resultados
    btc.processInput(argv[1]);
    
    return 0;
}