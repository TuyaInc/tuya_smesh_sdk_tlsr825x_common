
#ifndef _TY_NV_H
#define _TY_NV_H

#include "board.h"

#define FLASH_4K_PAGE_NUM              16
#define FLASH_PAGE_SIZE                256

#define NV_MAX_SECTION_BLOCK           5

#define NV_SECTION_SIZE                (FLASH_PAGE_SIZE * FLASH_4K_PAGE_NUM)

#define NV_ALIGN_LENTH(len)                ( ( ((len) % 4 ) == 0) ? len : ( ((len)/4 + 1) * 4 ) )

#define END_PAGE_FOR_NV         (START_PAGE_FOR_NV + (NV_SECTION_SIZE * NV_MAX_SECTION_BLOCK))


#define NV_HEADER_TABLE_SIZE           10

#define INVALID_NV_VALUE               0xFF

#define MOUDLES_START_ADDR(modules)   (START_PAGE_FOR_NV + NV_SECTION_SIZE * (modules))

#define MOUDLES_AVALIABLE_SIZE(usedSize)  (FLASH_4K_PAGE_NUM * FLASH_PAGE_SIZE - (usedSize))

#define PAGE_AVALIABLE_SIZE(offset)       (FLASH_PAGE_SIZE - (offset % FLASH_PAGE_SIZE))

#define PAGE_HEADER_SISE  (sizeof(page_header_t))
#define NV_HEADER_SIZE  (sizeof(nv_header_t))

#define READ_BYTES_PER_TIME                 16

typedef enum {
	NV_BLE_ITEM_LL,
	NV_BLE_ITEM_GAP,
	NV_BLE_ITEM_BOND_TBL,
	NV_BLE_ITEM_SM,
	NV_BLE_ITEM_NUM,
} nv_bleItemId_t;

typedef enum {
	NV_BASIC_WHITE_LIST,
	NV_BASIC_ITEM_NUM,
} nv_basicItemId_t;

typedef enum {
	NV_USER_ITEM_H_ID,
	NV_USER_ITEM_AUZ_KEY,
	NV_USER_ITEM_UUID,
	NV_USER_ITEM_MAC,
	NV_USER_ITEM_PID,
    NV_USER_ITEM_CONFIG,
    NV_USER_ITEM_IF_AUTH,
    NV_USER_ITEM_COUNTRY_CODE,
} nv_userItemId_t;//only read

typedef enum {
	NV_USER_ITEM_IF_CLOSE_FACTORY_TEST,
} nv_user1ItemId_t;//read and write

extern int ty_nv_user_data_read(u8 id, u16 len, u8 *buf);//use the user3Item
extern int ty_nv_user_data_write(u8 id, u16 len, u8 *buf);//user can define the id in the app level
extern int ty_nv_user_data_erase(void);

typedef struct {
	u16 offset;
	u16 len;
	u8 id;
} nv_header_t;


typedef struct {
	u16 usedSize;
	nv_header_t hdrList[NV_HEADER_TABLE_SIZE];
} page_header_t;

typedef struct {
	/* addr of header */
	u16 usedSize;
	u16 nvOffset;
	nv_header_t hdrInfo;
} item_info_t;


//#define START_PAGE_FOR_NV       (400 * FLASH_PAGE_SIZE)
#define START_PAGE_FOR_NV       0x78000

/**
 *  @brief  Specific purpose statement for different NV flash modules,
 *    each module occupies 4K memory.
 *
 *  @details By default, the BLE stack has allocated  three modules:
 *    - the first module is used for basic use.
 *    - the second module is used for ble stack use.
 *    - the third module is used for user application.
 *
 *  @details So if user need a NV memory size less than 4K, user can used the third
 *    module directly. Otherwise, user can declare some additional modules,
 *    ex, NV_USER_MODULE2=3, NV_USER_MODULE3=4,....
 *    All the modules specified should be declared before NV_MAX_MOULDS
 */
typedef enum {
	NV_USER_MODULE = 0,     //!< Used for user application
	NV_USER_MODULE1,
	NV_USER_MODULE2,
	NV_USER_MODULE3,
	NV_USER_MODULE4,
	NV_USER_MODULE5,
	NV_MAX_MOULDS,            //!< Represent the number of modules used
} nv_module_t;

/**
 *  @brief  Definition of nv_read/nv_write function return value type
 */
typedef enum nv_sts_e {
	NV_SUCCESS = 0,
	NV_INVALID_MODULS = 1,      //!< Module input has not been declared yet
	NV_INVALID_ID ,                     //!< ID input is not valid
	NV_ITEM_NOT_FOUND,           //!< ID not found for nv_read operation in this module
	NV_NOT_ENOUGH_SAPCE,       //!< No enough space for nv_write operation in this module
	NV_ITEM_LEN_NOT_MATCH,    //!< Length input doesn't meet the actual length stored
	NV_CHECK_SUM_ERROR,           //!< Check sum wrong for nv_read operation
} nv_sts_t;
/** @} end of group HAL_NV_Module_Types */



/** @addtogroup  HAL_NV_Module_Functions NV Flash APIs
 *  @{
 */
/**
  * @brief      Read NV Data
  *
  * @param[in]  modules - NV module used (4k memory each module)
  * @param[in]  id        - Specify different ID for all items needed to be stored in the same module (max 9)
  * @param[in]  len      - Length of data to be read (max 4K)
  * @param[in]  buf      - Buffer to store data read from NV
  *
  * @return     Status
  */
nv_sts_t nv_read(u8 modules, u8 id, u16 len, u8 *buf);

/**
  * @brief      Write NV Data
  *
  * @param[in]  modules - NV module used (4k memory each module)
  * @param[in]  id        - Specify different ID for all items needed to be stored in the same module (max 9)
  * @param[in]  len      - Length of data to be write (max 4K)
  * @param[in]  buf      - Buffer to store data to be written into NV
  *
  * @return     Status
  */
nv_sts_t nv_write(u8 modules, u8 id, u16 len, u8 *buf);

/**
  * @brief      Read NV Data for NV_USER_MODULE.
  *
  * @details   If user need a NV memory size less than 4K, user can use this API instead of nv_read
  *
  * @param[in]  id        - Specify different ID for all items needed to be stored in the same module (max 9)
  * @param[in]  len      - Length of data to be read (max 4K)
  * @param[in]  buf      - Buffer to store data read from NV
  *
  * @return     Status
  */
#define NV_USER_ITEM_LOAD(id, buf, len)              nv_read(NV_USER_MODULE, id, len, buf)
#define NV_USER1_ITEM_LOAD(id, buf, len)              nv_read(NV_USER_MODULE1, id, len, buf)
#define NV_USER2_ITEM_LOAD(id, buf, len)              nv_read(NV_USER_MODULE2, id, len, buf)
#define NV_USER3_ITEM_LOAD(id, buf, len)              nv_read(NV_USER_MODULE3, id, len, buf)
#define NV_USER4_ITEM_LOAD(id, buf, len)              nv_read(NV_USER_MODULE4, id, len, buf)
#define NV_USER5_ITEM_LOAD(id, buf, len)              nv_read(NV_USER_MODULE5, id, len, buf)

/**
  * @brief      Write NV Data for NV_USER_MODULE.
  *
  *@details    If user need a NV memory size less than 4K, user can use this API instead of nv_write
  *
  * @param[in]  modules - NV module used (4k memory each module)
  * @param[in]  id        - Specify different ID for all items needed to be stored in the same module (max 9)
  * @param[in]  len      - Length of data to be write (max 4K)
  * @param[in]  buf      - Buffer to store data to be written into NV
  *
  * @return     Status
  */
#define NV_USER_ITEM_SAVE(id, buf, len)              nv_write(NV_USER_MODULE, id, len, buf)
#define NV_USER1_ITEM_SAVE(id, buf, len)             nv_write(NV_USER_MODULE1, id, len, buf)
#define NV_USER2_ITEM_SAVE(id, buf, len)             nv_write(NV_USER_MODULE2, id, len, buf)
#define NV_USER3_ITEM_SAVE(id, buf, len)             nv_write(NV_USER_MODULE3, id, len, buf)
#define NV_USER4_ITEM_SAVE(id, buf, len)             nv_write(NV_USER_MODULE4, id, len, buf)
#define NV_USER5_ITEM_SAVE(id, buf, len)             nv_write(NV_USER_MODULE5, id, len, buf)

/** @} end of group HAL_NV_Module_Functions */


/** @} end of group HAL_NV_Module */

/** @} end of group TELINK_BLE_HAL */


/*Functions for internal use */

nv_sts_t nv_init(u8 rst);
nv_sts_t nv_resetModule(u8 modules);
nv_sts_t nv_resetAll(void);
void nv_flashWrite(u32 startAddr, u16 len, u8 *buf);

#endif
