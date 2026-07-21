NAME = ircserv

SRC_DIR = ./Srcs/
OBJ_DIR = obj/
SRC =	main.cpp\
		server.cpp\
#		client.cpp\

OBJS	= $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CC = c++
CFLAGS = -Wall -Wextra -Werror -g -std=c++98 -IIncludes
RM = rm -f

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) ${CFLAGS} -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo '$(NAME) compiled successfully!'

all: $(NAME)

fclean: clean
	@$(RM) $(NAME)
	@echo '$(NAME) deleted!'

clean:
	@$(RM) $(OBJS)
	@echo 'obj deleted!'

re: fclean all

.PHONY : all clean fclean re