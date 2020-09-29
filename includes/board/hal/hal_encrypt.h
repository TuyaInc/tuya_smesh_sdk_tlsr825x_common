/*************************************************************************
	> File Name: hal_encrypt.h
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Jun 2018 08:32:09 PM CST
 ************************************************************************/

#ifndef _HAL_ENCRYPT_H
#define _HAL_ENCRYPT_H

#include "hal_sys.h"

void hal_md5(unsigned char *in, int len, unsigned char *out);

u8 hal_aes_ecb_encryption(u8 *key, u8 mStrLen, u8 *mStr, u8 *result);
u8 hal_aes_ccm_encryption(u8 *key, u8 *iv, u8 *aStr, u8 *mic, u8 mStrLen, u8 *mStr, u8 *result);
u8 hal_aes_ccm_decryption(u8 *key, u8 *iv, u8 *aStr, u8 *mic, u8 mStrLen, u8 *mStr, u8 *result);


#endif
