# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 12:56:16 by rbestman          #+#    #+#              #
#    Updated: 2025/04/29 01:43:36 by rbestman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler & flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ift_printf -Iincludes

# Directories
FT_PRINTF_DIR = ft_printf
LIBFT_DIR = $(FT_PRINTF_DIR)/libft
SRC_DIR = VER

# Ft_printf & libft files

FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC_FILES = $(SRC_DIR)/pipex.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/split.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output files
NAME = pipex

# Default rule
all: $(FT_PRINTF) $(LIBFT) $(NAME)

# Link program
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(FT_PRINTF) $(LIBFT) -o $(NAME)

# Call ft_printf's Makefile (it will call libft's Makefile)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -f $(OBJ_FILES)
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
