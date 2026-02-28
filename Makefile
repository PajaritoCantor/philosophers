# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/28 22:05:40 by jurodrig          #+#    #+#              #
#    Updated: 2026/02/28 22:06:05 by jurodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

# Directorios
INC_DIR     = include/
OBJ_DIR     = obj/

# Lista de archivos fuente con sus rutas
SRCS        = main/main.c \
              utils/getters_setters.c \
              utils/safe_functions.c \
              utils/synchro_utils.c \
              utils/utils.c \
              utils/write.c \
              parse/parse.c \
              dinner/dinner.c \
              dinner/monitor.c \
              init/init.c

# Conversión de archivos .c a .o manteniendo la estructura en obj/
OBJS        = $(SRCS:%.c=$(OBJ_DIR)%.o)

# Colores
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilación de $(NAME) completada.$(RESET)"

# Regla para compilar archivos .o creando las subcarpetas necesarias en obj/
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Objetos eliminados.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Ejecutable eliminado.$(RESET)"

re: fclean all

.PHONY: all clean fclean re