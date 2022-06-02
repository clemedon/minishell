#  HELP

##  TODO.MD

**Issues** title verbs are *imperative*, start with a *Maj* and no '.' in
the title, like this:

- Issue/Commit message *title* (action + subject).
> Issue/Commit message *body*: any details about the issue or to reproduce it.
> Can be multiline

**Commit** message should be exact *copy/paste of the issue* without
the '-' and '>' chars, and without temporary notes in the title
like: '(parsing?or exec?)'.
Title and Body should be separated with *one blank line*.

 If the issue has a body, use `git commit` instead `git commit -m`.

**Tasks** must be organized from top to bottom (*priority at the top*).
Tasks that concern the *same subject* must be *close to each other*.

*Completed task* can be removed from todo.md with '*dap*' (vim normal
mode).

##  GIT

*Pull* when we have unstaged modified files:
    git stash
    git pull
    git stash pop

*Update the last commit* instead of creating a new one:
    git commit --amend
> Only work if not pushed yet!!
> Also useful when we want to fix the last commit message if there is
> a typo.

*Uncommit* unwanted file:
    git reset --soft HEAD~1
> Then `git reset` the unwanted files and commit again with `-c` flag
> to preserve the prev commit message.

*Explore* commit history:

Quick look (one commit per line + graph):
     git log --oneline  --graph --all
More in depth (detail of all modified files + author):
     git log --pretty=format:"%an %cr : %s" --stat --graph -2

###     Branch

**Manage branches:**

*Create* a new branch (don't switch to it):
    git branch <branch_name>
*Delete* a branch (has to be done from another branch):
    git branch -d <branch_name>

*Switch* to a branch:
    git switch <branch_name>
> Same as 'git checkout <branch_name>

Switch to the *previous* branch.
    git switch -

Fully *rename* a branch name
> Except master, which needs few more steps
1. rename the local branch
    git branch --move <wrong_name> <correct_name>
2. rename the remote branch ( update the upstream branch )
    git push -u <remote_name> <correct_name>
3. now remove the still existing local wrong_name
    git push <remote_name> --delete <bad_branch_name>

*List* the existing branches:
    git branch
Shows the last *commit* of each branches:
    git branch -v

**Merge the branch:**

1. specify mergetool:
    git mergetool --tool=vimdiff
> Vimdiff recap: 'do' to obtain from the other window, 'dp' to put
> into the other side.

2. diff a branch with HEAD:
    git diff <branch_name>

3. merge branch_name with the current branch:
    git merge <branch_name>
> If there is a *conflict*, `git status` to see unmerged files, manually
> fix them then `git add` / `git commit -a`.  + describe my merge in
> the commit message.

**Branching Rebasing**

***ONLY rebase local commits that haven't been pushed.***

> Take all the changes that were committed on one branch and replay
> them on a different branch.

Rebasing example, from 'experiment' to 'master':
1. move to the branch to rebase
    git switch experiment
2. target the rebase destination branch
    git rebase master
3. move to the rebase destination branch
   for a *fast-forward merge*
    git switch master
    git merge experiment

> If master has not diverged, instead of creating
> a 'merge commit', git will just point master to the
> latest commit of the feature branch: *fast-forward*

> There is no difference between the end product
> commit of *a rebasing or a merging*, but rebasing
> makes a cleaner history, a linear one.
