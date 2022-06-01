#  220419 - MINISHELL

##  HIGH

???
* Vars expand UNTIL a non-[alpha/num/underscore] char. Cf.: echo "$=TEST" $TEST=

ARCHI
* echo " " $USER
> Missing space

???
* Leaks: <space> + $ANYTHING

ARCHI
* echo "~"
> Shouldnt expand

ARCHI
* echo $123A
> Should display 23A

???
* export var1="|" var2="ls"
> Should work fine (*check expand quote timing*)

    ARCHI
    * sjsjs
    > Should print 'sjsjs: command not found' without 'minishell'

CLEM
* $EMPTYVAR
> Shoudln't print anything (instead print cmd not found)

    CLEM
    * mkdir a; cd a; rmdir ../a; pwd; cd -; cd -
    > ft_pwd should use data->cwd not CWD

    CLEM
    * echo -nnnnn"salu"
    > Should display -nnnnn"salu"

***???***
* export var="'cat Makefile'"
> Shouldn't print errorS

CLEM
* Protect malloc with `ft_clear_exit("malloc error")` with an strdup wrapper.

##  MID

CLEM
- export +=

    ARCHI
    - Add && strlen(stop word) to here_doc stopword checker

***???***
- 'ls: command not found' if there is a 'ls' file in the CWD.

???
- remove tokpos


##  LOW
CLEM
- Add remove_tok to libft
