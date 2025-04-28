# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 12:56:16 by rbestman          #+#    #+#              #
#    Updated: 2025/04/26 16:45:31 by rbestman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler & flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ift_printf -Iincludes

# Directories
FT_PRINTF_DIR = ft_printf
SRC_DIR = SRC
MAIN_DIR = main

# Ft_printf file

FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

# Source files
SRC_FILES = $(SRC_DIR)/pipex.c \
	$(SRC_DIR)/utils.c

//# Main files
//MAIN_FILES = $(MAIN_DIR)/main.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o) //$(MAIN_FILES:.c=.o)

# Output files
NAME = pipex

# Default rule
all: $(FT_PRINTF) $(NAME)

# Link program
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(FT_PRINTF) -o $(NAME)

# Call ft_printf's Makefile (it will call libft's Makefile)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -C $< -o $@

# Cleaning
clean:
	rm -f $(OBJ_FILES)
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
