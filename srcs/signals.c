/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:20 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/17 18:33:32 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
}

void	set_sign_ignore(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_int, NULL);
}

void	set_sign_def(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = SIG_DFL;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_int, NULL);
}

void	setup_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_int.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_int, NULL);
}
