#pragma once
class CStringArrayExt
{
public:
	CStringArrayExt(void);
	~CStringArrayExt(void);

	// 判断两个 CStringArray 数组中是否有相同的元素
	static BOOL intersect(CStringArray *array1, CStringArray *array2);
	// 判断CS他ringArray数组中是否包含指定CString字符串
	static BOOL isContain(CStringArray *array, CString str);
};

