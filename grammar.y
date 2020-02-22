/****************************/
/*** Grammar of minishell ***/
/****************************/

%token  WORD
%token  LPAREN       RPAREN
/*      '('          ')'                           */
%token  REDIREC_IN   REDIREC_OUT    DREDIREC_OUT
/*      '<'          '>'            '>>'           */
%token  SQUOTE       DQUOTE
/*      '''          '"'                           */
%token  PIPE
/*      '|'                                        */
%token  AND          OR
/*      '&'          '|'                          */
%token  SEMICON
/*      ';'                                        */
%token  SPACE        TAB
/*      ' '          '\t'                          */

%start expr
%%
expr            : (redirection)*
				| ((redirection)* cmd (redirection | (space arg))* (cmd_sep | expr_end)*)*
                | (LPAREN expr RPAREN (cmd_sep expr | expr_end)*)*
                | (expr_end)*
                ;
redirection     : REDIREC_IN file
                | REDIREC_OUT file
                | REDIREC_OUT REDIREC_OUT file
                ;
cmd             : word
                ;
arg             : word
                ;
file            : word
                ;
word            : WORD
                ;
cmd_sep         : ((dbl_and | dbl_or | pipe) expr)*
                ;
expr_end        : SEMICON (expr)*
                ;
dbl_and         : AND AND
                ;
dbl_or          : PIPE PIPE
                ;
pipe            : PIPE
                ;
space           : SPACE
                | TAB
                ;
/* END :) */
