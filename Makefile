#1;bold 2;low intensity 4;Underline 5;Blink 8;invis 9;strike
count = 0
BLK	= \033[30m
RED	= \033[31m
GRN	= \033[32m
BRN	= \033[33m
BLU	= \033[34m
PUR	= \033[35m
CYN	= \033[36m
LGR	= \033[37m
RST	= \033[0m
NAME		:=	cub3D
UNAME_S 	:= $(shell uname -s)
#---------------Directories----------------------
SRC_D		:=	src/
BUILD_D		:=	.build/
LIB_D		:=	libft/ mlx-opengl/
INC			:=	inc/ libft/inc mlx-opengl/
#---------------Add .c / .h here \/--------------
SRC			:=	main.c			console.c		init.c		vector.c 	free.c\
				ray_caster.c	digital_differential_analyzer.c setup_texture.c\
				shortcut.c
DRAW		:=	draw_line.c		draw_pixel.c	draw_square.c	draw_ray.c\
				background.c
COLOR		:=	rgbo_color.c	color_utils.c	extract_single_color.c	line_gradient.c
PARSE		:=	parse.c 		parse_validity.c	parse_utils.c	parse_file.c
MOVEMENT	:=	player_move_and_rotate.c
HOOKS		:=	key_hooks.c loop.c physics.c move.c
MINIMAP		:=	minimap.c
UTILS		:=	rotate_vector.c	terminal_mini_map.c	erase_img.c
LIB			:=	ft	mlx
FRAMEWORK	:=	OpenGL	AppKit
#----------------------IGNORE--------------------
#------------------------------------------------
SRC			+=	$(PARSE:%=parse/%) $(COLOR:%=color/%) $(DRAW:%=draw/%) $(HOOKS:%=hooks/%) $(MOVEMENT:%=movement/%) $(UTILS:%=utils/%) $(MINIMAP:%=minimap/%)
SRC			:=	$(SRC:%=$(SRC_D)%)
OBJ 		:=	$(SRC:$(SRC_D)%.c=$(BUILD_D)%.o)
DEPS        :=	$(OBJ:.o=.d)
#------------------------------------------------
#----------------Linux libs \/-------------------
ifeq ($(UNAME_S),Linux)
LIB_D		:=	libft/ mlx-linux/
INC			:=	inc/ libft/inc /usr/include mlx-linux/
LIB			:=	ft mlx_Linux Xext X11 m z
FRAMEWORK	:=	
endif
#-------------------------------------------------
TOTAL_OBJ		:=	$(words $(OBJ))
NB_OBJ			:=	0
RM			:=	rm -rf
CC			:=	gcc
DIR_DUP     =	mkdir -p "$(@D)"
#-MMD -MP = Used to add dependencies during precomp. (for .h)
CPPFLAGS    :=	-MMD -MP $(addprefix -I,$(INC))
CFLAGS		:=	-Wextra -Werror -Wall -g3
# -(r)eplace the older objects, -(c)reate if no lib, -s index stuff
AR          :=	ar
ARFLAGS     :=	-r -c -s
LDFLAGS     :=	$(addprefix -L,$(dir $(LIB_D)))
LDLIBS      :=	$(addprefix -l,$(LIB))
LDFMWK		:=	$(addprefix -framework ,$(FRAMEWORK))
MAKEFLAGS   += --no-print-directory
#-----------------------------all------------------------------------
all		:	$(NAME)
#-----------------------------NAME-----------------------------------
$(NAME)	:	$(OBJ)
			TOTAL_OBJ=$(find .build -name "*.o")
			echo "currently $(TOTAL_OBJ) objects out of $(TOTAL_OBJ) are compiled"
			$(MAKE) complib
			${CC} $(LDFLAGS) $(OBJ) $(LDLIBS) $(LDFMWK) -o $(NAME)
			$(info MAKING $(NAME).....)
			echo "\033[5;32m\t\tFinished compiling $(NAME) !!! $(RST)"
#------------------------OBJ COMPILATION-----------------------------
$(BUILD_D)%.o	:	$(SRC_D)%.c
			$(DIR_DUP)
			$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
			$(eval count=$(shell echo $$(($(count)+1))))
			clear -x
			echo compiled $(@F) "\n" $(count)/$(TOTAL_OBJ) objects

-include	${DEPS}
#----------------------------COMPLIB---------------------------------
complib	:
	$(info COMPILING THE LIBS)
	@$(MAKE) -s -C libft
ifeq ($(UNAME_S),Linux)
	@$(MAKE) -s -C mlx-linux
endif
ifeq ($(UNAME_S),Darwin)
	@$(MAKE) -s -C mlx-opengl
endif
#----------------------------CLEAN-----------------------------------
clean	:
	$(RM) $(OBJ) $(DEPS)
	$(MAKE) -C libft clean
ifeq ($(UNAME_S),Darwin)
	$(MAKE) -C mlx-opengl clean
else
	$(MAKE) -C mlx-linux clean
endif
	echo "$(CYN) \t\tALL CLEANED $(RST)"
#----------------------------FCLEAN----------------------------------
fclean	:
	$(RM) $(OBJ) $(DEPS)
	$(RM) $(NAME)
	$(MAKE) -C libft fclean
ifeq ($(UNAME_S),Darwin)
#	$(MAKE) -C mlx-opengl fclean
else
#	$(MAKE) -C mlx-linux fclean
endif
	echo "\033[5;36m \t\tALL F*NG CLEANED !!! $(RST)"
#------------------------------RE------------------------------------
re		:	fclean all
			echo "\033[5;33m \t\tALL RECOMPILED !!! $(RST)"
test	:	all

.PHONY	:	all clean fclean re test
.SILENT :
