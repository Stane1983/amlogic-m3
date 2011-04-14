// ----------------------------------------------------------------------
// This file is automatically generated from the script:
// 
// ./create_stb_define_for_C_code.pl
// 
// and was applied to the file
// 
// ./stb_define.h
// 
// DO NOT EDIT!!!!!
// ----------------------------------------------------------------------
// 
#ifdef C_STB_DEFINE_H
#else
#define C_STB_DEFINE_H

//========================================================================
//  STB Registers Start
//========================================================================
// -----------------------------------------------
#define STB_CBUS_BASE           0x1600
// -----------------------------------------------
// There are two instantiations under one CBUS slave.  Each CBUS slave can support
// 256 registers.  Each demux is allocated 128 registers so set the offset in
// the middle
// Copy this define but don't add a base address
#define DEMUX_1_OFFSET         0x00
#define DEMUX_2_OFFSET         0x50
#define DEMUX_3_OFFSET         0xa0
//========================================================================
//  STB TOP Registers				    (8'hf0 - 8'hf7)
//========================================================================
// bit 22 -- invert fec_error for S2P1
// bit 21 -- invert fec_data for S2P1
// bit 20 -- invert fec_sync for S2P1
// bit 19 -- invert fec_valid for S2P1
// bit 18 -- invert fec_clk for S2P1
// bit 17:16 -- fec_s_sel for S2P1  00 - select TS0, 01 -- select TS1, 10 -- select TS2, 11 - reserved
// Bit 15 -- enable_des_pl_clk
// Bit 14:13 -- reserved
// Bit 12:10 -- ts_out_select, 0-TS0, 1-TS1, 2-TS2, 3,4-Reserved, 5-S2P1, 6-S2P0, 7-File
// bit 9:8 -- des_i_sel 00 -- select demux0 as des input, 01 -- select_demux1, 10 -- select_demux2, 11 - reserved
// bit 7 -- enable_des_pl
// bit 6 -- invert fec_error for S2P0
// bit 5 -- invert fec_data for S2P0
// bit 4 -- invert fec_sync for S2P0
// bit 3 -- invert fec_valid for S2P0
// bit 2 -- invert fec_clk for S2P0
// bit 1:0 -- fec_s_sel for S2P0  00 - select TS0, 01 -- select TS1, 10 -- select TS2, 11 - reserved
#define STB_TOP_CONFIG          (STB_CBUS_BASE + 0xf0) // 0x16f0
    /*----------- bit define -----------*/
    #define INVERT_S2P1_FEC_ERROR       22
    #define INVERT_S2P1_FEC_DATA        21
    #define INVERT_S2P1_FEC_SYNC        20
    #define INVERT_S2P1_FEC_VALID       19
    #define INVERT_S2P1_FEC_CLK         18
    #define S2P1_FEC_SERIAL_SEL         16
    #define ENABLE_DES_PL_CLK           15
    #define TS_OUTPUT_SOURCE            10
    #define DES_INPUT_SEL               8
    #define ENABLE_DES_PL               7
    #define INVERT_S2P0_FEC_ERROR       6
    #define INVERT_S2P0_FEC_DATA        5
    #define INVERT_S2P0_FEC_SYNC        4
    #define INVERT_S2P0_FEC_VALID       3
    #define INVERT_S2P0_FEC_CLK         2
    #define S2P0_FEC_SERIAL_SEL         0

// 15:8 -- TS_package_length_sub_1 (default : 187)
//  7:0 -- fec_sync_byte (default : 0x47)
#define TS_TOP_CONFIG           (STB_CBUS_BASE + 0xf1) // 0x16f1
    /*----------- bit define -----------*/
    #define TS_PACKAGE_LENGTH_SUB_1     8
    #define FEC_DEFAULT_SYNC_BYTE       0

// Bit 23:16 -- file_m2ts_skip_bytes
// Bit 15:8 -- des_out_dly
// Bit 7:6 -- transport_scrambling_control_odd // should be 3
// Bit 5 -- ts_hiu_enable
// Bit 4:0 -- fec_clk_div
#define TS_FILE_CONFIG          (STB_CBUS_BASE + 0xf2) // 0x16f2
    /*----------- bit define -----------*/
    #define FILE_M2TS_SKIP_BYTES        16
    #define DES_OUT_DLY                 8
    #define TRANSPORT_SCRAMBLING_CONTROL_ODD 6
    #define TS_HIU_ENABLE               5
    #define FEC_FILE_CLK_DIV            0

// Bit 13:8 -- des ts pl state   -- Read Only
// Bit 3:0 PID index to 8 PID to get key-set
// auto increse after TS_PL_PID_DATA read/write
#define TS_PL_PID_INDEX         (STB_CBUS_BASE + 0xf3) // 0x16f3
    /*----------- bit define -----------*/
    #define DES_TS_PL_STATE             8

// Bit 13 -- PID match disble
// Bit 12:0 -- PID
#define TS_PL_PID_DATA          (STB_CBUS_BASE + 0xf4) // 0x16f4
    /*----------- bit define -----------*/
    #define PID_MATCH_DISABLE_HIGH       29
    #define PID_MATCH_HIGH               16
    #define PID_MATCH_DISABLE_LOW        13
    #define PID_MATCH_LOW                0

#define COMM_DESC_KEY0          (STB_CBUS_BASE + 0xf5) // 0x16f5 // Common descrambler key (key bits[63:32])
#define COMM_DESC_KEY1          (STB_CBUS_BASE + 0xf6) // 0x16f6 // Common descrambler key (key bits[31:0])
#define COMM_DESC_KEY_RW        (STB_CBUS_BASE + 0xf7) // 0x16f7 // bits[3:0] point to the address to write the key {COMM_DESC_KEY1, COMM_DESC_KEY0}
                                                                 // Writing this register writes the key to RAM

//========================================================================
//  Multiple STB Registers				    (8'h00 - 8'h45)
//========================================================================
// STB registers are 8'h0x
// Bit 15:0 -- version number : 0x0002  (v0.01)
#define STB_VERSION             (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x00)  // 0x1600 // read only
#define STB_VERSION_2           (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x00)  // 0x1650 // read only
#define STB_VERSION_3           (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x00)  // 0x16a0 // read only

#define STB_TEST_REG            (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x01)  // 0x1601
#define STB_TEST_REG_2          (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x01)  // 0x1651
#define STB_TEST_REG_3          (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x01)  // 0x16a1

// Bit 15 -- fec_core_select 1 - select descramble output
// Bit 14:12 -  fec_select 0-TS0, 1-TS1, 2-TS2, 3,4-Reserved, 5-S2P1, 6-S2P0, 7-File 
// Bit 11 -- FEC_CLK
// Bit 10 -- SOP
// Bit 9 -- D_VALID
// Bit 8 -- D_FAIL
// Bit 7:0 -- D_DATA 7:0
#define FEC_INPUT_CONTROL       (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x02)  // 0x1602
#define FEC_INPUT_CONTROL_2     (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x02)  // 0x1652
#define FEC_INPUT_CONTROL_3     (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x02)  // 0x16a2
    /*----------- bit define -----------*/
    #define FEC_CORE_SEL               15
    #define FEC_SEL                    12
    #define FEC_INPUT_FEC_CLK          11
    #define FEC_INPUT_SOP              10
    #define FEC_INPUT_D_VALID           9
    #define FEC_INPUT_D_FAIL            8

#define FEC_INPUT_DATA          (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x03)  // 0x1603 // read only
#define FEC_INPUT_DATA_2        (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x03)  // 0x1653 // read only
#define FEC_INPUT_DATA_3        (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x03)  // 0x16a3 // read only

// bit 31 -- enable_free_clk_fec_data_valid
// bit 30 -- enable_free_clk_stb_reg
// bit 29:21 -- reserved
// bit 20 (bit 4) -- Bypass use recoder path
// bit 19 (bit 3) -- clear_PID_continuity_counter_valid
// bit 18 (bit 2) -- Disable Splicing
// bit 17 (bit 1) -- Insert PES_STRONG_SYNC in Audio PES
// bit 16 (bit 0) -- Insert PES_STRONG_SYNC in Video PES
// Bit 15 - do not trust section length
// Bit 14 - om cmd push even zero
// Bit 13 - reserved
// Bit 12 - SUB, OTHER PES interrupt at beginning of PES
// Bit 11 - discard_av_package -- for ts_recorder use only 
// Bit 10 - ts_recorder_select  0:after PID filter 1:before PID filter
// Bit 9 - ts_recorder_enable
// Bit 8 - (table_id == 0xff) means section_end
// Bit 7 - do not send uncomplete section
// Bit 6 - do not discard duplicate package
// Bit 5 - search SOP when trasport_error_indicator
// Bit 4 - stb demux enable
// Bit 3 - do not reset state machine on SOP
// Bit 2 - search SOP when error happened ( when ignore_fail_n_sop, will have this case)
// Bit 1 - do not use SOP input ( check FEC sync byte instead )
// Bit 0 - ignore fec_error bit when non sop ( check error on SOP only)
#define DEMUX_CONTROL           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x04)  // 0x1604
#define DEMUX_CONTROL_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x04)  // 0x1654
#define DEMUX_CONTROL_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x04)  // 0x16a4
    /*----------- bit define -----------*/
    #define ENABLE_FREE_CLK_FEC_DATA_VALID          31
    #define ENABLE_FREE_CLK_STB_REG                 30
    #define BYPASS_USE_RECODER_PATH                 20
    #define CLEAR_PID_CONTINUITY_COUNTER_VALID      19
    #define DISABLE_SPLICING                        18
    #define INSERT_AUDIO_PES_STRONG_SYNC            17
    #define INSERT_VIDEO_PES_STRONG_SYNC            16
    #define SECTION_LENGTH_UNTRUSTY                 15
    #define OM_CMD_PUSH_EVEN_ZERO                   14
    #define OTHER_INT_AT_PES_BEGINING               12
    #define DISCARD_AV_PACKAGE                      11
    #define TS_RECORDER_SELECT                      10
    #define TS_RECORDER_ENABLE                      9
    #define SECTION_END_WITH_TABLE_ID               8
    #define SEND_COMPLETE_SECTION_ONLY              7
    #define KEEP_DUPLICATE_PACKAGE                  6
    #define SEACH_SOP_ON_TRANSPORT_ERROR            5
    #define STB_DEMUX_ENABLE                        4
    #define NO_RESET_ON_SOP                         3
    #define SEARCH_SOP_ON_ERROR                     2
    #define NOT_USE_OF_SOP_INPUT                    1
    #define IGNORE_NONSOP_FEC_ERROR                 0

// bit 15:8 demux package length - 1 ( default : 187 )
// bit 7:0 default is 0x47
#define FEC_SYNC_BYTE           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x05)  // 0x1605
#define FEC_SYNC_BYTE_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x05)  // 0x1655
#define FEC_SYNC_BYTE_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x05)  // 0x16a5

/******************************************************************************************************
FM Memory Usage :
0-15 (32 PID filter target) ---- 15:13-PID type 12:0-PID target or force data
(force data : 1 will mask corespoding bit, 0 will disable this PID filter channel)
advanced setting -- bit 7:0
                    bit 7 -- PID bit 12:11 compare result force  
                    bit 6 -- PID bit 10:9 compare result force  
                    bit 5 -- PID bit 8:7 compare result force  
                    bit 4 -- PID bit 6:5 compare result force  
                    bit 3 -- PID bit 4:3 compare result force  
                    bit 2 -- PID bit 2 compare result force  
                    bit 1 -- PID bit 1 compare result force  
                    bit 0 -- PID bit 0 compare result force  
16-255(15x32 Section filter target) 
For first byte : Table_ID
---- 15-Mask High 4-bits 
     14-Mask Low 4-bits 
     13-disable_PID_check 
     12:8-PIDindex 
     7:0-section target (always EQ)
For rest of bytes :
---- 15-Mask 14-EQ/NE 13-disable_PID_check 12:8-PIDindex 7:0-section target (or force data)
advanced setting -- bit 7:0 force compare result
******************************************************************************************************/
    /*----------- bit define -----------*/
    #define PID_TYPE                                13
    #define PID_TARGET                              0

    #define SECTION_FIRSTBYTE_MASKHIGH              15
    #define SECTION_FIRSTBYTE_MASKLOW               14
    #define SECTION_FIRSTBYTE_DISABLE_PID_CHECK     13
    #define SECTION_FIRSTBYTE_PID_INDEX             8
    #define SECTION_TARGET                          0

    #define SECTION_RESTBYTE_MASK                   15
    #define SECTION_RESTBYTE_MASK_EQ                14
    #define SECTION_RESTBYTE_DISABLE_PID_CHECK      13
    #define SECTION_RESTBYTE_PID_INDEX              8

// bit 31:16 -- filter memory write data hi[31:16]
// bit 15:0 -- filter memory write data low [15:0]
#define FM_WR_DATA              (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x06)  // 0x1606
#define FM_WR_DATA_2            (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x06)  // 0x1656
#define FM_WR_DATA_3            (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x06)  // 0x16a6
    /*----------- bit define -----------*/
    #define FM_WR_DATA_HI                           16

// bit 31:24 -- advanced setting hi
// bit 23:16 -- advanced setting low
// bit 15 -- filter memory write data request
// bit 7:0 -- filter memory write addr
#define FM_WR_ADDR              (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x07)  // 0x1607
#define FM_WR_ADDR_2            (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x07)  // 0x1657
#define FM_WR_ADDR_3            (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x07)  // 0x16a7
    /*----------- bit define -----------*/
    #define FM_ADVANCED_SETTING_HI                  24
    #define FM_ADVANCED_SETTING_LO                  16
    #define FM_WR_DATA_REQUEST                      15

// bit 13:8 demux state  -- read only
// bit 7:4 -- maxnum section filter compare address
// bit 3:0 -- maxnum PID filter compare address
#define MAX_FM_COMP_ADDR        (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x08)  // 0x1608
#define MAX_FM_COMP_ADDR_2      (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x08)  // 0x1658
#define MAX_FM_COMP_ADDR_3      (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x08)  // 0x16a8
    /*----------- bit define -----------*/
    #define DEMUX_STATE                             8
    #define MAX_FM_SECTION_FILTER_COMP_ADDR         4

// bit 15 - transport_error_indicator
// bit 14 - payload_unit_start_indicator
// bit 13 - transport_priority
// bit 12:0 - PID
#define TS_HEAD_0               (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x09)  // 0x1609
#define TS_HEAD_0_2             (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x09)  // 0x1659
#define TS_HEAD_0_3             (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x09)  // 0x16a9
    /*----------- bit define -----------*/
    #define TRANSPORT_ERROR_INDICATOR               15
    #define PAYLOAD_UNIT_START_INDICATOR            14
    #define TRANSPORT_PRIORITY                      13

// bit 7:6 transport_scrambling_control
// bit 5:4 adaptation_field_control
// bit 3:0 continuity_counter
#define TS_HEAD_1               (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x0a)  // 0x160a
#define TS_HEAD_1_2             (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x0a)  // 0x165a
#define TS_HEAD_1_3             (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x0a)  // 0x16aa
    /*----------- bit define -----------*/
    #define TRANSPORT_SCRAMBLING_CONTROL            6
    #define ADAPTATION_FIELD_CONTROL                4

// bit 15:12 -- om_cmd_count (read only)
// bit  11:9 -- overflow_count // bit  11:9 -- om_cmd_wr_ptr (read only)
// bit   8:6 -- om_overwrite_count // bit   8:6 -- om_cmd_rd_ptr (read only)
// bit   5:3 -- type_stb_om_w_rd (read only)
// bit     2 -- unit_start_stb_om_w_rd (read only)
// bit     1 -- om_cmd_overflow (read only)
// bit     0 -- om_cmd_pending (read) 
// bit     0 -- om_cmd_read_finished (write)
#define OM_CMD_STATUS           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x0b)  // 0x160b
#define OM_CMD_STATUS_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x0b)  // 0x165b
#define OM_CMD_STATUS_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x0b)  // 0x16ab
    /*----------- bit define -----------*/
    #define OM_CMD_COUNT                            12
    #define OM_OVERFLOW_COUNT                       9
    #define OM_OVERWRITE_COUNT                      6
    #define TYPE_STB_OM_W_RD                        3
    #define UNIT_START_STB_OM_W_RD                  2
    #define OM_CMD_OVERFLOW                         1

// bit 15:9 -- count_stb_om_w_rd  (read only)
// bit 8:0 -- start_stb_om_wa_rd (read only)
#define OM_CMD_DATA             (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x0c)  // 0x160c
#define OM_CMD_DATA_2           (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x0c)  // 0x165c
#define OM_CMD_DATA_3           (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x0c)  // 0x16ac
    /*----------- bit define -----------*/
    #define COUNT_STB_OM_W_RD                       9

// bit 11:0 -- offset for section data
#define OM_CMD_DATA2            (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x0d)  // 0x160d
#define OM_CMD_DATA2_2          (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x0d)  // 0x165d
#define OM_CMD_DATA2_3          (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x0d)  // 0x16ad

// bit 31:16 -- base address for section buffer group 0 (*0x400 to get real address)
// bit 15:0 -- base address for section buffer group 1 (*0x400 to get real address)
#define SEC_BUFF_01_START       (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x0e)  // 0x160e
#define SEC_BUFF_01_START_2     (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x0e)  // 0x165e
#define SEC_BUFF_01_START_3     (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x0e)  // 0x16ae
    /*----------- bit define -----------*/
    #define SEC_BUFF_0_BASE_ADDR                    16

// bit 31:16 -- base address for section buffer group 2 (*0x400 to get real address)
// bit 15:0 -- base address for section buffer group 3 (*0x400 to get real address)
#define SEC_BUFF_23_START       (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x0f)  // 0x160f
#define SEC_BUFF_23_START_2     (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x0f)  // 0x165f
#define SEC_BUFF_23_START_3     (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x0f)  // 0x16af
    /*----------- bit define -----------*/
    #define SEC_BUFF_2_BASE_ADDR                    16

// bit 15:12 -- section buffer size for group 3
// bit 11:8 -- section buffer size for group 2
// bit 7:4 -- section buffer size for group 1
// bit 3:0 -- section buffer size for group 0 (bit used,  for example, 10 means 1K)
#define SEC_BUFF_SIZE           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x10)  // 0x1610
#define SEC_BUFF_SIZE_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x10)  // 0x1660
#define SEC_BUFF_SIZE_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x10)  // 0x16b0
    /*----------- bit define -----------*/
    #define SEC_BUFF_3_SIZE                        12
    #define SEC_BUFF_2_SIZE                         8
    #define SEC_BUFF_1_SIZE                         4

// section buffer busy status for buff 31:0 ( Read Only )
#define SEC_BUFF_BUSY           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x11)  // 0x1611
#define SEC_BUFF_BUSY_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x11)  // 0x1661
#define SEC_BUFF_BUSY_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x11)  // 0x16b1

// section buffer write status for buff 31:0 -- Read
// clear buffer status ( buff READY and BUSY ) -- write
#define SEC_BUFF_READY          (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x12)  // 0x1612
#define SEC_BUFF_READY_2        (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x12)  // 0x1662
#define SEC_BUFF_READY_3        (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x12)  // 0x16b2

// bit 15 -- section_reset_busy (Read Only)
// bit 14 -- output_section_buffer_valid
// bit 12:8 -- SEC_BUFFER_NUMBER for the INDEX buffer  Read_Only
// bit 4:0 -- SEC_BUFFER_INDEX   RW
#define SEC_BUFF_NUMBER         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x13)  // 0x1613
#define SEC_BUFF_NUMBER_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x13)  // 0x1663
#define SEC_BUFF_NUMBER_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x13)  // 0x16b3
    /*----------- bit define -----------*/
    #define SECTION_RESET_BUSY                      15
    #define OUTPUT_SECTION_BUFFER_VALID             14
    #define INDEXED_SEC_BUFF_NUMBER                 8

// bit 9:5 -- BYPASS PID number
// bit 4:0 -- PCR PID number
#define ASSIGN_PID_NUMBER       (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x14)  // 0x1614
#define ASSIGN_PID_NUMBER_2     (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x14)  // 0x1664
#define ASSIGN_PID_NUMBER_3     (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x14)  // 0x16b4
    /*----------- bit define -----------*/
    #define BYPASS_PID_NUMBER                       5

// bit 15:0 -- stream_id filter bit enable
// bit 7:0 -- stream_id filter target
#define VIDEO_STREAM_ID         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x15)  // 0x1615
#define VIDEO_STREAM_ID_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x15)  // 0x1665
#define VIDEO_STREAM_ID_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x15)  // 0x16b5

#define AUDIO_STREAM_ID         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x16)  // 0x1616
#define AUDIO_STREAM_ID_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x16)  // 0x1666
#define AUDIO_STREAM_ID_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x16)  // 0x16b6

#define SUB_STREAM_ID           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x17)  // 0x1617
#define SUB_STREAM_ID_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x17)  // 0x1667
#define SUB_STREAM_ID_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x17)  // 0x16b7

#define OTHER_STREAM_ID         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x18)  // 0x1618
#define OTHER_STREAM_ID_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x18)  // 0x1668
#define OTHER_STREAM_ID_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x18)  // 0x16b8

// bit 12 -- PCR_EN
// bit 11:0 -- PCR90K_DIV
#define PCR90K_CTL              (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x19)  // 0x1619
#define PCR90K_CTL_2            (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x19)  // 0x1669
#define PCR90K_CTL_3            (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x19)  // 0x16b9
    /*----------- bit define -----------*/
    #define PCR_EN                     12
    
// bit 15:0 -- PCR[31:0] R/W
#define PCR_DEMUX               (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x1a)  // 0x161a
#define PCR_DEMUX_2             (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x1a)  // 0x166a
#define PCR_DEMUX_3             (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x1a)  // 0x16ba

// bit 15:0 -- VPTS[31:0] R/W
#define VIDEO_PTS_DEMUX         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x1b)  // 0x161b
#define VIDEO_PTS_DEMUX_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x1b)  // 0x166b
#define VIDEO_PTS_DEMUX_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x1b)  // 0x16bb

// bit 15:0 -- VDTS[31:0] R/W
#define VIDEO_DTS_DEMUX         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x1c)  // 0x161c
#define VIDEO_DTS_DEMUX_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x1c)  // 0x166c
#define VIDEO_DTS_DEMUX_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x1c)  // 0x16bc

// bit 15:0 -- APTS[31:0] R/W
#define AUDIO_PTS_DEMUX         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x1d)  // 0x161d
#define AUDIO_PTS_DEMUX_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x1d)  // 0x166d
#define AUDIO_PTS_DEMUX_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x1d)  // 0x16bd

// bit 15:0 -- SPTS[31:0] R/W
#define SUB_PTS_DEMUX           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x1e)  // 0x161e
#define SUB_PTS_DEMUX_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x1e)  // 0x166e
#define SUB_PTS_DEMUX_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x1e)  // 0x16be

// read -- status, write 1 clear status
// bit 15 -- SUB_PTS[32]
// bit 14 -- AUDIO_PTS[32]
// bit 13 -- VIDEO_DTS[32]
// bit 12 -- VIDEO_PTS[32]
// bit 3 -- sub_pts_ready
// bit 2 -- audio_pts_ready
// bit 1 -- video_dts_ready
// bit 0 -- video_pts_ready
#define STB_PTS_DTS_STATUS      (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x1f)  // 0x161f
#define STB_PTS_DTS_STATUS_2    (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x1f)  // 0x166f
#define STB_PTS_DTS_STATUS_3    (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x1f)  // 0x16bf
    /*----------- bit define -----------*/
    #define SUB_PTS_BIT32              15
    #define AUDIO_PTS_BIT32            14
    #define VIDEO_DTS_BIT32            13
    #define VIDEO_PTS_BIT32            12
    #define SUB_PTS_READY              3
    #define AUDIO_PTS_READY            2
    #define VIDEO_DTS_READY            1
    #define VIDEO_PTS_READY            0

// bit 3:0 --
//  0 -- adaptation_field_length[7:0], adaption_field_byte_1[7:0] 
//  1 -- stream_id[7:0], pes_header_bytes_left[7:0]
//  2 -- pes_package_bytes_left[15:0]
//  3 -- pes_ctr_byte[7:0], pes_flag_byte[7:0]
#define STB_DEBUG_INDEX         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x20)  // 0x1620
#define STB_DEBUG_INDEX_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x20)  // 0x1670
#define STB_DEBUG_INDEX_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x20)  // 0x16c0

// read only
#define STB_DEBUG_DATA_OUT      (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x21)  // 0x1621
#define STB_DEBUG_DATA_OUT_2    (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x21)  // 0x1671
#define STB_DEBUG_DATA_OUT_3    (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x21)  // 0x16c1

// default : 0x807f
// bit 15:9  -- MAX OM DMA COUNT  (default: 0x40) 
// bit 8:0   -- LAST ADDR OF OM ADDR (default: 127)
#define STB_OM_CTL              (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x22)  // 0x1622
#define STB_OM_CTL_2            (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x22)  // 0x1672
#define STB_OM_CTL_3            (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x22)  // 0x16c2
    /*----------- bit define -----------*/
    #define MAX_OM_DMA_COUNT           9
    #define LAST_OM_ADDR               0

// 15:0  WRITE 1 CLEAR to clear interrupt source
// 9 -- splicing_point
// 8 -- other_PES_int
// 7 -- sub_PES_int 
// 6 -- discontinuity
// 5 -- duplicated_pack_found
// 4 -- New PDTS ready
// 3 -- om_cmd_buffer ready for access
// 2 -- section buffer ready 
// 1 -- transport_error_indicator
// 0 -- TS ERROR PIN 
#define STB_INT_STATUS          (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x23)  // 0x1623
#define STB_INT_STATUS_2        (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x23)  // 0x1673
#define STB_INT_STATUS_3        (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x23)  // 0x16c3
    /*----------- bit define -----------*/
    #define PCR_READY                  11
    #define AUDIO_SPLICING_POINT       10
    #define VIDEO_SPLICING_POINT       9
    #define OTHER_PES_READY            8
    #define SUB_PES_READY              7
    #define DIS_CONTINUITY_PACKET      6
    #define DUPLICATED_PACKET          5
    #define NEW_PDTS_READY             4
    #define OM_CMD_READ_PENDING        3
    #define SECTION_BUFFER_READY       2
    #define TS_ERROR_PACKAGE           1
    #define TS_ERROR_PIN               0

// When Bit 31 - 1 write will indicate all type use sepertate endian (Write Only)
// When Bit 31 - 0 write will indicate all type else use Bit 8:6
// Bit 23:21 - demux om write endian control for OTHER_PES_PACKET
// Bit 20:18 - demux om write endian control for SCR_ONLY_PACKET
// Bit 17:15 - demux om write endian control for SUB_PACKET
// Bit 14:12 - demux om write endian control for AUDIO_PACKET
// Bit 11:9  - demux om write endian control for VIDEO_PACKET
// Bit 8:6 - demux om write endian control for else
// Bit 5:3 - demux om write endian control for bypass
// Bit 2:0 - demux om write endian control for section
#define DEMUX_ENDIAN            (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x24)  // 0x1624
#define DEMUX_ENDIAN_2          (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x24)  // 0x1674
#define DEMUX_ENDIAN_3          (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x24)  // 0x16c4
    /*----------- bit define -----------*/
    #define SEPERATE_ENDIAN            31
    #define OTHER_PES_ENDIAN           21
    #define SCR_ENDIAN                 18
    #define SUB_ENDIAN                 15
    #define AUDIO_ENDIAN               12
    #define VIDEO_ENDIAN               9
    #define OTHER_ENDIAN               6
    #define BYPASS_ENDIAN              3
    #define SECTION_ENDIAN             0

// Bit 7 -- use hi_bsf interface
#define TS_HIU_CTL              (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x25)  // 0x1625
#define TS_HIU_CTL_2            (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x25)  // 0x1675
#define TS_HIU_CTL_3            (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x25)  // 0x16c5
    /*----------- bit define -----------*/
    #define LAST_BURST_THRESHOLD       8
    #define USE_HI_BSF_INTERFACE       7

// bit 15:0 -- base address for section buffer start (*0x10000 to get real base)
#define SEC_BUFF_BASE           (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x26)  // 0x1626
#define SEC_BUFF_BASE_2         (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x26)  // 0x1676
#define SEC_BUFF_BASE_3         (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x26)  // 0x16c6

// bit 11 -- mask bit for OTHER_PES_AHB_DMA_EN
// bit 10 -- mask bit for SUB_AHB_DMA_EN
// bit 9 -- mask bit for BYPASS_AHB_DMA_EN
// bit 8 -- mask bit for SECTION_AHB_DMA_EN
// bit 7 -- mask bit for recoder stream
// bit 6:0 -- mask bit for each type
#define DEMUX_MEM_REQ_EN        (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x27)  // 0x1627
#define DEMUX_MEM_REQ_EN_2      (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x27)  // 0x1677
#define DEMUX_MEM_REQ_EN_3      (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x27)  // 0x16c7
    /*----------- bit define -----------*/
    #define OTHER_PES_AHB_DMA_EN       11
    #define SUB_AHB_DMA_EN             10
    #define BYPASS_AHB_DMA_EN          9
    #define SECTION_AHB_DMA_EN         8
    #define RECORDER_STREAM            7
    #define OTHER_PES_PACKET           6
    #define SCR_ONLY_PACKET            5
    #define BYPASS_PACKET              4
    #define SECTION_PACKET             3
    #define SUB_PACKET                 2
    #define AUDIO_PACKET               1
    #define VIDEO_PACKET               0

// bit 31:0 -- vb_wr_ptr for video PDTS 
#define VIDEO_PDTS_WR_PTR       (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x28)  // 0x1628
#define VIDEO_PDTS_WR_PTR_2     (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x28)  // 0x1678
#define VIDEO_PDTS_WR_PTR_3     (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x28)  // 0x16c8

// bit 31:0 -- ab_wr_ptr for audio PDTS
#define AUDIO_PDTS_WR_PTR       (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x29)  // 0x1629
#define AUDIO_PDTS_WR_PTR_2     (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x29)  // 0x1679
#define AUDIO_PDTS_WR_PTR_3     (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x29)  // 0x16c9

// bit 20:0 -- SB_WRITE_PTR (sb_wr_ptr << 3 == byte write position)
#define SUB_WR_PTR              (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x2a)  // 0x162a
#define SUB_WR_PTR_2            (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x2a)  // 0x167a
#define SUB_WR_PTR_3            (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x2a)  // 0x16ca

// bit 19:0 -- SB_START (sb_start << 12 == byte address);
#define SB_START                (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x2b)  // 0x162b
#define SB_START_2              (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x2b)  // 0x167b
#define SB_START_3              (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x2b)  // 0x16cb

// bit 20:0 -- SB_SIZE (sb_size << 3 == byte size, 16M maximun)
#define SB_LAST_ADDR            (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x2c)  // 0x162c
#define SB_LAST_ADDR_2          (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x2c)  // 0x167c
#define SB_LAST_ADDR_3          (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x2c)  // 0x16cc

// bit 31:0 -- sb_wr_ptr for sub PES
#define SB_PES_WRITE_PTR        (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x2d)  // 0x162d
#define SB_PES_WRITE_PTR_2      (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x2d)  // 0x167d
#define SB_PES_WRITE_PTR_3      (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x2d)  // 0x16cd

// bit 31:16 -- ob_wr_ptr for other PES
// bit 20:0 -- OB_WRITE_PTR (ob_wr_ptr << 3 == byte write position)
#define OTHER_WR_PTR            (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x2e)  // 0x162e
#define OTHER_WR_PTR_2          (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x2e)  // 0x167e
#define OTHER_WR_PTR_3          (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x2e)  // 0x16ce

// bit 19:0 -- OB_START (ob_start << 12 == byte address);
#define OB_START                (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x2f)  // 0x162f
#define OB_START_2              (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x2f)  // 0x167f
#define OB_START_3              (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x2f)  // 0x16cf

// bit 20:0 -- OB_SIZE (ob_size << 3 == byte size, 16M maximun)
#define OB_LAST_ADDR            (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x30)  // 0x1630
#define OB_LAST_ADDR_2          (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x30)  // 0x1680
#define OB_LAST_ADDR_3          (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x30)  // 0x16d0

// bit 31:0 -- ob_wr_ptr for sub PES
#define OB_PES_WRITE_PTR        (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x31)  // 0x1631
#define OB_PES_WRITE_PTR_2      (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x31)  // 0x1681
#define OB_PES_WRITE_PTR_3      (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x31)  // 0x16d1

// 15:0  DEMUX interrupt MASK
// 11 -- PCR_READY
// 10 -- audio_splicing_point
// 9 -- video_splicing_point
// 8 -- other_PES_int
// 7 -- sub_PES_int 
// 6 -- discontinuity
// 5 -- duplicated_pack_found
// 4 -- New PDTS ready
// 3 -- om_cmd_buffer ready for access
// 2 -- section buffer ready 
// 1 -- transport_error_indicator
// 0 -- TS ERROR PIN
#define STB_INT_MASK            (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x32)  // 0x1632
#define STB_INT_MASK_2          (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x32)  // 0x1682
#define STB_INT_MASK_3          (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x32)  // 0x16d2

// 31:16 VIDEO PID filter data
//15 -- splicing VIDEO PID change enable 
//14:10 -- VIDEO PID FILTER ADDRESS
// 9 -- PES splicing active (Read Only) 
// 8 -- splicing active (Read Only)
// 7:0  splicing countdown (Read Only)
#define VIDEO_SPLICING_CTL      (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x33)  // 0x1633
#define VIDEO_SPLICING_CTL_2    (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x33)  // 0x1683
#define VIDEO_SPLICING_CTL_3    (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x33)  // 0x16d3
    /*----------- bit define -----------*/
    #define VIDEO_PID_FILTER_DATA      16
    #define VIDEO_SPLICING_PID_CHANGE_ENABLE       15
    #define VIDEO_PID_FILTER_ADDRESS   10
    #define VIDEO_PES_SPLICING_ACTIVE  9
    #define VIDEO_SPLICING_ACTIVE      8


// 31:16 AUDIO PID filter data
//15 -- splicing AUDIO PID change enable 
//14:10 -- AUDIO PID FILTER ADDRESS
// 9 -- PES splicing active (Read Only) 
// 8 -- splicing active (Read Only)
// 7:0  splicing countdown (Read Only)
#define AUDIO_SPLICING_CTL      (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x34)  // 0x1634
#define AUDIO_SPLICING_CTL_2    (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x34)  // 0x1684
#define AUDIO_SPLICING_CTL_3    (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x34)  // 0x16d4
    /*----------- bit define -----------*/
    #define AUDIO_PID_FILTER_DATA      16
    #define AUDIO_SPLICING_PID_CHANGE_ENABLE       15
    #define AUDIO_PID_FILTER_ADDRESS   10
    #define AUDIO_PES_SPLICING_ACTIVE  9
    #define AUDIO_SPLICING_ACTIVE      8

// 23:16 M2TS_SKIP_BYTES
// 15:8 LAST TS PACKAGE BYTE COUNT (Read Only)
// 7:0  PACKAGE BYTE COUNT (Read Only)
#define TS_PACKAGE_BYTE_COUNT   (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x35)  // 0x1635
#define TS_PACKAGE_BYTE_COUNT_2 (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x35)  // 0x1685
#define TS_PACKAGE_BYTE_COUNT_3 (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x35)  // 0x16d5
    /*----------- bit define -----------*/
    #define M2TS_SKIP_BYTES            16
    #define LAST_TS_PACKAGE_BYTE_COUNT 8

// 15:0 2 bytes strong sync add to PES
#define PES_STRONG_SYNC         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x36)  // 0x1636
#define PES_STRONG_SYNC_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x36)  // 0x1686
#define PES_STRONG_SYNC_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x36)  // 0x16d6

// bit 15 -- stb_om_ren
// bit 14:11 -- reserved
// bit  10:0 -- OM_DATA_RD_ADDR
#define OM_DATA_RD_ADDR         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x37)  // 0x1637
#define OM_DATA_RD_ADDR_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x37)  // 0x1687
#define OM_DATA_RD_ADDR_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x37)  // 0x16d7
    /*----------- bit define -----------*/
    #define STB_OM_REN                 15

// bit 15:0 -- OM_DATA_RD
#define OM_DATA_RD              (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x38)  // 0x1638
#define OM_DATA_RD_2            (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x38)  // 0x1688
#define OM_DATA_RD_3            (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x38)  // 0x16d8

// AUTO STOP SETTING for 32 channels
// 4-bits per channel
// when write
// bit 3 -- set section active
// bit 2:0 -- auto stop after count (0 means never stop)
// when read
// bit 3 -- current active status (1 - active, 0 - stopped )
// bit 2:0 -- count down to auto stop
// section 31:24
#define SECTION_AUTO_STOP_3     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x39)  // 0x1639
#define SECTION_AUTO_STOP_3_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x39)  // 0x1689
#define SECTION_AUTO_STOP_3_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x39)  // 0x16d9
// section 23:16
#define SECTION_AUTO_STOP_2     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x3a)  // 0x163a
#define SECTION_AUTO_STOP_2_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x3a)  // 0x168a
#define SECTION_AUTO_STOP_2_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x3a)  // 0x16da
// section 15:8
#define SECTION_AUTO_STOP_1     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x3b)  // 0x163b
#define SECTION_AUTO_STOP_1_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x3b)  // 0x168b
#define SECTION_AUTO_STOP_1_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x3b)  // 0x16db
// section 7:0
#define SECTION_AUTO_STOP_0     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x3c)  // 0x163c
#define SECTION_AUTO_STOP_0_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x3c)  // 0x168c
#define SECTION_AUTO_STOP_0_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x3c)  // 0x16dc

// bit 31:0 reset channel status - each bit reset each channel 
// read -- 32 channel status 
#define DEMUX_CHANNEL_RESET     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x3d)  // 0x163d
#define DEMUX_CHANNEL_RESET_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x3d)  // 0x168d
#define DEMUX_CHANNEL_RESET_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x3d)  // 0x16dd

#define DEMUX_SCRAMBLING_STATE     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x3e)  // 0x163e
#define DEMUX_SCRAMBLING_STATE_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x3e)  // 0x168e
#define DEMUX_SCRAMBLING_STATE_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x3e)  // 0x16de

#define DEMUX_CHANNEL_ACTIVITY     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x3f)  // 0x163f
#define DEMUX_CHANNEL_ACTIVITY_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x3f)  // 0x168f
#define DEMUX_CHANNEL_ACTIVITY_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x3f)  // 0x16df

// bit 4 -- video_stamp_use_dts
// bit 3 -- audio_stamp_sync_1_en 
// bit 2 -- audio_stamp_insert_en 
// bit 1 -- video_stamp_sync_1_en 
// bit 0 -- video_stamp_insert_en
#define DEMUX_STAMP_CTL         (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x40)  // 0x1640
#define DEMUX_STAMP_CTL_2       (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x40)  // 0x1690
#define DEMUX_STAMP_CTL_3       (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x40)  // 0x16e0

#define DEMUX_VIDEO_STAMP_SYNC_0   (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x41)  // 0x1641
#define DEMUX_VIDEO_STAMP_SYNC_0_2 (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x41)  // 0x1691
#define DEMUX_VIDEO_STAMP_SYNC_0_3 (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x41)  // 0x16e1

#define DEMUX_VIDEO_STAMP_SYNC_1   (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x42)  // 0x1642
#define DEMUX_VIDEO_STAMP_SYNC_1_2 (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x42)  // 0x1692
#define DEMUX_VIDEO_STAMP_SYNC_1_3 (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x42)  // 0x16e2

#define DEMUX_AUDIO_STAMP_SYNC_0   (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x43)  // 0x1643
#define DEMUX_AUDIO_STAMP_SYNC_0_2 (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x43)  // 0x1693
#define DEMUX_AUDIO_STAMP_SYNC_0_3 (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x43)  // 0x16e3

#define DEMUX_AUDIO_STAMP_SYNC_1   (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x44)  // 0x1644
#define DEMUX_AUDIO_STAMP_SYNC_1_2 (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x44)  // 0x1694
#define DEMUX_AUDIO_STAMP_SYNC_1_3 (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x44)  // 0x16e4

// Write : Bit[4:0] secter filter number for reset
// Read  : select according to output_section_buffer_valid : 
//         per bit per section buffer valid status
//         or section_buffer_ignore
#define DEMUX_SECTION_RESET     (STB_CBUS_BASE + DEMUX_1_OFFSET + 0x45)  // 0x1645
#define DEMUX_SECTION_RESET_2   (STB_CBUS_BASE + DEMUX_2_OFFSET + 0x45)  // 0x1695
#define DEMUX_SECTION_RESET_3   (STB_CBUS_BASE + DEMUX_3_OFFSET + 0x45)  // 0x16e5

//========================================================================
//  STB Registers End
//========================================================================

#endif // C_STB_DEFINE_H

