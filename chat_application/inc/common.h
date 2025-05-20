#ifndef _COMMON_H_
#define _COMMON_H_

/*******************************************************************************
 ***********************   DEFAULT GLOBAL CLI PARAMETERS   ********************
 ******************************************************************************/
#define MAX_INPUT_SIZE      4U
#define MAX_CONNECTIONS     10U
#define MAX_BUFFER_SIZE     256U

// Default port/ip if not specified
#define DEFAULT_PORT        12345U
#define DEFAULT_IP          "127.0.0.1"

/*******************************************************************************
 *****************************   LOG DEBUG   ***********************************
 ******************************************************************************/
#define CR_LF "\r\n"
#define INT_ERR  "Internal Error: "
#define FILE_LINE "File: %s - line %d: "

#define PRINTF_LOG(format, args...) do { \
                                        printf(FILE_LINE INT_ERR format CR_LF, \
                                               __FILE__, __LINE__, ##args);    \
                                    } while (0)
#if DEBUG_EFM
#define LOG_DEBUG(format, args...) PRINTF_LOG(format, ##args)
#else
#define LOG_DEBUG(format, args...) (void)0
#endif


#endif /* _COMMON_H_ */