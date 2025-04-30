#ifndef IPC_COMMANDS_H
#define IPC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool ipc_rx_event_command(int32_t argc, char* argv[]) ;
bool ipc_signal_command(int32_t argc, char* argv[]) ;
bool ipc_rx_event_chan_command(int32_t argc, char* argv[]);
bool ipc_diag_command(int32_t argc, char* argv[]);

#define IPC_COMMANDS                                                                           \
    SHELL_CMD("ipc_rx_event_chan", "ipec", ipc_rx_event_chan_command, "IpcRxEventChan"),       \
    SHELL_CMD("ipc_diag", "ipd", ipc_diag_command, "IpcDiag"),       \
    SHELL_CMD("ipc_rx_event", "ipe", ipc_rx_event_command, "IpcRxEvent"),       \
    SHELL_CMD("ipc_sig", "ips", ipc_signal_command, "IpcSignal"),



#ifdef __cplusplus
}
#endif

#endif /* IPC_COMMANDS_H */
