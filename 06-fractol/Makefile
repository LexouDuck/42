NAME	=	fractol

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

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

HDRS	=	fractol.h			\
			$(LFTDIR)libft.h
SRCS	= 	color.c				\
			palette.c			\
			complex.c			\
			fractal.c			\
			render.c			\
			event.c				\
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
