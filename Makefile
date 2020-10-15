
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/15 01:02:41 by mbrunel           #+#    #+#              #
#    Updated: 2020/10/15 20:29:51 by mbrunel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=miniRTA2

BUILD=.build
D_SRC=src
D_INC=inc
D_LIB=lib
D_OBJ=$(BUILD)/obj
D_DEP=$(BUILD)/dep
D_SUB=
DIRS:=$(D_DEP) $(addprefix $(D_DEP)/, $(D_SUB))\
	$(D_OBJ) $(addprefix $(D_OBJ)/, $(D_SUB))

D_LIBFT=$(D_LIB)/libft
LIBFT=$(D_LIBFT)/libft.a

D_NOT_MLX=$(D_LIB)/NOT_MLX
NOT_MLX=$(D_NOT_MLX)/libnmlx.a

MK_LIB=$(NOT_MLX) $(LIBFT)

CC=clang
CFLAGS=-Wall -Wextra -Ofast #-Werror
DFLAGS=-MP -MMD -MF $(D_DEP)/$*.d -MT $@
IFLAGS=-I$(D_INC) -I$(D_LIBFT) -I$(D_NOT_MLX)/$(D_INC) `sdl2-config --cflags`
CPPFLAGS=$(CFLAGS) $(IFLAGS) $(DFLAGS)
LDFLAGS= `sdl2-config --libs` $(LIBFT) $(NOT_MLX)

C_RED=\033[31m
C_GREEN=\033[32m
C_CYAN=\033[36m
C_NONE=\033[0m
BUILD_MSG=$(C_GREEN)✔$(C_NONE)
REMOVE_MSG=$(C_RED)𐄂$(C_NONE)

INC=$(D_INC)/minishell.h

SRC=aliasing_threading_bonus.c\
	antialiasing.c\
	binds1.c\
	binds2.c\
	bmp.c\
	chng.c\
	colors_utils.c\
	colors_utils2.c\
	core_funcs.c\
	fill_it_bonus.c\
	intercy.c\
	interpl.c\
	intersp.c\
	intersq.c\
	intertr.c\
	main.c\
	parse_gets1.c\
	parse_gets2.c\
	parse_gets3.c\
	parse_utils.c\
	parser.c\
	raytracing_utils.c\
	stereo.c\
	stretch.c\
	utils_bonus.c\
	vec_utils1.c\
	vec_utils2.c\
	vec_utils3.c\
	vec_utils4.c

OBJ:=$(patsubst %.c, $(D_OBJ)/%.o, $(SRC))
DEP:=$(patsubst %.c, $(D_DEP)/%.d, $(SRC))

all :
	@$(MAKE) -sj $(NAME)

$(NAME) : $(MK_LIB) $(OBJ)
	@$(CC) $(LDFLAGS) $(OBJ) -o $@
	@printf "$(BUILD_MSG) %s\n" $@

clean :
	@rm -rf $(BUILD)
	@printf "$(REMOVE_MSG) rm %s\n" $(BUILD)

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(D_LIBFT) fclean
	@$(MAKE) -C $(D_NOT_MLX) fclean
	@printf "$(REMOVE_MSG) rm %s\n" $(NAME) $(LIBFT) $(NOT_MLX)

re : fclean all

$(BUILD) :
	@mkdir -p $@ $(DIRS)
	@printf "$(BUILD_MSG) %s\n" $@

$(MK_LIB) :
	@git submodule init
	@git submodule update --remote
	@$(MAKE) -C $(D_LIBFT)
	@$(MAKE) -C $(D_NOT_MLX)

-include $(DEP)

$(D_OBJ)/%.o : $(D_SRC)/%.c | $(BUILD)
	@$(CC) $(CPPFLAGS) -c $< -o $@
	@printf "$(BUILD_MSG) %s\n" $<

.PHONY: all clean fclean re test
