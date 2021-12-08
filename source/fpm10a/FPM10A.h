#ifndef __FPMXX_H__
#define __FPMXX_H__



extern volatile unsigned char FPM10A_RECEICE_BUFFER[32];

void FPM10A_Cmd_Get_Img(void);
void FPM10A_Cmd_Check(void);
uint32_t FPM10A_DeleChar(uint16_t id, uint16_t n);
uint32_t Device_Check(void);
void FPM10A_Receive_Data(unsigned char ucLength);
void FPM10A_Delete_All_Fingerprint();
void FPM10A_Find_Fingerprint();
void FPM10A_Cmd_Search_Finger(void);
void FPM10A_Add_Fingerprint();
void FPM10A_Cmd_Reg_Model();
void FPM10A_Cmd_Save_Finger(unsigned int storeID);
void FINGERPRINT_Cmd_Delete_All_Finger(void);
void FINGERPRINT_Cmd_Img_To_Buffer1(void);
void FINGERPRINT_Cmd_Img_To_Buffer2(void);
void FINGERPRINT_Cmd_Delete_All_Model(void);

#endif