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

LIBFT_DIR = ft_printf/libft
GNL_DIR = gnl
LIBFTPRINTF = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_DIR = ft_printf
SRC_DIR = sources
HEADERS_DIR = include
MLX_DIR = .mlx_linux

NAME = miniRT
CC = cc

OBJECTS = $(SOURCES:.c=.o)
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

CFLAGS = \
	-I$(HEADERS_DIR) \
	-I$(HEADERS_DIR)/event \
	-I$(HEADERS_DIR)/exit \
	-I$(HEADERS_DIR)/init_data \
	-I$(HEADERS_DIR)/linear_algebra \
	-I$(HEADERS_DIR)/matrix \
	-I$(HEADERS_DIR)/mesh \
	-I$(HEADERS_DIR)/parsing \
	-I$(HEADERS_DIR)/rays/colors \
	-I$(HEADERS_DIR)/rays/find_closest_intersection \
	-I$(HEADERS_DIR)/rays/shadows \
	-I$(HEADERS_DIR)/rays \
	-I$(HEADERS_DIR)/z_main \
	-I$(GNL_DIR) \
	-I$(LIBFT_DIR) \
	-I$(FT_PRINTF_DIR) \
	-I$(MLX_DIR) \
	-O3 \
	-Wall -Wextra -Werror

SOURCES = \
	$(SRC_DIR)/.meta/create_video_image.c \
	$(SRC_DIR)/.meta/scening.c \
	$(SRC_DIR)/.meta/save_image_reference.c \
	$(SRC_DIR)/.meta/test_prints.c \
	$(SRC_DIR)/.meta/meta_keycode.c \
	$(SRC_DIR)/.meta/transform_video_scene.c \
	$(SRC_DIR)/.meta/meta_utils.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/mesh/cam.c \
	$(SRC_DIR)/mesh/cam_trsf.c \
	$(SRC_DIR)/mesh/mesh_trsf.c \
	$(SRC_DIR)/mesh/change_mesh_size.c \
	$(SRC_DIR)/event/event.c \
	$(SRC_DIR)/parsing/parsing_utils.c \
	$(SRC_DIR)/exit/exit.c \
	$(SRC_DIR)/exit/data_store.c \
	$(SRC_DIR)/exit/data_store_shapes.c \
	$(SRC_DIR)/matrix/matrix.c \
	$(SRC_DIR)/matrix/matrix_trsf.c \
	$(SRC_DIR)/parsing/parse.c \
	$(SRC_DIR)/parsing/file_content_is_correct.c \
	$(SRC_DIR)/parsing/all_necessary_elements_are_present.c \
	$(SRC_DIR)/parsing/elements_data_are_valid.c \
	$(SRC_DIR)/parsing/elements_data_are_valid_utils.c \
	$(SRC_DIR)/init_data/init_data.c \
	$(SRC_DIR)/init_data/init_data_2.c \
	$(SRC_DIR)/init_data/fill_struct_funcs.c \
	$(SRC_DIR)/init_data/fill_struct_funcs_2.c \
	$(SRC_DIR)/init_data/create_data_structs.c \
	$(SRC_DIR)/parsing/check_funcs.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \
	$(SRC_DIR)/rays/rays.c \
	$(SRC_DIR)/rays/ray_utils.c \
	$(SRC_DIR)/rays/colors/mesh_color_effects.c \
	$(SRC_DIR)/rays/colors/color_effects.c \
	$(SRC_DIR)/rays/colors/get_sph_pl_bck_color.c \
	$(SRC_DIR)/rays/colors/get_cylinder_color.c \
	$(SRC_DIR)/rays/colors/get_cylinder_color_discs.c \
	$(SRC_DIR)/rays/colors/get_cylinder_color_utils.c \
	$(SRC_DIR)/rays/shadows/shadows.c \
	$(SRC_DIR)/xpm.c \
	$(SRC_DIR)/rays/shadows/shadows_exclusion.c \
	$(SRC_DIR)/rays/find_closest_intersection/find_closest_intersection.c \
	$(SRC_DIR)/rays/find_closest_intersection/is_intersect.c \
	$(SRC_DIR)/rays/find_closest_intersection/is_intersect_cylinder.c \
	$(SRC_DIR)/rays/find_closest_intersection/is_intersect_utils.c \
	$(SRC_DIR)/rays/exec_launch_ray.c \
	$(SRC_DIR)/linear_algebra/vector.c \
	$(SRC_DIR)/linear_algebra/color.c \
	$(SRC_DIR)/linear_algebra/color_utils.c \
	$(SRC_DIR)/linear_algebra/vector_utils.c \
	$(SRC_DIR)/linear_algebra/vector_utils_2.c \
	$(SRC_DIR)/event/events_keycode.c \
	$(SRC_DIR)/event/mouse_events.c \
	$(SRC_DIR)/event/event_reset.c \
	$(SRC_DIR)/event/key_event.c 
	
HEADERS = \
	$(HEADERS_DIR)/event/event_reset.h \
	$(HEADERS_DIR)/event/event.h \
	$(HEADERS_DIR)/event/events_keycode.h \
	$(HEADERS_DIR)/event/key_event.h \
	$(HEADERS_DIR)/event/mouse_events.h \
	$(HEADERS_DIR)/exit/data_store_shapes.h \
 	$(HEADERS_DIR)/exit/data_store.h \
 	$(HEADERS_DIR)/exit/exit.h \
	$(HEADERS_DIR)/init_data/create_data_structs.h \
	$(HEADERS_DIR)/init_data/fill_struct_funcs_2.h \
	$(HEADERS_DIR)/init_data/fill_struct_funcs.h \
	$(HEADERS_DIR)/init_data/init_data.h \
	$(HEADERS_DIR)/linear_algebra/color_utils.h \
	$(HEADERS_DIR)/linear_algebra/color.h \
	$(HEADERS_DIR)/linear_algebra/vector_utils_2.h \
	$(HEADERS_DIR)/linear_algebra/vector_utils.h \
	$(HEADERS_DIR)/linear_algebra/vector.h \
	$(HEADERS_DIR)/matrix/matrix_trsf.h \
	$(HEADERS_DIR)/matrix/matrix.h \
	$(HEADERS_DIR)/mesh/cam_trsf.h \
	$(HEADERS_DIR)/mesh/cam.h \
	$(HEADERS_DIR)/mesh/change_mesh_size.h \
	$(HEADERS_DIR)/mesh/mesh_trsf.h \
	$(HEADERS_DIR)/parsing/all_necessary_elements_are_present.h \
	$(HEADERS_DIR)/parsing/check_funcs.h \
	$(HEADERS_DIR)/parsing/elements_data_are_valid_utils.h \
	$(HEADERS_DIR)/parsing/elements_data_are_valid.h \
	$(HEADERS_DIR)/parsing/file_content_is_correct.h \
	$(HEADERS_DIR)/parsing/parse.h \
	$(HEADERS_DIR)/parsing/parsing_utils.h \
	$(HEADERS_DIR)/rays/colors/color_effects.h \
	$(HEADERS_DIR)/rays/colors/get_cylinder_color_discs.h \
	$(HEADERS_DIR)/rays/colors/get_cylinder_color_utils.h \
	$(HEADERS_DIR)/rays/colors/get_cylinder_color.h \
	$(HEADERS_DIR)/rays/colors/get_sph_pl_bck_color.h \
	$(HEADERS_DIR)/rays/colors/mesh_color_effects.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/find_closest_intersection.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/is_intersect_cylinder.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/is_intersect_utils.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/is_intersect.h \
	$(HEADERS_DIR)/rays/shadows/shadows_exclusion.h \
	$(HEADERS_DIR)/rays/shadows/shadows.h \
	$(HEADERS_DIR)/rays/exec_launch_ray.h \
	$(HEADERS_DIR)/rays/ray_utils.h \
	$(HEADERS_DIR)/rays/rays.h \
	$(HEADERS_DIR)/z_main/main.h \
	$(HEADERS_DIR)/z_main/se_camera.h \
	$(HEADERS_DIR)/z_main/se_color_image.h \
	$(HEADERS_DIR)/z_main/se_events.h \
	$(HEADERS_DIR)/z_main/se_exit.h \
	$(HEADERS_DIR)/z_main/se_funcs_params.h \
	$(HEADERS_DIR)/z_main/se_general.h \
	$(HEADERS_DIR)/z_main/se_geometry.h \
	$(HEADERS_DIR)/z_main/se_lighting.h \
	$(HEADERS_DIR)/z_main/se_mini_struct.h \
	$(HEADERS_DIR)/z_main/se_ray_vector.h \
	$(HEADERS_DIR)/z_main/x_color_effect.h \
	$(HEADERS_DIR)/z_main/x_linear_algebra.h \
	$(HEADERS_DIR)/z_main/x_matrix.h \
	$(HEADERS_DIR)/z_main/xpm.h

.PHONY: all mlx ft_printf clean fclean re intro l newline backline emoticon

TOG = 0

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(LIBFTPRINTF) $(HEADERS)
	@if [ $(TOG) -eq 0 ]; then \
		echo "\033[0;32m compiling...        🚀 "; \
	fi;	
	$(eval TOG=1)
	@$(CC) $(CFLAGS) $< -c -o $@

$(GNL_DIR)/%.o : $(GNL_DIR)/%.c $(LIBFTPRINTF) $(HEADERS)
# 	@echo "\033[0;32m compiling $(NAME) object $<...\033[0m" 🚀
	@$(CC) $(CFLAGS) $< -c -o $@

all: intro design mlx cursor_start ft_printf $(NAME) emoticon		

l:  design newline mlx ft_printf $(NAME)

$(NAME) : $(OBJECTS)
	@echo -n "\033[?25l"
	@$(MAKE) -s backline
	@echo "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b compiled            ✅\033[0m"	
	@sleep 1
	@echo "\033[0;36m linking...          🚀 "
	@sleep 1
	@$(MAKE) -s backline
	@$(CC) $(OBJECTS) $(LDFLAGS) $(LIBFTPRINTF) -o $@
	@echo "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b linked              ☑️\n\033[0m"
	@echo -n "\033[?25h"

mlx:
	@$(MAKE) -s -C $(MLX_DIR)

ft_printf: emoticon
#	@$(MAKE) -s -C $(LIBFT_DIR) bonus 
	@$(MAKE) -s -C $(FT_PRINTF_DIR) 

design:
	@echo "\033[0;32m"
	@cat mfile_design
	@echo "\033[0m"

cursor_end:
	@echo -n "\033[?25l"

cursor_start:
	@echo -n "\033[?25h"

emoticon:
	@echo "\n 🐇 🦄 🦄 🐇\n"

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
	@echo "\n"
	@words="\n\n\tFollow \n\t\tthe \t\b\b\033[0;96mColored! \
	\n\n\t\t\b\b\b\b\b\b\033[1;95mUnicorne!\033[0m...🦄\n\n"; \
	for j in $${words}; do \
		echo -n "$$j"; \
		sleep .4; \
	done
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