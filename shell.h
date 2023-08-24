#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;

/**
 * struct link_list - a singly linked list.
 * @str: string.
 * @num: integer number.
 * @next: pointer to the next node.
 */
typedef struct link_list
{
	int num;
	char *str;
	struct link_list *next;
} list_t;

/**
 * struct data - includes arguements to pass into a function.
 * @arg: a string generated from getline includes arguements.
 * @argv: an array of strings generated from arg.
 * @argc: number of arguments.
 * @path: the path for the current command.
 * @fname: the filename of the program.
 * @line_count: number of errors.
 * @err_num: the error code for exit()s.
 * @linecount_flag: if on count this line of input.
 * @env: local copy of environ.
 * @environ: custom modified copy of environ from local env.
 * @env_changed: changes of  environ.
 * @history: a node that holds history.
 * @histcount: the history line number count.
 * @alias: the alias node.
 * @status: status returned of the last executed cmd.
 * @cmd_buf: pointer to cmd_buf, if chaining.
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @read_fd: the file descriptor from which to read line input.
 */
typedef struct data
{
	char *arg;
	char **argv;
	int argc;
	char *path;
	char *fname;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	list_t *env;
	char **environ;
	int env_changed;
	list_t *history;
	int histcount;
	list_t *alias;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int read_fd;
} inf_t;

#define inf_init \
{NULL, NULL, 0, NULL, NULL, 0, 0, 0, NULL, NULL, 0, NULL, 0, NULL, 0,\
	NULL, 0, 0}

/**
 *struct builtin - contains a builtin str.
 *@type:  builtin command flag.
 *@func: function.
 */
typedef struct builtin
{
	char *type;
	int (*func)(inf_t *);
} builtin_table;
/* sh_ops.c */
int is_cmd(inf_t *, char *);
int cmd_loop(inf_t *, char **);
int f_bin(inf_t *);
void f_cmd(inf_t *);
void fork_cmd(inf_t *);
/* cmd_ops */
char *dup_char(char *, int, int);
char *f_path(inf_t *, char *, char *);
/* errors1.c */
void e_puts(char *);
int e_putchar(char);
int put_fd(char c, int fd);
int put_sfd(char *str, int fd);

/* strings.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* strings1.c */
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);
char *goes_by(const char *, const char *);

/* strings2.c */
char *_strcpy(char *, char *);
void put_s(char *);
int put_char(char);
char *_strdup(const char *);

/* token.c */
char **splitter(char *, char *);
char **splitter2(char *, char);
/* mem1.c */
char *_mem_set(char *, char, unsigned int);
void _ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int mem_free(void **);

/* interaction.c */
int interactive_md(inf_t *);
int _isalpha(int);
int _atoi(char *);
int delim_chk(char, char *);
/* error2.c */
int err_atoi(char *);
void p_err(inf_t *, char *);
int print_d(int, int);
char *transfer_numb(long int, int, int);
void delete_comm(char *);
/* built_in.c*/
int _exitshell(inf_t *);
int _cdir(inf_t *);
int _pdir(inf_t *);
/* built_in2.c */
int _history(inf_t *);
int _alias(inf_t *);

/* buffers.c */
ssize_t buff_input(inf_t *, char **, size_t *);
ssize_t get_length(inf_t *);
ssize_t buff_read(inf_t *, char *, size_t *);
int get_line(inf_t *, char **, size_t *);
void sigint_Handler(int);

/* init_inf.c */
void clear_inf(inf_t *);
void set_inf(inf_t *, char **);
void _ffree_inf(inf_t *, int);

/* environ.c */
int my_env(inf_t *);
char *get_env(inf_t *, const char *);
int set_env(inf_t *);
int unset_env(inf_t *);
int env_list(inf_t *);

/* environ1.c */
char **get_envir(inf_t *);
int _unset_envir(inf_t *, char *);
int _set_envir(inf_t *, char *, char *);
/* history */
char *get_h_file(inf_t *inf);
int write_h(inf_t *inf);
int read_h(inf_t *inf);
int build_h_list(inf_t *inf, char *buf, int linecount);
int renumber_h(inf_t *inf);
/* lists */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
/* lists */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *n_goes_by(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* alias.c */
int alias_exchange(inf_t *);
int vars_exchange(inf_t *);
int string_replace(char **, char *);
int chain_delim(inf_t *, char *, size_t *);
void chain_rev(inf_t *, char *, size_t *, size_t, size_t);

#endif
