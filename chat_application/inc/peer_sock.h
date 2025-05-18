#ifndef _PEER_SOCK_H_
#define _PEER_SOCK_H_


/*---- Register CLI param ---- */

typedef void (*cli_cmd_func_t)(int argc, char **argv);
typedef struct
{
    cli_cmd_func_t func;
    char *help_text;
} cli_cmd_info_t;

typedef struct
{
    const char *name;
    const cli_cmd_info_t *cmd;
} cli_cmd_entry_t;


void cli_cmd_init(char *input);

#endif /* _PEER_SOCK_H_ */