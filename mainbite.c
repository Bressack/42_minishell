/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainbite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:31:20 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/16 17:48:30 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
char *readline(FILE *file)
 {
    char  *line;
    size_t length;
    size_t count;
    int    chr;
    length = 100;
    line   = malloc(1 + length);
    if (line == NULL)
     {
        fprintf(stderr, "memory exhausted!\n");
        return NULL;
     }
    count = 0;
    while (((chr = fgetc(file)) != EOF) && (chr != '\n'))
     {
        if (count >= length)
         {
            void *pointer;
            length += length;
            pointer = realloc(line, 1 + length);
            if (pointer == NULL)
             {
                fprintf(stderr, "memory exhausted!\n");
                free(line);
                return NULL;
             }
            line = pointer;
         }
        line[count] = chr;
        count      += 1;
     }
    line[count] = '\0';
    return line;
 }
int main(void)
 {
    char *line = readline(stdin);
    if (line != NULL)
        printf("%s\n", line);
    free(line);
    return 0;
 }
