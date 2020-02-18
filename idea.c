/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idea.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 08:17:15 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/18 01:18:33 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

expr:	echo salut les amis des bois jolis >> test && ls -laG | cat -e | wc -l ; ls

AST:
                          _________________ [;] _________________
                         /                                       \
           ___________ [&&] ___________                          ls
          /                            \
    ___ [>>] ___                  ___ [|] ___
   /            \                /           \
 echo          test        ___ [|] ___       wc
  |                       /           \      |
salut                    ls           cat    -l
  |                      |             |
 les                   -laG           -e
  |
 amis
  |
 des
  |
 bois
  |
 jolis

"_"