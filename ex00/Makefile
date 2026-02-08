# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diana <diana@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/05 09:09:10 by diana             #+#    #+#              #
#    Updated: 2026/02/07 09:09:16 by diana            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable final
NAME = btc

# Compilador y flags
CXX = c++
# -Wall -Wextra -Werror: Warnings obligatorios en 42
# -std=c++98: Estándar C++98 (obligatorio en CPP modules)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Archivos fuente y objetos
SRCS = main.cpp BitcoinExchange.cpp
OBJS = $(SRCS:.cpp=.o)

# Regla por defecto: compilar todo
all: $(NAME)

# Regla de linkeo: crear ejecutable desde objetos
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# Regla de compilación: .cpp -> .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	rm -f $(OBJS)

# Limpiar todo (objetos + ejecutable)
fclean: clean
	rm -f $(NAME)

# Recompilar desde cero
re: fclean all

# Declarar reglas que no son archivos
.PHONY: all clean fclean re