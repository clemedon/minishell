

#           ISSUES


>       help

# ------------------------ ( ATHIRION )

##  Parsing

- Fix spaces parsing
> 'echo " " $USER' shouldn't remove the "space".
> "      " Shouldnt be reduced to ""

- Fix var expansion parsing
> 'echo "~"' shouldnt expand.

- Fix var expansion parsing
> 'echo $123A' should display '23A'.

# ------------------------ ( CVIDON )

##  Builtins

- Add export '+=' feature

- Add ft_exit

##  Exec

- Fix exec when cwd files named as programs are called
> 'ls: command not found' if there is a 'ls' file in the CWD.
> Might be fixed with the handling of './file' execution. Or the
> environ check for path before the exec a command.

##  Global

- Protect all the malloc
> Create a 'ft_clear_exit("malloc error")' and a 'ft_strdup' wrapper.

- Comply to norm

##  Other

- Add remove_tok to libft

# ------------------------ ( ? )

- Fix quote parsing:
> `'" "'`      prints> `"` instead `" "`
> `"' '"`      prints> `'` instead `' '`
> `"a    b"` prints> `a` instead `a    b`

- Fix empty var errmsg
> '$notavar' should not print ': command not found'

- Fix var expansion parsing
> Var names is ONLY made of ALPHANUMERIC and UNDERSCORE characters.
> Test with: 'echo "$=TEST" $TEST='
> Cf. export.c: ft_is_valid_export()

- Fix expand quote timing
> 'export var1="|" var2="ls"' should work fine.

- Fix export builtin (linked to quote timing?)
> export var="'cat Makefile'" OR export var='"cat Makefile"' shouldn't
> print errors.

- Add $? feature

- Add SHLVL feature

- Add error code management

- Add 'exit' builtin

- Remove tokpos
