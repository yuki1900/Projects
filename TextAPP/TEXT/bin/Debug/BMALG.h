#pragma once
/*
����dll�Ĺ���ʱ��vsĬ�϶����:DLL_EXPORTS������dll���̣�û�иú궨��
������"����->Ԥ������->Ԥ����������"���濴���ú�
�������ĺ��壺�������ú꣬��DLL_API�ǵ���.(dll���ɹ��̶����˸ú꣬�����ǵ���)
���δ����ú꣬��DLL_API�ǵ���.(����dll�Ĺ���û�ж���ú꣬�����ǵ���dll)
*/

#include <string>

namespace BMALGdll  
{
	//extern "C" �����Ǳ���ʱ��C�ı��뷽ʽ����֤����������
	//C++���ں������أ����Ա��뺯��ʱ���ں�����������ϲ������ͣ����C++����C��д��dll�����Ҫextern "C"
	extern "C" __declspec(dllexport) void setSuffix(std::string pString, int *su);
	extern "C" __declspec(dllexport) void getbChar(std::string pString, int *bc);
	extern "C" __declspec(dllexport) void getgSuff(std::string pString, int *gs, int *su);
	extern "C" __declspec(dllexport) int bm_search(int *bc, int* gs, std::string sString, std::string pString);
};
