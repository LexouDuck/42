NAME	=	fdf

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -O3
LIBS	=	$(LIBFT) $(LIBMATH) $(LIBMLX_WIN)

LIBFT		=	-L$(LFTDIR) -lft
LIBMATH		=	-lm
XWIN_PATH	=	/usr/include/X11/
LMLX_PATH	=	/usr/lib/
LMLX_SUFFIX	=	
LIBMLX_MAC	=	-lmlx -framework OpenGL -framework AppKit
LIBMLX_WIN	=	-L$(LMLX_PATH) -I$(XWIN_PATH) -lmlx -lX11.dll -lXext.dll
LIBMLX_LIN	=	-L$(LMLX_PATH) -lmlx$(LMLX_SUFFIX) -L$(XWIN_PATH) -lX11 -lXext

SRCDIR	=	./src/
OBJDIR	=	./obj/
MLXDIR	=	../minilibx/
LFTDIR	=	./libft/

HDRS	=	fdf.h				\
			$(LFTDIR)libft.h
SRCS	= 	../../get_next_line.c  \
			space_fdf.c			\
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

$(NAME): $(OBJS)
	@make -C $(LFTDIR) all
	@printf "Compiling program: "$@" -> "
	@$(CC) $(OBJS) $(CFLAGS) -o $@ $(LIBS)
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@printf "Compiling file: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

all: $(NAME)

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

mlx:
	@make -C $(MLXDIR) all && sh ../mlx.sh
	@make fclean
	@make test

test: all
	@printf "Testing $(NAME):\n"
	startxwin ./fdf tests/42.fdf
