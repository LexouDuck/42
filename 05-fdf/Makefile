NAME	=	fdf

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -O3

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

LIBS	=	$(LIBFT) $(LIBMATH) $(LIBMLX_WIN)

LIBFT		=	-L$(LFTDIR) -lft
LIBMATH		=	-lm
LMLX_PATH	=	/usr/lib/
LMLX_SUFFIX	=	
XWIN_PATH	=	/usr/include/X11/
LIBMLX_MAC	=	-lmlx -framework OpenGL -framework AppKit
LIBMLX_WIN	=	-L$(LMLX_PATH) -I$(XWIN_PATH) -lmlx -lX11.dll -lXext.dll
LIBMLX_LIN	=	-L$(LMLX_PATH) -lmlx$(LMLX_SUFFIX) -L$(XWIN_PATH) -lX11 -lXext

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
	@echo -n "Compiling program: "$@" -> "
	@$(CC) $(OBJS) $(CFLAGS) -o $@ $(LIBS)
	@echo -e $(GREEN)"OK!"$(RESET)

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@echo -n "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e $(GREEN)"OK!"$(RESET)

libraries:
	@make -C $(LFTDIR) all

clean:
	@make -C $(LFTDIR) clean
	@echo "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LFTDIR) fclean
	@echo "Deleting program: $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

test: all
	@printf "Testing $(NAME):\n"
	startxwin ./fdf tests/42.fdf
