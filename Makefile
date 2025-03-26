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
RED     = \033[31m
GREEN   = \033[32m
YELLOW	= \033[0;33m
BLUE    = \033[34m
PURPLE	= \033[0;35m
CYAN    = \033[36m
RESET   = \033[0m

# Barre de progression
define PROGRESS_BAR
	$(eval TOTAL_FILES := $(words $(OBJ_CL) $(OBJ_SV) $(OBJ_BC) $(OBJ_BSV)))
	$(eval COMPILED := $(shell echo $$(( $(COMPILED) + 1 ))))
	$(eval PERCENT := $(shell echo $$(( $(COMPILED) * 100 / $(TOTAL_FILES) ))))
	@printf "\r$(CYAN)[minitalk]$(RESET): Compilation... %-20s %3d%% " \
		$$(printf '$(RED)%0.s▮$(RESET)' $$(seq 1 $$(($(PERCENT) / 5)))) \
		$(PERCENT)
endef

MAKEFLAGS += --no-print-directory

all: $(LIBFT_A) $(NAME_CL) $(NAME_SV)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Compilation terminée ! 🥳$(RESET)"

$(LIBFT_A):
	@echo "\n<<<<$(CYAN)[minitalk]$(RESET): DEBUT D'EXECUTION>>>>\n"
	@make -s -C $(LIBFT)

$(NAME_CL): $(OBJ_CL) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_CL) $(INC) $(LIBFT_A) -o $(NAME_CL)
	@echo ":$(GREEN) Client compilé avec succès ! $(RESET)"

$(NAME_SV): $(OBJ_SV) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_SV) $(INC) $(LIBFT_A) -o $(NAME_SV)
	@echo ":$(GREEN) Serveur compilé avec succès !$(RESET)"

bonus: $(LIBFT_A) $(NAME_BC) $(NAME_BSV)
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Bonus bien compilé ! 🥳$(RESET)"

$(NAME_BC): $(OBJ_BC) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_BC) $(INC) $(LIBFT_A) -o $(NAME_BC)
	@echo ":$(GREEN) Client bonus compilé avec succès !$(RESET)"

$(NAME_BSV): $(OBJ_BSV) $(LIBFT_A)
	@$(CC) $(FLAGS) $(OBJ_BSV) $(INC) $(LIBFT_A) -o $(NAME_BSV)
	@echo ":$(GREEN) Serveur bonus compilé avec succès !$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	$(eval COMPILED := $(shell echo $$(( $(COMPILED) + 1 ))))
	$(PROGRESS_BAR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@make -s -C $(LIBFT) clean
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"
	@echo "$(CYAN)[libft]$(RESET):$(GREEN) Fichiers objets => Cleaned!$(RESET)"

fclean: clean
	@$(RM) $(NAME_CL) $(NAME_SV) $(NAME_BC) $(NAME_BSV)
	@make -s -C $(LIBFT) fclean
	@echo "$(CYAN)[minitalk]$(RESET):$(GREEN) Exécutables => Cleaned!$(RESET)"
	@echo "$(CYAN)[libft]$(RESET):$(GREEN) libft.a => Cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus

# ---------------------------------------------------
# Autisme 2.0

flex:
	@echo "🎉 Flexing those muscles! 📸"
	@sleep 0.5
	@echo "\n    ${RED}✨ ᕙ(⇀‸↼‶)ᕗ ✨${NC}\n"
	@sleep 0.5
	@echo "\n    ${GREEN}   ᕙ(✧ڡ✧)ᕗ  ${NC}\n"
	@sleep 0.5
	@echo "\n    ${YELLOW}⚡️ ᕙ(^▽^)ᕗ ⚡️${NC}\n"
	@sleep 0.5
	@echo "\n    ${BLUE}   ᕦ(ò_óˇ)ᕤ  ${NC}\n"
	@sleep 0.5
	@echo "\n    ${PURPLE}💥 ᕙ(▀̿̿Ĺ̯̿̿▀̿ ̿)ᕗ 💥${NC}\n"
	@sleep 0.5
	@echo "\n🏆 Flex session complete! I'm a fcking boss"!

seum:
	@echo "\n ${RED}   Pls... ${NC}\n"
	@sleep 0.5
	@echo "\n ${GREEN}   (˚ ˃̣̣̥⌓˂̣̣̥ ) ${NC}\n"
	@sleep 0.5
	@echo "\n ${CYAN}╭∩╮( •̀_•́ )╭∩╮${NC}\n"
	@sleep 0.5
	@echo "\n ${PURPLE}   (ﾉಥ益ಥ) ${NC}\n"
	@sleep 0.5
	@echo "\n ${YELLOW}   ᶠᶸᶜᵏᵧₒᵤ!${NC}\n"
	@sleep 0.5