#ifndef __LPS22HB_DEF_H
#define __LPS22HB_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Registers */
#define LPS22HB_REGISTER_INTERRUPT_CFG  (uint8_t)0x0B
#define LPS22HB_REGISTER_THS_P_L        (uint8_t)0x0C
#define LPS22HB_REGISTER_THS_P_H        (uint8_t)0x0D
#define LPS22HB_REGISTER_WHO_AM_I       (uint8_t)0x0F // Device identification
#define LPS22HB_REGISTER_CTRL_REG1      (uint8_t)0x10
#define LPS22HB_REGISTER_CTRL_REG2      (uint8_t)0x11
#define LPS22HB_REGISTER_CTRL_REG3      (uint8_t)0x12
#define LPS22HB_REGISTER_FIFO_CTRL      (uint8_t)0x14
#define LPS22HB_REGISTER_REF_P_XL       (uint8_t)0x15
#define LPS22HB_REGISTER_REF_P_L        (uint8_t)0x16
#define LPS22HB_REGISTER_REF_P_H        (uint8_t)0x17
#define LPS22HB_REGISTER_RPDS_L         (uint8_t)0x18
#define LPS22HB_REGISTER_RPDS_H         (uint8_t)0x19
#define LPS22HB_REGISTER_RES_CONF       (uint8_t)0x1A
#define LPS22HB_REGISTER_INT_SOURCE     (uint8_t)0x25
#define LPS22HB_REGISTER_FIFO_STATUS    (uint8_t)0x26
#define LPS22HB_REGISTER_STATUS         (uint8_t)0x27
#define LPS22HB_REGISTER_PRESS_OUT_XL   (uint8_t)0x28
#define LPS22HB_REGISTER_PRESS_OUT_L    (uint8_t)0x29
#define LPS22HB_REGISTER_PRESS_OUT_H    (uint8_t)0x2A
#define LPS22HB_REGISTER_TEMP_OUT_L     (uint8_t)0x2B
#define LPS22HB_REGISTER_TEMP_OUT_H     (uint8_t)0x2C
#define LPS22HB_REGISTER_LPFP_RES       (uint8_t)0x33

#define LPS22HB_BIT(x) ((uint8_t)x) /* Bitfield positioning. */

/* WHO_AM_I Register */
#define LPS22HB_WHO_AM_I_VALUE           (uint8_t)0xB1

/** Pressure and temperature resolution mode Register. Default value: 0x05
  *        7:2 These bits must be set to 0 for proper operation of the device
  *        1: Reserved
  *        0 LC_EN: Low Current Mode Enable. Default 0
  */
#define LPS22HB_LCEN_MASK        (uint8_t)0x01

/** Control Register 1. Default value: 0x00
  *        7: This bit must be set to 0 for proper operation of the device
  *        6:4 ODR2, ODR1, ODR0: output data rate selection.Default 000
  *            ODR2  | ODR1  | ODR0  | Pressure output data-rate(Hz)  | Pressure output data-rate(Hz)
  *          ----------------------------------------------------------------------------------
  *             0    |  0    |  0    |         one shot               |         one shot
  *             0    |  0    |  1    |            1                   |            1
  *             0    |  1    |  0    |            10                  |           10
  *             0    |  1    |  1    |            25                  |           25
  *             1    |  0    |  0    |            50                  |           50
  *             1    |  0    |  1    |            75                  |         75
  *             1    |  1    |  0    |         Reserved               |         Reserved
  *             1    |  1    |  1    |         Reserved               |         Reserved
  *        
  *        3 EN_LPFP: Enable Low Pass filter on Pressure data. Default value:0
  *        2:LPF_CFG Low-pass configuration register. (0: Filter cutoff is ODR/9; 1: filter cutoff is ODR/20)
  *        1 BDU: block data update. 0 - continuous update; 1 - output registers not updated until MSB and LSB reading.
  *        0 SIM: SPI Serial Interface Mode selection. 0 - SPI 4-wire; 1 - SPI 3-wire
  */
#define LPS22HB_ODR_MASK                (uint8_t)0x70
#define LPS22HB_LPFP_MASK               (uint8_t)0x08
#define LPS22HB_LPFP_CUTOFF_MASK        (uint8_t)0x04
#define LPS22HB_BDU_MASK                (uint8_t)0x02
#define LPS22HB_SIM_MASK                (uint8_t)0x01
#define LPS22HB_LPFP_BIT                LPS22HB_BIT(3)

/** Control  Register 2. Default value: 0x10
  *        7 BOOT:  Reboot memory content. 0: normal mode; 1: reboot memory content. Self-clearing upon completation
  *        6 FIFO_EN: FIFO Enable. 0: disable; 1:  enable
  *        5 STOP_ON_FTH: Stop on FIFO Threshold  FIFO Watermark level use. 0: disable; 1: enable
  *        4 IF_ADD_INC: Register address automatically incrementeed during a multiple byte access with a serial interface (I2C or SPI). 
  *                      Default value 1.( 0: disable; 1: enable)
  *        3 I2C DIS:  Disable I2C interface 0: I2C Enabled; 1: I2C disabled
  *        2 SWRESET: Software reset. 0: normal mode; 1: SW reset. Self-clearing upon completation
  *        1 AUTO_ZERO: Autozero enable. 0: normal mode; 1: autozero enable.
  *        0 ONE_SHOT: One shot enable. 0: waiting for start of conversion; 1: start for a new dataset
  */
#define LPS22HB_BOOT_BIT       LPS22HB_BIT(7)
#define LPS22HB_FIFO_EN_BIT    LPS22HB_BIT(6)
#define LPS22HB_WTM_EN_BIT     LPS22HB_BIT(5)
#define LPS22HB_ADD_INC_BIT    LPS22HB_BIT(4)
#define LPS22HB_I2C_BIT        LPS22HB_BIT(3)
#define LPS22HB_SW_RESET_BIT   LPS22HB_BIT(2)
#define LPS22HB_FIFO_EN_MASK   (uint8_t)0x40
#define LPS22HB_WTM_EN_MASK    (uint8_t)0x20
#define LPS22HB_ADD_INC_MASK   (uint8_t)0x10
#define LPS22HB_I2C_MASK       (uint8_t)0x08
#define LPS22HB_ONE_SHOT_MASK  (uint8_t)0x01

/**
  * @brief CTRL Reg3 Interrupt Control Register
  *        Read/write
  *        Default value: 0x00
  *        7 INT_H_L: Interrupt active high, low. 0:active high; 1: active low.
  *        6 PP_OD: Push-Pull/OpenDrain selection on interrupt pads. 0: Push-pull; 1: open drain.
  *        5 F_FSS5: FIFO full flag on INT_DRDY pin. Defaul value: 0. (0: Diasable; 1 : Enable).
  *        4 F_FTH: FIFO threshold (watermark) status on INT_DRDY pin. Defaul value: 0. (0: Diasable; 1 : Enable).
  *        3 F_OVR: FIFO overrun interrupt on INT_DRDY pin. Defaul value: 0. (0: Diasable; 1 : Enable).
  *        2 DRDY: Data-ready signal on INT_DRDY pin. Defaul value: 0. (0: Diasable; 1 : Enable).
  *        1:0 INT_S2, INT_S1: data signal on INT pad control bits.
  *           INT_S2  | INT_S1  | INT pin
  *          ------------------------------------------------------
  *               0       |      0      |     Data signal( in order of priority:PTH_DRDY or F_FTH or F_OVR_or F_FSS5
  *               0       |      1      |     Pressure high (P_high)
  *               1       |      0      |     Pressure low (P_low)
  *               1       |      1      |     P_low OR P_high
  */
#define LPS22HB_PP_OD_BIT         LPS22HB_BIT(6)
#define LPS22HB_FIFO_FULL_BIT     LPS22HB_BIT(5)
#define LPS22HB_FIFO_FTH_BIT      LPS22HB_BIT(4)
#define LPS22HB_FIFO_OVR_BIT      LPS22HB_BIT(3)
#define LPS22HB_DRDY_BIT          LPS22HB_BIT(2)
#define LPS22HB_INT_H_L_MASK      (uint8_t)0x80
#define LPS22HB_PP_OD_MASK        (uint8_t)0x40
#define LPS22HB_FIFO_FULL_MASK    (uint8_t)0x20
#define LPS22HB_FIFO_FTH_MASK     (uint8_t)0x10
#define LPS22HB_FIFO_OVR_MASK     (uint8_t)0x08
#define LPS22HB_DRDY_MASK         (uint8_t)0x04
#define LPS22HB_INT_S12_MASK      (uint8_t)0x03

/** Interrupt Differential configuration Register. Default value: 0x00.
  *        7 AUTORIFP: AutoRifP Enable
  *        6 RESET_ARP: Reset AutoRifP function
  *        4 AUTOZERO: Autozero enabled
  *        5 RESET_AZ: Reset Autozero Function
  *        3 DIFF_EN: Interrupt generation enable
  *        2 LIR: Latch Interrupt request into INT_SOURCE register. 0 - interrupt request not latched
  *                                                                 1 - interrupt request latched
  *        1 PL_E: Enable interrupt generation on differential pressure low event. 0 - disable; 1 - enable
  *        0 PH_E: Enable interrupt generation on differential pressure high event. 0 - disable; 1 - enable
  */
#define LPS22HB_DIFF_EN_BIT       LPS22HB_BIT(3)
#define LPS22HB_LIR_BIT           LPS22HB_BIT(2)
#define LPS22HB_PLE_BIT           LPS22HB_BIT(1)
#define LPS22HB_PHE_BIT           LPS22HB_BIT(0)
#define LPS22HB_AUTORIFP_MASK     (uint8_t)0x80
#define LPS22HB_RESET_ARP_MASK    (uint8_t)0x40
#define LPS22HB_AUTOZERO_MASK     (uint8_t)0x20
#define LPS22HB_RESET_AZ_MASK     (uint8_t)0x10
#define LPS22HB_DIFF_EN_MASK      (uint8_t)0x08
#define LPS22HB_LIR_MASK          (uint8_t)0x04
#define LPS22HB_PLE_MASK          (uint8_t)0x02
#define LPS22HB_PHE_MASK          (uint8_t)0x01

/**Interrupt source Register (It is cleared by reading it. It is read only)
  *        7 BOOT_STATUS:  If 1 indicates that the Boot (Reboot) phase is running.
  *        6:3 Reserved: Keep these bits at 0
  *        2 IA: Interrupt Active.0: no interrupt has been generated
  *                               1: one or more interrupt events have been generated.
  *        1 PL: Differential pressure Low. 0: no interrupt has been generated
  *                                         1: Low differential pressure event has occurred.
  *        0 PH: Differential pressure High. 0: no interrupt has been generated
  *                                          1: High differential pressure event has occurred.
  */
#define LPS22HB_BOOT_STATUS_BIT        LPS22HB_BIT(7)
#define LPS22HB_IA_BIT                 LPS22HB_BIT(2)
#define LPS22HB_PL_BIT                 LPS22HB_BIT(1)
#define LPS22HB_PH_BIT                 LPS22HB_BIT(0)
#define LPS22HB_BOOT_STATUS_MASK      (uint8_t)0x80
#define LPS22HB_IA_MASK               (uint8_t)0x04
#define LPS22HB_PL_MASK               (uint8_t)0x02
#define LPS22HB_PH_MASK               (uint8_t)0x01

/** Status Register (Read only)
  *         7:6 Reserved: 0
  *         5 T_OR: Temperature data overrun. 0: no overrun has occurred
  *                                           1: a new data for temperature has overwritten the previous one.
  *         4 P_OR: Pressure data overrun. 0: no overrun has occurred
  *                                        1: new data for pressure has overwritten the previous one.
  *         3:2 Reserved: 0
  *         1 T_DA: Temperature data available. 0: new data for temperature is not yet available
  *                                             1: new data for temperature is available.
  *         0 P_DA: Pressure data available. 0: new data for pressure is not yet available
  *                                          1: new data for pressure is available.
  */
#define LPS22HB_TOR_BIT            LPS22HB_BIT(5)
#define LPS22HB_POR_BIT            LPS22HB_BIT(4)
#define LPS22HB_TDA_BIT            LPS22HB_BIT(1)
#define LPS22HB_PDA_BIT            LPS22HB_BIT(0)
#define LPS22HB_TOR_MASK           (uint8_t)0x20
#define LPS22HB_POR_MASK           (uint8_t)0x10
#define LPS22HB_TDA_MASK           (uint8_t)0x02
#define LPS22HB_PDA_MASK           (uint8_t)0x01

/** FIFO control register. Default value: 0x00
  *        7:5 F_MODE2, F_MODE1, F_MODE0: FIFO mode selection.
  *            FM2   | FM1   | FM0   |    FIFO MODE
  *          ---------------------------------------------------
  *             0    |  0    |  0    | BYPASS MODE
  *             0    |  0    |  1    | FIFO MODE. Stops collecting data when full
  *             0    |  1    |  0    | STREAM MODE: Keep the newest measurements in the FIFO
  *             0    |  1    |  1    | STREAM MODE until trigger deasserted, then change to FIFO MODE
  *             1    |  0    |  0    | BYPASS MODE until trigger deasserted, then STREAM MODE
  *             1    |  0    |  1    | Reserved for future use
  *             1    |  1    |  0    | Reserved
  *             1    |  1    |  1    | BYPASS mode until trigger deasserted, then FIFO MODE
  *       
  *        4:0 WTM_POINT4-0 : FIFO Watermark level selection (0-31)
  */
#define LPS22HB_FIFO_MODE_MASK        (uint8_t)0xE0
#define LPS22HB_WTM_POINT_MASK        (uint8_t)0x1F

/** FIFO Status register (Read only)
  *        7 FTH_FIFO: FIFO threshold status. 0:FIFO filling is lower than FTH level
  *                                           1: FIFO is equal or higher than FTH level.
  *        6 OVR: Overrun bit status. 0 - FIFO not full
  *                                   1 - FIFO is full and at least one sample in the FIFO has been overwritten.
  *        5:0 FSS: FIFO Stored data level. 000000: FIFO empty, 100000: FIFO is full and has 32 unread samples.
  */
#define LPS22HB_FTH_FIFO_BIT          LPS22HB_BIT(7)
#define LPS22HB_OVR_FIFO_BIT          LPS22HB_BIT(6)
#define LPS22HB_FTH_FIFO_MASK         (uint8_t)0x80
#define LPS22HB_OVR_FIFO_MASK         (uint8_t)0x40
#define LPS22HB_LEVEL_FIFO_MASK       (uint8_t)0x3F
#define LPS22HB_FIFO_EMPTY            (uint8_t)0x00
#define LPS22HB_FIFO_FULL             (uint8_t)0x20


#ifdef __cplusplus
}
#endif

#endif /* __LPS22HB_DEF_H */
