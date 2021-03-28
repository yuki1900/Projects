using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Threading;
using System.Diagnostics;
using System.Windows.Forms;
using System.Runtime.InteropServices;


namespace SpareTimeApp
{

    public partial class Form1 : Form
    {

        [DllImport("user32.dll", EntryPoint = "FindWindow")]
        private extern static IntPtr FindWindow(string lpClassName, string lpWindowName);

        public Form1()
        {
            InitializeComponent();
            IntPtr hWnd = FindWindow(null, "阴阳师-网易游戏");
            if (hWnd != IntPtr.Zero)
            {
                MessageBox.Show("找到阴阳师窗口");
            }
            else
            {
                MessageBox.Show("没有找到阴阳师窗口");
            }
            API.SetWindowPos(hWnd);
        }
        
        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
