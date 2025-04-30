/*
 * Copyright (c) 2016, mod0keecrack
 *    Thorsten Schroeder <ths at modzero dot ch>
 *
 * All rights reserved.
 *
 * This file is part of mod0keecrack.
 *
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Thorsten Schroeder <ths at modzero dot ch> wrote this file. As long as you
 * retain this notice you can do whatever you want with this stuff. If we meet
 * some day, and you think this stuff is worth it, you can buy me a beer in
 * return. Thorsten Schroeder.
 *
 * NON-MILITARY-USAGE CLAUSE
 * Redistribution and use in source and binary form for military use and
 * military research is not permitted. Infringement of these clauses may
 * result in publishing the source code of the utilizing applications and
 * libraries to the public. As this software is developed, tested and
 * reviewed by *international* volunteers, this clause shall not be refused
 * due to the matter of *national* security concerns.
 *
 * File: mod0keecrack.h
 * Description: Project header files.
 */

#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#ifndef HAS_AES256
#error "+HAS_AES256"
#endif /*HAS_AES256*/

bool aes_decrypt_payload_frag(KdbxHeaderEntry_t* hdr, uint8_t* masterkey, kdbx_payload_t* payload);
bool aes_decrypt_payload(KdbxHeaderEntry_t* hdr, uint8_t* masterkey, kdbx_payload_t* payload);
// implementation in platform specific files: crypto-XX.c
int aes_transformkey(KdbxHeaderEntry_t* hdr, uint8_t* tkey, size_t tkeylen);
//bool aes_decrypt_check(KdbxHeaderEntry_t* hdr, uint8_t* masterkey, uint8_t* encrypted);

#endif /*CRYPTO_UTILS_H*/
