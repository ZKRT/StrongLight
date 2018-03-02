/**
  ******************************************************************************
  * @file    appprotocol.h 
  * @author  ZKRT
  * @version V1.0
  * @date    9-May-2017
  * @brief   
	*					 + (1) init
  ******************************************************************************
  * @attention
  *
  * ...
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APPPROTOCOL_H
#define __APPPROTOCOL_H 
/* Includes ------------------------------------------------------------------*/
#include "zkrt.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
//type num enum
typedef enum
{
	TN_None =0,
	TN_HEARTBEAT,
	TN_MAX
}TypeNumEnum;
//hb flag
#define TNHB_FLAG                     0xaabbccdd
#define THHB_FIXED_LEN                5
/* Exported types ------------------------------------------------------------*/
#pragma pack(1)
///////////////////////////////subdev to uav zkrt data struct
//////common command
typedef struct
{
	u8 type_num;
	u8 type_data[ZK_DATA_MAX_LEN-1];
}common_data_plst;
//heartbeat data
typedef struct
{
	u32 hb_flag;
	u8 hb_data[ZK_DATA_MAX_LEN-THHB_FIXED_LEN];
}common_hbd_plst;
//throw heartbeat
typedef struct
{
	u8 v1;
}light_hbccplst;
///////////////////////////////
#pragma pack() 
/* Exported functions ------------------------------------------------------- */
#endif /* __APPCAN_H */
/**
  * @}
  */ 

/**
  * @}
  */
	
/************************ (C) COPYRIGHT ZKRT *****END OF FILE****/
