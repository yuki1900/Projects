using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace SpareTimeApp
{
    public sealed class API
    {
        /// <summary>
        /// API 的摘要说明。
        /// </summary>

        public static int WM_KEYDOWN = 0x0100;
        public static int WM_KEYUP = 0x0101;
        public static int WM_SYSKEYDOWN = 0x0104;
        public static int WM_SYSKEYUP = 0x0105;

        public static int WM_MOUSEMOVE = 0x0200;
        public static int WM_LBUTTONDOWN = 0x0201;
        public static int WM_LBUTTONUP = 0x0202;
        public static int WM_LBUTTONDBLCLK = 0x0203;
        public static int WM_RBUTTONDOWN = 0x0204;
        public static int WM_RBUTTONUP = 0x0205;
        public static int WM_RBUTTONDBLCLK = 0x0206;
        public static int WM_USER = 0x0400;

        public static int MK_LBUTTON = 0x0001;
        public static int MK_RBUTTON = 0x0002;
        public static int MK_SHIFT = 0x0004;
        public static int MK_CONTROL = 0x0008;
        public static int MK_MBUTTON = 0x0010;

        public static int MK_XBUTTON1 = 0x0020;
        public static int MK_XBUTTON2 = 0x0040;

        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

        //此处主要用来让窗口置于最前(SetWindowPos(this.Handle,-1,0,0,0,0,0x4000|0x0001|0x0002);)
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern bool SetWindowPos(IntPtr hWnd,
        int hWndInsertAfter,
        int X,
        int Y,
        int cx,
        int cy,
        int uFlags
        );
        /// <summary>
        /// 窗口置前
        /// </summary>
        /// <param name="hWnd"></param>
        public static void SetWindowPos(IntPtr hWnd)
        {
            SetWindowPos(hWnd, -1, 0, 0, 0, 0, 0x4000 | 0x0001 | 0x0002);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="processName"></param>
        /// <returns></returns>
        public static Process GetGameProcess(string processName)
        {
            Process pro = null;
            Process[] pros = Process.GetProcessesByName(processName);
            if (pros.Length > 0)
            {
                pro = pros[0];
            }
            return pro;
        }
    }
}

