# Minishell

0) isatty?

1) On se ramene a un input to read comme ca:
> abc def | ghi | jkl << mno < < pqr > stu | vwx < yz

2) On split(' '), on a tableau de "truc"
[">","abc","def","|","ghi","|","jkl","<<","mno","<","<","pqr",">","stu","|","vwx","<","yz"]

3) On definit le type de chaque "truc" (avec un code/define/enum?)
- limiter (0)
- infile (1)
- outile (2)
- outfile+ (3)
- symbol (4)
- cmd (5)
- arg (6)
(autre type?)

pour obtenir un  tableau de "type" correspondant 
[symbol, outfile, cmd, symbol, cmd, symbol, cmd, symbol, ...]

Pour trouver le tableau des types voici un pre-algo
je prends un "truc" (hors symbol)
1) | avant => cmd
2) | apres => cmd ou arg => access => soit cmd soit arg et truc-1 = cmd
3) < avant => infile
4) > avant => outfile
5) >> avant => outfile+
6) << avant => limiter
7) rien => si 1er => cmd sinon arg du 1er

How to execve:
~$ >> out cat < Makefile << eof > out2 | << eof ls -la >> out3 | >> out4 > out3 grep mini < out2 --> ok

Solved:
1) << eof echo toto | << eof2 cat --> ok
2) cat < Makefile | echo toto | wc >> out --> ok
3) cat | wc << eof --> ok as bash (~~but next weird (need to enter on each new prompt)~~)
5) wc << eof | cat --> ok
Issues:
4) sleep 2 | sleep 2 | cat << e | sleep 2 | cat << f
6) wc << eof | ls | wc << e | cat
7) wc << eof | cat > out | wc << eof | cat
8) << eof
9) << eof | << rt
10) << eof | << rt wc

un truc a tester a la fin: 1) lancer minishell 2) faire une modif dans le code 3) faire make dans le minishell en cours 4) lancer le nouveau minshell dans minishell 5) verifier la modif 6) exit 7) verififier qu'il n'y a plus la modif
 
Syntax error to be checked
1) at least one CMD by block (and only one ?)
2) last word of the prompt is not a pipe
3) we need to be sure there is a LIMITER just after HEREDOC

Ask
- open (0666), mais rw/r/r ??? 
- double_free((void **)(mini->cmd_arg));
- mettre NULL apres free