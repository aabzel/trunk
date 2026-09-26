#include "wav_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "float_diag.h"
#include "log.h"
#include "macro_utils.h"
#include "utils_math.h"
#include "wav.h"

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

bool WavHeaderToFileName(const WavHeader_t* const Header, char* const file_name, uint32_t size) {
    bool res = false;
    if(Header) {
        if(file_name) {
            strcpy(file_name, "");
            snprintf(file_name, size, "%sCH%u_", file_name, Header->numChannels);
            snprintf(file_name, size, "%sF%uHz_", file_name, Header->sampleRate);
            snprintf(file_name, size, "%sB%ubit_", file_name, Header->bitsPerSample);
            snprintf(file_name, size, "%sSZ%uByte.wav", file_name, Header->subchunk2Size);
            res = true;
        }
    }
    return res;
}

const char* WavInfoToStr(const WavInfo_t* const Info) {
    static char lText[350] = {0};
    strcpy(lText, "");
    if(Info) {
        snprintf(lText, sizeof(lText), "%sChannels:%u,", lText, Info->channels);
        snprintf(lText, sizeof(lText), "%sSampleCnt:%u,", lText, Info->sample_cnt);
        snprintf(lText, sizeof(lText), "%sSampleTime:%s s,", lText, FloatToStr(Info->sample_time_s, 3));
        snprintf(lText, sizeof(lText), "%sPlayDir:%f s", lText, Info->duration_s);
        snprintf(lText, sizeof(lText), "%sFS:%u Hz", lText, Info->sampling_frequency_hz);
        snprintf(lText, sizeof(lText), "%sDataSize:%u Byte", lText, Info->data_size);
    }
    return lText;
}

const char* WavNodeToStr(const WavHandle_t* const Node) {
    static char lText[350] = "";
    if(Node) {
        strcpy(lText, "WAVnode:");
        // snprintf(lText, sizeof(lText), "%sDuration:%s s", lText, FloatToStr(Node->duration_s, 3));

        snprintf(lText, sizeof(lText), "%sDuration:%5.2f s,", lText, Node->duration_s);

        snprintf(lText, sizeof(lText), "%sCH:%u,", lText, Node->channels);
        snprintf(lText, sizeof(lText), "%sFS:%u Hz,", lText, Node->sampling_frequency_hz);
        snprintf(lText, sizeof(lText), "%sFILEnum:%u,", lText, Node->file_num);
        snprintf(lText, sizeof(lText), "%sFileName:[%s],", lText, Node->fileName);
        snprintf(lText, sizeof(lText), "%sSampleCnt:%u,", lText, Node->sample_cnt);
        snprintf(lText, sizeof(lText), "%sSampleTime:%s s,", lText, FloatToStr(Node->sample_time_s, 2));
    }
    return lText;
}

const char* WavHeaderToStr(const WavHeader_t* const Header) {
    static char lText[350] = "";
    if(Header) {
        float sample_time_s = 1.0f / ((float)Header->sampleRate);
        uint32_t sample_cnt = Header->subchunk2Size / Header->blockAlign;
        float duration_s = sample_time_s * ((float)sample_cnt);

        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sDuration:%5.2f s,", lText, duration_s);
        snprintf(lText, sizeof(lText), "%sSamples:%u,", lText, sample_cnt);
        snprintf(lText, sizeof(lText), "%sChunkId:%s,", lText, ArrayToAsciiStr((uint8_t*)&Header->chunkId, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sChunkSize:%u Byte,", lText, Header->chunkSize);
        snprintf(lText, sizeof(lText), "%sFormat:%s,", lText, ArrayToAsciiStr((uint8_t*)&Header->format, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sSubchunk1Id:%s,", lText,
                 ArrayToAsciiStr((uint8_t*)&Header->subchunk1Id, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sSubchunk1Size:%u," CRLF, lText, Header->subchunk1Size);
        snprintf(lText, sizeof(lText), "%sAudioFormat:0x%04x,", lText, Header->audioFormat);
        snprintf(lText, sizeof(lText), "%sNumChannels:%u,", lText, Header->numChannels);
        snprintf(lText, sizeof(lText), "%sSampleRate:%u Hz,", lText, Header->sampleRate);
        snprintf(lText, sizeof(lText), "%sByteRate:%u Byte,", lText, Header->aver_bytes_per_sec);
        snprintf(lText, sizeof(lText), "%sBlockAlign:%u Byte,", lText, Header->blockAlign);
        snprintf(lText, sizeof(lText), "%sBitsPerSample:%u bit,", lText, Header->bitsPerSample);
        snprintf(lText, sizeof(lText), "%sSubchunk2Id:%s,", lText,
                 ArrayToAsciiStr((uint8_t*)&Header->subchunk2Id, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sDataSize:%u Byte", lText, Header->subchunk2Size);
    }
    return lText;
}
