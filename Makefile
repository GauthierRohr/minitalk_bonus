# Nom des exécutables
NAME_CL  = client
NAME_SV  = server
NAME_BC  = client_bonus
NAME_BSV = server_bonus

# Librairie
LIBFT    = libft
LIBFT_A  = $(LIBFT)/libft.a

# Compilation
CC       = gcc
FLAGS    = -Wall -Werror -Wextra
SRC_DIR  = src/
OBJ_DIR  = obj/
INC      = -I inc
RM       = rm -rf

# Sources et objets
SRC_CL  = $(SRC_DIR)client.c
SRC_SV  = $(SRC_DIR)server.c
SRC_BC  = $(SRC_DIR)client_bonus.c
SRC_BSV = $(SRC_DIR)server_bonus.c

OBJ_CL  = $(OBJ_DIR)client.o
OBJ_SV  = $(OBJ_DIR)server.o
OBJ_BC  = $(OBJ_DIR)client_bonus.o
OBJ_BSV = $(OBJ_DIR)server_bonus.o

# Couleurs
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RED     = \033[31m
CYAN    = \033[36m
RESET   = \033[0m

# Barre de progression
define PROGRESS_BAR
	$(eval PROGRESS += ▓)
	@printf "\r$(CYAN)[minitalk]:$(RESET) Compilation en cours... $(PROGRESS)"
endef

all: $(LIBFT_A) $(NAME_CL) $(NAME_SV)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Compilation terminée !$(RESET)"

$(LIBFT_A):
	@echo "$(BLUE)[minitalk]: Compilation de libft...$(RESET)"
	@make -C $(LIBFT)

$(NAME_CL): $(OBJ_CL) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_CL) $(INC) $(LIBFT_A) -o $(NAME_CL)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Client compilé avec succès !$(RESET)"

$(NAME_SV): $(OBJ_SV) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_SV) $(INC) $(LIBFT_A) -o $(NAME_SV)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Serveur compilé avec succès !$(RESET)"

bonus: $(LIBFT_A) $(NAME_BC) $(NAME_BSV)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Bonus compilé avec succès !$(RESET)"

$(NAME_BC): $(OBJ_BC) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_BC) $(INC) $(LIBFT_A) -o $(NAME_BC)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Client bonus compilé avec succès !$(RESET)"

$(NAME_BSV): $(OBJ_BSV) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_BSV) $(INC) $(LIBFT_A) -o $(NAME_BSV)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Serveur bonus compilé avec succès !$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	$(PROGRESS_BAR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Object files => Cleaned!$(RESET)"

fclean: clean
	@$(RM) $(NAME_CL) $(NAME_SV) $(NAME_BC) $(NAME_BSV) $(LIBFT_A)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) All binaries & libft.a => Cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
