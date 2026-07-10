ifneq ($(UDS_PRECONFIG_MK),Y)
    UDS_PRECONFIG_MK=Y
    UDS=Y
    # We can use and test UDS without ISO-TP
    #ISO_TP=Y
    PROTOCOLS=Y
    TIME=Y
    TRNG=Y
    CONNECTIVITY=Y
endif
