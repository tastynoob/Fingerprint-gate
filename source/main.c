#include "init.h"
#include "FPM10A.h"


#define wait_time 1
#define max_person 100
static int finger_id[max_person];
static int finger_time[max_person];



//删除id
void Deleid(int id) {
    finger_id[id] = 0;
}

//生成id
int summonid() {
    for (int i = 0;i < max_person;i++) {
        if (finger_id[i] == 0) {
            finger_id[i] = 1;
            return i;
        }
    }
}


char buff1[16] = "the id:";
char buff2[16] = "the time:";
int main() {
    init();
    close_door();

    for (int i = 0;i < max_person;i++) {
        finger_id[i] = 0;
    }

    write_string("start", "power on");
    delay_1ms(1000);

    int i = Device_Check();

    if (i == 1) {
        write_string("finish", "");
        //开机，删除所有指纹
        FINGERPRINT_Cmd_Delete_All_Model();
        FPM10A_Receive_Data(12);
    }
    else {
        write_string("fail", "pls restart");
        while (1);
    }

    delay_1ms(1000);
    while (1) {
        write_string("wait for finger", "pls press 1sec");

        //等待录入手指
        while (1) {
            FPM10A_Cmd_Get_Img(); //获得指纹图像
            FPM10A_Receive_Data(12); //等待响应
            if (FPM10A_RECEICE_BUFFER[9] == 0)break;
            delay_1ms(500);
        }

        if (FPM10A_RECEICE_BUFFER[9] == 0) { //获得响应
            delay_1ms(100);
            //判断改指纹是否已经存在
            FINGERPRINT_Cmd_Img_To_Buffer1();
            FPM10A_Receive_Data(12);
            if (FPM10A_RECEICE_BUFFER[9] == 0) { //获得响应

                FPM10A_Cmd_Search_Finger();
                FPM10A_Receive_Data(16);
                if (FPM10A_RECEICE_BUFFER[9] == 0) { //搜索到,代表指纹已经存在，需要等待30分钟
                    //拼接指纹ID数
                    int id = (((int)FPM10A_RECEICE_BUFFER[10]) << 8) + FPM10A_RECEICE_BUFFER[11];


                    sprintf(&buff1[7], "%d", id);

                    write_string("find a finger!", buff1);

                    delay_1ms(1000);

                    int time_pass = TIME_TICK - finger_time[id];

                    if (time_pass >= wait_time) {//判断时间是否超过设定时间

                        FPM10A_DeleChar(id, 1);//删除该指纹
                        Deleid(id);

                        open_door();
                        write_string("now you can", "safty go out");
                        delay_1ms(2000);
                    }
                    else {


                        sprintf(&buff2[9], "%dmin", time_pass);

                        write_string("you can't go out", buff2);
                        delay_1ms(2000);
                        write_string("pls go back", "");
                        delay_1ms(1000);

                    }


                    write_string("OK!", "next");
                    close_door();
                    delay_1ms(1000);
                }
                else {//没有搜索到,则录入指纹
                    write_string("not find id", "pls finger");
                    delay_1ms(1000);
                    while (1) {//再次录入指纹
                        FPM10A_Cmd_Get_Img(); //获得指纹图像
                        FPM10A_Receive_Data(12);
                        if (FPM10A_RECEICE_BUFFER[9] == 0)break;
                        delay_100us(500);
                    }


                    int id = summonid();

                    FINGERPRINT_Cmd_Img_To_Buffer2();
                    FPM10A_Receive_Data(12);
                    FPM10A_Cmd_Reg_Model();//转换成特征码
                    FPM10A_Receive_Data(12);
                    FPM10A_Cmd_Save_Finger(id);
                    FPM10A_Receive_Data(12);


                    finger_time[id] = TIME_TICK;//录入时间(分)


                    sprintf(&buff1[7], "%d", id);
                    write_string("finish", buff1);
                    open_door();
                    delay_1ms(1000);
                    write_string("now you can", "safty go in");
                    delay_1ms(2000);
                    close_door();
                    delay_1ms(500);
                }
            }
        }
    }







    while (1) {

    }
    return 0;
}