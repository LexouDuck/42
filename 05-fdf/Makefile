NAME	=	fdf

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -O3

LIBS	=	$(LIBFT) $(LIBX_WIN)
LIBFT	=	-L$(LFTDIR) -lft
LIBX_MAC	=	-lm -lmlx -framework OpenGL -framework AppKit
LIBX_WIN	=	-lm -L/usr/lib/ -I/usr/include/X11/ -lmlx -lX11.dll -lXext.dll

SRCDIR	=	./src/
OBJDIR	=	./obj/
MLXDIR	=	../minilibx/
LFTDIR	=	./libft/
TSTDIR	=	./tests/

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

HDRS	=	fdf.h				\
			$(LFTDIR)libft.h
SRCS	= 	main.c				\
			read.c				\
			space_fdf.c			\
			space_add.c			\
			space_get.c			\
			event.c				\
			color.c				\
			vector.c			\
			vector_op.c			\
			matrix.c			\
			window.c			\
			projection.c		\
			camera.c			\
			render.c			\
			draw_line.c			\
			draw_rectangle.c	\
			../get_next_line.c

OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}

$(OBJDIR)%.o : $(SRCDIR)%.c
	@printf "Compiling file: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(NAME): $(OBJS)
	@make -C $(LFTDIR) all
	@printf "Compiling program: "$@" -> "
	@$(CC) $^ $(CFLAGS) -o $@ $(LIBS)
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

test: all
	@printf "Testing $(NAME):\n"
	startxwin ./fdf $(TSTDIR)42.fdf

mlx:
	@make -C $(MLXDIR) all && sh ../mlx.sh
	@make fclean
	@make test
