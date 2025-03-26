/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grohr <grohr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:07:02 by grohr             #+#    #+#             */
/*   Updated: 2025/03/26 20:54:20 by grohr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 199309L
//	Active les fonctionnalités POSIX (un standard Unix/Linux).
//	199309L correspond à POSIX.1b (1993), qui inclut :
//	- struct sigaction (pour une gestion avancée des signaux).
//	- siginfo_t (infos détaillées sur le signal reçu, comme PID de l'émetteur).
# define _XOPEN_SOURCE 500
//	Active des extensions UNIX supplémentaires (X/Open).
//	500 correspond à SUSv2 (Single UNIX Specification version 2).
//	Complète _POSIX_C_SOURCE : ajoute fonctions ex: usleep() + des APIs système.
//	Certaines implémentations de <signal.h> nécessitent _XOPEN_SOURCE
//	pour avoir accès à tous les champs de siginfo_t.

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

#endif