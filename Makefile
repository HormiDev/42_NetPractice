# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 21:16:53 by ide-dieg          #+#    #+#              #
#    Updated: 2025/06/01 21:39:22 by ide-dieg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = subneting

SRC =	src/subneting.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBSA = 42_Libft/libft.a \

OBJDIR = obj
OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): ide-dieg netpractice_title update_submodules build_libft $(OBJ)
	@echo "$(NARANJA)Building $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBSA)
	@tput cuu1 && tput el
	@echo "$(VERDE)$(NAME) built!$(NC)"

clean: fclean_libft
	@echo "Cleaning objects..."
	@rm -rf $(OBJDIR)
	@tput cuu1 && tput el
	@echo "Objects cleaned!"

fclean: clean
	@echo "Cleaning $(NAME)..."
	@rm -f $(NAME)
	@tput cuu1 && tput el
	@echo "$(NAME) cleaned!"

re: fclean $(NAME)

build_libft:
	@if [ ! -f 42_Libft/libft.a ]; then \
		echo "$(NARANJA)Compiling Libft...$(NC)"; \
		make all -C 42_Libft > /dev/null 2>&1; \
		tput cuu1 && tput el; \
		echo "$(VERDE)Libft compiled!$(NC)"; \
	fi

fclean_libft:
	@echo "Cleaning Libft..."
	@make fclean -C 42_Libft > /dev/null 2>&1
	@tput cuu1 && tput el
	@echo "Libft cleaned!"

update_submodules:
	@echo "$(NARANJA)Updating submodules...$(NC)"
	@git submodule update --init --recursive > /dev/null 2>&1
	@tput cuu1 && tput el
	@echo "$(VERDE)Submodules updated!$(NC)"

ROJO = \033[0;31m
NC = \033[0m
NARANJA = \033[0;33m
AZUL = \033[0;34m
VERDE = \033[0;32m

ide-dieg:
	@clear	
	@echo "$(ROJO)██╗██████╗ ███████╗    ██████╗ ██╗███████╗ ██████╗ $(AZUL)         ██╗  ██╗██████╗ "
	@echo "$(ROJO)██║██╔══██╗██╔════╝    ██╔══██╗██║██╔════╝██╔════╝ $(AZUL)         ██║  ██║╚════██╗"
	@echo "$(ROJO)██║██║  ██║█████╗█████╗██║  ██║██║█████╗  ██║  ███╗$(AZUL)         ███████║ █████╔╝"
	@echo "$(ROJO)██║██║  ██║██╔══╝╚════╝██║  ██║██║██╔══╝  ██║   ██║$(AZUL)         ╚════██║██╔═══╝ "
	@echo "$(ROJO)██║██████╔╝███████╗    ██████╔╝██║███████╗╚██████╔╝$(AZUL)              ██║███████╗"
	@echo "$(ROJO)╚═╝╚═════╝ ╚══════╝    ╚═════╝ ╚═╝╚══════╝ ╚═════╝ $(AZUL)              ╚═╝╚══════╝"
	@echo "$(NARANJA)██╗  ██╗ ██████╗ ██████╗ ███╗   ███╗██╗██████╗ ███████╗██╗   ██╗$(VERDE)       ██╗  "
	@echo "$(NARANJA)██║  ██║██╔═══██╗██╔══██╗████╗ ████║██║██╔══██╗██╔════╝██║   ██║$(VERDE)   ██╗ ╚═██╗"
	@echo "$(NARANJA)███████║██║   ██║██████╔╝██╔████╔██║██║██║  ██║█████╗  ██║   ██║$(VERDE)   ╚═╝   ██║"
	@echo "$(NARANJA)██╔══██║██║   ██║██╔══██╗██║╚██╔╝██║██║██║  ██║██╔══╝  ╚██╗ ██╔╝$(VERDE)   ██╗   ██║"
	@echo "$(NARANJA)██║  ██║╚██████╔╝██║  ██║██║ ╚═╝ ██║██║██████╔╝███████╗ ╚████╔╝ $(VERDE)   ╚═╝ ██╔═╝"
	@echo "$(NARANJA)╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═════╝ ╚══════╝  ╚═══╝  $(VERDE)       ╚═╝  $(NC)"

netpractice_title:
	@echo " __ _  ____  ____  ____  ____   __    ___  ____  __  ___  ____ "
	@echo "(  ( \(  __)(_  _)(  _ \(  _ \ / _\  / __)(_  _)(  )/ __)(  __)"
	@echo "/    / ) _)   )(   ) __/ )   //    \( (__   )(   )(( (__  ) _) "
	@echo "\_)__)(____) (__) (__)  (__\_)\_/\_/ \___) (__) (__)\___)(____)"

