# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 03:24:21 by mbrunel           #+#    #+#              #
#    Updated: 2020/03/02 01:17:32 by mbrunel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_DIR = libs
INC_DIR = incs
SRC_DIR = srcs
OBJ_DIR = objs

CC =		gcc
CFLAGS =	-Wall -Wextra -I$(NOT_MLX_DIR)/incs -I/
OFLAGS =	$(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT) $(MLX)
NAME =		miniRT

GIT=$(NOT_MLX)/.git

SRCS = 		main.c \
			vec_utils1.c \
			vec_utils2.c \
			vec_utils3.c \
			vec_utils4.c \
			colors_utils.c \
			colors_utils2.c \
			parser.c \
			parse_gets1.c \
			parse_utils.c \
			intersq.c \
			intertr.c \
			interpl.c \
			intersp.c \
			intercy.c \
			fill_it.c \
			chng.c\
			bmp.c \
			parse_gets2.c\
			stretch.c\
			parse_gets3.c \
			stereo.c\
			binds1.c\
			binds2.c\
			core_funcs.c\
			raytracing_utils.c\
			antialiasing.c

OBJS =		$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
MLX_DIR = mlx
LIBFT_DIR = libft
MLX = libmlx.dylib
LIBFT = libft.a

all :	${NAME} $(GIT)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIB_DIR)/$(MLX_DIR)
			$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
			cp $(LIB_DIR)/$(MLX_DIR)/$(MLX)  .
			$(CC) $(OFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/* Makefile
			mkdir -p $(OBJ_DIR)/
			$(CC) $(CFLAGS) -c $< -o $@

$(GIT) :
	git submodule init
	git submodule update --remote

clean :
			rm -rf $(OBJS) $(LIB_DIR)/$(LIBFT_DIR)/*/*.o $(LIB_DIR)/$(MLX_DIR)/*.o $(OBJS_BONUS)

fclean : clean
			rm -rf $(NAME) $(LIB_DIR)/$(MLX_DIR)/$(MLX) $(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT) $(LIB_DIR)/$(LIBFT_DIR)/libc/libc.a $(MLX)

re :	fclean all

SRCS_BONUS =main.c \
			vec_utils1.c \
			vec_utils2.c \
			vec_utils3.c \
			vec_utils4.c \
			colors_utils.c \
			colors_utils2.c \
			parser.c \
			parse_gets1.c \
			parse_utils.c \
			intersq.c \
			intertr.c \
			interpl.c \
			intersp.c \
			intercy.c \
			fill_it_bonus.c \
			aliasing_threading_bonus.c \
			chng.c\
			bmp.c \
			parse_gets2.c\
			stretch.c\
			parse_gets3.c \
			stereo.c\
			binds1.c\
			binds2.c\
			core_funcs.c\
			raytracing_utils.c\
			utils_bonus.c

OBJS_BONUS =$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS_BONUS))

bonus :		$(OBJS_BONUS) $(GIT)
			rm -rf $(OBJ_DIR)/fill_it.o
			$(MAKE) -C $(LIB_DIR)/$(MLX_DIR)
			$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
			cp $(LIB_DIR)/$(MLX_DIR)/$(MLX)  .
			$(CC) $(OFLAGS) $(OBJS_BONUS) -o $(NAME)

LIB_NOT_MLX_NAME = libnmlx.a
NOT_MLX_DIR = NOT_MLX
LIB_NOT_MLX = $(NOT_MLX_DIR)/$(LIB_NOT_MLX_NAME)
SDL_DIR = $(NOT_MLX_DIR)/$(LIB_DIR)/SDL2-2.0.10
SDL2_FLAGS = `$(SDL_DIR)/sdl2-config --cflags --libs`
LINUX_FLAGS = $(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT) $(LIB_NOT_MLX) -lm $(SDL2_FLAGS) -lpthread

portable :	$(OBJS_BONUS) $(GIT)
			rm -rf $(OBJ_DIR)/fill_it.o
			$(MAKE) -C $(NOT_MLX_DIR)
			$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
			$(CC) $(OBJS_BONUS) $(LINUX_FLAGS) -o $(NAME)

fullfclean : fclean
			$(MAKE) -C $(NOT_MLX_DIR) fullfclean

