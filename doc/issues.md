

#           ISSUES


>       help

# ------------------------ ( ATHIRION )

- Fix error message
> 'sjsjs' should print 'sjsjs: command not found' without
> 'minishell' prefix.

- Fix here_stopword checker
> Maybe with a '&& strlen(stop word)'

- Fix spaces parsing
> 'echo " " $USER' shouldn't remove the "space".

- Fix var expansion parsing
> 'echo "~"' shouldnt expand.

- Fix var expansion parsing
> 'echo $123A' should display '23A'.

# ------------------------ ( CVIDON )

- Fix leaks
> From parsing? exec?
> When we input one space followed by a dollar and any word:
> <space> + $ANY_WORD

##  Exec

- Fix exec emptyvar
> '$EMPTYVAR' shoudln't print anything instead of 'command not found'.
> ***TODO*** exec.c: ft_is_builtin:
> + `if (!((t_cmd *)cmd->content)->cmd[0])`
> +     `return (FALSE);`
> Fixes segfault but perror ':command not found'

- Fix exec quoted space
> exec.c: ft_is_builtin / ft_exec
> '" "' = segfault

- Fix exec when cwd files named as programs are called
> 'ls: command not found' if there is a 'ls' file in the CWD.
> Might be fixed with the handling of './file' execution. Or the
> environ check for path before the exec a command.

##  Builtins

- Add export '+=' feature

##  Global

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

- Comply to norm

- Add remove_tok to libft

##  Other

# ------------------------ ( ? )

- Fix error message
> Space after the ':' not before:
> `salut :command not found` should be `salut: command not found`

- Fix var expansion parsing
> Var names is ONLY made of ALPHANUMERIC and UNDERSCORE characters.
> Test with: 'echo "$=TEST" $TEST='
> Cf. export.c: ft_is_valid_export()

- Fix expand quote timing
> 'export var1="|" var2="ls"' should work fine.

- Fix export builtin (linked to quote timing?)
> export var="'cat Makefile'" OR export var='"cat Makefile"' shouldn't
> print errors.

- Add error code management

- Add SHLVL feature

- Remove tokpos
