*This project has been created as part of the 42 curriculum by amurtas, mageneix*

![Norm_pass](https://img.shields.io/badge/Norm-Passed-green)
![Score](https://img.shields.io/badge/Score-In_Progress-green)
![Language](https://img.shields.io/badge/Language-C-blue)

# **Description**
This project is about creating a simple shell. The project requires recreating bash behavior as closely as possible. It learns to use redirections, parsing, command execution, and a whole range of other features. All commands can be executed using the `execve` function, except for the built-in commands: `cd`, `pwd`, `echo`, `export`, `unset`, `env`, and `exit`. The commands are compatible with file redirection, including with HereDoc.

| Key / Action | Effect |
| :--- | :--- |
| **`Ctrl + C`** | Displays a new prompt on a new line |
| **`Ctrl + D`** | Exits the shell (EOF) |
| **`Ctrl + \`** | Does nothing on the prompt (quits the current running process if any) |

# **Instructions :**

## **Here is how to compile and run the project:**

* ### **Compilation :**

```bash
make
```

* ### **Execution :**

```bash
./minishell
```

```bash
minishell> your_prompt/command
```

# **Resources**

We used the official documentation and AI to understand the functions and track valgrind errors. We also used bash to compare our project to how bash works.