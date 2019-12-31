extern HINSTANCE hModule;



typedef int (PASCAL *pUCmmand1)(BYTE *pcmd,int *p1,int *p2,int *p3);
typedef int (PASCAL *pGetInfo)(BYTE *buf);

extern pUCmmand1		mycmd;

extern pGetInfo GetSAMIDToStr;
extern pGetInfo myGetName    ;     //读取姓名
extern pGetInfo myGetSex     ;     //读取性别
extern pGetInfo myGetFolk    ;     //读取民族
extern pGetInfo myGetBirth   ;     //读取出生
extern pGetInfo myGetAddr    ;     //读取住址
extern pGetInfo myGetIDNum   ;     //读取公民身份号码
extern pGetInfo myGetDep     ;     //读取签发机关
extern pGetInfo myGetBegin   ;     //读取有效期起
extern pGetInfo myGetEnd     ;     //读取有效期止
extern pGetInfo myGetNewAddr ;     //读取最新地址
extern pGetInfo myGetPicPath ;     //读取头像图片路径

// extern BOOL LoadDll();
// extern void FreeDll();

BOOL LoadDll();
void FreeDll();
