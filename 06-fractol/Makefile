NAME	=	fractol

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
CFLAGS	=	-Wall -Werror -Wextra -O3 -MMD $(INCLUDE)

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
DEPENDS	=	${OBJS:.o=.d}

all: libraries $(NAME)

$(NAME): $(OBJS) $(HDRS)
	@printf "Compiling program: "$@" -> "
	@$(CC) $(OBJS) $(CFLAGS) -o $@ $(LIBS)
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@ -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"

libraries:
	@make -C $(LFTDIR) all

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: "$(NAME)"\n"
	@rm -f $(NAME)

re: fclean all

-include ${DEPENDS}
