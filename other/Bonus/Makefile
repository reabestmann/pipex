# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbestman <rbestman@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 12:56:16 by rbestman          #+#    #+#              #
#    Updated: 2025/05/08 17:12:37 by rbestman         ###   ########.fr        #
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

# Bonus files
# SRC_BONUS = $(SRC_DIR)/pipex_bonus.c \
	$(SRC_DIR)/utils_bonus.c \
	$(SRC_DIR)/utils_cmd.c \
	$(SRC_DIR)/utils.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Output files
NAME = pipex

# Default rule
all: $(LIBFT) $(NAME)

# Link program
$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "$(NAME) compiled! ✔️"

# Call libft's Makefile
$(LIBFT):
	@make -C $(LIBFT_DIR) --silent
	@echo "$(LIBFT) compiled! ✔️"

# Compile object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# clean & remake
clean:
	@rm -f $(OBJ_FILES) $(OBJ_BONUS)
	@make -C $(LIBFT_DIR) clean --silent
	@echo "cleaned! 🧹"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent
	@echo "fully cleaned! 🗑️"

re: fclean all

# bonus rule
# bonus : $(LIBFT) $(OBJ_BONUS)
	#$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME)
	#echo "$(NAME) bonus compiled! ✔️"

.PHONY: all clean fclean re
