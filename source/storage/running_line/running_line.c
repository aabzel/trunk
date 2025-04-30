#include "running_line.h"

#include <stdio.h>
#include <string.h>

#include "code_generator.h"
#include "log.h"
#include "time_mcal.h"

COMPONENT_GET_NODE(RunningLine, running_line)
COMPONENT_GET_CONFIG(RunningLine, running_line)

const char* running_line_get_text(uint8_t num) {
    char* text = "";
    RunningLineHandle_t* Node = RunningLineGetNode(num);
    if(Node) {
        if(Node->WindowText) {
            text = Node->WindowText;
        }
    }
    return text;
}

bool running_line_build_linked_list_ll(RunningLineHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->len = strlen(Node->Text);
            LOG_DEBUG(RUNNING_LINE, "[%s],len:%u", Node->Text, Node->len);
            //Node->i_start = 0;
            // len = 5
            //        Hello
            // cur_i  01234
            // next_i 12340
            uint32_t i = 0;
            Node->Symbol[Node->len - 1].next_i = 0;
            for(i = 0; i < Node->size; i++) {
                Node->Symbol[i].letter = Node->Text[i];
                // Node->Symbol[i].cur_i = i;
                if(i < (Node->len - 1)) {
                    Node->Symbol[i].next_i = i + 1;
                    res = true;
                }
            }

    }
    return res;
}

bool running_line_set_text(uint8_t num, const char* const text) {
    bool res = false;
    RunningLineHandle_t* Node = RunningLineGetNode(num);
    if(Node) {
        if(Node->Text) {
            if(text) {
                size_t len=strlen(text);
                if(len < Node->size){
                } else {
                    LOG_ERROR(RUNNING_LINE,"%u,NoMem,Need:%u,max%u",num,len,Node->size);
                    len=Node->size-1;
                    res = false;
                }
                memset(Node->Text,0, Node->size);
                memcpy(Node->Text, text,len);
                res = running_line_build_linked_list_ll(Node);
            }
        }
    }
    return res;
}

bool running_line_add_suffix(uint8_t num, const char* const suffix) {
    bool res = false;
    RunningLineHandle_t* Node = RunningLineGetNode(num);
    if(Node) {
        snprintf(Node->Text, Node->size, "%s%s", Node->Text, suffix);
        res = running_line_build_linked_list_ll(Node);
    }
    return res;
}

bool running_line_add_prefix(uint8_t num, const char* const prefix) {
    bool res = false;
    RunningLineHandle_t* Node = RunningLineGetNode(num);
    if(Node) {
        snprintf(Node->Text, Node->size, "%s%s", prefix, Node->Text);
        res = running_line_build_linked_list_ll(Node);
    }
    return res;
}

static bool running_line_init_custom(void) {
    bool res = true;
    return res;
}

static bool running_line_is_valid_config(const RunningLineConfig_t* const Config) {
    bool res = false;
    if(Config) {
        if(Config->Text) {
            if(0 < Config->size) {
                if(Config->duration_ms) {
                    if(Config->WindowText) {
                        if(Config->window_size) {
                        	  if(Config->Symbol) {
                                 res = true;
                        	  }
                        }
                    }
                }

            }
        }
    }
    return res;
}

static bool running_line_proc_one(uint8_t num) {
    bool res = false;
    RunningLineHandle_t* Node = RunningLineGetNode(num);
    if(Node) {
        uint32_t up_time_ms = time_get_ms32();
        if(Node->next_update_time_ms < up_time_ms) {
            Node->i_start++;
            Node->len = strlen(Node->Text);
            if(Node->len <= Node->i_start) {
                Node->i_start = 0;
            }

            uint32_t phy_i = Node->i_start;
            uint32_t k = 0;

            for(k = 0; k < Node->window_size; k++) {
                Node->WindowText[k] = Node->Symbol[phy_i].letter;
                phy_i = Node->Symbol[phy_i].next_i;
            }
            Node->next_update_time_ms = up_time_ms + Node->duration_ms;
            LOG_DEBUG(RUNNING_LINE, "[%s],len:%u", Node->WindowText, Node->window_size);
        }
    }
    return res;
}

static bool running_line_init_common(const RunningLineConfig_t* const Config, RunningLineHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->duration_ms = Config->duration_ms;
            Node->num = Config->num;
            Node->Symbol = Config->Symbol;
            Node->Text = Config->Text;
            Node->size = Config->size;
            Node->WindowText = Config->WindowText;
            Node->window_size = Config->window_size;
            Node->valid = true;
            Node->i_start = 0;
            memset(Node->WindowText, 0, Node->window_size);
            res = true;
        }
    }
    return res;
}

bool running_line_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(RUNNING_LINE, "Init %u", num);
    const RunningLineConfig_t* Config = RunningLineGetConfig(num);
    if(Config) {
#if HAS_RUNNING_LINE_DIAG
        LOG_WARNING(RUNNING_LINE, "%s", RunningLineConfigToStr(Config));
#endif
        res = running_line_is_valid_config(Config);
        if(res) {
            RunningLineHandle_t* Node = RunningLineGetNode(num);
            if(Node) {
                res = running_line_init_common(Config, Node);
                res = running_line_build_linked_list_ll(Node);
                uint32_t up_time_ms = time_get_ms32();
                Node->next_update_time_ms = up_time_ms + Node->duration_ms;
                LOG_INFO(RUNNING_LINE, "%u,InitOk", num);
                res = true;
            }
        }
    }

    return res;
}

COMPONENT_INIT_PATTERT(RUNNING_LINE, RUNNING_LINE, running_line)
COMPONENT_PROC_PATTERT(RUNNING_LINE, RUNNING_LINE, running_line)
