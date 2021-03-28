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

namespace TEXT
{
    public partial class fatherForm : Form
    {
        String filename = "";
        public int LastPos;
        bool isChanged;

        public fatherForm()
        {
            InitializeComponent();
        }

        private void 新建NToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MyText myChildText = new MyText();
            myChildText.MdiParent = this;
            this.ActivateMdiChild(myChildText);
            myChildText.Show();

        }

        private void 打开OToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MyText myChildText = new MyText();
            myChildText.MdiParent = this;
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
                myChildText.Controls["txtNote"].Text = sr.ReadToEnd();
                sr.Close();
                filename = openFileDialog1.FileName;/**/
                isChanged = false;
            }
            this.ActivateMdiChild(myChildText);
            myChildText.Show();
        }

        private void 退出EToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void 关于AToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            aboutForm aboutForm = new aboutForm();
            aboutForm.Show(this);
        }

        private void 子窗口排列CToolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void 关闭CToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (MyText childForm in this.MdiChildren)
            {
                if (childForm.Name == "MyText")
                {
                    childForm.Close();
                }
            }
        }

        private void 水平并排HToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void 垂直并排ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileVertical);
        }

        private void 层叠排列ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.Cascade);
        }
    }
}
