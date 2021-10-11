/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_create_jobs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:22:35 by bcosters          #+#    #+#             */
/*   Updated: 2021/10/11 10:33:35 by bcosters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extras/includes/minishell.h"

/**
 * Everything before a '|' or the end of argv is split into a job
 *  =>	Order of execution is important
 * 	INPUT:
 * 		PRIORITIES:
 * 			1.	Here_doc input (and error checking)
 * 			2.	Input files	(and error checking)
 * 			3.	Input from command (and error checking)
 * EXAMPLE: "< logfile cat << EOF < lel"
 * 	-> here_doc until EOF then error on lel because it doesn't exist
*/

