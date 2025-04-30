#ifndef CRYP_GENERAL_COMMANDS_H
#define CRYP_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifdef HAS_CRYP_CUSTOM_COMMANDS
#include "cryp_custom_commands.h"
#else /*HAS_CRYP_CUSTOM_COMMANDS*/
#define CRYP_CUSTOM_COMMANDS
#endif /*HAS_CRYP_CUSTOM_COMMANDS*/

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool cryp_encrypt_ecb_command(int32_t argc, char* argv[]);
bool cryp_decrypt_ecb_command(int32_t argc, char* argv[]);
bool cryp_encrypt_cbc_command(int32_t argc, char* argv[]);
bool cryp_decrypt_cbc_command(int32_t argc, char* argv[]);
bool cryp_init_command(int32_t argc, char* argv[]);
bool cryp_diag_command(int32_t argc, char* argv[]);

#define CRYP_COMMANDS                                                                                                       \
		CRYP_CUSTOM_COMMANDS                                                                                                \
        SHELL_CMD("cryp_encrypt_ecb", "ecbe", cryp_encrypt_ecb_command, "CrypEncryptEcb"),                             \
        SHELL_CMD("cryp_decrypt_ecb", "ecbd", cryp_decrypt_ecb_command, "CrypDecryptEcb"),                             \
        SHELL_CMD("cryp_encrypt_cbc", "cbce", cryp_encrypt_cbc_command, "CrypEncryptCbc"),                             \
        SHELL_CMD("cryp_decrypt_cbc", "cbcd", cryp_decrypt_cbc_command, "CrypDecryptCbc"),                             \
        SHELL_CMD("cryp_init", "ci", cryp_init_command, "CrypInit"),                                                        \
        SHELL_CMD("cryp_diag", "cdi", cryp_diag_command, "CrypDiag"),

#ifdef __cplusplus
}
#endif

#endif /* CRYP_GENERAL_COMMANDS_H */
