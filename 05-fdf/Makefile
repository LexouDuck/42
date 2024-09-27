NAME	=	fdf

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

OSFLAG := 
ifeq ($(OS),Windows_NT)
	OSFLAG := WIN
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG := LIN
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG := MAC
	endif
endif
ifeq ($(OSFLAG),)
_:=$(error "Could not estimate the current target platform")
endif

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -O3 $(INCLUDE)

INCLUDE	=	-I$(LMLX_PATH)

LIBS	=	$(LIBFT) $(LIBMLX_$(OSFLAG)) $(LIBMATH)

LIBFT		=	-L$(LFTDIR) -lft
LIBMATH		=	-lm
LMLX_PATH	=	../minilibx/
XWIN_PATH	=	/usr/include/X11/
LIBMLX_MAC	=	-lmlx -framework OpenGL -framework AppKit
LIBMLX_WIN	=	-L$(LMLX_PATH) -lmlx -L$(XWIN_PATH) -lX11.dll -lXext.dll
LIBMLX_LIN	=	-L$(LMLX_PATH) -lmlx -L$(XWIN_PATH) -lX11     -lXext

SRCDIR	=	./src/
OBJDIR	=	./obj/
LFTDIR	=	./libft/

HDRS	=	fdf.h				\
			$(LFTDIR)libft.h
SRCS	= 	space_fdf.c			\
			space_add.c			\
			space_get.c			\
			draw_line.c			\
			draw_rectangle.c	\
			color.c				\
			vector.c			\
			vector_op.c			\
			matrix.c			\
			projection.c		\
			window.c			\
			camera.c			\
			render.c			\
			event.c				\
			read.c				\
			main.c

OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}

all: libraries $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling program: "$@" -> "
	@$(CC) $(OBJS) $(CFLAGS) -o $@ $(LIBS)
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

libraries:
	@make -C $(LFTDIR) all

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

test: all
	@printf "Testing $(NAME):\n"
	startxwin ./fdf tests/42.fdf
