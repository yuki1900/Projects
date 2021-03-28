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

    public partial class findWordForm : Form
    {
        private MyText myText;
        public findWordForm()
        {
            InitializeComponent();
        }
        public findWordForm(MyText mytext)
        {
            InitializeComponent();
            this.myText = mytext;
        }

        private void findWordForm_Load(object sender, EventArgs e)
        {
            cParameter.sword = "";                  // 初始化文本框内容
            cParameter.dword = "";
            cParameter.order = 0;                   // （如果要查找或替换的单词有很多）记录当前查询或替换到的位置
            cParameter.wordsPos.Clear();            // 如果“查找”文本框中的内容被更改，则需要清除旧内容
            cParameter.confirm = false;             // 确定键用于文本框中内容修改的特殊情况
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            cParameter.sword = textBox1.Text;       // 获取“查找”文本框中的内容，即要查找或替换的目标
            cParameter.swordChanged = true;         // 设置标记，判断文本框中的内容是否被更改过
            cParameter.order = 0;                   // （如果要查找或替换的单词有很多）记录当前查询或替换到的位置
            cParameter.wordsPos.Clear();            // 如果“查找”文本框中的内容被更改，则需要清除旧内容
            if (cParameter.sword == "") cParameter.swordChanged = false;        // 如果为空字符串，则不认为对“查找”文本框进行了修改
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            cParameter.dword = textBox2.Text;       // 获取“替换”文本框中的内容，即替换后的内容
            cParameter.dwordChanged = true;         // 设置标记，判断文本框中的内容是否被更改过
        }
        
        // 点击“确定”按钮触发事件

        private void button2_Click(object sender, EventArgs e)
        {
            //点击第一个确定按钮，执行如下操作
            bool FuzzyOperation = false;
            if (cParameter.dword == "")             // 如果是空字符串则判断是否要删除目标单词
            {
                DialogResult result = MessageBox.Show("是否启用替换功能？", "提示", MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                    cParameter.dwordChanged = true;
                else cParameter.dwordChanged = false;
            }
            if(cParameter.swordChanged == true && cParameter.dwordChanged == false)
            {
                
                DialogResult dialogResult = MessageBox.Show("是否启用模糊查询？", "提示", MessageBoxButtons.YesNo);
                if (dialogResult == DialogResult.Yes) FuzzyOperation = true;

            }
            //偶然得知的知识点
            //content = content.Replace("\n", "\r\n"); txt文档中的换行符是\r\n
            
            cParameter.wordsPos.Clear();
            //MyText fForm = myText;
            string sword = cParameter.sword;    // sword为原单词，即要查找的单词或要被替换掉的单词
            string dword = cParameter.dword;    // dword为要替换成的单词，即替换后的单词
            string content = ((RichTextBox)myText.Controls["txtNote"]).Text;     // content为读取的文档的内容
            int i = 0, textSize = content.Length, wordSize = sword.Length, rangeFind = textSize - wordSize;     
            // 设置长度变量便于后续使用
            cParameter.beginExchange = true;
            if (cParameter.beginExchange)
            {
                Stopwatch oTime = new Stopwatch();
                oTime.Start();
                cParameter.initialSearch(sword);    //重要的一步，初始化cParameter类中的数组变量，为BM算法的实现做准备
                for (i = 0; i <= textSize - wordSize;)          //BM算法开始
                {
                    int j = wordSize - 1;
                    for (; j >= 0 && sword[j] == content[i + j]; --j) ;

                    if (j < 0 )
                    {
                        if(FuzzyOperation == true)              // 根据文本的特点增加额外的判定条件，用于区分精确查询和模糊查询
                        {
                            cParameter.wordsPos.Add(i);         // 若该单词为单独的单词则记录其位置
                        }
                        else
                        {
                            // 此处为判断该单词是否为单独的单词，用于精确查询，假设每个单词都以空格或者换行符隔开
                            if ((i == 0 || content[i - 1] == ' ' || content[i - 1] == '\n') && (i + wordSize == textSize || content[i + wordSize] == ' ' || content[i + wordSize] == '\n'))
                                cParameter.wordsPos.Add(i);     // 若该单词为单独的单词则记录其位置
                        }
                        i++;                            // 不管该查询目标是否为单独的单词或是某一单词的一部分
                        continue;                       // 都将查询位置后移一位，并继续查询
                    }
                                                        // 利用坏字符规则和好后缀规则进行跳转
                    int bad_char_index = j;             // 求出坏字符的位置

                    char bad_char = content[i + j];     // 求处坏字符的内容，用char类型变量保存

                    int bc_move = bad_char_index - cParameter.bc[bad_char];     // 求出根据坏字符规则可以跳转的距离
                                            
                    if (bc_move < 0){bc_move = 1;}      // 如果跳转距离小于0，说明坏字符出现在好后缀中故只需要向后移动一位

                    int gs_move = cParameter.gs[bad_char_index];                // 求出好后缀的移动距离

                    int move = (bc_move > gs_move ? bc_move : gs_move);         // 为了保证不会跳过正确结果，则需每次跳跃两者中的较小值
                    i += move;
                }
                cParameter.beginExchange = false;
                oTime.Stop();
                label6.Visible = true;
                label6.Text = oTime.Elapsed.TotalMilliseconds + "ms";
            }
            
            //对查找到的单词进行修改
            if (cParameter.dwordChanged == true && cParameter.swordChanged == true)
            {
                int sLength = sword.Length, dLength = dword.Length;
                RichTextBox bcontent = (RichTextBox)myText.Controls["txtNote"];
                if (content.Contains(cParameter.sword))
                {
                    int k = cParameter.order;
                    if (cParameter.dwordChanged == true && cParameter.swordChanged == true)
                    {
                        content = ((RichTextBox)myText.Controls["txtNote"]).Text;
                        int index = cParameter.wordsPos[k] + k * (dword.Length - sword.Length);
                        if (content.Contains(cParameter.sword))
                        {
                            if ((index == 0 || content[index - 1] == ' ' || content[index - 1] == '\n') && (content[index + sLength] == ' ' || content[index + sLength] == '\n'))
                            {
                                int row = ((RichTextBox)myText.Controls["txtNote"]).GetLineFromCharIndex(index);
                                String previewText = ((RichTextBox)myText.Controls["txtNote"]).Lines[row];
                                bcontent.Select(index, sLength);
                                bcontent.SelectedText = dword;
                                preViewTextBox.Text = "替换前：" + previewText + "\n替换后：" + bcontent.Lines[row];
                            }
                        }
                    }
                }
                else
                {
                    preViewTextBox.Text = "未查找到当前所制定的单词";
                }
            }
            //仅仅为查找，不进行修改；
            if(cParameter.swordChanged == true && cParameter.dwordChanged == false)
            {
                int sLength = sword.Length;
                int index = content.IndexOf(sword);
                if (content.Contains(cParameter.sword))
                {
                    if (cParameter.order >= cParameter.wordsPos.Count) { cParameter.order--; return; }
                    int n = cParameter.order;
                    int dLength = dword.Length;
                    content = ((RichTextBox)myText.Controls["txtNote"]).Text;
                    index = cParameter.wordsPos[n];
                    int indexINline = 0;
                    while (index != 0 && content[index - 1] != '\n')
                    {
                        indexINline++;
                        index--;
                    }
                    index += indexINline;
                    int row = ((RichTextBox)myText.Controls["txtNote"]).GetLineFromCharIndex(index);
                    String previewText = ((RichTextBox)myText.Controls["txtNote"]).Lines[row];
                    int indexOfString = previewText.IndexOf(sword, indexINline);
                    row++;
                    indexOfString++;
                    int len = 0, k = 10;
                    while (row / k != 0)
                    {
                        k *= 10;
                        len++;
                    }
                    k = 10;
                    while (indexOfString / k != 0)
                    {
                        k *= 10;
                        len++;
                    }
                    preViewTextBox.Text = "第" + row + "行，第" + indexOfString + "列：" + previewText;
                    preViewTextBox.Select(indexOfString + 7 + len, sLength);
                    preViewTextBox.SelectionBackColor = Color.Yellow;
                }
                else
                {
                    preViewTextBox.Text = "未查找到当前所指定的单词";
                }

            }
            textBox3.Text = "" + cParameter.wordsPos.Count;
        }
        
        // 点击“下一个”按钮触发事件

        private void button6_Click(object sender, EventArgs e)
        {
            //查找下一个同名单词
            if (cParameter.dword == "" && !(cParameter.swordChanged == true && cParameter.dwordChanged == false))
            {
                MessageBox.Show("请先设定目标单词，并点击确定按钮。");
                return;
            }
            //MyText fForm = myText;
            String sword = cParameter.sword;
            String dword = cParameter.dword;

            if (cParameter.dwordChanged == true && cParameter.swordChanged == true)
            {
                string content = ((RichTextBox)fForm.Controls["txtNote"]).Text;
                cParameter.order++;
                if (cParameter.order >= cParameter.wordsPos.Count) { cParameter.order--; return; }

                int i = cParameter.order, wordSize = dword.Length;
                if (cParameter.dwordChanged == true && cParameter.swordChanged == true)
                {
                    int sLength = sword.Length, dLength = dword.Length;
                    RichTextBox bcontent = (RichTextBox)fForm.Controls["txtNote"];
                    content = ((RichTextBox)fForm.Controls["txtNote"]).Text;
                    int index = cParameter.wordsPos[i] + i * (dword.Length - sword.Length);
                    if (content.Contains(cParameter.sword))
                    {
                        if ((index == 0 || content[index - 1] == ' ' || content[index - 1] == '\n') && (content[index + sLength] == ' ' || content[index + sLength] == '\n'))
                        {
                            int row = ((RichTextBox)fForm.Controls["txtNote"]).GetLineFromCharIndex(index);
                            String previewText = ((RichTextBox)fForm.Controls["txtNote"]).Lines[row];
                            bcontent.Select(index, sLength);
                            bcontent.SelectedText = dword;
                            preViewTextBox.Text = "替换前：" + previewText + "\n替换后：" + bcontent.Lines[row];
                        }
                    }
                }
            }
            if (cParameter.dwordChanged == false && cParameter.swordChanged == true)
            {
                string content = ((RichTextBox)myText.Controls["txtNote"]).Text;
                cParameter.order++;
                if (cParameter.order >= cParameter.wordsPos.Count) { cParameter.order--; return; }
                int i = cParameter.order, wordSize = dword.Length;
                int sLength = sword.Length, dLength = dword.Length;
                content = ((RichTextBox)myText.Controls["txtNote"]).Text;
                int index = cParameter.wordsPos[i];
                int indexINline = 0;
                while ( index != 0 && content[index-1] != '\n')
                {
                    indexINline++;
                    index--;
                }
                index += indexINline;
                int row = ((RichTextBox)myText.Controls["txtNote"]).GetLineFromCharIndex(index);
                String previewText = ((RichTextBox)myText.Controls["txtNote"]).Lines[row];
                int indexOfString = previewText.IndexOf(sword, indexINline);
                row++;
                indexOfString++;
                int len = 0, k = 10;
                while (row / k != 0)
                {
                    k *= 10;
                    len++;
                }
                k = 10;
                while (indexOfString / k != 0)
                {
                     k *= 10;
                     len++;
                }
                preViewTextBox.Text = "第" + row + "行，第" + indexOfString + "列：" + previewText;
                preViewTextBox.Select(indexOfString + 7 + len, sLength);
                preViewTextBox.SelectionBackColor = Color.Yellow;        
            }
        }
        
        // 点击“上一个”按钮触发事件

        private void button1_Click(object sender, EventArgs e)
        {
            //查找上一个同名单词
            if (cParameter.dword == "" && !(cParameter.swordChanged == true && cParameter.dwordChanged == false))
            {
                MessageBox.Show("请先设定目标单词，并点击确定按钮。");
                return;
            }
            //MyText fForm = myText;
            if (cParameter.order == 0)
            {
                ((RichTextBox)fForm.Controls["txtNote"]).Undo();
                if (cParameter.swordChanged == true && cParameter.dwordChanged == true)
                {
                    preViewTextBox.Clear();
                    textBox2.Clear();
                }
                return;
            }
            
            int i = cParameter.order, wordSize = cParameter.dword.Length;
            if (cParameter.dwordChanged == true && cParameter.swordChanged == true)
            {
                int index = cParameter.wordsPos[i] + i * (cParameter.dword.Length - cParameter.sword.Length);
                int row = ((RichTextBox)fForm.Controls["txtNote"]).GetLineFromCharIndex(index);
                String info = ((RichTextBox)fForm.Controls["txtNote"]).Lines[row];
                ((RichTextBox)fForm.Controls["txtNote"]).Undo();
                i = cParameter.order; wordSize = cParameter.dword.Length;
                index = cParameter.wordsPos[i] + i * (cParameter.dword.Length - cParameter.sword.Length);
                row = ((RichTextBox)fForm.Controls["txtNote"]).GetLineFromCharIndex(index);
                info = "撤销前：" + info + "\n" + "撤销后：" + ((RichTextBox)fForm.Controls["txtNote"]).Lines[row];
                preViewTextBox.Text = info;
                cParameter.order--;
            }
            if (cParameter.dwordChanged == false && cParameter.swordChanged == true)
            {
                String sword = cParameter.sword;
                String dword = cParameter.dword;
                cParameter.order--;
                i = cParameter.order; 
                int sLength = sword.Length, dLength = dword.Length;
                String content = ((RichTextBox)myText.Controls["txtNote"]).Text;
                int index = cParameter.wordsPos[i];
                int indexINline = 0;
                while (index != 0 && content[index - 1] != '\n')
                {
                    indexINline++;
                    index--;
                }
                index += indexINline;
                int row = ((RichTextBox)myText.Controls["txtNote"]).GetLineFromCharIndex(index);
                String previewText = ((RichTextBox)myText.Controls["txtNote"]).Lines[row];
                int indexOfString = previewText.IndexOf(sword, indexINline);
                row++;
                indexOfString++;
                int len = 0, k = 10;
                while (row / k != 0)
                {
                    k *= 10;
                    len++;
                }
                k = 10;
                while (indexOfString / k != 0)
                {
                    k *= 10;
                    len++;
                }
                preViewTextBox.Text = "第" + row + "行，第" + indexOfString + "列：" + previewText;
                preViewTextBox.Select(indexOfString + 7 + len, sLength);
                preViewTextBox.SelectionBackColor = Color.Yellow;
            }
        }

        // 点击“撤销”按钮触发事件

        private void button4_Click(object sender, EventArgs e)
        {
            //点击撤销
            if (cParameter.dword == "" && !(cParameter.swordChanged == true && cParameter.dwordChanged == false))
            {
                MessageBox.Show("请先设定目标单词，并点击确定按钮。");
                return;
            }
            if (cParameter.order != 0)
            button1_Click(sender, e);
            else
            {
                MyText fForm = myText;
                ((RichTextBox)fForm.Controls["txtNote"]).Undo();
                if (cParameter.swordChanged == true && cParameter.dwordChanged == true)
                {
                    preViewTextBox.Clear();
                    textBox2.Clear();
                }
            }
        }

        // 点击“返回”按钮触发事件

        private void button3_Click(object sender, EventArgs e)
        {
            //点击返回，退出当前界面
            this.Close();
        }

        // 点击“重置”按钮触发事件

        private void button5_Click(object sender, EventArgs e)
        {
            findWordForm_Load(sender, e);
            textBox1.Clear();
            textBox2.Clear();
            textBox3.Clear();
            preViewTextBox.Clear();
            label6.Text = "";
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }
        
        //以下注释代码为设计初期采用的算法，为了尽早实现功能观察效果，采用了最简单的BF算法和C#自带的函数

        /*string sword = cParameter.sword, dword = cParameter.dword, content = ((RichTextBox)fForm.Controls["txtNote"]).Text;
        int i = 0, rowNumber = 0, colNumber = 0, textSize = content.Length, wordSize = sword.Length, rangeFind = textSize - wordSize;
        while (i < rangeFind)
        {
            if (content[i] == '\n')
            {
                rowNumber++;
                colNumber = 0;
                i++;
                continue;
            }
            if (sword[0] == content[i] && (i == 0 || content[i - 1] == ' ' || content[i - 1] == '\n'))
            {
                int k = 1;
                while (k < wordSize)
                {
                    if (sword[k] != content[i + k]) break;
                    k++;
                }
                if (k == wordSize && (content[i + wordSize] == ' ' || content[i + wordSize] == '\n'))
                {
                    //arrayOps.Add(rowNumber);  用于记录单词出现的行数
                    //arrayOps.Add(colNumber);  用于记录单词出现在某行的字符串中的位置（列数）
                    cParameter.wordsPos.Add(i);
                }
            }
            colNumber++;
            i++;
        }*/
    }
}
