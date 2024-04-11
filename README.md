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
~$ >> out cat < Makefile << eof > out2 | << eof ls -la >> out3 | >> out4 > out3 grep mini < out2

Issues:
1) << eof echo toto | << eof2 cat
2) cat < Makefile | echo toto | wc >> out