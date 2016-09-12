# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sduprey <sduprey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/17 05:35:05 by sduprey           #+#    #+#              #
#    Updated: 2016/09/12 17:39:14 by sduprey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC =	main.c \
		camera.c \
		cylinder.c \
		draw_scene.c \
		find_closest_object.c \
		get_file_content.c \
		get_objects.c \
		get_scene.c \
		get_val.c \
		light.c \
		node.c \
		part.c \
		parse.c \
		parse_scop.c \
		parse_tools.c \
		parse_tools_is.c \
		plane.c \
		refraction.c \
		scene.c \
		sphere.c \
		vector.c \
		vector_math.c \
		vector_math2.c \
		cone.c \
		color.c \
		perlin.c \
		checker.c \
		elipsoid.c \
		triangle.c \
		parallelo.c \
		write_scene.c \
		image_buffer.c \
		save_bmp.c \

SRCDIR = src/

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

CC = clang

INC = -I ./inc -I libft

LIB = -L libft -lft

RM = rm -rf

C_FLAGS= -Wall -Werror -Wextra -o3 `pkg-config --cflags gtk+-3.0` -fsanitize=address

MLX_FLAGS = `pkg-config --libs gtk+-3.0` -fsanitize=address

all: lft $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) $(MLX_FLAGS) -o $(NAME) $(LIB) $^
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
