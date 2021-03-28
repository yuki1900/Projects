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
using System.Runtime.InteropServices;

namespace TEXT
{
    public partial class MyText : Form
    {

        String filename = "";
        public int LastPos;
        bool isChanged;

        public MyText()
        {
            InitializeComponent();

        }

        private void MyText_Load(object sender, EventArgs e)
        {
            
        }

        private void 打开OToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //添加文本过滤器，(*.txt)显示在文件类型里，中间用|隔开，|后面代表过滤txt以外的其他类型文件
            //让记事本默认打开.txt文件，所以过滤器的index为前者：1
            openFileDialog1.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            openFileDialog1.FilterIndex = 1;
            //是否存储文件路径，在这里是存储，在做动态菜单的时候会让显示曾经加载路径
            openFileDialog1.RestoreDirectory = true;
            //读取文本文件
            StreamReader sr = null;
            if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                sr = new StreamReader(openFileDialog1.FileName, System.Text.Encoding.UTF8);
                txtNote.Text = sr.ReadToEnd();
                sr.Close();
                filename = openFileDialog1.FileName;/**/
                isChanged = false;
            }
        }

        private void 新建NToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtNote.Text = "";
            isChanged = true;
        }

        private void 保存SToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filename == "")
            {
                saveFileDialog1.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
                saveFileDialog1.Title = "保存";
                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    filename = saveFileDialog1.FileName;
                    StreamWriter sw = new StreamWriter(filename, false, System.Text.Encoding.UTF8);

                    // MessageBox.Show( sw.Encoding.ToString());
                    if (sw != null)
                    {
                        // 创建新文件后，向其中写入测试内容
                        String s = txtNote.Text;
                        s = s.Replace("\n", "\r\n");
                        sw.Write(s);
                        sw.Close();
                        isChanged = false;
                    }
                }
            }
            else
            {
                //直接保存，不显示对话框
                StreamWriter sw = new StreamWriter(filename, false, System.Text.Encoding.UTF8);
                if (sw != null)
                {
                    // 创建新文件后，向其中写入测试内容
                    String s = txtNote.Text;
                    s = s.Replace("\n", "\r\n");
                    sw.Write(s);
                    sw.Close();
                    isChanged = false;
                }
            }
        }

        private void 退出EToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (isChanged)
            {
                DialogResult dr = MessageBox.Show("是否保存当前文档？", "提示", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {
                    //保存
                    保存SToolStripMenuItem_Click(sender, e);
                    this.Close();
                }
            }
            else
            {
                isChanged = false;
                this.Close();
            }
                
        }

        private void txtNote_TextChanged(object sender, EventArgs e)
        {
            isChanged = true;
        }

        private void FormClose(object sender, FormClosingEventArgs e)
        {
            if (isChanged)
            {
                DialogResult dr = MessageBox.Show("是否保存当前文档？", "提示", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {
                    //保存
                    保存SToolStripMenuItem_Click(sender, e);
                    //this.Close();
                }
                
            }
            else
            {
                isChanged = false;
                //this.Close();
            }
                
        }

        private void 另存为OToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            saveFileDialog1.Title = "另存为";
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                filename = saveFileDialog1.FileName;
                StreamWriter sw = new StreamWriter(filename, false, System.Text.Encoding.UTF8);

                // MessageBox.Show( sw.Encoding.ToString());
                if (sw != null)
                {
                    // 创建新文件后，向其中写入测试内容
                    String s = txtNote.Text;
                    s = s.Replace("\n", "\r\n");
                    sw.Write(s);
                    sw.Close();
                    isChanged = false;
                }
            }
        }

        private void 编辑EToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void 撤回CToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtNote.Undo();
        }

        private void 恢复RToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtNote.Redo();
        }

        private void 查找RToolStripMenuItem_Click(object sender, EventArgs e)
        {
            findWordForm findwordform = new findWordForm(this);
            findwordform.Show(this);
        }
        private void 替换RToolStripMenuItem_Click(object sender, EventArgs e)
        {
            findWordForm findwordform = new findWordForm(this);
            findwordform.Show(this);

            //也可以采用showdialogue()，在主窗体等待参数的设置完毕
            //这里采用Show()，并在子窗体完成对主窗体控件的内容的获取，以此进行查找
        }

        private void 修改字体ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fontDialog1.ShowDialog() == DialogResult.OK)
                txtNote.SelectionFont = fontDialog1.Font;
        }

        private void 关于AToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            aboutForm aboutForm = new aboutForm();
            aboutForm.Show(this);
        }

        
    }
}
