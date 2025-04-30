#include "cryp_diag.h"

#include "cryp_drv.h"
#include "data_utils.h"
#include "table_utils.h"
#include "writer_config.h"

const char* CrypAlgo2Str(CrypAlgorithm_t Algo) {
    const char* name = "?";
    switch((uint32_t)Algo) {
    case CRYP_ALGO_AES:
        name = "Aes";
        break;
    case CRYP_ALGO_AES_ECB:
        name = "AesEcb";
        break;
    case CRYP_ALGO_AES_CBC:
        name = "AesCbc";
        break;
    case CRYP_ALGO_DES_ECB:
        name = "DesEcb";
        break;
    case CRYP_ALGO_DES_CBC:
        name = "DesCbc";
        break;
    case CRYP_ALGO_AES_CTR:
        name = "AesCtr";
        break;
    case CRYP_ALGO_AES_CCM:
        name = "AesCCm";
        break;
    case CRYP_ALGO_AES_GCM:
        name = "AesGcm";
        break;
    case CRYP_ALGO_AES_GCM_GMAC:
        name = "AesGcm";
        break;
    case CRYP_ALGO_TDES_ECB:
        name = "TDesEcb";
        break;
    case CRYP_ALGO_DES:
        name = "Des";
        break;
    }
    return name;
}

const char* AlgoImpl2Str(AlgImpl_t Algo) {
    const char* name = "?";
    switch((uint32_t)Algo) {
    case ALG_IMPL_SW:
        name = "Sw";
        break;
    case ALG_IMPL_HW:
        name = "Hw";
        break;
    }
    return name;
}

bool cryp_diag(void) {
    bool res = false;
    const table_col_t cols[] = {
        {8, "Algo"}, {7, "keySize"}, {7, "init"}, {7, "int"}, {7, "err"},

    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    CrypHandle_t* CrypNode = CrypGetNode(0);
    if(CrypNode) {
        cli_printf(TSEP);
        cli_printf(" %06s " TSEP, CrypAlgo2Str(CrypNode->algo));
        cli_printf(" %05u " TSEP, CrypNode->key_size);
        cli_printf(" %05u " TSEP, CrypNode->init_done);
        cli_printf(" %05u " TSEP, CrypNode->int_cnt);
        cli_printf(" %05u " TSEP, CrypNode->error_cnt);
        res = true;
        cli_printf(CRLF);
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
