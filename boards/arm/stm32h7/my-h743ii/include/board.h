/****************************************************************************
 * boards/arm/stm32h7/nucleo-h743ii/include/board.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_ARM_STM32H7_NUCLEO_H743ZI_INCLUDE_BOARD_H
#define __BOARDS_ARM_STM32H7_NUCLEO_H743ZI_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
# include <stdint.h>
#endif

/* Do not include STM32 H7 header files here */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

/* The board provides the following clock sources:
 *
 *   X3:  32.768 KHz crystal for LSE
 *   X2:  25 MHz HSE crystal oscillator
 *
 * So we have these clock source available within the STM32
 *
 *   HSI: 16 MHz RC factory-trimmed
 *   LSI: 32 KHz RC
 *   HSE: 25 MHz oscillator X2
 *   LSE: 32.768 kHz
 */

#define STM32_BOARD_XTAL        25000000ul /* ST-LINK MCO */

#define STM32_HSI_FREQUENCY     64000000ul
#define STM32_LSI_FREQUENCY     32768
#define STM32_HSE_FREQUENCY     STM32_BOARD_XTAL
#define STM32_LSE_FREQUENCY     32768


/* Main PLL Configuration.
 *
 * PLL source is HSE = 25,000,000
 *
 * When STM32_HSE_FREQUENCY / PLLM <= 2MHz VCOL must be selected.
 * VCOH otherwise.
 *
 * PLL_VCOx = (STM32_HSE_FREQUENCY / PLLM) * PLLN
 * Subject to:
 *
 *     1 <= PLLM <= 63
 *     4 <= PLLN <= 512
 *   150 MHz <= PLL_VCOL <= 420MHz
 *   192 MHz <= PLL_VCOH <= 836MHz
 *
 * SYSCLK  = PLL_VCO / PLLP
 * CPUCLK  = SYSCLK / D1CPRE
 * Subject to
 *
 *   PLLP1   = {2, 4, 6, 8, ..., 128}
 *   PLLP2,3 = {2, 3, 4, ..., 128}
 *   CPUCLK <= 400 MHz
 */

#define STM32_BOARD_USEHSE 1
//#define STM32_HSEBYP_ENABLE
#define STM32_PLLCFG_PLLSRC      RCC_PLLCKSELR_PLLSRC_HSE

/* PLL1, wide 4 - 8 MHz input, enable DIVP, DIVQ, DIVR
 *
 *   PLL1_VCO = (25,000,000 / 5) * 160 = 800 MHz
 *
 *   PLL1P = PLL1_VCO/2  = 800 MHz / 2   = 400 MHz
 *   PLL1Q = PLL1_VCO/4  = 800 MHz / 8   = 100 MHz
 *   PLL1R = PLL1_VCO/8  = 800 MHz / 4   = 200 MHz
 */

#define STM32_PLLCFG_PLL1CFG     (RCC_PLLCFGR_PLL1VCOSEL_WIDE | \
                                  RCC_PLLCFGR_PLL1RGE_4_8_MHZ | \
                                  RCC_PLLCFGR_DIVP1EN | \
                                  RCC_PLLCFGR_DIVQ1EN | \
                                  RCC_PLLCFGR_DIVR1EN)
#define STM32_PLLCFG_PLL1M       RCC_PLLCKSELR_DIVM1(5)
#define STM32_PLLCFG_PLL1N       RCC_PLL1DIVR_N1(160)
#define STM32_PLLCFG_PLL1P       RCC_PLL1DIVR_P1(2)
#define STM32_PLLCFG_PLL1Q       RCC_PLL1DIVR_Q1(8)
#define STM32_PLLCFG_PLL1R       RCC_PLL1DIVR_R1(4)

#define STM32_VCO1_FREQUENCY     ((STM32_HSE_FREQUENCY / 5) * 160)
#define STM32_PLL1P_FREQUENCY    (STM32_VCO1_FREQUENCY / 2)
#define STM32_PLL1Q_FREQUENCY    (STM32_VCO1_FREQUENCY / 8)
#define STM32_PLL1R_FREQUENCY    (STM32_VCO1_FREQUENCY / 4)

/* PLL2 */

//   RCC_PLLCFGR_DIVP2EN
#define STM32_PLLCFG_PLL2CFG (RCC_PLLCFGR_PLL2VCOSEL_WIDE | \
                              RCC_PLLCFGR_PLL2RGE_4_8_MHZ | \
                              RCC_PLLCFGR_DIVR2EN)
#define STM32_PLLCFG_PLL2M       RCC_PLLCKSELR_DIVM2(5)
#define STM32_PLLCFG_PLL2N       RCC_PLL2DIVR_N2(100)
#define STM32_PLLCFG_PLL2P       RCC_PLL2DIVR_P2(2)
#define STM32_PLLCFG_PLL2Q       RCC_PLL2DIVR_Q2(5)
#define STM32_PLLCFG_PLL2R       RCC_PLL2DIVR_R2(3)

#define STM32_VCO2_FREQUENCY     ((STM32_HSE_FREQUENCY / 5) * 100)
#define STM32_PLL2P_FREQUENCY    (STM32_VCO2_FREQUENCY / 2)
#define STM32_PLL2Q_FREQUENCY    (STM32_VCO2_FREQUENCY / 5)
#define STM32_PLL2R_FREQUENCY    (STM32_VCO2_FREQUENCY / 3)

/* PLL3 */

//  /* VCO freq range: Medium VCO range: 150 to 420 MHz, input clock <= 2 MHz */
#define STM32_PLLCFG_PLL3CFG (RCC_PLLCFGR_PLL3VCOSEL_MEDIUM | \
                              RCC_PLLCFGR_PLL3RGE_1_2_MHZ | \
                              RCC_PLLCFGR_DIVR3EN)
#define STM32_PLLCFG_PLL3M       RCC_PLLCKSELR_DIVM3(25)
#define STM32_PLLCFG_PLL3N       RCC_PLL3DIVR_N3(333)
#define STM32_PLLCFG_PLL3P   0//    RCC_PLL2DIVR_P3(2)
#define STM32_PLLCFG_PLL3Q   0
#define STM32_PLLCFG_PLL3R      RCC_PLL3DIVR_R3(10)

#define STM32_VCO3_FREQUENCY    ((STM32_HSE_FREQUENCY / 25) * 333)
#define STM32_PLL3P_FREQUENCY
#define STM32_PLL3Q_FREQUENCY
#define STM32_PLL3R_FREQUENCY   (STM32_VCO3_FREQUENCY / 10)

/* SYSCLK = PLL1P = 400 MHz
 * CPUCLK = SYSCLK / 1 = 400 MHz
 */

#define STM32_RCC_D1CFGR_D1CPRE  (RCC_D1CFGR_D1CPRE_SYSCLK)
#define STM32_SYSCLK_FREQUENCY   (STM32_PLL1P_FREQUENCY)
#define STM32_CPUCLK_FREQUENCY   (STM32_SYSCLK_FREQUENCY / 1)

/* Power D3 domain control
MHz
                      VOS
              0   1     2     3
Peripherals 
Core        480   400   300   200
          with ODN
FMC         300   250   200   133
QUADSPI     250   200   150   100
SDMMC1      250   200   150   100

*/
#define STM32_PWR_VOS_SCALE PWR_D3CR_VOS_SCALE_1



/* Configure Clock Assignments */

/* AHB clock (HCLK) is SYSCLK/2 (200 MHz max)
 * HCLK1 = HCLK2 = HCLK3 = HCLK4
 */

#define STM32_RCC_D1CFGR_HPRE   RCC_D1CFGR_HPRE_SYSCLKd2        /* HCLK  = SYSCLK / 2 */
#define STM32_ACLK_FREQUENCY    (STM32_CPUCLK_FREQUENCY / 2)    /* ACLK in D1, HCLK3 in D1 */
#define STM32_HCLK_FREQUENCY    (STM32_CPUCLK_FREQUENCY / 2)    /* HCLK in D2, HCLK4 in D3 */

/* APB1 clock (PCLK1) is HCLK/n ( MHz) */

#define STM32_RCC_D2CFGR_D2PPRE1  RCC_D2CFGR_D2PPRE1_HCLKd2       /* PCLK1 = HCLK / n */
#define STM32_PCLK1_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* APB2 clock (PCLK2) is HCLK/n ( MHz) */

#define STM32_RCC_D2CFGR_D2PPRE2  RCC_D2CFGR_D2PPRE2_HCLKd2       /* PCLK2 = HCLK / n */
#define STM32_PCLK2_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* APB3 clock (PCLK3) is HCLK/n ( MHz) */

#define STM32_RCC_D1CFGR_D1PPRE   RCC_D1CFGR_D1PPRE_HCLKd2        /* PCLK3 = HCLK / n */
#define STM32_PCLK3_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* APB4 clock (PCLK4) is HCLK/n ( MHz) */

#define STM32_RCC_D3CFGR_D3PPRE   RCC_D3CFGR_D3PPRE_HCLKd2       /* PCLK4 = HCLK / n */
#define STM32_PCLK4_FREQUENCY     (STM32_HCLK_FREQUENCY/2)

/* Timer clock frequencies */

/* Timers driven from APB1 will be twice PCLK1 */

#define STM32_APB1_TIM2_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM5_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN   (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM12_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM13_CLKIN  (2*STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM14_CLKIN  (2*STM32_PCLK1_FREQUENCY)

/* Timers driven from APB2 will be twice PCLK2 */

#define STM32_APB2_TIM1_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN   (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM15_CLKIN  (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM16_CLKIN  (2*STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM17_CLKIN  (2*STM32_PCLK2_FREQUENCY)

/* Kernel Clock Configuration
 *
 * Note: look at Table 54 in ST Manual
 */

/* I2C123 clock source - HSI */

#define STM32_RCC_D2CCIP2R_I2C123SRC RCC_D2CCIP2R_I2C123SEL_HSI

/* I2C4 clock source - HSI */

#define STM32_RCC_D3CCIPR_I2C4SRC    RCC_D3CCIPR_I2C4SEL_HSI

/* SPI123 clock source - PLL1Q */

#define STM32_RCC_D2CCIP1R_SPI123SRC RCC_D2CCIP1R_SPI123SEL_PLL1

/* SPI45 clock source - APB (PCLK2?) */

#define STM32_RCC_D2CCIP1R_SPI45SRC  RCC_D2CCIP1R_SPI45SEL_APB

/* SPI6 clock source - APB (PCLK4) */

#define STM32_RCC_D3CCIPR_SPI6SRC    RCC_D3CCIPR_SPI6SEL_PCLK4

/* USB 1 and 2 clock source - HSI48 */

#define STM32_RCC_D2CCIP2R_USBSRC    RCC_D2CCIP2R_USBSEL_HSI48

/* ADC 1 2 3 clock source - pll2_pclk */

#define STM32_RCC_D3CCIPR_ADCSEL     RCC_D3CCIPR_ADCSEL_PLL2

/* FLASH wait states
 *
 *  ------------ ---------- -----------
 *  Vcore        MAX ACLK   WAIT STATES
 *  ------------ ---------- -----------
 *   VOS0 range     70 MHz    0
 *  1.26-1.40 V    140 MHz    1
 *                 210 MHz    2
 *                 225 MHz    3
 *                 240 MHz    4
 *
 *  1.15-1.26 V     70 MHz    0
 *  (VOS1 level)   140 MHz    1
 *                 185 MHz    2
 *                 225 MHz    3
 
 *  1.05-1.15 V     55 MHz    0
 *  (VOS2 level)   110 MHz    1
 *                 165 MHz    2
 *                 225 MHz    3
 *                 225 MHz    4
 
 *  0.95-1.05 V     45 MHz    0
 *  (VOS3 level)    90 MHz    1
 *                 135 MHz    2
 *                 180 MHz    3
 *                 225 MHz    4
 *  ------------ ---------- -----------
 */

#define BOARD_FLASH_WAITSTATES 4

/* QSPI pinset 

		PB2     ------> QUADSPI_CLK	
		PB6     ------> QUADSPI_BK1_NCS 		
		PD11    ------> QUADSPI_BK1_IO0
		PD12    ------> QUADSPI_BK1_IO1		
		PE2     ------> QUADSPI_BK1_IO2	
		PD13    ------> QUADSPI_BK1_IO3
*/

#define GPIO_QSPI_CS                    (GPIO_QUADSPI_BK1_NCS_1 | GPIO_SPEED_50MHz)
#define GPIO_QSPI_IO0                   (GPIO_QUADSPI_BK1_IO0_3 | GPIO_SPEED_50MHz)
#define GPIO_QSPI_IO1                   (GPIO_QUADSPI_BK1_IO1_3 | GPIO_SPEED_50MHz)
#define GPIO_QSPI_IO2                   (GPIO_QUADSPI_BK1_IO2_1 | GPIO_SPEED_50MHz)
#define GPIO_QSPI_IO3                   (GPIO_QUADSPI_BK1_IO3_2 | GPIO_SPEED_50MHz)
#define GPIO_QSPI_SCK                   (GPIO_QUADSPI_CLK_1 | GPIO_SPEED_50MHz)

#define BOARD_QSPI_CLK    RCC_D1CCIPR_QSPISEL_HCLK // 200 M
#define DMAMAP_QUADSPI    DMAP_MDMA_QUADSPI_FT

/* SDMMC definitions ********************************************************/

#define STM32_RCC_D1CCIPR_SDMMCSEL  RCC_D1CCIPR_SDMMC_PLL1

/* Init 400kHz, PLL1Q/(2*250) */

#define STM32_SDMMC_INIT_CLKDIV     (250 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)

/* Just set these to 25 MHz for now, PLL1Q/(2*4), default speed 12.5MB/s */

#define STM32_SDMMC_MMCXFR_CLKDIV   (4 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)
#define STM32_SDMMC_SDXFR_CLKDIV    (4 << STM32_SDMMC_CLKCR_CLKDIV_SHIFT)

#define STM32_SDMMC_CLKCR_EDGE      STM32_SDMMC_CLKCR_NEGEDGE

/* Ethernet definitions *****************************************************/

#define GPIO_ETH_RMII_TXD0    GPIO_ETH_RMII_TXD0_2    /* PG13 */
#define GPIO_ETH_RMII_TXD1    GPIO_ETH_RMII_TXD1_1    /* PB 13 */
#define GPIO_ETH_RMII_TX_EN   GPIO_ETH_RMII_TX_EN_2

/* SDRAM FMC definitions ****************************************************/

/*W9825G6KH 6l 

*/

//#define BOARD_SDRAM1_SIZE               (32*1024*1024)
// from 0xc0000000  len (0x2000000)33554432  = 0xc2000000 - 0x200000 (video buf ~2Mb) = 0xC1E00000
#define BOARD_SDRAM1_SIZE               (32*1024*1024 - 2097152)

/* BOARD_FMC_SDCR[1..2] - Initial value for SDRAM control registers for SDRAM
 *      bank 1-2. Note that some bits in SDCR1 influence both SDRAM banks and
 *      are unused in SDCR2!
 */

#define BOARD_FMC_SDCR1 \
      (FMC_SDCR_COLBITS_9 | FMC_SDCR_ROWBITS_13 | FMC_SDCR_WIDTH_16 |\
       FMC_SDCR_BANKS_4 | FMC_SDCR_CASLAT_2 | FMC_SDCR_SDCLK_2X |\
       FMC_SDCR_BURST_READ | FMC_SDCR_RPIPE_1)

/*
Fixed
        SdramTiming.LoadToActiveDelay      tMRD     2
        SdramTiming.WriteRecoveryTime      tWR/tDPL 2


SdramTiming on 130MHz
        SdramTiming.LoadToActiveDelay      tMRD
        SdramTiming.ExitSelfRefreshDelay   tXSR     10
        SdramTiming.SelfRefreshTime        tRAS     6
        SdramTiming.RowCycleDelay          tRC      8
        SdramTiming.WriteRecoveryTime      tWR/tDPL
        SdramTiming.RPDelay                tRP      4
        SdramTiming.RCDDelay               tRCD     4
        
SdramTiming on 100MHz
        SdramTiming.LoadToActiveDelay      tMRD
        SdramTiming.ExitSelfRefreshDelay   tXSR     8
        SdramTiming.SelfRefreshTime        tRAS     5
        SdramTiming.RowCycleDelay          tRC      6
        SdramTiming.WriteRecoveryTime      tWR/tDPL
        SdramTiming.RPDelay                tRP      2
        SdramTiming.RCDDelay               tRCD     2
*/
//130MHz
/*#define BOARD_FMC_SDTR1 \
      (FMC_SDTR_TMRD(2) | FMC_SDTR_TXSR(10) | FMC_SDTR_TRAS(6) | \
       FMC_SDTR_TRC(8) | FMC_SDTR_TWR(2) | FMC_SDTR_TRP(4) | \
       FMC_SDTR_TRCD(4))
*/
//100MHz
#define BOARD_FMC_SDTR1 \
      (FMC_SDTR_TMRD(2) | FMC_SDTR_TXSR(8) | FMC_SDTR_TRAS(5) | \
       FMC_SDTR_TRC(6) | FMC_SDTR_TWR(2) | FMC_SDTR_TRP(2) | \
       FMC_SDTR_TRCD(2))


//#define BOARD_FMC_CLK                   RCC_D1CCIPR_FMCSEL_PLL2 // 250 M
//#define FMC_CLK_FREQUENCY               (STM32_PLL2R_FREQUENCY / 2) // 125 M
#define BOARD_FMC_CLK                   RCC_D1CCIPR_FMCSEL_HCLK // 200 M
//#define FMC_CLK_FREQUENCY               (STM32_HCLK_FREQUENCY / 2) // 100 M
//#define BOARD_FMC_SDRAM_REFR_RATE_COUNT   995
#define BOARD_FMC_SDRAM_REFR_CYCLES     8192
#define BOARD_FMC_SDRAM_REFR_PERIOD     64
#define BOARD_FMC_SDRAM_AUTOREFRESH     8
#define BOARD_FMC_SDRAM_MODE \
      (FMC_SDCMR_MRD_BURST_LENGTH_2 |\
       FMC_SDCMR_MRD_BURST_TYPE_SEQUENTIAL |\
       FMC_SDCMR_MRD_CAS_LATENCY_2 |\
       FMC_SDCMR_MRD_OPERATING_MODE_STANDARD |\
       FMC_SDCMR_MRD_WRITEBURST_MODE_SINGLE)

#define BOARD_FMC_GPIO_CONFIGS \
       GPIO_FMC_A0, GPIO_FMC_A1, GPIO_FMC_A2, GPIO_FMC_A3, \
       GPIO_FMC_A4, GPIO_FMC_A5, GPIO_FMC_A6, GPIO_FMC_A7, \
       GPIO_FMC_A8, GPIO_FMC_A9, GPIO_FMC_A10, GPIO_FMC_A11, \
       GPIO_FMC_A12, \
       GPIO_FMC_D0, GPIO_FMC_D1, GPIO_FMC_D2, GPIO_FMC_D3, \
       GPIO_FMC_D4, GPIO_FMC_D5, GPIO_FMC_D6, GPIO_FMC_D7, \
       GPIO_FMC_D8, GPIO_FMC_D9, GPIO_FMC_D10, GPIO_FMC_D11, \
       GPIO_FMC_D12, GPIO_FMC_D13, GPIO_FMC_D14, GPIO_FMC_D15, \
       GPIO_FMC_NBL0, GPIO_FMC_NBL1, \
       GPIO_FMC_BA0, GPIO_FMC_BA1, \
       GPIO_FMC_SDNCAS, GPIO_FMC_SDNRAS, \
       GPIO_FMC_SDNWE_3, GPIO_FMC_SDNE0_3, GPIO_FMC_SDCKE0_3, \
       GPIO_FMC_SDCLK


/********************************* LCD definitions ******************************/

#define BOARD_LTDC_WIDTH                800
#define BOARD_LTDC_HEIGHT               480

#define BOARD_LTDC_OUTPUT_BPP           18
#define BOARD_LTDC_HFP                  40
#define BOARD_LTDC_HBP                  40
#define BOARD_LTDC_VFP                  13
#define BOARD_LTDC_VBP                  29

#define BOARD_LTDC_HSYNC                48
#define BOARD_LTDC_VSYNC                3


/* Pixel Clock Polarity */

#define BOARD_LTDC_GCR_PCPOL            0 /* !LTDC_GCR_PCPOL */

/* Data Enable Polarity */

#define BOARD_LTDC_GCR_DEPOL            0 /* !LTDC_GCR_DEPOL */

/* Vertical Sync Polarity */

#define BOARD_LTDC_GCR_VSPOL            0 /* !LTDC_GCR_VSPOL */

/* Horizontal Sync Polarity */

#define BOARD_LTDC_GCR_HSPOL            0 /* !LTDC_GCR_HSPOL */

/* GPIO pinset 
// AT070TN83
    PG13    ------> LTDC_R0      PE5     ------> LTDC_G0       PG14    ------> LTDC_B0
    PA2     ------> LTDC_R1      PE6     ------> LTDC_G1       PG12    ------> LTDC_B1
    
    PH8     ------> LTDC_R2      PH13    ------> LTDC_G2       PD6     ------> LTDC_B2
    PH9     ------> LTDC_R3      PH14    ------> LTDC_G3       PA8     ------> LTDC_B3
    PH10    ------> LTDC_R4      PH15    ------> LTDC_G4       PI4     ------> LTDC_B4
    PH11    ------> LTDC_R5      PI0     ------> LTDC_G5       PI5     ------> LTDC_B5
    PH12    ------> LTDC_R6      PI1     ------> LTDC_G6       PI6     ------> LTDC_B6
    PG6     ------> LTDC_R7      PI2     ------> LTDC_G7       PI7     ------> LTDC_B7
    
    PG7     ------> LTDC_CLK     PH4  ------> AT070TN83_MODE
    PF10    ------> LTDC_DE      PI11 ------> AT070TN83_LR
    PI9     ------> LTDC_VSYNC   PI8  ------> AT070TN83_UD
    PI10    ------> LTDC_HSYNC
*/

//#define GPIO_LTDC_PINS                  18 /* -bit display */

//#define GPIO_LTDC_R0                    none
//#define GPIO_LTDC_R1                    none
#define GPIO_LTDC_R2                    GPIO_LCD_R2_3
#define GPIO_LTDC_R3                    GPIO_LCD_R3_1
#define GPIO_LTDC_R4                    GPIO_LCD_R4_3
#define GPIO_LTDC_R5                    GPIO_LCD_R5_4
#define GPIO_LTDC_R6                    GPIO_LCD_R6_2
#define GPIO_LTDC_R7                    GPIO_LCD_R7_2

//#define GPIO_LTDC_G0                    none
//#define GPIO_LTDC_G1                    none
#define GPIO_LTDC_G2                    GPIO_LCD_G2_2
#define GPIO_LTDC_G3                    GPIO_LCD_G3_3
#define GPIO_LTDC_G4                    GPIO_LCD_G4_2
#define GPIO_LTDC_G5                    GPIO_LCD_G5_2
#define GPIO_LTDC_G6                    GPIO_LCD_G6_2
#define GPIO_LTDC_G7                    GPIO_LCD_G7_3

//#define GPIO_LTDC_B0                    none
//#define GPIO_LTDC_B1                    none
#define GPIO_LTDC_B2                    GPIO_LCD_B2_2
#define GPIO_LTDC_B3                    GPIO_LCD_B3_1
#define GPIO_LTDC_B4                    GPIO_LCD_B4_3
#define GPIO_LTDC_B5                    GPIO_LCD_B5_2
#define GPIO_LTDC_B6                    GPIO_LCD_B6_2
#define GPIO_LTDC_B7                    GPIO_LCD_B7_2

#define GPIO_LTDC_VSYNC                 GPIO_LCD_VSYNC_3
#define GPIO_LTDC_HSYNC                 GPIO_LCD_HSYNC_2
#define GPIO_LTDC_DE                    GPIO_LCD_DE_2
#define GPIO_LTDC_CLK                   GPIO_LCD_CLK_2



//Backlight PWM

#define GPIO_TIM12_CH1OUT       GPIO_TIM12_CH1OUT_2

/* LED definitions **********************************************************/

/* The Nucleo-144 board has numerous LEDs but only three, LD1 a Green LED,
 * LD2 a Blue LED and LD3 a Red LED, that can be controlled by software.
 * The following definitions assume the default Solder Bridges are installed.
 *
 * If CONFIG_ARCH_LEDS is not defined, then the user can control the LEDs in
 * any way.
 * The following definitions are used to access individual LEDs.
 */

/* LED index values for use with board_userled() */

#define BOARD_LED1        0
#define BOARD_NLEDS       1

#define BOARD_LED   BOARD_LED1

/* LED bits for use with board_userled_all() */

#define BOARD_LED1_BIT    (1 << BOARD_LED1)

/* If CONFIG_ARCH_LEDS is defined, the usage by the board port is defined in
 * include/board.h and src/stm32_leds.c.
 * The LEDs are used to encode OS-related events as follows:
 *
 *
 *   SYMBOL                     Meaning                      LED state
 *                                                        Red   Green Blue
 *   ----------------------  --------------------------  ------ ------ ---
 */

#define LED_STARTED        0 /* NuttX has been started   OFF    OFF   OFF  */
#define LED_HEAPALLOCATE   1 /* Heap has been allocated  OFF    OFF   ON   */
#define LED_IRQSENABLED    2 /* Interrupts enabled       OFF    ON    OFF  */
#define LED_STACKCREATED   3 /* Idle stack created       OFF    ON    ON   */
#define LED_INIRQ          4 /* In an interrupt          N/C    N/C   GLOW */
#define LED_SIGNAL         5 /* In a signal handler      N/C    GLOW  N/C  */
#define LED_ASSERTION      6 /* An assertion failed      GLOW   N/C   GLOW */
#define LED_PANIC          7 /* The system has crashed   Blink  OFF   N/C  */
#define LED_IDLE           8 /* MCU is is sleep mode     ON     OFF   OFF  */

/* Thus if the Green LED is statically on, NuttX has successfully booted and
 * is, apparently, running normally.  If the Red LED is flashing at
 * approximately 2Hz, then a fatal error has been detected and the system
 * has halted.
 */

/* Button definitions *******************************************************/

/* The NUCLEO board supports one button:  Pushbutton B1, labeled "User", is
 * connected to GPIO PI11.
 * A high value will be sensed when the button is depressed.
 */
/*
#define BUTTON_USER        0
#define NUM_BUTTONS        1
#define BUTTON_USER_BIT    (1 << BUTTON_USER)
*/
/* Alternate function pin selections ****************************************/

/* USART1 ( Console) */

#define GPIO_USART1_RX     GPIO_USART1_RX_2  /* PA10 */
#define GPIO_USART1_TX     GPIO_USART1_TX_2  /* PA9 */
/*
#define DMAMAP_USART3_RX DMAMAP_DMA12_USART3RX_0
#define DMAMAP_USART3_TX DMAMAP_DMA12_USART3TX_1
*/

/* I2C1 Use Nucleo I2C1 pins */

#define GPIO_I2C1_SCL GPIO_I2C1_SCL_2 /* PB8 - D15 */
#define GPIO_I2C1_SDA GPIO_I2C1_SDA_2 /* PB9 - D14 */

/* I2C2 Use Nucleo I2C2 pins */

#define GPIO_I2C2_SCL  GPIO_I2C2_SCL_2  /* PF1 - D69 */
#define GPIO_I2C2_SDA  GPIO_I2C2_SDA_2  /* PF0 - D68 */
#define GPIO_I2C2_SMBA GPIO_I2C2_SMBA_2 /* PF2 - D70 */

/* SPI3 */

#define GPIO_SPI3_MISO GPIO_SPI3_MISO_1 /* PB4 */
#define GPIO_SPI3_MOSI GPIO_SPI3_MOSI_4 /* PB5 */
#define GPIO_SPI3_SCK  GPIO_SPI3_SCK_1  /* PB3 */
#define GPIO_SPI3_NSS  GPIO_SPI3_NSS_2  /* PA4 */

/* TIM1 */

#define GPIO_TIM1_CH1OUT  GPIO_TIM1_CH1OUT_2  /* PE9  - D6 */
#define GPIO_TIM1_CH1NOUT GPIO_TIM1_CH1NOUT_3 /* PE8  - D42 */
#define GPIO_TIM1_CH2OUT  GPIO_TIM1_CH2OUT_2  /* PE11 - D5 */
#define GPIO_TIM1_CH2NOUT GPIO_TIM1_CH2NOUT_3 /* PE10 - D40 */
#define GPIO_TIM1_CH3OUT  GPIO_TIM1_CH3OUT_2  /* PE13 - D3 */
#define GPIO_TIM1_CH3NOUT GPIO_TIM1_CH3NOUT_3 /* PE12 - D39 */
#define GPIO_TIM1_CH4OUT  GPIO_TIM1_CH4OUT_2  /* PE14 - D38 */

/* DMA **********************************************************************/

#define DMAMAP_SPI3_RX DMAMAP_DMA12_SPI3RX_0 /* DMA1 */
#define DMAMAP_SPI3_TX DMAMAP_DMA12_SPI3TX_0 /* DMA1 */

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_STM32H7_NUCLEO_H743ZI_INCLUDE_BOARD_H */
