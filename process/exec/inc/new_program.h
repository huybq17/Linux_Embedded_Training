#ifndef _NEW_PROGRAM_H_
#define _NEW_PROGRAM_H_

/*************************************************************************
 * Definitions
 ************************************************************************/
// Number of argurments for using a new program
#define ARG_COUNT       10U
#define NUMBER_PROGRAM  4U

typedef enum {
    UNKNOWN,
    LIST,
    DATE,
    TIME,
    PROCESS
} new_program_t;


/*************************************************************************
 * Prototypes
 ************************************************************************/
/*!
 * @brief .
 *------
 * @param none.
 *
 * @return none.
 */
void sigchld_handler(int sig);

/*!
 * @brief .
 *------
 * @param none.
 *
 * @return none.
 */
pid_t replace_process(const char *program, char *const *args);


/*!
 * @brief.
 *------
 * @param none.
 *
 * @return none.
 */
char **check_value(char const *args);

#endif /* _NEW_PROGRAM_H_ */

/*************************************************************************
 * EOF
 ************************************************************************/
