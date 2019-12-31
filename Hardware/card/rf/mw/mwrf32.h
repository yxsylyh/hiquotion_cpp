extern "C"
{
void __stdcall usb_set_timeouts(unsigned long _TotalTimeOuts);

//1.
HANDLE __stdcall  rf_init(__int16 port,long baud);
//2.
__int16 __stdcall rf_exit(HANDLE icdev);
//3.
__int16 __stdcall rf_config(HANDLE icdev,unsigned char _Mode,unsigned char _Baud);
//4.
__int16 __stdcall rf_request(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType);
__int16 __stdcall rf_request_std(HANDLE icdev,unsigned char _Mode,unsigned __int16 *TagType);

//5.
__int16 __stdcall rf_anticoll(HANDLE icdev,unsigned char _Bcnt,unsigned long *_Snr);
//6.
__int16 __stdcall rf_select(HANDLE icdev,unsigned long _Snr,unsigned char *_Size);
//7.
__int16 __stdcall rf_authentication(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr);
//8.
__int16 __stdcall rf_halt(HANDLE icdev);
//9
__int16 __stdcall rf_read(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//10.
__int16 __stdcall rf_read_hex(HANDLE icdev,unsigned char _Adr, char *_Data);
//11.
__int16 __stdcall rf_write(HANDLE icdev,unsigned char _Adr,unsigned char *_Data);
//12.
__int16 __stdcall rf_write_hex(HANDLE icdev,unsigned char _Adr,char *_Data);
//13.
__int16 __stdcall rf_load_key(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned char *_NKey);
//14.
__int16 __stdcall rf_load_key_hex(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr, char *_NKey);
//15.
__int16 __stdcall rf_increment(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//16.
__int16 __stdcall rf_decrement(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//17
__int16 __stdcall rf_decrement_ml(HANDLE icdev,unsigned __int16 _Value);
//18.
__int16 __stdcall rf_restore(HANDLE icdev,unsigned char _Adr);
//19
__int16 __stdcall rf_transfer(HANDLE icdev,unsigned char _Adr);
//20.
__int16 __stdcall rf_card(HANDLE icdev,unsigned char _Mode,unsigned long *_Snr);
//21.
__int16 __stdcall rf_initval(HANDLE icdev,unsigned char _Adr,unsigned long _Value);
//22
__int16 __stdcall rf_initval_ml(HANDLE icdev,unsigned __int16 _Value);
//23.
__int16 __stdcall rf_readval(HANDLE icdev,unsigned char _Adr,unsigned long *_Value);
//24
__int16 __stdcall rf_readval_ml(HANDLE icdev,unsigned __int16 *_Value);
//25.
__int16 __stdcall rf_changeb3(HANDLE icdev,unsigned char _SecNr,unsigned char *_KeyA,unsigned char _B0,unsigned char _B1,unsigned char _B2,unsigned char _B3,unsigned char _Bk,unsigned char *_KeyB);
//26.
__int16 __stdcall rf_get_status(HANDLE icdev,unsigned char *_Status);
//27.
__int16 __stdcall rf_clr_control_bit(HANDLE icdev,unsigned char _b);
//28.
__int16 __stdcall rf_set_control_bit(HANDLE icdev,unsigned char _b);
//29.
__int16 __stdcall rf_reset(HANDLE icdev,unsigned __int16 _Msec);
//30.
__int16 __stdcall rf_HL_decrement(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//31.
__int16 __stdcall rf_HL_increment(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long _Snr,unsigned long *_NValue,unsigned long *_NSnr);
//32.
__int16 __stdcall rf_HL_write(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr,unsigned char *_Data);
//33.
__int16 __stdcall rf_HL_writehex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long *_Snr, char *_Data);
//34
__int16 __stdcall rf_HL_read(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr,unsigned char *_Data,unsigned long *_NSnr);
//35
__int16 __stdcall rf_HL_readhex(HANDLE icdev,unsigned char _Mode,unsigned char _Adr,unsigned long _Snr, char *_Data,unsigned long *_NSnr);
//36.
__int16 __stdcall rf_HL_initval(HANDLE icdev,unsigned char _Mode,unsigned char _SecNr,unsigned long _Value,unsigned long *_Snr);
//37.
__int16 __stdcall rf_beep(HANDLE icdev,unsigned short _Msec);
//38.
__int16 __stdcall rf_disp8(HANDLE icdev,__int16 pt_mode,unsigned char* disp_str);
//39.
__int16 __stdcall rf_disp(HANDLE icdev,unsigned char pt_mode,unsigned short digit);
//40.
__int16 __stdcall rf_encrypt(unsigned char *key,unsigned char *ptrSource, unsigned __int16 msgLen,unsigned char *ptrDest);
//41.
__int16 __stdcall rf_decrypt(unsigned char *key,unsigned char *ptrSource, unsigned __int16 msgLen,unsigned char *ptrDest);
//42
__int16 __stdcall rf_HL_authentication(HANDLE icdev,unsigned char reqmode,unsigned long snr,unsigned char authmode,unsigned char secnr);
//43
__int16 __stdcall rf_srd_eeprom(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char *rec_buffer);
//44
__int16 __stdcall rf_swr_eeprom(HANDLE icdev,__int16 offset,__int16 lenth,unsigned char* send_buffer);
//45
__int16 __stdcall rf_srd_snr(HANDLE icdev,__int16 lenth,unsigned char *rec_buffer);
//46
__int16 __stdcall rf_check_write(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr,unsigned char * _data);
//47
__int16 __stdcall rf_check_writehex(HANDLE icdev,unsigned long Snr,unsigned char authmode,unsigned char Adr, char * _data);
//48
__int16 __stdcall rf_authentication_2(HANDLE icdev,unsigned char _Mode,unsigned char KeyNr,unsigned char Adr);
//49
__int16 __stdcall rf_decrement_transfer(HANDLE icdev,unsigned char Adr,unsigned long _Value);
//50
__int16 __stdcall rf_setport(HANDLE icdev,unsigned char _Byte);
//51
__int16 __stdcall rf_getport(HANDLE icdev,unsigned char *receive_data);
//52
__int16 __stdcall rf_gettime(HANDLE icdev,unsigned char *time);
//53
__int16 __stdcall rf_gettimehex(HANDLE icdev,char *time);
//54
__int16 __stdcall rf_settime(HANDLE icdev,unsigned char *time);
//55
__int16 __stdcall rf_settimehex(HANDLE icdev,char *time);
//56
__int16 __stdcall rf_setbright(HANDLE icdev,unsigned char bright);
//57
__int16 __stdcall rf_ctl_mode(HANDLE icdev,unsigned char mode);
//58
__int16 __stdcall rf_disp_mode(HANDLE icdev,unsigned char mode);
//59
__int16 __stdcall lib_ver(unsigned char *str_ver);
//60
__int16 __stdcall rf_comm_check(HANDLE icdev,unsigned char _Mode);
//61
__int16 __stdcall set_host_check(unsigned char _Mode);
//62
__int16 __stdcall set_host_485(unsigned char _Mode);
//63
__int16 __stdcall rf_set_485(HANDLE icdev,unsigned char _Mode);
//64
__int16 __stdcall hex_a(unsigned char *hex,char *a,unsigned char length);
//65
__int16 __stdcall a_hex(char *a,unsigned char *hex,unsigned char len);
//66
//__int16 __stdcall srd_alleeprom(HANDLE icdev,__int16 offset,__int16 len,unsigned char *receive_buffer);
//67
//__int16 __stdcall swr_alleeprom(HANDLE icdev,__int16 offset,__int16 len,unsigned char* send_buffer);
//68
__int16 __stdcall rf_swr_snr(HANDLE icdev,__int16 lenth,unsigned char* send_buffer);
//69
__int16 __stdcall rf_sam_rst(HANDLE icdev, unsigned char baud, unsigned char *samack);
//70
__int16 __stdcall rf_sam_trn(HANDLE icdev, unsigned char *samblock,unsigned char *recv);
//71
__int16 __stdcall rf_sam_off(HANDLE icdev);
//72
__int16 __stdcall mf2_protocol(HANDLE icdev,unsigned __int16 timeout,unsigned char slen,char *dbuff);
//73
__int16 __stdcall rf_cpu_rst(HANDLE icdev, unsigned char baud, unsigned char *cpuack);
//74
__int16 __stdcall rf_cpu_trn(HANDLE icdev, unsigned char *cpublock,unsigned char *recv);
//75
__int16 __stdcall rf_pro_rst(HANDLE icdev,unsigned char *_Data);
//76
__int16 __stdcall rf_pro_trn(HANDLE icdev,unsigned char *problock,unsigned char *recv);
//77
__int16 __stdcall rf_pro_halt(HANDLE icdev);
//78
void __stdcall Set_Reader_Mode(unsigned char _Mode);
__int16 __stdcall rf_get_snr(HANDLE icdev,unsigned char *_Snr);


////////////////////////////////////////////////////////////////////////
//以下是关于ICODE卡片的操作函数
//80
__int16 __stdcall rf_icode_config(HANDLE icdev,unsigned char mode,unsigned char confbyte);
//81.
__int16 __stdcall rf_icode_get_info(HANDLE icdev,unsigned char *recv);
//82.
__int16 __stdcall rf_icode_set_port(HANDLE icdev,unsigned char portbyte);
//83.
__int16 __stdcall rf_icode_get_port(HANDLE icdev,unsigned char *portbyte);
//84.
__int16 __stdcall rf_icode_anticoll(HANDLE icdev,unsigned char hash,unsigned char tse,unsigned char *recv);
//85.
__int16 __stdcall rf_icode_read(HANDLE icdev,unsigned char blnr,unsigned char nobl,unsigned char *recv);
//86.
__int16 __stdcall rf_icode_read_unselected(HANDLE icdev,unsigned char hash,unsigned char tse,unsigned char blnr,
						 unsigned char nobl,unsigned char *recv);
//87.
__int16 __stdcall rf_icode_write(HANDLE icdev,unsigned char hash,unsigned char blnr,unsigned char *data,
			   unsigned char *timeslots,unsigned char *recv);
//88.
__int16 __stdcall rf_icode_halt(HANDLE icdev,unsigned char hash,unsigned char *timeslots,unsigned char *recv);
//89.
__int16 __stdcall rf_reset_quiet_bit(HANDLE icdev);
//90.
__int16 __stdcall rf_eas(HANDLE icdev,unsigned char *recv);

//91.
//__int16 __stdcall set_card_type(unsigned char cardtype);

//92.
unsigned int __stdcall rf_get_timeslots(void);
//93.
unsigned int __stdcall rf_get_datalen(void);

///////////////////////////////////////////////////////////
//以下是TYPEB协议的相关函数
__int16 __stdcall rf_select_protocal(HANDLE icdev,unsigned char protype);
__int16 __stdcall rf_requestb(HANDLE icdev,unsigned char mode,unsigned char afi,
							  unsigned char param,unsigned char *recv_data);
//__int16 __stdcall rf_slot_marker(HANDLE icdev,unsigned char slotnum,unsigned char *recv_data);
__int16 __stdcall rf_attrib(HANDLE icdev,unsigned long pupi,unsigned char param,unsigned char cid,unsigned char brTx,unsigned char brRx);
__int16 __stdcall rf_apdu_trn(HANDLE icdev,unsigned char pcb,unsigned char cid,unsigned char nad,
							  unsigned char len,unsigned char *command,unsigned char *answer);
__int16 __stdcall rf_haltb(HANDLE icdev, unsigned long pupi);

//Special to AT88RF020:
__int16  __stdcall at88rf020_read(HANDLE icdev,unsigned char cid,unsigned char Adr,unsigned char *_Data);
__int16  __stdcall at88rf020_write(HANDLE icdev,unsigned char cid, unsigned char Adr, unsigned char *_Data);
__int16  __stdcall at88rf020_lock(HANDLE icdev,unsigned char cid,unsigned char *_Data);
__int16  __stdcall at88rf020_check(HANDLE icdev,unsigned char cid, unsigned char *password);
__int16  __stdcall at88rf020_deselect(HANDLE icdev,unsigned char cid);
__int16  __stdcall at88rf020_count(HANDLE icdev,unsigned char cid, unsigned char *Signature);

/////////////////////////////////////////////////////////////////////////
//以下为ISO15693协议相关操作函数
__int16 __stdcall rf_config_mode(HANDLE icdev,unsigned char cardtype,unsigned char _Mode);
//__int16 __stdcall rf_get_config_info(HANDLE icdev,unsigned char *info);
__int16 __stdcall rf_inventory(HANDLE icdev,unsigned char mode,unsigned char afi,unsigned char *card_info);
__int16 __stdcall rf_select_uid(HANDLE icdev,unsigned char *uid);
__int16 __stdcall rf_reset_to_ready(HANDLE icdev,unsigned char mode,unsigned char *uid);
__int16 __stdcall rf_stay_quiet(HANDLE icdev,unsigned char *uid);
__int16 __stdcall rf_get_sysinfo(HANDLE icdev,unsigned char mode,unsigned char *uid,unsigned char *sysinfo);
__int16 __stdcall rf_read_mulblock(HANDLE icdev,unsigned char mode,unsigned char startblock,
								   unsigned char blocknum,unsigned char *uid,
								   unsigned char *_Data);
__int16 __stdcall rf_write_mulblock(HANDLE icdev,unsigned char mode,unsigned char startblock,
									unsigned char blocknum,unsigned char *uid,unsigned char *_Data);
__int16 __stdcall rf_lock_block(HANDLE icdev,unsigned char mode,unsigned char block,unsigned char *uid);
__int16 __stdcall rf_write_AFI(HANDLE icdev,unsigned char mode,unsigned char afi,unsigned char *uid);
__int16 __stdcall rf_write_DSFID(HANDLE icdev,unsigned char mode,unsigned char dsfid,unsigned char *uid);
__int16 __stdcall rf_lock_DSFID(HANDLE icdev,unsigned char mode,unsigned char *uid);
__int16 __stdcall rf_get_mulblock_security(HANDLE icdev,unsigned char mode,
										   unsigned char startblock,
										   unsigned char blocknum,
										   unsigned char *uid,
										   unsigned char *security);
__int16 __stdcall rf_lock_AFI(HANDLE icdev,unsigned char mode,unsigned char *uid);
//custom functions
__int16 __stdcall rf_inventory_read(HANDLE icdev,
									unsigned char mode,
									unsigned char _Afi,
									unsigned char startblock,
									unsigned char blocknum,
									unsigned char *_Data);
__int16 __stdcall rf_fast_inventory_read(HANDLE icdev,
										 unsigned char mode,
										 unsigned char _Afi,
										 unsigned char startblock,
										 unsigned char blocknum,
										 unsigned char *_Data);
__int16 __stdcall rf_set_EAS(HANDLE icdev,unsigned char mode);
__int16 __stdcall rf_clear_EAS(HANDLE icdev,unsigned char mode);
__int16 __stdcall rf_alarm_EAS(HANDLE icdev,unsigned char mode,unsigned char *seq);
__int16 __stdcall rf_lock_EAS(HANDLE icdev,unsigned char mode);

__int16 __stdcall rf_write_2_blocks(HANDLE icdev,unsigned char mode,unsigned char startblock,
									unsigned char *uid,unsigned char *_Data);
__int16 __stdcall rf_lock_2_blocks(HANDLE icdev, unsigned char mode, unsigned char startblock,
								   unsigned char *uid);
__int16 __stdcall rf_write_single_block(HANDLE icdev, unsigned char mode, unsigned char block,
										unsigned char *uid,unsigned char *_Data);
////////////////////////////////////////////////////////////////////////////////////

//sam卡多卡座操作函数
__int16 __stdcall rf_sam_sel_rst(HANDLE icdev, unsigned char cardset,unsigned char baud,unsigned char *samack);
__int16 __stdcall rf_sam_sel_trn(HANDLE icdev, unsigned char cardset,unsigned char *samblock,unsigned char *recv);

//authenticate with the embered key
__int16 __stdcall rf_authentication_key(HANDLE icdev, unsigned char _Mode,unsigned char _BlockNr, unsigned char *_Key);

//functions related to desfile
__int16 __stdcall rf_anticoll_level(HANDLE icdev,unsigned char level, unsigned char *_Snr);

__int16 __stdcall rf_select_2(HANDLE icdev,unsigned char *_Snr, unsigned char *_Size);

__int16 __stdcall rf_desfile_ats(HANDLE icdev, unsigned char cid, unsigned char *desack);

__int16 __stdcall rf_desfile_pps(HANDLE icdev, unsigned char DIV=0);

__int16 __stdcall rf_desfile_trn(HANDLE icdev, unsigned char cid, unsigned char *_Cmd,unsigned char _sLen,
								 unsigned char *_Recv, unsigned char *_rLen);

__int16 __stdcall des_op(HANDLE icdev, unsigned char mode, unsigned char *source, unsigned char *dest);

//以下为SRIX4K卡操作函数

__int16 __stdcall srix4k_poll(HANDLE icdev, unsigned char *chip_id);
__int16 __stdcall srix4k_select(HANDLE icdev, unsigned char chip_id);
__int16 __stdcall srix4k_completion(HANDLE icdev);
__int16 __stdcall srix4k_reset_to_inventory(HANDLE icdev);
__int16 __stdcall srix4k_read(HANDLE icdev, unsigned char _Adr, unsigned char *_Data);
__int16 __stdcall srix4k_write(HANDLE icdev, unsigned char _Adr, unsigned char *_Data);
__int16 __stdcall srix4k_getuid(HANDLE icdev, unsigned char *_Uid);

//以下为AT080卡操作函数
__int16 __stdcall at080_request(HANDLE icdev, unsigned char *Card_ID);

__int16 __stdcall at080_authen(HANDLE icdev, unsigned short appl, 
								   unsigned char keytype, unsigned char *pwd);
__int16 __stdcall at080_read(HANDLE icdev, unsigned char block, unsigned char *content);

__int16 __stdcall at080_write(HANDLE icdev, unsigned char block, unsigned char *content);

__int16 __stdcall at080_write_val(HANDLE icdev, unsigned char block, 
									  unsigned char offset, unsigned char *value);
__int16 __stdcall at080_read_val(HANDLE icdev, unsigned char block, 
									 unsigned char offset, unsigned char *value);
__int16 __stdcall at080_decrement(HANDLE icdev, unsigned char block,
									  unsigned char offset, unsigned char *value);
__int16 __stdcall at080_increment(HANDLE icdev, unsigned char block,
									  unsigned char offset, unsigned char *value);
__int16 __stdcall at080_common_decrement(HANDLE icdev, unsigned char block,
									  unsigned char offset, unsigned char *value,
									  unsigned char *cur_value);
__int16 __stdcall at080_commit(HANDLE icdev);
__int16 __stdcall at080_halt(HANDLE icdev);
__int16 __stdcall at080_write_key(HANDLE icdev, unsigned char offset, unsigned char *pwd);

__int16 __stdcall at080_write_afi(HANDLE icdev, unsigned short appl, 
								  unsigned char config, unsigned char afi);
__int16 __stdcall set_work_mode(HANDLE icdev, unsigned char mode);
__int16 __stdcall open_card(HANDLE icdev, unsigned char *cardtype, unsigned long *cardno);

__int16 __stdcall FNK_CheckCard(HANDLE icdev, unsigned char *_Status);
__int16 __stdcall FNK_PushCard(HANDLE icdev);

__int16 __stdcall LCD_On(HANDLE icdev);
__int16 __stdcall LCD_Off(HANDLE icdev);
__int16 __stdcall LCD_Clear(HANDLE icdev);
__int16 __stdcall LCD_move_cursor(HANDLE icdev, unsigned char offset);
__int16 __stdcall LCD_Line(HANDLE icdev, unsigned char LineNr, unsigned char offset, unsigned char length, unsigned char *sChar);
__int16 __stdcall FM24C16_Read(HANDLE icdev, unsigned __int16 offset, unsigned char length, unsigned char *_Data);
__int16 __stdcall FM24C16_Write(HANDLE icdev, unsigned __int16 offset, unsigned char length, unsigned char *_Data);
__int16 __stdcall AT45DB161B_Read(HANDLE icdev, unsigned long offset, unsigned __int16 length, unsigned char *_Data);
__int16 __stdcall AT45DB161B_Write(HANDLE icdev, unsigned long offset, unsigned __int16 length, unsigned char *_Data);
__int16 __stdcall Get_Keyboard(HANDLE icdev, unsigned __int16 *_KeyVal);
__int16 __stdcall IO_Input_Control(HANDLE icdev, unsigned char *ctlBits);
__int16 __stdcall IO_Output_Control(HANDLE icdev, unsigned char ctlBits);
///////////////////////////////////////////////////////////////////////////////
//新增函数
__int16 __stdcall rf_sam_sel_pps(HANDLE icdev, unsigned char cardset, unsigned char *baud);
__int16 __stdcall rf_sam_sel_trans(HANDLE icdev, unsigned char cardset,unsigned char slen, unsigned char *send,
								   unsigned char rlen, unsigned char *recv);
__int16 __stdcall SeekCard(HANDLE icdev, unsigned char *snr);
__int16 __stdcall TCL_Command_PPS(HANDLE icdev, unsigned char baud);

__int16 __stdcall ARM_sam_sel_rst(HANDLE icdev, unsigned char cardset,unsigned char baud, unsigned char *samack);
__int16 __stdcall ARM_sam_sel_pps(HANDLE icdev, unsigned char cardset, unsigned char *param);
__int16 __stdcall ARM_sam_sel_trn(HANDLE icdev, unsigned char cardset,
								   unsigned char slen, unsigned char *sendblock,
								   unsigned char *recv);
/////////////////////////////////////////////////////////////////////////////////////
//
__int16 __stdcall rf_disp_val(HANDLE icdev, __int16 disp_len, char *val);

}