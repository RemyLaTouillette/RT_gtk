# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sduprey <sduprey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/17 05:35:05 by sduprey           #+#    #+#              #
#    Updated: 2016/10/03 19:16:01 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC =	main.c \
		aa.c \
		blur.c \
		camera.c \
		cylinder.c \
		cylinder2.c \
		cone.c \
		cone2.c \
		depth_of_field.c \
		tetra.c \
		tetra2.c \
		cyco_common_function.c \
		draw_scene.c \
		color_render.c \
		find_closest_object.c \
		find_closest_neg_object.c \
		get_cam.c \
		get_cylinder.c \
		get_cone.c \
		get_elips.c \
		get_invalid.c \
		get_sphere.c \
		get_para.c \
		get_plane.c \
		get_file_content.c \
		get_light.c \
		get_objects.c \
		get_tetra.c \
		get_triangle.c \
		get_scene.c \
		get_val.c \
		init_objects1.c \
		init_objects2.c \
		light.c \
		light_tool1.c \
		light_tool2.c \
		node.c \
		part.c \
		parse.c \
		parse_get.c \
		parse_get2.c \
		parse_scop.c \
		parse_tools.c \
		parse_tools_is.c \
		plane.c \
		refraction.c \
		scene.c \
		sphere.c \
		sepia.c \
		vector.c \
		vector_math.c \
		vector_math2.c \
		math.c \
		color.c \
		marble.c \
		checker.c \
		elipsoid.c \
		triangle.c \
		parallelo.c \
		image_buffer.c \
		save_bmp.c \
		save_jpeg.c \
		scene_finder.c \
		ui_init.c \
		ui_get_values.c \
		ui_get_values2.c \
		ui_set_values.c \
		ui_get_values_from_scene.c \
		cartoon.c \
		scene_cmp.c \
		objects_cmp.c \
		objects_cmp2.c \
		objects_cmp3.c \
		tools_cmp.c \
		lights_cmp.c \
		error_handler.c \
		event_handler.c \
		event_handler2.c \
		get_texture.c \
		texture_mapping.c \
		event_draw.c \
		post_processing_effects.c \

SRCDIR = src/

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

CC = clang

INC = -I ./inc -I libft

LIB = -L libft -lft

RM = rm -rf

FS = -fsanitize=address

C_FLAGS= -Wall -Werror -Wextra -o3 `pkg-config --cflags gtk+-3.0`

GTK_FLAGS = `pkg-config --libs gtk+-3.0`

all: lft $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) $(GTK_FLAGS) -o $(NAME) $(LIB) $^
	@echo ""
	@echo $(PX_STR) : $(EX_STR)
	@echo ""

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c $(C_FLAGS) $(INC) $< -o $@ 
	@echo $(CC_STR) $*

lft:
	@make -C libft

clean:
	@$(RM) $(OBJDIR)
	@echo $(RM_STR) objects

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)
	@echo $(RM_STR) $(NAME)

re: fclean all

NO_COLOR = "\033[0;0m"
CC_COLOR = "\033[0;33m"
EX_COLOR = "\033[0;32m"
PX_COLOR = "\033[4;37m"
RM_COLOR = "\033[0;31m"

CC_STR = $(CC_COLOR)[CC]$(NO_COLOR)
EX_STR = $(EX_COLOR)$(NAME)$(NO_COLOR)
PX_STR = $(PX_COLOR)Binary compiled successfully$(NO_COLOR)
RM_STR = $(RM_COLOR)Remove$(NO_COLOR)
