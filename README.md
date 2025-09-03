# Minishell - A 42 School Project
## "As beautiful as a shell"

```
This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.
```
~ The subject for this project

Minishell is a simplified copy of bash.
Among the things that bash does that msh doesn't, the most important are:
- Logical operators such as && and ||
- Wildcards (*)
- Escape characters (\\)
- Semicolons
- Msh is not a command language like bash is!

## Dependencies
This program requires the ```libreadline-dev``` package to work correctly.
It can be installed with whatever package manager your Linux distribution uses, for example:
- On Debian-based distributions:
```sudo apt-get install libreadline-dev```

- On Arch-based distributions:
```sudo pacman -S libreadline-dev```

## Usage
Compile with ```make```.

Delete object files with ```make clean```.

Delete all files generated during compiling with ```make fclean```.

## Known Issues
- Minishell does not update the SHLVL environment variable.
- Minishell instances that open other shells do not stop listening to signals.
  + This leads to odd behaviour such as writing N newlines to stdout when pressing ctrl+c, where N is the number of opened recursive minishells.
\
\
\
\
\
Msh is written in accordance with 42 School's coding norm, see here:
https://github.com/42School/norminette
