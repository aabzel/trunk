#include "wav_diag.h"

#include <stdio.h>
#include <string.h>

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif
#include "array_diag.h"
#include "log.h"
#include "macro_utils.h"
#include "utils_math.h"
#include "wav.h"

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

const char* WavHandleToStr(const WavHandle_t* const Handle) {
    static char lText[350] = "";
    if(Handle) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sSampleCnt:%u,", lText, Handle->sample_cnt);
        snprintf(lText, sizeof(lText), "%sSampleTime:%s s,", lText, DoubleToStr(Handle->sample_time_s));
        snprintf(lText, sizeof(lText), "%sPlayDir:%f s", lText, Handle->duration_s);
    }
    return lText;
}

const char* WavHeaderToStr(const WavHeader_t* const Header) {
    static char lText[350] = "";
    if(Header) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sChunkId:%s,", lText, ArrayToAsciiStr((uint8_t*)&Header->chunkId, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sChunkSize:%u Byte,", lText, Header->chunkSize);
        snprintf(lText, sizeof(lText), "%sFormat:%s,", lText, ArrayToAsciiStr((uint8_t*)&Header->format, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sSubchunk1Id:%s,", lText,
                 ArrayToAsciiStr((uint8_t*)&Header->subchunk1Id, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sSubchunk1Size:%u,", lText, Header->subchunk1Size);
        snprintf(lText, sizeof(lText), "%sAudioFormat:0x%04x,", lText, Header->audioFormat);
        snprintf(lText, sizeof(lText), "%sNumChannels:%u,", lText, Header->numChannels);
        snprintf(lText, sizeof(lText), "%sSampleRate:%u Hz,", lText, Header->sampleRate);
        snprintf(lText, sizeof(lText), "%sByteRate:%u Byte,", lText, Header->byteRate);
        snprintf(lText, sizeof(lText), "%sBlockAlign:%u Byte,", lText, Header->blockAlign);
        snprintf(lText, sizeof(lText), "%sBitsPerSample:%u bit,", lText, Header->bitsPerSample);
        snprintf(lText, sizeof(lText), "%sSubchunk2Id:%s,", lText,
                 ArrayToAsciiStr((uint8_t*)&Header->subchunk2Id, 4)); // ASCII
        snprintf(lText, sizeof(lText), "%sDataSize:%u Byte", lText, Header->subchunk2Size);
    }
    return lText;
}
