# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 12:56:16 by rbestman          #+#    #+#              #
#    Updated: 2025/05/07 17:57:01 by rbestman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler & flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iincludes

# Directories

LIBFT_DIR = libft
SRC_DIR = src

# libft files

LIBFT = $(LIBFT_DIR)/libft.a

# Source files
SRC_FILES = $(SRC_DIR)/pipex.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/utils_cmd.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output files
NAME = pipex

# Default rule
all: $(LIBFT) $(NAME)

# Link program
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)

# Call libft's Makefile

$(LIBFT):
	make -C $(LIBFT_DIR)

# Compile object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	rm -f $(OBJ_FILES)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
