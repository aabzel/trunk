#include "decadriver_diag.h"

#include "data_types.h"
#include "decadriver_config.h"
#include "decadriver_const.h"
#include "dw1000_const.h"
#include "log.h"
#include "timer_utils.h"

static bool decadriver_diagnostics_parse(dwt_rxdiag_t const* const diagnostics) {
    bool res = false;
    if(diagnostics) {
        LOG_INFO(DECA, "maxNoise %u", diagnostics->maxNoise);           // LDE max value of noise
        LOG_INFO(DECA, "firstPathAmp1 %u", diagnostics->firstPathAmp1); // Amplitude at floor(index FP) + 1
        LOG_INFO(DECA, "stdNoise %u", diagnostics->stdNoise);           // Standard deviation of noise
        LOG_INFO(DECA, "firstPathAmp2 %u", diagnostics->firstPathAmp2); // Amplitude at floor(index FP) + 2
        LOG_INFO(DECA, "firstPathAmp3 %u", diagnostics->firstPathAmp3); // Amplitude at floor(index FP) + 3
        LOG_INFO(DECA, "maxGrowthCIR %u", diagnostics->maxGrowthCIR);   // Channel Impulse Response max growth CIR
        LOG_INFO(DECA, "rxPreamCount %u", diagnostics->rxPreamCount);   // Count of preamble symbols accumulated
        LOG_INFO(DECA, "firstPath %u", diagnostics->firstPath); // First path index (10.6 bits fixed point integer)
        res = true;
    }
    return res;
}

bool decadriver_event_counters_parse(dwt_deviceentcnts_t const* const counters) {
    bool res = false;
    LOG_INFO(DECA, "NumOf Rx header errors %u", counters->PHE);          // number of received header errors
    LOG_INFO(DECA, "NumOf Rx frame sync loss events %u", counters->RSL); // number of received frame sync loss events
    LOG_INFO(DECA, "NumOf good CRC Rx frames %u", counters->CRCG);       // number of good CRC received frames
    LOG_INFO(DECA, "NumOf bad CRC (CRC error) Rx frames %u",
             counters->CRCB);                                         // number of bad CRC (CRC error) received frames
    LOG_INFO(DECA, "NumOf address filter errors %u", counters->ARFE); // number of address filter errors
    LOG_INFO(DECA, "NumOf receiver overflows  %u",
             counters->OVER);                              // number of receiver overflows (used in double buffer mode)
    LOG_INFO(DECA, "SFD timeouts %u", counters->SFDTO);    // SFD timeouts
    LOG_INFO(DECA, "Preamble timeouts %u", counters->PTO); // Preamble timeouts
    LOG_INFO(DECA, "RX frame wait timeouts %u", counters->RTO); // RX frame wait timeouts
    LOG_INFO(DECA, "NumOfTxFrames %u", counters->TXF);          // number of transmitted frames
    LOG_INFO(DECA, "half period warn %u", counters->HPW);       // half period warn
    LOG_INFO(DECA, "power up warn %u", counters->TXW);          // power up warn

    return res;
}

bool decadriver_diag(DecaDriverInstance_t* const Node) {
    bool res = false;

    if(Node) {
        LOG_INFO(DECA, "RxCnt %u TxCnt", Node->rx_cnt, Node->tx_cnt);
        Type64Union_t un64;
        un64.u64 = 0;
        dwt_geteui(un64.u8);
        Node->eui = un64.u64;
        LOG_INFO(DECA, "EUI 0x%llx", un64.u64);

        dwt_readsystime((uint8*)&Node->sys_time);
        Node->sys_time_s = timer_2_seconds(Node->sys_time, DW1000_SYS_CLOCK_FREQ_HZ);

        LOG_INFO(DECA, "SysTime %llu=%f s", Node->sys_time, Node->sys_time_s);

        Node->xtal_trim = dwt_getxtaltrim();
        LOG_INFO(DECA, "XTAL TRIM 0x%x", Node->xtal_trim);
        LOG_INFO(DECA, "ProcCnt %u", Node->proc_cnt);

        Node->part_id = dwt_getpartid();
        LOG_INFO(DECA, "PartId 0x%x", Node->part_id);

        Node->lot_id = dwt_getlotid();
        LOG_INFO(DECA, "LotId 0x%x", Node->lot_id);

        Node->icref_volt = dwt_geticrefvolt();
        LOG_INFO(DECA, "IcRefVolt 0x%x", Node->icref_volt);

        Node->icref_temp = dwt_geticreftemp();
        LOG_INFO(DECA, "IcRefTemp 0x%x", Node->icref_temp);

        Node->dev_id = dwt_readdevid();
        LOG_INFO(DECA, "DevId 0x%x", Node->dev_id);

        dwt_readtxtimestamp((uint8*)&Node->tx_time_stamp);
        LOG_INFO(DECA, "TxTimeStamp 0x%llx", Node->tx_time_stamp);

        dwt_readrxtimestamp((uint8*)&Node->rx_time_stamp);
        LOG_INFO(DECA, "RxTimeStamp 0x%llx", Node->rx_time_stamp);

        Node->tx_time_stamp_hi32 = dwt_readtxtimestamphi32();
        LOG_INFO(DECA, "TxTimeStampHi32 0x%x", Node->tx_time_stamp_hi32);

        Node->rx_time_stamp_hi32 = dwt_readrxtimestamphi32();
        LOG_INFO(DECA, "RxTimeStampHi32 0x%x", Node->rx_time_stamp_hi32);

        dwt_readdiagnostics(&Node->diagnostics);
        decadriver_diagnostics_parse(&Node->diagnostics);

        dwt_readeventcounters(&Node->counters);
        decadriver_event_counters_parse(&Node->counters);

        Node->temp_vbat.word = dwt_readtempvbat(SPI_RATE_SLOW);
        LOG_INFO(DECA, "Vbat %u", Node->temp_vbat.voltage);
        LOG_INFO(DECA, "Temperature %u", Node->temp_vbat.temperature);

        Node->wakeup_temp = dwt_readwakeuptemp();
        LOG_INFO(DECA, "WakeupTemp %u", Node->wakeup_temp);

        Node->wakeup_vbat = dwt_readwakeupvbat();
        LOG_INFO(DECA, "WakeupVbat %u", Node->wakeup_vbat);

        Node->carrier_integrator = dwt_readcarrierintegrator();
        LOG_INFO(DECA, "CarrierIntegrator %d", Node->carrier_integrator);

        res = true;
    } else {
        LOG_ERROR(DECA, "NodeErr");
    }
    return res;
}

const char* DecaErrToStr(int ret) {
    const char* name = "";
    switch(ret) {

    case DWT_SUCCESS:
        name = "Ok";
        break;
    case DWT_ERROR:
        name = "Err";
        break;
    }
    return name;
}
