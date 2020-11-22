#define DEBUG 1
#if DEBUG
/**
* Macros that implements debug loging.
* @lvl: type of log.
* @msg: log message.
*
* It writes 3 types of logs:
*   * INFO - short loging of main daemon actions.
*   * SNIFFER logs - messages about catched packets.
*   * DEBUG - more detailed logging of daemon actions.
*
* Return: void.
*/
#define _log(msg) do{printf(">> DEBUG : %s \n", msg);}while(0)
#else
#define _log(msg) do{}while(0)
#endif
