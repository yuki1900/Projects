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
using System.Diagnostics;

namespace TEXT
{
    public partial class exChangeForm : Form
    {
        private MyText myText;
        public exChangeForm()
        {
            InitializeComponent();
        }
        public exChangeForm(MyText mytext)
        {
            InitializeComponent();
            this.myText = mytext;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "") return;
            DateTime beginTime = DateTime.Now;
            DateTime endTime;
            cParameter.wordsPos.Clear();
            //获取目标单词（将要替换成的单词）
            cParameter.dword = textBox1.Text;
            //获取源单词（被替换的单词）
            cParameter.sword = textBox2.Text;
            cParameter.beginExchange = true;
            string sword = cParameter.sword;    // sword为原单词，即要查找的单词或要被替换掉的单词
            string dword = cParameter.dword;    // dword为要替换成的单词，即替换后的单词
            string content = ((RichTextBox)myText.Controls["txtNote"]).Text;     // content为读取的文档的内容
            int i, textSize = content.Length, wordSize = sword.Length, rangeFind = textSize - wordSize;     // 设置长度变量便于后续使用
                
            if (cParameter.beginExchange)
            {
                cParameter.beginExchange = true;
                if (cParameter.beginExchange)
                {
                    cParameter.initialSearch(sword);    //重要的一步，初始化cParameter类中的数组变量，为BM算法的实现做准备
                    for (i = 0; i <= textSize - wordSize;)      //BM算法开始
                    {
                        int j = wordSize - 1;
                        for (; j >= 0 && sword[j] == content[i + j]; --j) ;

                        if (j < 0)
                        {
                            if ((i == 0 || content[i - 1] == ' ' || content[i - 1] == '\n') && (i + wordSize == textSize || content[i + wordSize] == ' ' || content[i + wordSize] == '\n'))
                                    cParameter.wordsPos.Add(i);     //若该单词为单独的单词则记录其位置
                            i++;        // 不管该查询目标是否为单独的单词或是某一单词的一部分，都将查询位置后移一位，进行后续的查询
                            continue;   // 继续查询
                        }
                        
                    

                        // 利用坏字符规则和好后缀规则进行跳转
                        int bad_char_index = j;
                        char bad_char = content[i + j];
                        int bc_move = bad_char_index - cParameter.bc[bad_char];
                        if (bc_move < 0)
                        {
                            bc_move = 1;
                        }
                        int gs_move = cParameter.gs[bad_char_index];
                        int move = (bc_move > gs_move ? bc_move : gs_move);
                        i += move;
                    }
                }
                cParameter.beginExchange = false;
            }
            i = 0;
            while (i < cParameter.wordsPos.Count())
            {
                if ((cParameter.wordsPos[i] == 0 || content[cParameter.wordsPos[i] - 1] == ' ' || content[cParameter.wordsPos[i] - 1] == '\n') && (cParameter.wordsPos[i] + wordSize == content.Length || content[cParameter.wordsPos[i] + wordSize] == ' '|| content[cParameter.wordsPos[i] + wordSize] == '\n'))
                {
                   ((RichTextBox)myText.Controls["txtNote"]).Select(cParameter.wordsPos[i]+i*(dword.Length - sword.Length), wordSize);
                   ((RichTextBox)myText.Controls["txtNote"]).SelectedText = dword;
                }
                i++;
            }
            if (i == 0) MessageBox.Show("未查询到目标单词");
            cParameter.beginExchange = false;
            textBox3.Text = "" + cParameter.wordsPos.Count;
            endTime = DateTime.Now;
            TimeSpan timeSpan = endTime.Subtract(beginTime);
            label5.Text = "" + timeSpan.TotalMilliseconds + "ms";
            label5.Visible = true;
        }
        
        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int i = cParameter.wordsPos.Count;
            while (i > 0)
            {
                ((RichTextBox)myText.Controls["txtNote"]).Undo();
                i--;
            }
            cParameter.wordsPos.Clear();
            cParameter.order = 0;
            MessageBox.Show("已撤销操作。");
            textBox1.Clear();
            textBox2.Clear();
            textBox3.Clear();
            label5.Text = "";
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            cParameter.wordsPos.Clear();
            textBox3.Text = "";
            cParameter.sword = textBox2.Text;
            textBox1.Clear();
            cParameter.dword = "";
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            cParameter.wordsPos.Clear();
            textBox3.Text = "";
            cParameter.dword = textBox1.Text;
        }
    }
}
