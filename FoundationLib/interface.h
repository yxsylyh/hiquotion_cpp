
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// namespace DesignerFramework
// {
	#define MyInterface class __declspec(novtable)
// }

// 
// Interface ICodec
// {
// public:
// 	virtual bool Decode(char * lpDataSrc,unsigned int nSrcLen,char * lpDataDst,unsigned int *pnDstLen);
// 	virtual bool Encode(char * lpDataSrc,unsigned int nSrcLen,char * lpDataDst,unsigned int *pnDstLen);
// };
// 
// class CCodec : public ICodec
// {
// public:
//     virtual bool Decode(char * lpDataSrc,unsigned int nSrcLen,char * lpDataDst,unsigned int *pnDstLen)
//      {
//          cout << "½âÂë..." << endl;
//         return true;
//      }
//     virtual bool Encode(char * lpDataSrc,unsigned int nSrcLen,char * lpDataDst,unsigned int *pnDstLen)
//      {
//          cout << "±àÂë..." << endl;
//         return true;
//      }
// };
// 
// template <class T,int Size> Interface IContainer
// {
// virtual bool add(T item);
// virtual bool get(int index);
// virtual bool removeAt(int index);
// virtual bool remove(T item);
// 
// };
// 
// template <class T,int Size> class CContainerImpl : public IContainer<T,Size>
// {
// public:
// 
// private:
// 	T buffer[Size];
// };
// 
// #define Container_Max_Size 100
// 
// template <class T> class CContainer : public CContainerImpl<T,Container_Max_Size>
// {
// public:
// 
// private:
// 
// };
