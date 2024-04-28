# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svidot <svidot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 06:54:46 by svidot            #+#    #+#              #
#    Updated: 2023/12/04 06:54:46 by svidot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#OBJECTS_BONUS = $(SOURCES_BONUS:.c=_bonus.o)
#SRC_BONUS_DIR = $(BONUS_DIR)/sources
#NAME_BONUS = $(BONUS_DIR)/$(NAME)
#BONUS_DIR = bonus
#HEADERS_BONUS = 
#SOURCES_BONUS = 
#CFLAGS_BONUS =
#GNL_DIR = gnl

NAME = miniRT
LIBFT_DIR = ft_printf/libft
LIBFTPRINTF = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_DIR = ft_printf
SRC_DIR = sources
HEADERS_DIR = include
MLX_DIR = mlx_linux

CC = cc
CFLAGS = \
	-I$(HEADERS_DIR) \
	-I$(HEADERS_DIR)/exit \
	-I$(LIBFT_DIR) \
	-I$(FT_PRINTF_DIR) \
	-I$(MLX_DIR) \
	-g
	# -O3 -Wall -Wextra -Werror -g

LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz 

OBJECTS = $(SOURCES:.c=.o)

SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/exit/exit.c \
	$(SRC_DIR)/exit/data_store.c \
	$(SRC_DIR)/parsing/parse.c \

HEADERS = \
	$(HEADERS_DIR)/main.h \
	$(HEADERS_DIR)/x_mini_struct.h \
	$(HEADERS_DIR)/x_exit.h \
	$(HEADERS_DIR)/exit/exit.h \
	$(HEADERS_DIR)/exit/data_store.h \

.PHONY: all mlx ft_printf clean fclean re intro l newline backline emoticon
#bonus

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(LIBFTPRINTF) $(HEADERS)
	@echo "\033[0;32m compiling $(NAME) object $<...\033[0m" 🚀
	@$(CC) $(CFLAGS) $< -c -o $@

# $(GNL_DIR)/%.o : $(GNL_DIR)/%.c $(HEADERS)
# 	@echo "\033[0;32m compiling $(NAME) object $<...\033[0m" 🚀
# 	@$(CC) $(CFLAGS) $< -c -o $@

# $(BONUS_DIR)/%_bonus.o : $(BONUS_DIR)/%.c $(LIBFTPRINTF) $(HEADERS) 
# 	@echo "\033[0;32m compiling $(NAME) object bonus $<...\033[0m" 🚀
# 	@$(CC) $(CFLAGS) $(CFLAGS_BONUS) $< -c -o $@

# $(GNL_DIR)/%_bonus.o : $(GNL_DIR)/%.c $(HEADERS)
# 	@echo "\033[0;32m compiling $(NAME) object bonus $<...\033[0m" 🚀
# 	@$(CC) $(CFLAGS) $< -c -o $@

#all: intro mlx ft_printf $(NAME) emoticon		

l: newline mlx ft_printf $(NAME)

mlx:
	@$(MAKE) -s -C $(MLX_DIR)

ft_printf: emoticon
#	@$(MAKE) -s -C $(LIBFT_DIR) bonus 
	@$(MAKE) -s -C $(FT_PRINTF_DIR) 

$(NAME) : $(OBJECTS) 
	@echo "\n\033[0;32m linking $(NAME) objects \
	with $(LIBFTPRINTF)...\033[0m 🚀\n\n 💗 💎 💎 💗\n"
	@$(CC) $(OBJECTS) $(LDFLAGS) $(LIBFTPRINTF) -o $@

# bonus: ft_printf $(NAME_BONUS)
# 	@echo " 💎 🧯 🔥 😵\n"

# $(NAME_BONUS) : $(OBJECTS_BONUS)
# 	@echo "\n\033[0;32m linking $(NAME) objects and objects bonus with $(LIBFTPRINTF) to $(NAME_BONUS) \033[0m 🚀\n"
# 	@$(CC) $(OBJECTS_BONUS) $(LDFLAGS) $(LIBFTPRINTF) -o $@

emoticon:
	@echo "\n 💗 😀 😃 😍\n"

newline: 
	@echo ""

backline: 
	@echo "\033[A\033[A"

intro:
	@echo -e "\033[?25l"
	clear
	@sleep 1
	@echo -n " Wake"
	@sleep .4
	@echo " up...\n"
	@sleep .1
	@echo -n " "
	@letters="The Makefile has you..."; \
	echo "\033[1;92m$$letters\033[0m" | awk '{split($$0, chars, ""); \
	for (i = 1; i <= length($$0); i++) \
	{printf "%s", chars[i]; system("sleep 0.2");}} \
	system("sleep 1");' 
	@words="\n\n\tFollow \n\t\tthe \t\b\b\033[0;96mColored! \
	\n\n\t\t\b\b\b\b\b\b\033[1;95mUnicorne!\033[0m...🦄\n\n"; \
	for j in $${words}; do \
		echo -n "$$j"; \
		sleep .4; \
	done
	@sleep .4
	@cat mfile_design
	@$(MAKE) -s emoticon
	@echo "\033[?25h"
	@$(MAKE) -s backline	

clean:
	@echo "\n cleanning $(NAME) objects 🧻"
	@rm -f $(OBJECTS) $(OBJECTS_BONUS);
	@$(MAKE) -C $(FT_PRINTF_DIR) clean -s
	@echo ""
	@$(MAKE) -C $(MLX_DIR) clean -s
	@echo ""

fclean: 
	@echo "\n cleanning $(NAME) objects 🧻"
	@rm -f $(OBJECTS) $(OBJECTS_BONUS);
	@echo " cleanning $(NAME) 🚽" 
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean -s
	@echo ""
	@$(MAKE) -C $(MLX_DIR) clean -s
	@echo ""

re: fclean backline l
