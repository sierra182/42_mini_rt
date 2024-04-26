# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svidot <svidot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/29 08:16:28 by seblin            #+#    #+#              #
#    Updated: 2023/12/21 16:43:24 by svidot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SOURCES = ft_printf.c
OBJECTS = $(SOURCES:.c=.o)
LIBFTDIR = ./libft
LIBFTPATH = $(LIBFTDIR)/libft.a
HEADER = ft_printf.h

.PHONY : all libft clean fclean re 

all : libft $(NAME)
	
libft : 	
	@$(MAKE) -s -C $(LIBFTDIR)	
	
%.o : %.c $(LIBFTPATH) $(HEADER)	
	@echo "\033[0;32m compiling $<...\033[0m" 🚀
	@$(CC) $(CFLAGS) $< -c -o $@

$(NAME) :: $(LIBFTPATH)
	@echo "\n\033[0;32m copying $(LIBFTPATH) to $(NAME)...\033[0m 🚀\n"
	@cp $(LIBFTPATH) $(NAME)

$(NAME) :: $(OBJECTS)
	@echo "\n\033[0;32m adding $(OBJECTS) to $(NAME)...\033[0m 🚀\n"	
	@ar rcs $@ $(OBJECTS)	
	
clean :
	@echo " cleanning ft_printf objects 🧻"
	@rm -f $(OBJECTS)
	@$(MAKE) -s -C $(LIBFTDIR) clean 
	
fclean : 
	@echo " cleanning ft_printf objects 🧻"
	@rm -f $(OBJECTS)
	@echo " cleanning $(NAME) 🚽"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFTDIR) fclean 
	
re : fclean all
