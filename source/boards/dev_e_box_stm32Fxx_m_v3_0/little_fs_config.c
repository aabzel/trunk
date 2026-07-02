#include "little_fs_config.h"

#include "data_utils.h"
#include "sw_nor_flash.h"
#include "log.h"

#ifdef LFS_NO_MALLOC
// Optional statically allocated read buffer.
// Must be cache_size.
// By default lfs_malloc is used to allocate this buffer.
static uint8_t StaticFileBuffer[LITTLE_FS_CACHE_SIZE] = {0};

static uint8_t readBuffer[LITTLE_FS_CACHE_SIZE] = {0};
static uint8_t progBuffer[LITTLE_FS_CACHE_SIZE] = {0};
static uint8_t lookaheadBuffer[LITTLE_FS_PAGE_SIZE] = {0};
#endif

static int FlashToLittleFsRet(bool res) {
    int ret = LFS_ERR_OK;
    if (false == res) {
        ret = LFS_ERR_CORRUPT;
    }
    return ret;
}

static int user_provided_block_device_prog(const struct lfs_config* c,
                                           lfs_block_t block,
                                           lfs_off_t off,
                                           const void* buffer,
                                           lfs_size_t size) {
    int ret = LFS_ERR_CORRUPT;
    bool res = false;
    LOG_NOTICE(LITTLE_FS, "Write,Block:%u,OffSet:%u,Size:%u", block, off, size);
    uint32_t phy_address = 0;
    phy_address = block * LITTLE_FS_BLOCK_SIZE + off;
    res = sw_nor_flash_write(LITTLE_FS_NOR_FLASH_NUM,
                             phy_address,
                             (uint8_t*) buffer,
                             size);
    ret = FlashToLittleFsRet(res);
    return ret;
}

static int user_provided_block_device_read(const struct lfs_config* c,
                                           lfs_block_t block,
                                           lfs_off_t off,
                                           void* buffer,
                                           lfs_size_t size) {
    int ret = 0;
    LOG_PARN(LITTLE_FS, "Read,Block:%u,OffSet:%u,Size:%u", block, off, size);
    uint32_t phy_address = 0;
    phy_address = block * LITTLE_FS_BLOCK_SIZE + off;
    bool res = sw_nor_flash_read(LITTLE_FS_NOR_FLASH_NUM,
                                 phy_address,
                                 (uint8_t*) buffer,
                                 (uint32_t) size);
    ret = FlashToLittleFsRet(res);
    return ret;
}

static int user_provided_block_device_erase(const struct lfs_config* c,
                                            lfs_block_t block) {
    int ret = LFS_ERR_CORRUPT;
    LOG_WARNING(LITTLE_FS, "EraseBlock:%u", block);
    uint32_t phy_address = block * LITTLE_FS_BLOCK_SIZE;
    bool res = sw_nor_flash_erase_mem(LITTLE_FS_NOR_FLASH_NUM,
                                      phy_address,
                                      LITTLE_FS_BLOCK_SIZE);
    ret = FlashToLittleFsRet(res);
    return ret;
}

static int user_provided_block_device_sync(const struct lfs_config* c) {
    int ret = LFS_ERR_OK;
    LOG_DEBUG(LITTLE_FS, "Sync");
    return ret;
}

static struct lfs_attr attrs={
        // 8-bit type of attribute, provided by user and used to
        // identify the attribute
        .type = 0,

        // Pointer to buffer containing the attribute
        .buffer = NULL,

        // Size of attribute in bytes, limited to LFS_ATTR_MAX
        .size = 0,
};

const LittleFsConfig_t LittleFsConfig[] = {
        {
          .num = 1,
          .valid = true,
          .name = "LittleFsForNVRAM",
          // Optional configuration provided during lfs_file_opencfg
          .file_config = {
                // Optional statically allocated file buffer. Must be cache_size.
                // By default lfs_malloc is used to allocate this buffer.
               .buffer= StaticFileBuffer,

                // Optional list of custom attributes related to the file. If the file
                // is opened with read access, these attributes will be read from disk
                // during the open call. If the file is opened with write access, the
                // attributes will be written to disk every file sync or close. This
                // write occurs atomically with update to the file's contents.
                //
                // Custom attributes are uniquely identified by an 8-bit type and limited
                // to LFS_ATTR_MAX bytes. When read, if the stored attribute is smaller
                // than the buffer, it will be padded with zeros. If the stored attribute
                // is larger, then it will be silently truncated. If the attribute is not
                // found, it will be created implicitly.

                // Custom attribute structure, used to describe custom attributes
                // committed atomically during file writes.
               .attrs = &attrs,

                // Number of custom attributes in the list
               .attr_count=0,
          },
          .cfg = {
                 // block device operations
              .read = user_provided_block_device_read,
              .prog = user_provided_block_device_prog,
              .erase =                user_provided_block_device_erase,
              .sync = user_provided_block_device_sync,
        #ifdef LFS_NO_MALLOC
              .read_buffer = readBuffer,
              .prog_buffer = progBuffer,
              .lookahead_buffer = lookaheadBuffer,
        #endif
              // block device configuration
              .read_size = LITTLE_FS_PAGE_SIZE,
              .prog_size = LITTLE_FS_PAGE_SIZE,
              .cache_size = LITTLE_FS_CACHE_SIZE,
              .lookahead_size = LITTLE_FS_PAGE_SIZE,
              .block_cycles = 4,
              .block_size = LITTLE_FS_BLOCK_SIZE,
              .block_count = 4,
        },
    },
};

LittleFsHandle_t LittleFsInstance[] = { { .num = 1, .valid = true, }, };

COMPONENT_GET_CNT(LittleFs, little_fs)


