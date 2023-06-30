NAME	=	Cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

PARSING	=	map_read.c read_map_check.c read_config_file.c parsing_utils.c
RENDERING = boot_mlx.c
MAIN    =	Cub3D.c
# UTILS   =	intialize_list.c
OBJPATH = 	./obj/
LIBFT = 	./sources/utils/Libft

GREEN   =   \033[1;32m 
RESET   =   \033[0m 

SRC = 	$(addprefix sources/parsing/, $(PARSING)) \
	 	$(addprefix sources/render/, $(RENDERING)) \
	 	$(addprefix , $(MAIN))

OBJ = 	$(patsubst %.c,$(OBJPATH)%.o,$(SRC))

all		:	$(MAKELIBFT) $(OBJPATH) $(NAME)

$(OBJPATH):
		mkdir -p $(OBJPATH)sources/parsing/
		mkdir -p $(OBJPATH)sources/render/
		mkdir -p $(OBJPATH)

$(NAME)	:	$(OBJ)
		@echo "$(GREEN)Building $(NAME) $(RESET)..."
		@make -C $(LIBFT)
		$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib $(LIBFT)/libft.a -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
		@echo "$(GREEN)\033[1mCompilation complete$(RESET)"

$(OBJPATH)%.o: %.c
		$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(OBJPATH)
	cd $(LIBFT) && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT) && $(MAKE) fclean

re:		fclean all

.PHONY	:	all clean fclean re
