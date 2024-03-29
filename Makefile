# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmacgyve <fmacgyve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/08 17:22:13 by fmacgyve          #+#    #+#              #
#    Updated: 2019/02/15 20:42:02 by fmacgyve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = fractol
FLAGS       = -Wall -Wextra -Werror
SRC_DIR		= ./srcs
OBJ_DIR		= ./obj
CFILES		= main.c fractol_struct.c image.c hooks.c fractals.c calculate_zone.c threads.c calculate_utils.c color.c
OFILES		= $(CFILES:.c=.o)
RAW_CFILES	= $(addprefix $(SRC_DIR)/,$(CFILES))
RAW_OFILES	= $(addprefix $(OBJ_DIR)/,$(OFILES))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(RAW_OFILES)
		make -C ./minilibx_macos
		make -C ./libft
		gcc $(RAW_OFILES) $(FLAGS) libft/libft.a minilibx_macos/libmlx.a -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit -I ./includes -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		gcc $(FLAGS) -I ./includes -c $< -o $@
clean:
		make clean -C ./minilibx_macos
		make clean -C ./libft
		rm -f $(RAW_OFILES)

fclean: clean
		make clean -C ./minilibx_macos
		make fclean -C ./libft
		rm -rf $(NAME)

re: fclean all
