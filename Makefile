# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 03:24:21 by mbrunel           #+#    #+#              #
#    Updated: 2020/02/06 08:18:54 by yvanat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_DIR = libs
INC_DIR = incs
SRC_DIR = srcs
OBJ_DIR = objs

CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
OFLAGS =	$(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT) $(MLX)
NAME =		miniRT

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

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIB_DIR)/$(MLX_DIR)
			$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
			cp $(LIB_DIR)/$(MLX_DIR)/$(MLX)  .
			$(CC) $(OFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/* Makefile
			mkdir -p $(OBJ_DIR)/
			$(CC) $(CFLAGS) -c $< -o $@


all :	${NAME}

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

bonus :		$(OBJS_BONUS)
			rm -rf $(OBJ_DIR)/fill_it.o
			$(MAKE) -C $(LIB_DIR)/$(MLX_DIR)
			$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
			cp $(LIB_DIR)/$(MLX_DIR)/$(MLX)  .
			$(CC) $(OFLAGS) $(OBJS_BONUS) -o $(NAME)

