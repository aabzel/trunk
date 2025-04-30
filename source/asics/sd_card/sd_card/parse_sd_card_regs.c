#include "parse_sd_card_regs.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "convert.h"
#include "sd_card_bits_offsets.h"
#include "str_ops.h"
#include "utils.h"

uint8_t procRegCnd = 0;

SdReg32bit_t SdCardRegMap[NUM_OF_REGISTERS + 1] = {0};

bool init_reg_map(void) {
  bool res = false;
  SdCardRegMap[0].reg8BitAddr = REG_SSR;
  SdCardRegMap[0].regName = "SD Status";
  SdCardRegMap[0].reg_bitness = 512;

  SdCardRegMap[1].reg8BitAddr = REG_CID;
  SdCardRegMap[1].regName = "Card ID";
  SdCardRegMap[1].reg_bitness = 128;

  SdCardRegMap[2].reg8BitAddr = REG_CSD;
  SdCardRegMap[2].regName = "Card specific data";
  SdCardRegMap[2].reg_bitness = 128;

  SdCardRegMap[3].reg8BitAddr = REG_SCR;
  SdCardRegMap[3].regName = "Card specific data";
  SdCardRegMap[3].reg_bitness = 64;

  SdCardRegMap[4].reg8BitAddr = REG_CSR;
  SdCardRegMap[4].regName = "Card Status Register";
  SdCardRegMap[4].reg_bitness = 32;

  SdCardRegMap[5].reg8BitAddr = REG_OCR;
  SdCardRegMap[5].regName = "Operation Conditions Register";
  SdCardRegMap[5].reg_bitness = 32;

  SdCardRegMap[6].reg8BitAddr = REG_DSR;
  SdCardRegMap[6].regName = "Drive stage register";
  SdCardRegMap[6].reg_bitness = 16;

  SdCardRegMap[7].reg8BitAddr = REG_RCA;
  SdCardRegMap[7].regName = "relative card address";
  SdCardRegMap[7].reg_bitness = 16;

  return res;
}
static char *sd_card_reg_name(uint8_t reg) {
  for (int i = 0; i < NUM_OF_REGISTERS; i++) {
    if (reg == SdCardRegMap[i].reg8BitAddr) {
      if (NULL != SdCardRegMap[i].regName) {
        return SdCardRegMap[i].regName;
      }
    }
  }
  return "undef";
}





#define NUM_BIT_CSD 128U
#define NUM_BYTE_CSD (NUM_BIT_CSD / 8U)
// 5.3.3
// 400e00325b5900001da77f800a40002dc609
static bool parse_sd_card_card_specific_data_register_v2_49h(
    uint8_t *reg_array_blob, uint16_t reg_blob_len, FILE *out_file_prt,
    uint8_t reg8bitAddr) {
  bool res = false;
  if (0x49 == reg8bitAddr) {
    res = true;
    SdReg32bit_t *item = get_reg_item_by_reg_addr(reg8bitAddr);

    fprintf(out_file_prt, "\n%s() [%s] reg %x reg blob len: %u", __FUNCTION__,
            item->regName, reg8bitAddr, reg_blob_len);

    // res = print_mem_horisonal(out_file_prt, reg_array_blob, reg_blob_len,
    // false);

    uint8_t sd_scruct =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 127, 126);
    fprintf(out_file_prt,
            "\n0x7A: byte %u bit 127-126:2b %u (0x%02x) SD_STRUCTURE ",
            (NUM_BIT_CSD - 127) / 8, sd_scruct, sd_scruct);

    uint8_t reserved8bit =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 125, 120);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 119-112:8b %u (0x%02x) TAAC ",
            (NUM_BIT_CSD - 119) / 8, reg_array_blob[1], reg_array_blob[1]);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 111-104:8b %u (0x%02x) NSAC ",
            (NUM_BIT_CSD - 111) / 8, reg_array_blob[2], reg_array_blob[2]);
    fprintf(out_file_prt,
            "\n0x7A: byte %u bit 103--96:8b %u (0x%02x) TRAN_SPEED ",
            (NUM_BIT_CSD - 103) / 8, reg_array_blob[3], reg_array_blob[3]);
    uint8_t card_cmd_class, block_len;
    uint16_t val16;
    memcpy(&val16, &reg_array_blob[4], 2);
    // fprintf(out_file_prt, "\n  0x7A: byte %u bit 95-80:16b %u (0x%04x)
    // ",(NUM_BIT_CSD-95)/8,  val16,val16);
    val16 = reverse_byte_order_uint16(val16);
    // fprintf(out_file_prt, "\n  0x7A: byte %u bit 95-80:16b %u (0x%04x)
    // ",(NUM_BIT_CSD-95)/8,  val16,val16);
    card_cmd_class = extract_subval_from_16bit(val16, 15, 4);
    block_len = extract_subval_from_16bit(val16, 3, 0);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 95-84:12b %u (0x%04x) CCC ",
            (NUM_BIT_CSD - 95) / 8, card_cmd_class, card_cmd_class);
    fprintf(out_file_prt,
            "\n0x7A: byte %u bit 83-80:4b %u (0x%01x) READ_BL_LEN",
            (NUM_BIT_CSD - 83) / 8, block_len, block_len);

    uint8_t read_bl_partial =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 79, 79);
    fprintf(out_file_prt,
            "\n0x7A: byte %u bit 79:1b %u (0x%01x) READ_BL_PERTIAL",
            (NUM_BIT_CSD - 79) / 8, read_bl_partial);

    uint8_t write_blk_misalign =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 78, 78);
    fprintf(out_file_prt,
            "\n0x7A: byte %u bit 78:1b %u (0x%01x) WRITE_BLK_MISALIGN",
            (NUM_BIT_CSD - 78) / 8, write_blk_misalign);

    uint8_t read_blk_misalign =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 77, 77);
    fprintf(out_file_prt,
            "\n0x7A: byte %u bit 77:1b %u (0x%01x) READ_BLK_MISALIGN",
            (NUM_BIT_CSD - 77) / 8, read_blk_misalign);

    uint8_t dsr_imp =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 76, 76);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 76:1b %u (0x%01x) DSR_IMP",
            (NUM_BIT_CSD - 76) / 8, dsr_imp);

    uint32_t c_size =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 75, 48);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 75-48:28b %u (0x%08x) C_SIZE",
            (NUM_BIT_CSD - 75) / 8, c_size, c_size);

    uint8_t res8 = eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 47, 47);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 47-47:1b %u res",
            (NUM_BIT_CSD - 47) / 8, res8);

    uint8_t erase_single_blk_en =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 46, 46);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 46-46:1b %u ERASE_BLK_EN",
            (NUM_BIT_CSD - 47) / 8, erase_single_blk_en);

    uint8_t erase_sector_size =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 45, 39);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 45-39:7b %u ERASE SECTOR_SIZE",
            (NUM_BIT_CSD - 47) / 8, erase_sector_size);

    uint8_t wp_group_size =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 38, 32);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 38-32:7b %u WP_GRP_SIZE",
            (NUM_BIT_CSD - 38) / 8, wp_group_size);

    uint8_t wp_group_en =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 31, 31);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 31:1b %u WP_GRP_ENABLE",
            (NUM_BIT_CSD - 31) / 8, wp_group_en);

    res8 = eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 30, 29);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 30-29:2b %u res",
            (NUM_BIT_CSD - 29) / 8, res8);

    uint8_t ws_factor =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 28, 26);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 28-26:3b %u R2W_FACTOR",
            (NUM_BIT_CSD - 28) / 8, ws_factor);

    uint8_t write_data_blk_len =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 25, 22);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 25-22:4b %u WRITE_BL_LEN",
            (NUM_BIT_CSD - 25) / 8, write_data_blk_len);

    uint8_t write_blk_part =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 21, 21);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 21:1b %u WRITE_BL_PARTIAL",
            (NUM_BIT_CSD - 21) / 8, write_blk_part);

    res8 = eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 20, 16);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 20-16:5b %u res",
            (NUM_BIT_CSD - 20) / 8, res8);

    uint8_t file_format_gr =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 15, 15);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 15:1b %u FILE_FORMAT_GRP",
            (NUM_BIT_CSD - 15) / 8, file_format_gr);

    uint8_t copy_flag =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 14, 14);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 14:1b %u COPY",
            (NUM_BIT_CSD - 14) / 8, copy_flag);

    uint8_t perm_write_prot =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 13, 13);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 13:1b %u PERM_WRITE_PROTECT",
            (NUM_BIT_CSD - 13) / 8, perm_write_prot);

    uint8_t temp_write_prot =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 12, 12);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 12:1b %u TMP_WRITE_PROTECT",
            (NUM_BIT_CSD - 12) / 8, temp_write_prot);

    uint8_t file_format =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 11, 10);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 11-10:2b %u FILE_FORMAT",
            (NUM_BIT_CSD - 11) / 8, file_format);

    res8 = eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 9, 8);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 9-8:2b %u reserved",
            (NUM_BIT_CSD - 9) / 8, res8);

    uint8_t crc = eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 7, 1);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 7-1:7b %u CRC",
            (NUM_BIT_CSD - 7) / 8, crc);

    uint8_t note_used =
        eject_value_from_array(reg_array_blob, NUM_BYTE_CSD, 0, 0);
    fprintf(out_file_prt, "\n0x7A: byte %u bit 0:1b %u Not used",
            (NUM_BIT_CSD - 0) / 8, note_used);
  }
  return res;
}

static char *calc_size_of_prot_area(uint32_t size_of_prot_area) {
  static char size_str[80] = "";
  snprintf(size_str, sizeof(size_str), "%u byte", size_of_prot_area);
  return size_str;
}

static char *au_size_str(uint8_t au_size) {
  static const char *au_size_str_out = "none";

  switch (au_size) {
  case 9:
    au_size_str_out = "4 MByte";
    break;
  default:
    au_size_str_out = "undef";
    break;
  }
  return au_size_str_out;
}

#define NUM_BIT_SD_STATUS 512U
// 4.10.2 SD Status
static bool parse_sd_status_register_4dh(uint8_t *reg_array_blob,
                                         uint16_t reg_blob_len,
                                         FILE *out_file_prt,
                                         uint8_t reg8bitAddr) {
  printf("\n%s reg 0x%02x", __FUNCTION__, reg8bitAddr);
  bool res = false;

  uint32_t reserved16bit = 0;
  uint32_t data_bus_width = 0;
  fprintf(out_file_prt, "\nSD Status");
  res = print_mem_horisonal(out_file_prt, reg_array_blob, reg_blob_len, false);

  data_bus_width = 0x03 & (reg_array_blob[0] >> 6);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 511-510:2b %u DAT_BUS_WIDTH",
          (NUM_BIT_SD_STATUS - 511) / 8, data_bus_width);

  uint8_t sc_mode = 0x01 & (reg_array_blob[0] >> 5);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 509:1b %u SECURED_MODE",
          (NUM_BIT_SD_STATUS - 509) / 8, sc_mode);

  memcpy(&reserved16bit, &reg_array_blob[2], 2);
  reserved16bit = reverse_byte_order_uint16(reserved16bit);
  reserved16bit = extract_subval_from_16bit(reserved16bit, 12, 6);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 508-502:7b %u Reserved",
          (NUM_BIT_SD_STATUS - 508) / 8, reserved16bit);

  uint8_t reserved8bit = 0x3F & reg_array_blob[1];
  fprintf(out_file_prt, "\n0x4D: byte %u bit 501-496:6b %u Reserved",
          (NUM_BIT_SD_STATUS - 501) / 8, reserved8bit);

  uint16_t sd_card_type = 0;
  memcpy(&sd_card_type, &reg_array_blob[2], 2);
  sd_card_type = reverse_byte_order_uint16(sd_card_type);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 495-480:16 %u (0x%04x) SD_CARD_TYPE",
          (NUM_BIT_SD_STATUS - 495) / 8, sd_card_type, sd_card_type);

  uint32_t size_of_prot_area = 0;
  memcpy(&size_of_prot_area, &reg_array_blob[4], 4);

  size_of_prot_area = reverse_byte_order_uint32(size_of_prot_area);

  fprintf(
      out_file_prt,
      "\n0x4D: byte %u bit 479-448:32 %u (0x%08x) SIZE_OF_PROTECTED_AREA %s ",
      (NUM_BIT_SD_STATUS - 479) / 8, size_of_prot_area, size_of_prot_area,
      calc_size_of_prot_area(size_of_prot_area));

  data_bus_width = eject_value_from_array(reg_array_blob, 64, 447, 440);

  uint8_t speed_class = reg_array_blob[8];

  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 447-440:8b %u (0x%02x) SPEED_CLASS",
          (NUM_BIT_SD_STATUS - 447) / 8, speed_class, speed_class);

  uint8_t performance_move = reg_array_blob[9];
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 439-432:8b %u (0x%02x) PERFORMANCE_MOVE",
          (NUM_BIT_SD_STATUS - 439) / 8, performance_move, performance_move);

  uint8_t au_size = eject_value_from_array(reg_array_blob, 64, 431, 428);

  fprintf(out_file_prt, "\n0x4D: byte %u bit 431-428:3b %u (0x%01x) AU_SIZE %s",
          (NUM_BIT_SD_STATUS - 431) / 8, au_size, au_size, "4");

  data_bus_width = eject_value_from_array(reg_array_blob, 64, 427, 424);

  fprintf(out_file_prt, "\n0x4D: byte %u bit 427-424:4b %u (0x%01x) Reserved",
          (NUM_BIT_SD_STATUS - 427) / 8, data_bus_width, data_bus_width);

  uint16_t erase_size = 0;
  memcpy(&erase_size, &reg_array_blob[11], 2);
  erase_size = reverse_byte_order_uint16(erase_size);
  fprintf(out_file_prt,
          "\n0x4D: byte %u   bit 423-408:16b %u (0x%04x) ERASE_SIZE allocation "
          "units AU",
          (NUM_BIT_SD_STATUS - 423) / 8, erase_size, erase_size);

  uint8_t erase_timeout = eject_value_from_array(reg_array_blob, 64, 407, 402);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 407-402:6b %u (0x%02x) ERASE_TIMEOUT ",
          (NUM_BIT_SD_STATUS - 407) / 8, erase_timeout, erase_timeout);

  uint8_t erase_offset = eject_value_from_array(reg_array_blob, 64, 401, 400);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 401-400:2b %u (0x%01x) ERASE_OFFSET ",
          (NUM_BIT_SD_STATUS - 401) / 8, erase_offset, erase_offset);

  uint8_t uhs_speed_grade =
      eject_value_from_array(reg_array_blob, 64, 399, 396);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 399-396:4b %u (0x%02x) UHS_SPEED_GRADE ",
          (NUM_BIT_SD_STATUS - 399) / 8, uhs_speed_grade, uhs_speed_grade);

  uint8_t uhs_au_size = eject_value_from_array(reg_array_blob, 64, 395, 392);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 395-392:4b %u (0x%02x) UHS_AU_SIZE ",
          (NUM_BIT_SD_STATUS - 395) / 8, uhs_au_size, uhs_au_size);

  uint8_t video_speed_class =
      eject_value_from_array(reg_array_blob, 64, 391, 384);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 391-384:8b %u (0x%02x) VIDEO_SPEED_CLASS ",
          (NUM_BIT_SD_STATUS - 391) / 8, video_speed_class, video_speed_class);

  uint8_t reserved = eject_value_from_array(reg_array_blob, 64, 383, 378);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 383-378:5b %u (0x%02x) reserved ",
          (NUM_BIT_SD_STATUS - 383) / 8, reserved, reserved);

  // vsc_au_size= eject_value_from_array(reg_array_blob,64, 377, 368);

  uint16_t vsc_au_size = 0;
  memcpy(&vsc_au_size, &reg_array_blob[16], 2);
  vsc_au_size = reverse_byte_order_uint16(vsc_au_size);
  vsc_au_size = extract_subval_from_16bit(vsc_au_size, 9, 0);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 377-368:10b %u (0x%04x) VSC_AU_SIZE",
          (NUM_BIT_SD_STATUS - 377) / 8, vsc_au_size, vsc_au_size);

  uint32_t sus_addr = 0;
  memcpy(&sus_addr, &reg_array_blob[18], 4);
  sus_addr = reverse_byte_order_uint32(sus_addr);
  sus_addr = extract_subval_from_32bit(sus_addr, 31, 10);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 367-346:22b %u (0x%08x) SUS_ADDR",
          (NUM_BIT_SD_STATUS - 367) / 8, sus_addr, sus_addr);

  memcpy(&reserved16bit, &reg_array_blob[20], 2);
  reserved16bit = reverse_byte_order_uint16(reserved16bit);
  reserved16bit = extract_subval_from_16bit(reserved16bit, 8, 4);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 345-340:6b %u (0x%02x) reserved ",
          (NUM_BIT_SD_STATUS - 345) / 8, reserved16bit, reserved16bit);

  uint8_t app_perf_class = eject_value_from_array(reg_array_blob, 64, 339, 336);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 339-336:4b %u (0x%01x) APP_PERF_CLASS",
          (NUM_BIT_SD_STATUS - 339) / 8, app_perf_class, app_perf_class);

  uint8_t performance_enhance =
      eject_value_from_array(reg_array_blob, 64, 335, 328);
  fprintf(out_file_prt,
          "\n0x4D: byte %u bit 335-328:8b %u (0x%02x) PERFORMANCE_ENHANCE",
          (NUM_BIT_SD_STATUS - 335) / 8, performance_enhance,
          performance_enhance);

  // 14 bit
  memcpy(&reserved16bit, &reg_array_blob[23], 2);
  reserved16bit = reverse_byte_order_uint16(reserved16bit);
  reserved16bit = extract_subval_from_16bit(reserved16bit, 16, 2);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 327-314:14b %u (0x%04x) reserved",
          (NUM_BIT_SD_STATUS - 327) / 8, reserved16bit, reserved16bit);

  uint8_t discard_support =
      eject_value_from_array(reg_array_blob, 64, 313, 313);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 313:1b %u DISCARD_SUPPORT",
          (NUM_BIT_SD_STATUS - 313) / 8, discard_support, discard_support);

  uint8_t fule_support = eject_value_from_array(reg_array_blob, 64, 312, 312);
  fprintf(out_file_prt, "\n0x4D: byte %u bit 312:1b %u FULE_SUPPORT",
          (NUM_BIT_SD_STATUS - 312) / 8, fule_support, fule_support);

  fprintf(out_file_prt, "\n0x4D: byte %u bit 311-0:312b 39 byte reserved",
          (NUM_BIT_SD_STATUS - 311) / 8);

  printf("\n%s reg 0x%02x done", __FUNCTION__, reg8bitAddr);

  return res;
}
// 0  1  2 3  4 5 6 7 8  9  10111213 14 15 16 1718
// fe 27_5048_5344344742_50_dad49145_0_119_77_852f
static bool parse_card_identification_register_4ah(uint8_t *reg_array_blob,
                                                   uint16_t reg_blob_len,
                                                   FILE *out_file_prt,
                                                   uint8_t reg8bitAddr) {
  bool res = false;
  if (out_file_prt) {
    res = true;
    fprintf(out_file_prt, "\n%s() reg %x reg blob len: %u", __FUNCTION__,
            reg8bitAddr, reg_blob_len);
    res =
        print_mem_horisonal(out_file_prt, reg_array_blob, reg_blob_len, false);
    res = parse_manufaturer_id(reg_array_blob[1], out_file_prt);
    fprintf(out_file_prt, "\nOEM/Application ID: %c%c", reg_array_blob[2],
            reg_array_blob[3]);

    fprintf(out_file_prt, "\nProduct name: %c%c%c%c%c", reg_array_blob[4],
            reg_array_blob[5], reg_array_blob[6], reg_array_blob[7],
            reg_array_blob[8]);

    fprintf(out_file_prt, "\nProduct revision: %u %c 0x%02x", reg_array_blob[9],
            reg_array_blob[9], reg_array_blob[9]);

    uint32_t psn_le;
    memcpy(&psn_le, &reg_array_blob[10], 4);
    fprintf(out_file_prt, "\nProduct serial number: 0x%08x or %c%c%c%c",
            reverse_byte_order_uint32(psn_le), reg_array_blob[10],
            reg_array_blob[11], reg_array_blob[12], reg_array_blob[13]);
    uint16_t mdt_le, mdt_be;
    memcpy(&mdt_le, &reg_array_blob[14], 2);
    mdt_be = reverse_byte_order_uint16(mdt_le);
    uint16_t year = extract_subval_from_16bit(mdt_be, 12, 4);
    // uint16_t year = extract_subval_from_16bit(mdt_be, 19, 12);
    uint16_t month = extract_subval_from_16bit(mdt_be, 3, 0);

    fprintf(out_file_prt, "\nManufacturing date YYM : %04x year %u month %u",
            mdt_be, year + 2000, month);

    fprintf(out_file_prt, "\nCRC7: %08x", 0x7F & (reg_array_blob[16] >> 1));
  }

  return res;
}

// OCR returns c0ff8000 1100_0000_1111_1111_1000_0000_0000_0000
static bool parse_sd_card_operation_conditions_register_7ah(
    uint32_t reg32_val, FILE *out_file_prt, uint8_t reg8bitAddr) {
  printf("\n%s 0x7A %08x %s", __FUNCTION__, reg32_val, utoa_bin32(reg32_val));
#ifdef DEBUG_SD_CARD
#endif
  bool res = false;
  if (0x7A == reg8bitAddr) {
    res = true;
    uint16_t reserved = extract_subval_from_32bit(reg32_val, 14, 0);
    fprintf(out_file_prt, "\n 0x%02x bit %u-%u: 0x%04x reverved ", reg8bitAddr,
            0, 14, reserved);

    uint32_t vdd_voltage_window = extract_subval_from_32bit(reg32_val, 23, 0);
    fprintf(out_file_prt, "\n 0x%02x bit %u-%u: 0x%04x  vdd voltage window ",
            reg8bitAddr, 0, 23, vdd_voltage_window);

    if ((1 << 15) == (reg32_val & (1 << 15))) {
      fprintf(out_file_prt, "\n 0x%02x bit 15: 1 2.7-2.8 V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 15: 0    ", reg8bitAddr);
    }
    if ((1 << 16) == (reg32_val & (1 << 16))) {
      fprintf(out_file_prt, "\n 0x%02x bit 16: 1 2.8-2.9 V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 16: 0    ", reg8bitAddr);
    }
    if ((1 << 17) == (reg32_val & (1 << 17))) {
      fprintf(out_file_prt, "\n 0x%02x bit 17: 1 2.9-3.0 V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 17: 0    ", reg8bitAddr);
    }
    if ((1 << 18) == (reg32_val & (1 << 18))) {
      fprintf(out_file_prt, "\n 0x%02x bit 18: 1 3.0-3.1 V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 18: 0    ", reg8bitAddr);
    }
    if ((1 << 19) == (reg32_val & (1 << 19))) {
      fprintf(out_file_prt, "\n 0x%02x bit 19: 1 3.1...3.2 V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 19: 0    ", reg8bitAddr);
    }
    if ((1 << 20) == (reg32_val & (1 << 20))) {
      fprintf(out_file_prt, "\n 0x%02x bit 20: 1 3.2...3.3 V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 20: 0    ", reg8bitAddr);
    }
    if ((1 << 21) == (reg32_val & (1 << 21))) {
      fprintf(out_file_prt, "\n 0x%02x bit 21: 1 3.3...3.4 V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 21: 0    ", reg8bitAddr);
    }
    if ((1 << 22) == (reg32_val & (1 << 22))) {
      fprintf(out_file_prt, "\n 0x%02x bit 22: 1 3.4...3.5V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 22: 0    ", reg8bitAddr);
    }
    if ((1 << 23) == (reg32_val & (1 << 23))) {
      fprintf(out_file_prt, "\n 0x%02x bit 23: 1 3.5...3.6V   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 23: 0    ", reg8bitAddr);
    }

    if ((1 << 24) == (reg32_val & (1 << 24))) {
      fprintf(out_file_prt, "\n 0x%02x bit 24: 1 Switching to 1.8V accepted  ",
              reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 24: 0 Switching to 1.8V rejected   ",
              reg8bitAddr);
    }

    reserved = extract_subval_from_32bit(reg32_val, 26, 25);
    fprintf(out_file_prt, "\n 0x%02x bit %u-%u: 0x%04x reverved ", reg8bitAddr,
            25, 26, reserved);

    if ((1 << 27) == (reg32_val & (1 << 27))) {
      fprintf(out_file_prt, "\n 0x%02x bit 27: 1 Over 2TB support Status CO2T",
              reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 27: 0 Over 2TB support Status CO2T",
              reg8bitAddr);
    }

    fprintf(out_file_prt, "\n 0x%02x bit 28: %u reserved  ", reg8bitAddr,
            (1 << 28) == (reg32_val & (1 << 28)));

    if ((1 << 29) == (reg32_val & (1 << 29))) {
      fprintf(out_file_prt, "\n 0x%02x bit 29: 1 UHS-II Card   ", reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 29: 0 Non UHS-II Card   ",
              reg8bitAddr);
    }
    if ((1 << 30) == (reg32_val & (1 << 30))) {
      fprintf(out_file_prt,
              "\n 0x%02x bit 30: 1 Card Capacity SDSC or SDXC. Ver2.00 High "
              "Capacity or Extended Capacity SD "
              "Memory Card ",
              reg8bitAddr);
    } else {
      fprintf(out_file_prt,
              "\n 0x%02x bit 30: 0 Card Capacity Status SDSC Standard Capacity "
              "SD Memory Card",
              reg8bitAddr);
    }
    if ((1 << 31) == (reg32_val & (1 << 31))) {
      fprintf(out_file_prt,
              "\n 0x%02x bit 31: 1 Card power up procedure finished  ",
              reg8bitAddr);
    } else {
      fprintf(out_file_prt, "\n 0x%02x bit 31: 0 Card power up status ",
              reg8bitAddr);
    }
  }

  return res;
}

static bool parse_sd_card_reg(uint8_t reg8bitAddr, FILE *out_file_prt) {
#ifdef DEBUG_SD_CARD
  printf("\n%s reg 0x%02x", __FUNCTION__, reg8bitAddr);
#endif
  if (NULL == out_file_prt) {
    return false;
  }
  bool res = false;
  printf("\n%s 1", __FUNCTION__);
  SdReg32bit_t *reg_item = get_reg_item_by_reg_addr(reg8bitAddr);
  // uint8_t ind = get_reg_ind(reg8bitAddr);
  if (NULL == reg_item) {
    return false;
  }
  printf("\n%s 2", __FUNCTION__);
  if (false == reg_item->valid) {
    if (reg_item->reg8BitAddr != reg8bitAddr) {
      printf("\nDiff Register 0x%x 0x%x  \n", reg_item->reg8BitAddr,
             reg8bitAddr);
    }
#ifdef DEBUG_SD_CARD
    printf("\nRegister 0x%x    or %u is not valid index %u\n", reg8bitAddr,
           reg8bitAddr);
#endif
    return false;
  }
  printf("\n%s 3", __FUNCTION__);
  uint32_t reg32_val = reg_item->reg_data.reg_32_bit_val;
  // SdCardRegMap[reg_addr].reg_32_bit_val = reg32_val;
  fprintf(stdout, "\n\nreg [%s] addr 0x%02x val 0x%08x 0b_%s",
          sd_card_reg_name(reg8bitAddr), reg8bitAddr, reg32_val,
          utoa_bin32(reg32_val));
  printf("\n%s 4", __FUNCTION__);
  fprintf(out_file_prt, "\n\nreg [%s] addr 0x%02x val 0x%08x 0b_%s",
          sd_card_reg_name(reg8bitAddr), reg8bitAddr, reg32_val,
          utoa_bin32(reg32_val));
  printf("\n%s 5", __FUNCTION__);
  switch (reg8bitAddr) {
  case REG_CSD:
    printf("\n%s 6", __FUNCTION__);
    procRegCnd++;
    res = parse_sd_card_card_specific_data_register_v2_49h(
        reg_item->reg_data.reg_array_ptr, reg_item->reg_array_len, out_file_prt,
        reg8bitAddr);
    break;

  case REG_OCR:
    printf("\n%s 7", __FUNCTION__);
    procRegCnd++;
    res = parse_sd_card_operation_conditions_register_7ah(
        reg32_val, out_file_prt, reg8bitAddr);
    break;
  case REG_CID:
    printf("\n%s 8", __FUNCTION__);
    procRegCnd++;
    res = parse_card_identification_register_4ah(
        reg_item->reg_data.reg_array_ptr, reg_item->reg_array_len, out_file_prt,
        reg8bitAddr);
    break;
  case REG_SSR:
    printf("\n%s 9", __FUNCTION__);
    procRegCnd++;
    res = parse_sd_status_register_4dh(reg_item->reg_data.reg_array_ptr,
                                       reg_item->reg_array_len, out_file_prt,
                                       reg8bitAddr);
    break;
#if 0
	case REG_CSR:
		break;
	case REG_DSR:
		break;
	case REG_CSD:
		break;
    case REG_RCA:
        break;
    case REG_SCR:
        break;

#endif
  default:
    printf("\n%s 10", __FUNCTION__);
    res = false;
    fprintf(out_file_prt, "\n Lack of parser for reg [%s] addr 0x%x val 0x%x",
            sd_card_reg_name(reg8bitAddr), reg8bitAddr, reg32_val);
    break;
  }
  printf("\n%s 11", __FUNCTION__);
  printf("\n%s reg 0x%02x done", __FUNCTION__, reg8bitAddr);
  return res;
}

bool parse_sd_card_regs_file(char *inFileName, char *outFileName) {
#ifdef DEBUG_SD_CARD
  printf("\n%s() in file: %s out file: %s\n", __FUNCTION__, inFileName,
         outFileName);
#endif
  char curFileStr[500];
  bool res = false;
  FILE *inFilePrt = NULL;
  res = init_reg_map();
  printf("\n>In file: [%s]", inFileName);
  inFilePrt = fopen(inFileName, "r");
  if (inFilePrt) {
    int line = 0;
    while (NULL != fgets(curFileStr, sizeof(curFileStr), inFilePrt)) {
      uint8_t reg8bitAddr = 0;
      uint32_t reg32bitVal = 0;

#if DEBUG_IN_FILE_STR
      printf("\n> string: [%s]", curFileStr);
#endif
      if ((REG_ADDR_LEN + REG_VAL32_LEN) < strlen(curFileStr)) {
        res =
            try_extract_hex_uint8(curFileStr, strlen(curFileStr), &reg8bitAddr);
        if (true == res) {
          res = try_extract_hex_uint32(curFileStr, strlen(curFileStr),
                                       &reg32bitVal);
          if (true == res) {
            load_sd_card_reg(reg8bitAddr, reg32bitVal);
          } else {
            printf("\n[d]   Unable to parse 32 bit reg val in [%s]",
                   curFileStr);
            uint8_t reg_blob_array[512 * 2];
            uint16_t reg_blob_len = 0;
            res = try_extract_hex_uint8_array(curFileStr, strlen(curFileStr),
                                              reg_blob_array, &reg_blob_len);
            if (true == res) {
              printf("\n[d] Extracted hex array %u byte", reg_blob_len);
              res = load_sd_card_reg_array(reg8bitAddr, reg_blob_array,
                                           reg_blob_len);
              if (false == res) {
                printf("\n[!]     Unable to load reg array in RAM");
              }
            } else {
              printf("\n[!] Unable to extract reg array in [%s]", curFileStr);
            }
          }
        } else {
          printf("\n Unable to parse 8 bit reg addr in [%s]", curFileStr);
        }
      }
#if DEBUG_IN_FILE_STR
      printf("\n reg 0x%x val 0x%x", reg8bitAddr, reg32bitVal);
#endif
      line++;
    }
    fclose(inFilePrt);
    res = true;
  } else {
    printf("\nUnable to open file [%s]", inFileName);
  }

  if (true == res) {
    FILE *out_file_prt = NULL;
    out_file_prt = fopen(outFileName, "w");
    if (out_file_prt) {
      uint8_t num = 0;
      for (num = 0; num <= NUM_OF_REGISTERS; num++) {
        res = parse_sd_card_reg(SdCardRegMap[num].reg8BitAddr, out_file_prt);
        if (false == res) {
          printf("\n[!] Unable to parse reg 0x%02x",
                 SdCardRegMap[num].reg8BitAddr);
        } else {
          printf("\n[d] Parse reg 0x%02x OK", SdCardRegMap[num].reg8BitAddr);
        }
      }

      printf("\n processed %u/8 registers %7.2f%% remain %u registers",
             procRegCnd, cacl_percent((float)procRegCnd, NUM_OF_REGISTERS),
             NUM_OF_REGISTERS - procRegCnd);
      printf("\n processed %u/1128 bits %7.2f%%", procRegCnd * 24,
             cacl_percent((float)procRegCnd * 24.0, NUM_OF_REGISTERS * 24.0));
      fprintf(out_file_prt,
              "\n\n Support: aabzele@gmail.com Alexander Barunin");
      fclose(out_file_prt);
    }
  }

  return res;
}
