/**
    Network Driver for Beckhoff CCAT communication controller
    Copyright (C) 2014  Beckhoff Automation GmbH
    Author: Patrick Bruenn <p.bruenn@beckhoff.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef _CCAT_DEFINITIONS_H_
#define _CCAT_DEFINITIONS_H_

#ifndef WINDOWS
#include <linux/kernel.h>
typedef u8 BYTE;
typedef u32 ULONG;
typedef u16 USHORT;
typedef u8 UINT8;
typedef u16 UINT16;
typedef u32 UINT32;
typedef u64 UINT64;
#endif

#define CCAT_DMA_FRAME_HEADER_LENGTH (196 / 8) // 196 bit

typedef struct _ETHERNET_ADDRESS
{
	UINT8 b[6];
}ETHERNET_ADDRESS;

typedef enum CCatInfoTypes
{
	CCATINFO_NOTUSED				= 0,
	CCATINFO_BLOCK					= 1,
	CCATINFO_ETHERCAT_SLAVE		= 2,
	CCATINFO_ETHERCAT_MASTER	= 3,
	CCATINFO_ETHERNET_MAC		= 4,
	CCATINFO_ETHERNET_SWITCH	= 5,
	CCATINFO_SERCOS3				= 6,
	CCATINFO_PROFIBUS				= 7,
	CCATINFO_CAN_CONTROLLER		= 8,
	CCATINFO_KBUS_MASTER			= 9,
	CCATINFO_IP_LINK				= 10,
	CCATINFO_SPI_MASTER			= 11,
	CCATINFO_I2C_MASTER			= 12,
	CCATINFO_GPIO					= 13,
	CCATINFO_DRIVEIP				= 14,
	CCATINFO_EPCS_PROM			= 15,
	CCATINFO_SYSTIME				= 16,
	CCATINFO_INTCTRL				= 17,
	CCATINFO_EEPROM				= 18,
	CCATINFO_DMA					= 19,
	CCATINFO_ETHERCAT_MASTER_DMA	= 20,
	CCATINFO_ETHERNET_MAC_DMA		= 21,
	CCATINFO_SRAM					= 22,
	CCATINFO_COPY_BLOCK			= 23,
	CCATINFO_MAX
} _CCatInfoTypes;

typedef struct
{
	USHORT	eCCatInfoType;
	USHORT	nRevision;
	union
	{
		ULONG		nParam;
		struct
		{
			BYTE nMaxEntries;
			BYTE compileDay;
			BYTE compileMonth;
			BYTE compileYear;
		};
		struct
		{
			BYTE txDmaChn;
			BYTE rxDmaChn;
		};
		struct
		{
			BYTE		nExternalDataSize	: 2;
			BYTE		reserved1			: 6;
			BYTE		nRamSize; //size = 2^ramSize
			USHORT	reserved2;
		};
	};
	ULONG		nAddr;
	ULONG		nSize;
} CCatInfoBlock, *PCCatInfoBlock;

typedef struct _CCatMacRegs
{
	union
	{
		struct
		{
			UINT8			frameLenErrCnt;
			UINT8			rxErrCnt;
			UINT8			crcErrCnt;
			UINT8			linkLostErrCnt;
		};
		UINT32 errCnt;
	};
	UINT32			reserved1;
	UINT8				dropFrameErrCnt; // 0x08
	UINT8				reserved2[7];
	UINT32			txFrameCnt;		  // 0x10
	UINT32			rxFrameCnt;		  // 0x14
	UINT32   reserved3[2];
	UINT8    txFifoLevel  : 7;
	UINT8    reserved4    : 1;
	UINT8    reserved5[7];
	UINT8    txErrMemFull;
	UINT8    reserved6[7];
	UINT32   reserved8[18];
	UINT8    miiConnected;
}CCatMacRegs;

typedef struct _CCatMii
{
	USHORT		startMiCycle	: 1;
	USHORT		reserved1		: 6;
	USHORT		cmdErr			: 1;
#define MII_CMD_READ 1
#define MII_CMD_WRITE 2
	USHORT		cmd				: 2;
	USHORT		reserved2		: 6;
	USHORT		phyAddr			: 5;
	USHORT		reserved3		: 3;
	USHORT		phyReg			: 5;
	USHORT		reserved4		: 3;
	USHORT		phyWriteData;
	USHORT		phyReadData;
	ETHERNET_ADDRESS	macAddr;
	USHORT		macFilterEnabled		: 1;
	USHORT		reserved6				: 7;
	USHORT		linkStatus				: 1;
	USHORT		reserved7				: 7;
	ULONG       led0;
	ULONG       led1;
	ULONG       led2[2];
	ULONG       systimeInsertion[4];
	ULONG		interruptState[2];
	ULONG		interruptMask[2];
}CCatMii;

typedef struct _CCatDmaTxFifo
{
	UINT32   startAddr      : 24;
	UINT32   numQuadWords   : 8;
	UINT32   reserved1;
	UINT8    fifoReset;
	UINT8    reserved2[7];
}CCatDmaTxFifo;

typedef union _CCatDmaRxActBuf
{
	struct
	{
		UINT32			startAddr	: 24;
		UINT32			reserved1	: 7;
		UINT32			nextValid	: 1;
		UINT32			lastAddr		: 24;
		UINT32			reserved2	: 8;
		UINT32			FifoLevel	: 24;
		UINT32			bufferLevel	: 8;
		UINT32			nextAddr;
	};
	UINT32			rxActBuf;
}CCatDmaRxActBuf;

typedef struct _CCatInfoBlockOffs
{
	UINT32			reserved;
	UINT32			nMMIOffs;
	UINT32			nTxFifoOffs;
	UINT32			nMacRegOffs;
	UINT32			nRxMemOffs;
	UINT32			nTxMemOffs;
	UINT32			nMiscOffs;
} CCatInfoBlockOffs;
#endif /* #ifndef _CCAT_DEFINITIONS_H_ */
