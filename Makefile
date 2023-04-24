# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 20:15:08 by amorel            #+#    #+#              #
#    Updated: 2022/12/12 14:52:13 by johrober         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#*****************************	MANDATORY PART	********************************
SRCS	= $(addprefix srcs/, main.c)
SRCS	+= $(addprefix srcs/raycasting/, raycasting.c raycasting_utils.c raycasting_lighting.c)
SRCS	+= $(addprefix srcs/parsing/, get_scene.c parsing_utils.c check.c check_shapes.c check_params.c)
SRCS	+= $(addprefix srcs/rendering/, refresh_screen.c window_management.c render_scene.c draw_management.c)
SRCS	+= $(addprefix srcs/intersection/, hit_sphere.c hit_cylinder.c hit_plane.c)
SRCS	+= $(addprefix srcs/utils/, misc_utils.c geo_algebra_utils.c vector_allocation_utils.c \
	vector_basics_utils.c quaternion_utils.c vector_operation_utils.c)
SRCS	+= $(addprefix srcs/struct/, tamblight.c tcamera.c tcylinder.c tlight.c tplane.c tsphere.c tprogram.c)
SRCS	+= $(addprefix srcs/gui/, blit_shapes.c ft_ftoa.c gui_hooks.c gui.c gui_init.c gui_print.c change_sphere.c change_plane.c change_cylinder.c print_utils.c print_utils_2.c blit.c change_amb.c change_light.c)

#*****************************	BONUS PART	***********************************
BSRCS	= $(addprefix bonus/, main_bonus.c)
BSRCS	+= $(addprefix bonus/bumpmap/, bumpmap_apply_bonus.c bumpmap_init_bonus.c bumpmap_utils_bonus.c sort_bumpmaps_bonus.c)
BSRCS	+= $(addprefix bonus/gui/, blit_bonus.c change_cylinder_bonus.c change_sphere_bonus.c gui_init_bonus.c gui_print_shapes_bonus.c \
	blit_shapes_bonus.c change_light_bonus.c gui_bonus.c gui_init_utils_bonus.c print_utils_2_bonus.c ft_ftoa_bonus.c \
	change_amb_bonus.c change_plane_bonus.c gui_hooks_bonus.c gui_hooks_shapes_bonus.c gui_print_bonus.c print_utils_bonus.c change_cone_bonus.c)
BSRCS	+= $(addprefix bonus/rendering/, window_management_bonus.c render_scene_bonus.c draw_management_bonus.c refresh_screen_bonus.c)
BSRCS	+= $(addprefix bonus/raycasting/, raycasting_bonus.c raycasting_utils_bonus.c raycasting_lighting_bonus.c) 
BSRCS	+= $(addprefix bonus/parsing/, get_scene_bonus.c check_bonus.c check_params_bonus.c check_angle_bonus.c check_shapes_bonus.c parsing_utils_bonus.c)
BSRCS	+= $(addprefix bonus/intersection/, hit_plane_bonus.c hit_sphere_bonus.c hit_cylinder_bonus.c hit_cone_bonus.c hit_cone_utils_bonus.c) 
BSRCS	+= $(addprefix bonus/mapping/, cone_mapping_bonus.c cone_mapping_utils_bonus.c sphere_mapping_bonus.c plane_mapping_bonus.c cylinder_mapping_bonus.c cylinder_mapping_utils_bonus.c) 
BSRCS	+= $(addprefix bonus/struct/, tamblight_bonus.c tcamera_bonus.c tcone_bonus.c tcylinder_bonus.c tlight_bonus.c tplane_bonus.c tsphere_bonus.c tprogram_bonus.c)
BSRCS	+= $(addprefix bonus/texture/, texture_apply_bonus.c texture_init_bonus.c sort_textures_bonus.c)
BSRCS	+= $(addprefix bonus/utils/, vector_operation_utils_bonus.c misc_utils_bonus.c vector_basics_utils_bonus.c vector_allocation_utils_bonus.c\
	geo_algebra_utils_bonus.c quaternion_utils_bonus.c increment_and_print.c)
OBJS	= $(SRCS:%.c=%.o)
BOBJS	= $(BSRCS:%.c=%.o)
CFLAGS	= -Wextra -Wall -Werror -g3 -Iincludes -O0
CC		= clang
NAME	= miniRT
BNAME	= miniRT_bonus
LIBFT_FLAGS = -Lincludes/libft -lft -Iincludes/libft
MLX_FLAGS = -Lincludes/mlx -lmlx -L/usr/lib -Iincludes/mlx -lXext -lX11 -lm -lz

all: $(NAME)
%.o	:	%.c
	$(CC) $(CFLAGS) -I/usr/include -Iincludes/mlx -Iincludes/libft -c $< -o $@
$(NAME): $(OBJS)
	make -C includes/libft
	make -C includes/mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
bonus: $(BNAME)
$(BNAME): $(BOBJS)
	make -C includes/libft
	make -C includes/mlx
	$(CC) $(CFLAGS) $(BOBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(BNAME)
re: clean all
clean:
	make -C includes/libft clean
	make -C includes/mlx clean
	rm -f $(OBJS)
	rm -f $(BOBJS)
fclean: clean
	make -C includes/libft fclean
	make -C includes/mlx clean
	rm -f $(NAME)
	rm -f $(BNAME)
mtags:
	rm -f tags
	ctags srcs/* srcs/**/** includes/libft/* includes/libft/**/**
btags:
	rm -f tags
	ctags bonus/* bonus/**/** includes/libft/* includes/libft/**/**
.PHONY: all clean fclean re bonus
