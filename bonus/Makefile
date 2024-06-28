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

GNL_DIR = ../gnl
FT_PRINTF_DIR = ../ft_printf
LIBFTPRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT_DIR = $(FT_PRINTF_DIR)/libft
SRC_DIR = sources
HEADERS_DIR = include
MLX_DIR = ../.mlx_linux	

NAME = ../miniRT_bonus
CC = cc

OBJECTS = $(SOURCES:.c=.o)
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz -pthread

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
	-pthread \
	-Wall -Wextra -Werror \
	# -g

SOURCES = \
	$(SRC_DIR)/.meta/create_video_image_bonus.c \
	$(SRC_DIR)/.meta/scening_bonus.c \
	$(SRC_DIR)/.meta/save_image_reference_bonus.c \
	$(SRC_DIR)/.meta/test_prints_bonus.c \
	$(SRC_DIR)/.meta/meta_keycode_bonus.c \
	$(SRC_DIR)/.meta/transform_video_scene_bonus.c \
	$(SRC_DIR)/.meta/meta_utils_bonus.c \
	$(SRC_DIR)/.meta/newton.c \
	$(SRC_DIR)/main_bonus.c \
	$(SRC_DIR)/mesh/cam_bonus.c \
	$(SRC_DIR)/mesh/cam_trsf_bonus.c \
	$(SRC_DIR)/mesh/mesh_trsf_bonus.c \
	$(SRC_DIR)/mesh/change_mesh_size_bonus.c \
	$(SRC_DIR)/event/event_bonus.c \
	$(SRC_DIR)/event/event_light_bonus.c \
	$(SRC_DIR)/parsing/parsing_utils_bonus.c \
	$(SRC_DIR)/exit/exit_bonus.c \
	$(SRC_DIR)/exit/data_store_bonus.c \
	$(SRC_DIR)/exit/data_store_shapes_bonus.c \
	$(SRC_DIR)/matrix/matrix_bonus.c \
	$(SRC_DIR)/matrix/matrix_trsf_bonus.c \
	$(SRC_DIR)/parsing/parse_bonus.c \
	$(SRC_DIR)/parsing/file_content_is_correct_bonus.c \
	$(SRC_DIR)/parsing/all_necessary_elements_are_present_bonus.c \
	$(SRC_DIR)/parsing/elements_data_are_valid_bonus.c \
	$(SRC_DIR)/parsing/elements_data_are_valid_utils_bonus.c \
	$(SRC_DIR)/init_data/init_data_bonus.c \
	$(SRC_DIR)/init_data/init_data_2_bonus.c \
	$(SRC_DIR)/init_data/fill_struct_funcs_bonus.c \
	$(SRC_DIR)/init_data/fill_struct_funcs_2_bonus.c \
	$(SRC_DIR)/init_data/create_data_structs_bonus.c \
	$(SRC_DIR)/init_data/xpm_bonus.c \
	$(SRC_DIR)/init_data/get_texture_bonus.c \
	$(SRC_DIR)/init_data/get_texture_utils_bonus.c \
	$(SRC_DIR)/parsing/check_funcs_bonus.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \
	$(SRC_DIR)/rays/multy_thrd_bonus.c \
	$(SRC_DIR)/rays/rays_bonus.c \
	$(SRC_DIR)/rays/ray_utils_bonus.c \
	$(SRC_DIR)/rays/compute_rays_bonus.c \
	$(SRC_DIR)/rays/colors/mesh_color_effects_bonus.c \
	$(SRC_DIR)/rays/colors/color_effects_bonus.c \
	$(SRC_DIR)/rays/colors/color_effects_utils_bonus.c \
	$(SRC_DIR)/rays/colors/get_sphere_color_bonus.c \
	$(SRC_DIR)/rays/colors/get_plane_color_bonus.c \
	$(SRC_DIR)/rays/colors/get_cylinder_color_bonus.c \
	$(SRC_DIR)/rays/colors/get_cylinder_color_discs_bonus.c \
	$(SRC_DIR)/rays/colors/get_cylinder_color_utils_bonus.c \
	$(SRC_DIR)/rays/colors/color_disruption_bonus.c \
	$(SRC_DIR)/rays/colors/color_disruption_utils_bonus.c \
	$(SRC_DIR)/rays/colors/bump_mapping_bonus.c \
	$(SRC_DIR)/rays/colors/get_triangle_color_bonus.c \
	$(SRC_DIR)/rays/shadows/shadows_bonus.c \
	$(SRC_DIR)/rays/shadows/shadows_exclusion_bonus.c \
	$(SRC_DIR)/rays/find_closest_intersection/find_closest_intersection_bonus.c \
	$(SRC_DIR)/rays/find_closest_intersection/is_intersect_bonus.c \
	$(SRC_DIR)/rays/find_closest_intersection/is_intersect_cylinder_bonus.c \
	$(SRC_DIR)/rays/find_closest_intersection/is_intersect_utils_bonus.c \
	$(SRC_DIR)/rays/exec_launch_ray_bonus.c \
	$(SRC_DIR)/linear_algebra/clamping_bonus.c \
	$(SRC_DIR)/linear_algebra/vector_bonus.c \
	$(SRC_DIR)/linear_algebra/color_bonus.c \
	$(SRC_DIR)/linear_algebra/color_utils_bonus.c \
	$(SRC_DIR)/linear_algebra/vector_utils_bonus.c \
	$(SRC_DIR)/linear_algebra/vector_utils_2_bonus.c \
	$(SRC_DIR)/event/events_keycode_bonus.c \
	$(SRC_DIR)/event/mouse_events_bonus.c \
	$(SRC_DIR)/event/event_reset_bonus.c \
	$(SRC_DIR)/event/key_event_bonus.c
	
HEADERS = \
	$(HEADERS_DIR)/event/event_reset_bonus.h \
	$(HEADERS_DIR)/event/event_bonus.h \
	$(HEADERS_DIR)/event/event_light_bonus.h \
	$(HEADERS_DIR)/event/events_keycode_bonus.h \
	$(HEADERS_DIR)/event/key_event_bonus.h \
	$(HEADERS_DIR)/event/mouse_events_bonus.h \
	$(HEADERS_DIR)/exit/data_store_shapes_bonus.h \
 	$(HEADERS_DIR)/exit/data_store_bonus.h \
 	$(HEADERS_DIR)/exit/exit_bonus.h \
	$(HEADERS_DIR)/init_data/create_data_structs_bonus.h \
	$(HEADERS_DIR)/init_data/fill_struct_funcs_2_bonus.h \
	$(HEADERS_DIR)/init_data/fill_struct_funcs_bonus.h \
	$(HEADERS_DIR)/init_data/init_data_bonus.h \
	$(HEADERS_DIR)/init_data/xpm_bonus.h \
	$(HEADERS_DIR)/linear_algebra/clamping_bonus.h \
	$(HEADERS_DIR)/linear_algebra/color_utils_bonus.h \
	$(HEADERS_DIR)/linear_algebra/color_bonus.h \
	$(HEADERS_DIR)/linear_algebra/vector_utils_2_bonus.h \
	$(HEADERS_DIR)/linear_algebra/vector_utils_bonus.h \
	$(HEADERS_DIR)/linear_algebra/vector_bonus.h \
	$(HEADERS_DIR)/matrix/matrix_trsf_bonus.h \
	$(HEADERS_DIR)/matrix/matrix_bonus.h \
	$(HEADERS_DIR)/mesh/cam_trsf_bonus.h \
	$(HEADERS_DIR)/mesh/cam_bonus.h \
	$(HEADERS_DIR)/mesh/change_mesh_size_bonus.h \
	$(HEADERS_DIR)/mesh/mesh_trsf_bonus.h \
	$(HEADERS_DIR)/parsing/all_necessary_elements_are_present_bonus.h \
	$(HEADERS_DIR)/parsing/check_funcs_bonus.h \
	$(HEADERS_DIR)/parsing/elements_data_are_valid_utils_bonus.h \
	$(HEADERS_DIR)/parsing/elements_data_are_valid_bonus.h \
	$(HEADERS_DIR)/parsing/file_content_is_correct_bonus.h \
	$(HEADERS_DIR)/parsing/parse_bonus.h \
	$(HEADERS_DIR)/parsing/parsing_utils_bonus.h \
	$(HEADERS_DIR)/rays/colors/color_effects_bonus.h \
	$(HEADERS_DIR)/rays/colors/color_effects_utils_bonus.h \
	$(HEADERS_DIR)/rays/colors/get_cylinder_color_discs_bonus.h \
	$(HEADERS_DIR)/rays/colors/get_cylinder_color_utils_bonus.h \
	$(HEADERS_DIR)/rays/colors/get_cylinder_color_bonus.h \
	$(HEADERS_DIR)/rays/colors/get_sphere_color_bonus.h \
	$(HEADERS_DIR)/rays/colors/get_plane_color_bonus.h \
	$(HEADERS_DIR)/rays/colors/get_triangle_color_bonus.h \
	$(HEADERS_DIR)/rays/colors/mesh_color_effects_bonus.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/find_closest_intersection_bonus.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/is_intersect_cylinder_bonus.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/is_intersect_utils_bonus.h \
	$(HEADERS_DIR)/rays/find_closest_intersection/is_intersect_bonus.h \
	$(HEADERS_DIR)/rays/shadows/shadows_exclusion_bonus.h \
	$(HEADERS_DIR)/rays/shadows/shadows_bonus.h \
	$(HEADERS_DIR)/rays/exec_launch_ray_bonus.h \
	$(HEADERS_DIR)/rays/compute_rays_bonus.h \
	$(HEADERS_DIR)/rays/ray_utils_bonus.h \
	$(HEADERS_DIR)/rays/multy_thrd_bonus.h \
	$(HEADERS_DIR)/rays/rays_bonus.h \
	$(HEADERS_DIR)/z_main/main_bonus.h \
	$(HEADERS_DIR)/z_main/se_camera_bonus.h \
	$(HEADERS_DIR)/z_main/se_color_image_bonus.h \
	$(HEADERS_DIR)/z_main/se_events_bonus.h \
	$(HEADERS_DIR)/z_main/se_exit_bonus.h \
	$(HEADERS_DIR)/z_main/se_funcs_params_bonus.h \
	$(HEADERS_DIR)/z_main/se_general_bonus.h \
	$(HEADERS_DIR)/z_main/se_geometry_bonus.h \
	$(HEADERS_DIR)/z_main/se_lighting_bonus.h \
	$(HEADERS_DIR)/z_main/se_mini_struct_bonus.h \
	$(HEADERS_DIR)/z_main/se_ray_vector_bonus.h \
	$(HEADERS_DIR)/z_main/x_color_effect_bonus.h \
	$(HEADERS_DIR)/z_main/x_linear_algebra_bonus.h \
	$(HEADERS_DIR)/z_main/x_matrix_bonus.h \
	
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

all:  design newline mlx ft_printf $(NAME) 

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
	@rm -f $(OBJECTS);
	@$(MAKE) -C $(FT_PRINTF_DIR) clean -s
	@echo ""
	@$(MAKE) -C $(MLX_DIR) clean -s
	@echo ""

fclean: 
	@echo "\n cleanning $(NAME) objects 🧻"
	@rm -f $(OBJECTS);
	@echo " cleanning $(NAME) 🚽" 
	@rm -f $(NAME) 
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean -s
	@echo ""
	@$(MAKE) -C $(MLX_DIR) clean -s
	@echo ""

re: fclean backline all