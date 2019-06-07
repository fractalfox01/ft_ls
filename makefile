NAME= ft_ls

LIBFT= -Llibft -lft

SRC= main.c

$(NAME):
	@make -C libft all
	$(CC) $(SRC) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	@make -C libft clean

fc: fclean

fclean:
	@make -C libft fclean
	@rm -f ft_ls

re: fclean all
	@clear

gitsync: fc
	@git status
	@echo "\033[0;32m"
	git add $(SRC) makefile ft_ls.h
	@echo "\033[0;37m"
	@git commit -m "updating repo"
	@echo "\033[0;34m"
	git push origin master
	@echo "\033[0;37m"

.PHONY: ft_ls all clean fclean re gitsync