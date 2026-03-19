#include "vector_cli.h"

#include "convert.h"
#include "log.h"
#include "vector_diagnostic.h"
/*
 */
STD_RESULT VECTOR_ReadVfromCli(const S32 argc,
                               char* argv[],
                               const S32 startArg,
                               VECTOR_F* const Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    bool res = false;
    U32 okCnt=0;

    if(startArg <= argc)
    {
        res = try_str2float(argv[startArg], &Node->dx);
        if(false == res)
        {
            LOG_ERROR(VECTOR, "ParseXerr [%s]", argv[startArg]);
        }
        else
        {
            okCnt++;
        }
    }

    if((startArg+1) <= argc)
    {
        res = try_str2float(argv[startArg+1], &Node->dy);
        if(false == res) {
            LOG_ERROR(VECTOR, "ParseYerr [%s]", argv[startArg+1]);
        }
        else
        {
            okCnt++;
        }
    }

    if((startArg+2) <= argc)
    {
        res = try_str2float(argv[startArg+2], &Node->dz);
        if(false == res) {
            LOG_ERROR(VECTOR, "ParseZerr [%s]", argv[startArg+2]);
        }
        else
        {
            okCnt++;
        }
    }



    if(3==okCnt)
    {
        LOG_INFO(VECTOR, "ReadOk:%s",VECTOR_fToStr(Node));
        ret = RESULT_OK;
    }
    else
    {
        LOG_ERROR(VECTOR, "ReadFromCliErr");
        ret = RESULT_NOT_OK;
    }

    return ret;
}
