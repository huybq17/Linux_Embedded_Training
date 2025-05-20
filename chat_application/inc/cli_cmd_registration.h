#ifndef _CLI_CMD_REGISTRATION_H_
#define _CLI_CMD_REGISTRATION_H_

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

/**************************************************************************//**
 * @brief Regiter all cli commands
 *
 *****************************************************************************/
extern const cli_cmd_entry_t cli_cmd_table[];


#endif /* _CLI_CMD_REGISTRATION_H_ */