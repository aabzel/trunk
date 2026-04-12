#include "string_reader.h"

#include <stdlib.h>
#include <string.h>
#ifdef HAS_MINGW
#include <conio.h> /*for kbhit getch function. Clang/cygwin64 build error*/
#endif

#include "array.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "convert.h"
#include "log.h"
#include "terminal_codes.h"
#include "writer.h"

#ifdef HAS_AUTO_EXIT
#include "auto_exit.h"
#endif

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

#ifdef HAS_CLI
#include "cli_drv.h"
#endif

/* const StringReaderConfig_t* StringReaderGetConfig(uint8_t num); */
COMPONENT_GET_CONFIG(StringReader, string_reader)

/* StringReaderHandle_t* StringReaderGetNode(uint8_t num) */
COMPONENT_GET_NODE(StringReader, string_reader)

static bool string_reader_init_custom(void) {
    bool res = true;
    return res;
}

_WEAK_FUN_ bool string_reader_proc_custom(void) {
    bool res = true;
    return res;
}

StringReaderHandle_t* StringReaderInterfaceToNode(const InterfaceType_t interface_if) {
    StringReaderHandle_t* Node = NULL;
    uint32_t cnt = string_reader_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(StringReaderInstance[i].valid) {
            if(interface_if.word == StringReaderInstance[i].interface_if.word) {
                Node = &StringReaderInstance[i];
            }
        }
    }
    return Node;
}

/*called from ISR*/
bool string_reader_rx_character(StringReaderHandle_t* Node, char character) {
    bool res = false;
    if(Node) {
        res = fifo_push(&Node->fifo, character);
        if(false == res) {
            Node->lost_char_count++;
        }
    }
    return res;
}

/*called from ISR*/
bool string_reader_rx_byte(const InterfaceType_t interface_if, uint8_t rx_byte) {
    bool res = false;
    writer_interface_set(interface_if);
    StringReaderHandle_t* Node = StringReaderInterfaceToNode(interface_if);
    if(Node) {
        res = string_reader_rx_character(Node, (char)rx_byte);
    }
    return res;
}

bool string_reader_proc_rx_byte(uint8_t num, uint8_t rx_byte) {
    bool res = false;
    StringReaderHandle_t* Node = StringReaderGetNode(num);
    if(Node) {
        LOG_DEBUG(STRING_READER, "SR_%u,RxByte:0x%x=[%c]", num, rx_byte, rx_byte);
        res = string_reader_rx_character(Node, (char)rx_byte);
    }
    return res;
}

static const char StringReaderSpecialCharacters[] = {
    ' ',
    '{',
    '}',
    '[',
    ']',
    '>',
    '<',
    '(',
    ')',
    '.',
    '@',
    '#',
    '^',
    '%',
    '$',
    ',',
    '"',
    ':',
    ';',
    '_',
    '-',
    '|',
    '\\',
    '/',
    '~',
    '&',
    '!',
    '?',
    ASCII_ESC,
    ASCII_TAB,
    ASCII_BACKSPACE,
    ASCII_ENTER,
    ASCII_LINE_FEED,
    0,
    '+',
    '=',
    '*',
};

/*TODO test it*/
static bool string_reader_is_valid_char(char character) {
    bool res = false;
    res = is_hex_digit(character);
    if('a' <= character) {
        if(character <= 'z') {
            res = true;
        }
    }
    if('A' <= character) {
        if(character <= 'Z') {
            res = true;
        }
    }

    if(false == res) {
        uint32_t size = ARRAY_SIZE(StringReaderSpecialCharacters);
        res = array_is_exist(character, StringReaderSpecialCharacters, size);
    }
    return res;
}

static bool string_reader_writer_ctrl(StringReaderHandle_t* Node, bool on_off) {
    bool res = true;
    if(on_off) {
        res = writer_interface_set(Node->interface_if);
    } else {
        curWriterPtr = writer_set_default();
    }
    return res;
}

static bool string_reader_echo_putchar(StringReaderHandle_t* Node, char ch) {
    bool res = true;
    res = string_reader_is_valid_char(ch);
    if(res) {
    } else {
        LOG_ERROR(STRING_READER, "UndefChar:0x%x=(%c)", ch, ch);
        // ch = '?';
    }

    res = writer_interface_set(Node->interface_if);

    if(Node->secure_echo) {
        ch = '*';
    }

    if(curWriterPtr) {
        if(curWriterPtr->stream.f_putch) {
            curWriterPtr->stream.f_putch(&curWriterPtr->stream, ch);
        }
    }
#if 0

#ifdef HAS_USB
    if(IF_USB_HID != Node->interface_if) {
        cli_putstr(VT_SETCOLOR_NORMAL);
    }
#else
    cli_putstr(VT_SETCOLOR_NORMAL);
#endif

    curWriterPtr = &dbg_o;
#endif
    return res;
}

#ifdef HAS_READER_CMD_HISTORY
static Arrow_t sr_arrows_parse(StringReaderHandle_t* Node, char cur_char) {
    Arrow_t arrow = ARROW_UNDEF;
    if(0x41 == cur_char) {                     // A
        if(0x5B == Node->prev_char) {          //[
            if(0x1B == Node->prev_prev_char) { // ESC
                arrow = ARROW_UP;
            }
        }
    }
    Node->prev_prev_char = Node->prev_char;
    Node->prev_char = cur_char;
    return arrow;
}
#endif

static bool string_reader_proc_enter(StringReaderHandle_t* const Node) {
    bool res = false;
    LOG_DEBUG(STRING_READER, "Enter");
    if(Node->echo) {
        cli_putstr(CRLF);
    }
    Node->string[Node->string_len] = 0;
    Node->total_string_count++;

    string_reader_writer_ctrl(Node, true);
    char tonen[300] = {0};
    strcpy(tonen, (char*)Node->string);
    strcpy((char*)Node->string, "");
    /* can be non return */
    res = cli_process_cmd(Node->cli_num, tonen);
    string_reader_writer_ctrl(Node, false);
    if(res) {
        memset(Node->string, 0, Node->string_size);
        strncpy(Node->prev_cmd, (char*)Node->string, sizeof(Node->prev_cmd));
    }
    Node->string_len = 0;
    Node->string[0] = 0;
    return res;
}

bool string_reader_proc_one(uint8_t num) {
    bool res = false;

    StringReaderHandle_t* Node = StringReaderGetNode(num);
    if(Node) {
#ifdef HAS_PC
        // int character = getch();
        int is_pressed = 0;
        is_pressed = kbhit(); /*Works with MinGW (32bit)*/
        if(is_pressed) {
            char key_char = _getch();
            LOG_DEBUG(STRING_READER, "Rx:0x%x=%u=[%c]", key_char, key_char, key_char);
            res = string_reader_rx_character(Node, key_char);
        }
#endif /*HAS_PC*/

        while(1) {
            uint32_t size = 0, i = 0;
            uint8_t data[100] = "";
            fifo_pull_array(&Node->fifo, data, sizeof(data), &size);
            if(size) {
#ifdef HAS_AUTO_EXIT
                auto_exit_postone();
#endif
                LOG_DEBUG(STRING_READER, "Rx:%u bytes", size);
#ifdef HAS_LED_MONO
                if(Node) {
                    res = led_mono_blink(Node->feedback_led, 50);
                }
#endif
                res = writer_interface_set(Node->interface_if);
            } else {
                break;
            }

            Arrow_t arr = ARROW_UNDEF;

            for(i = 0; i < size; i++) {
#ifdef HAS_AUTO_EXIT
                auto_exit_postone();
#endif
                char character = data[i];
                if(character) {

                    // LOG_DEBUG(STRING_READER, "Proc:Char:0x%x=%u=[%c]", character, character, character);
                    Node->tx_cnt++;
#ifdef HAS_READER_CMD_HISTORY
                    arr = sr_arrows_parse(Node, character);
                    if(ARROW_UP == arr) {
                        cli_printf("%s", Node->prev_cmd);
                        strncpy((char*)Node->string, (char*)Node->prev_cmd, Node->string_size);
                        Node->string_len = 0;
                        character = 0x00;
                    }
#endif

                    // LOG_INFO(STRING_READER,"NotEnter");
                    if(Node->echo) {
                        if(ARROW_UP != arr) {
                            string_reader_echo_putchar(Node, character);
                        }
                    }
                    switch(character) {
                    case KEY_BACKSPACE: // ASCII_BACKSPACE
                        LOG_DEBUG(STRING_READER, "Back");
                        if(Node->string_len) {
                            Node->string[Node->string_len] = 0;
                            Node->string_len--;
                        }
                        if(Node->echo) {
                            cli_putchar(' ');
                            cli_putchar('\b');
                        }
                        break;
                    case KEY_TAB:
                        Node->string_len = 0;
                        LOG_DEBUG(STRING_READER, "TAB");
                        res = cli_cmd_list_print(1, "", "");
                        /*TAB*/
                        break;
                    case KEY_ESC:
                        Node->string_len = 0;
                        LOG_DEBUG(STRING_READER, "Esc");
#ifdef HAS_PC
                        LOG_WARNING(STRING_READER, "TerminateProccess");
                        exit(-1);
#endif
                        break;
                    case KEY_LINE_FEED: //'\n'://
                    case KEY_ENTER:     //'\r'://
                        res = string_reader_proc_enter(Node);
                        break;
                    default:
                        if(Node->string_len < Node->string_size) {
                            // LOG_DEBUG(STRING_READER, "AddChar %c", character);
                            Node->string[Node->string_len] = character;
                            Node->string_len++;
                        } else {
                            // LOG_ERROR(STRING_READER, "LostChar");
                            Node->lost_char_count++;
                        }
                        break;
                    }
#ifdef HAS_STRING_READER_DIAG
                    LOG_DEBUG(STRING_READER, "%s", StringReaderNodeToStr(Node));
#endif
                } //  if(character)
            }     // for(i = 0; i < size; i++)
        }         // while(1) {
    }

    return res;
}

static bool string_reader_init_chache(const StringReaderConfig_t* const Config, StringReaderHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->callback = Config->callback;
            Node->cli_num = Config->cli_num;
            Node->core = Config->core;
            Node->echo = Config->echo;
            Node->fifo_heap = Config->fifo_heap;
            Node->fifo_heap_size = Config->fifo_heap_size;
            Node->feedback_led = Config->feedback_led;
            Node->interface_if = Config->interface_if;
            Node->name = Config->name;
            Node->num = Config->num;
            Node->string = Config->string;
            Node->string_size = Config->string_size;
            Node->secure_echo = Config->secure_echo;
            res = true;
        }
    }
    return res;
}

bool string_reader_secure_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    StringReaderHandle_t* Node = StringReaderGetNode(num);
    if(Node) {
        Node->secure_echo = on_off;
        res = true;
    }
    return res;
}

bool string_reader_reset_one(uint8_t num) {
    bool res = false;
    StringReaderHandle_t* Node = StringReaderGetNode(num);
    if(Node) {
        memset(Node->string, 0, Node->string_size);
        Node->string_len = 0;
        res = true;
    }
    return res;
}

bool string_reader_init_one(uint8_t num) {
    bool res = false;
    const StringReaderConfig_t* Config = StringReaderGetConfig(num);
    if(Config) {
#ifdef HAS_STRING_READER_DIAG
        LOG_WARNING(STRING_READER, "%s", StringReaderConfigToStr(Config));
#endif
        // res = StringReaderIsValidConfig(Config);
        StringReaderHandle_t* Node = StringReaderGetNode(num);
        if(Node) {
            res = string_reader_init_chache(Config, Node);
            Node->valid = true;
            Node->echo = true;
            Node->error_count = 0;
            Node->lost_char_count = 0;
            Node->tx_cnt = 0;
            Node->total_string_count = 0;
            res = fifo_init(&Node->fifo, Config->fifo_heap, Config->fifo_heap_size);
            LOG_WARNING(STRING_READER, "Init %u", num);
            log_level_get_set(STRING_READER, LOG_LEVEL_INFO);
            res = string_reader_reset_one(num);
        }
    }
    return res;
}

bool string_reader1_proc(void) {
    bool res = true;
    res = string_reader_proc_one(1);
    return res;
}

bool string_reader2_proc(void) {
    bool res = true;
    res = string_reader_proc_one(2);
    return res;
}

bool string_reader3_proc(void) {
    bool res = true;
    res = string_reader_proc_one(3);
    return res;
}

COMPONENT_PROC_PATTERT(STRING_READER, STRING_READER, string_reader)

COMPONENT_INIT_PATTERT(STRING_READER, STRING_READER, string_reader)
