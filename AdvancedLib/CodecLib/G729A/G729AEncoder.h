#pragma once

extern "C"
{
#include "g.729a\typedef.h"
#include "g.729a\basic_op.h"
#include "g.729a\ld8k.h"
};

// #define L_TOTAL     240        /* Total size of speech buffer.              */
// #define L_WINDOW    240        /* Window size in LP analysis.               */
// #define L_NEXT      40         /* Lookahead in LP analysis.                 */
// #define L_FRAME     80         /* Frame size.                               */
// #define L_SUBFR     40         /* Subframe size.                            */

/*----------------------------------------------------------------------*
*      Initialize pointers to speech vector.                            *
*                                                                       *
*                                                                       *
*   |--------------------|-------------|-------------|------------|     *
*     previous speech           sf1           sf2         L_NEXT        *
*                                                                       *
*   <----------------  Total speech vector (L_TOTAL)   ----------->     *
*   <----------------  LPC analysis window (L_WINDOW)  ----------->     *
*   |                   <-- present frame (L_FRAME) -->                 *
* old_speech            |              <-- new speech (L_FRAME) -->     *
* p_window              |              |                                *
*                     speech           |                                *
*                             new_speech                                *
*-----------------------------------------------------------------------*/

// sf1 = sf2 = L_NEXT
// L_FRAME = 2 * L_NEXT


// 编码后的长度以在库中修正，修正为 10 字节

// extern Word16 *new_speech;     /* Pointer to new speech data            */

class CG729AEncoder
{
public:
	CG729AEncoder(void);
	~CG729AEncoder(void);

	void init();

	// src长度和dst长度都是固定的
	// 库以 Word16 为长度单位处理数据，Word16 即 short int
	// 查看网上实测结果：无论 32 位还是 64 位下，short int 都是 2 字节，即 16 位
	// 所以，src 长度 = L_FRAME（库中定义为是80） × sizeof(Word16) = 160
	// xxx dst长度 = SERIAL_SIZE（库中定义为是80+2） × sizeof(Word16) = 164（32位下）或 328（64位下）
	// dst长度已修正为 10 字节，即原长度的 1/16。
	int encode(char *src, char *dst);
// 	// src的长度得是80，Word16是2字节，所以总长度是160
// 	int encode(Word16 *src, char *dst);

	// 编码
	// 原长度必须是 160 的整数倍
	int encodeEx(char *src, unsigned int srcLen, char *dst);


private:

	Word16 prm[PRM_SIZE];          /* Analysis parameters.                  */
// 	Word16 serial[SERIAL_SIZE];    /* Output bitstream buffer               */
	unsigned char serial[SERIAL_SIZE];    /* Output bitstream buffer               */
	Word16 syn[L_FRAME];           /* Buffer for synthesis speech           */

	Word16 i, frame;               /* frame counter */

	Word16 srcLen;
	Word16 dstLen;
};
