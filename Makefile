NAME	=	Cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

PARSING	=	main_arguments.c map_read.c read_map_check.c read_config_file.c parsing_utils.c
OBJPATH = 	./obj/
LIBFT = 	./sources/utils/Libft

GREEN   =   \033[1;32m 
RESET   =   \033[0m 

SRC = 	$(addprefix sources/parsing, $(PARSING))
OBJ = 	$(addprefix $(OBJPATH), $(PARSING:.c=.o)) 

all		:	$(MAKELIBFT) $(OBJPATH) $(NAME)


$(OBJPATH):
		mkdir $(OBJPATH)

$(NAME)	:	$(OBJ)
		@echo "$(GREEN)Building $(NAME) $(RESET)..."
		@make -C $(LIBFT)
		$(CC) $(CFLAGS) $^ -o $@ $(LIBFT)/libft.a
		@echo "$(GREEN)\033[1mCompilation complete$(RESET)"

$(OBJPATH)%.o:	sources/parsing/%.c
			$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJPATH)
	cd $(LIBFT) && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT) && $(MAKE) fclean

re:		fclean all

.PHONY	:	all clean fclean re