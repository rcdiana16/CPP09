NAME = RPN

# Compilador y flags
CXX = c++
# -Wall -Wextra -Werror: Warnings obligatorios en 42
# -std=c++98: Estándar C++98 (obligatorio en CPP modules)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Archivos fuente y objetos
SRCS = main.cpp RPN.cpp
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
