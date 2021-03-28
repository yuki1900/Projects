using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using Microsoft.VisualBasic;

namespace TEXT
{
    class cParameter
    {
        public static DateTime bTime, eTime;
        public static String dword = "" ;
        public static bool dwordChanged = false;
        public static String sword = "";
        public static bool swordChanged = false;
        public static bool beginExchange = false;
        public static int order = 0;
        public static bool confirm = false;
        public static List<int> wordsPos = new List<int>();
        public static int[] su;
        public static int[] bc = new int[256];
        public static int[] gs;
        public static void initialSearch(string pString)
        {
            getbChar(pString,ref bc);
            setSuffix(pString,ref su);
            getgSuff(pString,ref gs);
        }
        public static void getbChar(string pString,ref int[] bc)
        {
            //坏字符规则，数组中存储256个字符（假设包含当前所有的字符，采用UTF-8编码集）
            int i = 0;
            while (i < 256)     // 初始化数组
            {
                bc[i] = -1;     // -1代表跳跃幅度整个数组长度
                i++;
            }
            i = 0;              // 确定数组中每个字符的跳跃距离
            while (i < pString.Length)
            {
                bc[pString[i]] = i;     // 从右向左，找出每个字符最先出现的位置
                                        // 字符的ASCII码为数组的下标，出现的位置对应其值
                i++;
            }

        }
        public static void setSuffix(string pString,ref int[] su)
        {
            // 动态创建数组，依据模式串的长度
            su = new int[pString.Length];
            int len = pString.Length, i = len - 1;
            while (i >= 0)
            {
                int j = i, ops = len - 1;
                while (j >= 0 && ops >= 0 && pString[ops] == pString[j])
                {
                    j--;        // 此处求解相同字段的长度
                    ops--;
                }
                su[i] = i - j;  // i - j 即求出最大前缀的长度
                i--;
            }
        }
        public static void getgSuff(string pString,ref int[] gs)
        {   // 三种情况分别判断
            // 第一种情况为：好后缀为坏字符之前的字符串中的子串且不为结尾部分
            // 第二种情况为：好后缀为坏字符之前的字符串中的字串且为结尾部分
            // 第三种情况为：好后缀在前串不存在
            // 为了保证跳跃的正确性要确保跳跃的距离为三种情况中的最短距离
            gs = new int[pString.Length];
            int len = pString.Length,i;
            // 第三种情况，从右往左扫描，因为要确保模式串移动最少。
            for (i = 0; i < len; ++i)
            {
                gs[i] = len;        // 当第三种情况发生时，跳转距离都为字符串的长度且是最大移动距离
            }
            //第二种情况
            for (i = len - 1; i >= 0; --i) 
            {
                if (su[i] == i + 1) //是一个与好后缀匹配的最大前缀
                {
                    int j;
                    for (j = 0; j < len - 1 - i; ++j)
                    {
                        if (gs[j] == len)       // gs[j]初始值为len, 这样确保gs[j]只被修改一次
                        {                       // 在从右向左检查的情况下，只修改一次能确保字符串跳转后
                            gs[j] = len - 1 - i;// 好后缀能与距离最近的前缀匹配
                        }
                    }
            }}
            //第一种情况，当第一种情况发生时总为移动距离最少的情况
            for (i = 0; i < len - 1; ++i)
            {
                gs[len - 1 - su[i]] = len - 1 - i;
            }
        }}
}
