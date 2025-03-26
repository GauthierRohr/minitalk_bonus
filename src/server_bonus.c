/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:28:03 by grohr             #+#    #+#             */
/*   Updated: 2025/03/26 21:06:59 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk_bonus.h"

char	*g_msg = NULL;

// Calculer la longueur actuelle du message
// Allouer un nouveau buffer (+2 pour le nouveau char et le '\0')
// Copier l'ancien message si existant
// Ajouter le nouveau caractère
// Mettre à jour le pointeur global
void	add_char(char c)
{
	char	*new;
	size_t	len;

	if (g_msg)
		len = ft_strlen(g_msg);
	else
		len = 0;
	new = malloc(len + 2);
	if (!new)
		exit(1);
	if (g_msg)
	{
		ft_memcpy(new, g_msg, len);
		free(g_msg);
	}
	new[len] = c;
	new[len + 1] = '\0';
	g_msg = new;
}

// <<<Le gestionnaire de signaux>>>
//----
// Lorsqu'un signal SIGUSR1 ou SIGUSR2 arrive, le système va :
// Appeler la fonction handler
// Lui passer 3 infos :
// 		Le numéro du signal reçu (SIGUSR1 ou SIGUSR2)
// 		Pointeur vers sig_info qui contient des détails sur l'émetteur du signal
// 		Un pointeur context sur le contexte système (ignoré ici)
//----
// 1.Construit chaque caractère bit par bit
// 2.Quand un caractère complet est reçu :
// 		Si c'est '\0', c'est la fin du message
// 		Affiche le message
// 		Envoie un signal de confirmation au client
// 		Libère la mémoire
// 3.Sinon, ajoute le caractère au message global
//
// `context` fait partie de la signature de fonction pour `sa_sigaction`
// C'est un pointeur vers une structure `ucontext_t` qui contient des
// informations sur le contexte du signal.
// Ignorer ici car pas besoin, mais on ne peut pas le supprimer car c'est
// la signature standard de la fonction de gestion de signal avec `SA_SIGINFO`.
// signal : le numéro du signal reçu
// sig_info : informations détaillées sur le signal
// context : contexte d'exécution du programme au moment du signal
//
// c |= (1 << bit_index) met à 1 le bit à la position i
// 		Pour i=0 : 00000001
// 		Pour i=1 : 00000010
// 		Pour i=2 : 00000100
//
// kill(sig_info->si_pid, SIGUSR2);
//		sig_info->si_pid récupère PID exact du client qui a envoyé le signal
// 		Permet de renvoyer un signal de confirmation UNIQUEMENT à ce client
void	handler(int signal, siginfo_t *sig_info, void *context)
{
	static int	bit_index = 0;
	static char	c = 0;

	(void)context;
	if (signal == SIGUSR2)
		c |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (c == '\0')
		{
			ft_printf("%s\n", g_msg);
			kill(sig_info->si_pid, SIGUSR2);
			free(g_msg);
			g_msg = NULL;
		}
		else
			add_char(c);
		bit_index = 0;
		c = 0;
	}
}

// Le main() fait :
// 1.Vérifier qu'aucun argument n'est passé
// 2.Configurer le gestionnaire de signaux
// 3.Afficher le PID du serveur
// 4.Entrer en mode attente avec pause()
//
// sa.sa_flags = SA_SIGINFO;
// 		Permet d'utiliser la version AVANCÉE de gestion de signal
// 		Active réception d'infors supplémentaires via siginfo_t
// 		Sans ce flag, PAS ACCES à sig_info->si_pid
//
// &sa contient :
// 		La fonction de gestion du signal (handler)
// 		Les drapeaux de comportement (SA_SIGINFO)
// 		Le masque de signaux à bloquer pendant le traitement
// &sa indique au système :
// 		Comment réagir quand SIGUSR1 est reçu
// 		Quelle fonction appeler
// 		Avec quelles options spéciales
// Le troisième argument NULL signifie :
// 		Ne pas sauvegarder l'ancienne configuration de signal
// 		Remplacer directement le comportement précédent
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 1)
	{
		ft_printf("\033[38;5;196mError: wrong format.\033[0m\n");
		return (ft_printf("\033[33mUsage: %s\033[0m\n", argv[0]), 0);
	}
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("\033[94mPID -> \033[0m%d\n", getpid());
	ft_printf("\033[90mWaiting...\033[0m\n");
	while (1)
		pause();
	return (0);
}
