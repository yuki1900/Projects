namespace TEXT
{
    partial class MyText
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新建NToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存为OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.退出EToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.查询CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.查找RToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.替换RToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.编辑EToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.撤回CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.恢复RToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.字体WToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.修改字体ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于AToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.txtNote = new System.Windows.Forms.RichTextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.fontDialog1 = new System.Windows.Forms.FontDialog();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件FToolStripMenuItem,
            this.查询CToolStripMenuItem,
            this.编辑EToolStripMenuItem,
            this.字体WToolStripMenuItem,
            this.关于AToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(588, 25);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件FToolStripMenuItem
            // 
            this.文件FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建NToolStripMenuItem,
            this.打开OToolStripMenuItem,
            this.保存SToolStripMenuItem,
            this.另存为OToolStripMenuItem,
            this.toolStripSeparator1,
            this.退出EToolStripMenuItem});
            this.文件FToolStripMenuItem.Name = "文件FToolStripMenuItem";
            this.文件FToolStripMenuItem.Size = new System.Drawing.Size(58, 21);
            this.文件FToolStripMenuItem.Text = "文件(F)";
            // 
            // 新建NToolStripMenuItem
            // 
            this.新建NToolStripMenuItem.Name = "新建NToolStripMenuItem";
            this.新建NToolStripMenuItem.Size = new System.Drawing.Size(130, 22);
            this.新建NToolStripMenuItem.Text = "新建(N)";
            this.新建NToolStripMenuItem.Click += new System.EventHandler(this.新建NToolStripMenuItem_Click);
            // 
            // 打开OToolStripMenuItem
            // 
            this.打开OToolStripMenuItem.Name = "打开OToolStripMenuItem";
            this.打开OToolStripMenuItem.Size = new System.Drawing.Size(130, 22);
            this.打开OToolStripMenuItem.Text = "打开(O)";
            this.打开OToolStripMenuItem.Click += new System.EventHandler(this.打开OToolStripMenuItem_Click);
            // 
            // 保存SToolStripMenuItem
            // 
            this.保存SToolStripMenuItem.Name = "保存SToolStripMenuItem";
            this.保存SToolStripMenuItem.Size = new System.Drawing.Size(130, 22);
            this.保存SToolStripMenuItem.Text = "保存(S)";
            this.保存SToolStripMenuItem.Click += new System.EventHandler(this.保存SToolStripMenuItem_Click);
            // 
            // 另存为OToolStripMenuItem
            // 
            this.另存为OToolStripMenuItem.Name = "另存为OToolStripMenuItem";
            this.另存为OToolStripMenuItem.Size = new System.Drawing.Size(130, 22);
            this.另存为OToolStripMenuItem.Text = "另存为(O)";
            this.另存为OToolStripMenuItem.Click += new System.EventHandler(this.另存为OToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(127, 6);
            // 
            // 退出EToolStripMenuItem
            // 
            this.退出EToolStripMenuItem.Name = "退出EToolStripMenuItem";
            this.退出EToolStripMenuItem.Size = new System.Drawing.Size(130, 22);
            this.退出EToolStripMenuItem.Text = "退出(E)";
            this.退出EToolStripMenuItem.Click += new System.EventHandler(this.退出EToolStripMenuItem_Click);
            // 
            // 查询CToolStripMenuItem
            // 
            this.查询CToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.查找RToolStripMenuItem,
            this.替换RToolStripMenuItem});
            this.查询CToolStripMenuItem.Name = "查询CToolStripMenuItem";
            this.查询CToolStripMenuItem.Size = new System.Drawing.Size(60, 21);
            this.查询CToolStripMenuItem.Text = "查询(C)";
            // 
            // 查找RToolStripMenuItem
            // 
            this.查找RToolStripMenuItem.Name = "查找RToolStripMenuItem";
            this.查找RToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.查找RToolStripMenuItem.Text = "查找(F)";
            this.查找RToolStripMenuItem.Click += new System.EventHandler(this.查找RToolStripMenuItem_Click);
            // 
            // 替换RToolStripMenuItem
            // 
            this.替换RToolStripMenuItem.Name = "替换RToolStripMenuItem";
            this.替换RToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.替换RToolStripMenuItem.Text = "替换(R)";
            this.替换RToolStripMenuItem.Click += new System.EventHandler(this.替换RToolStripMenuItem_Click);
            // 
            // 编辑EToolStripMenuItem
            // 
            this.编辑EToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.撤回CToolStripMenuItem,
            this.恢复RToolStripMenuItem});
            this.编辑EToolStripMenuItem.Name = "编辑EToolStripMenuItem";
            this.编辑EToolStripMenuItem.Size = new System.Drawing.Size(59, 21);
            this.编辑EToolStripMenuItem.Text = "编辑(E)";
            this.编辑EToolStripMenuItem.Click += new System.EventHandler(this.编辑EToolStripMenuItem_Click);
            // 
            // 撤回CToolStripMenuItem
            // 
            this.撤回CToolStripMenuItem.Name = "撤回CToolStripMenuItem";
            this.撤回CToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.撤回CToolStripMenuItem.Text = "撤回(C)";
            this.撤回CToolStripMenuItem.Click += new System.EventHandler(this.撤回CToolStripMenuItem_Click);
            // 
            // 恢复RToolStripMenuItem
            // 
            this.恢复RToolStripMenuItem.Name = "恢复RToolStripMenuItem";
            this.恢复RToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
            this.恢复RToolStripMenuItem.Text = "恢复(R)";
            this.恢复RToolStripMenuItem.Click += new System.EventHandler(this.恢复RToolStripMenuItem_Click);
            // 
            // 字体WToolStripMenuItem
            // 
            this.字体WToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.修改字体ToolStripMenuItem});
            this.字体WToolStripMenuItem.Name = "字体WToolStripMenuItem";
            this.字体WToolStripMenuItem.Size = new System.Drawing.Size(64, 21);
            this.字体WToolStripMenuItem.Text = "字体(W)";
            // 
            // 修改字体ToolStripMenuItem
            // 
            this.修改字体ToolStripMenuItem.Name = "修改字体ToolStripMenuItem";
            this.修改字体ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.修改字体ToolStripMenuItem.Text = "修改字体(C)";
            this.修改字体ToolStripMenuItem.Click += new System.EventHandler(this.修改字体ToolStripMenuItem_Click);
            // 
            // 关于AToolStripMenuItem
            // 
            this.关于AToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.关于AToolStripMenuItem1});
            this.关于AToolStripMenuItem.Name = "关于AToolStripMenuItem";
            this.关于AToolStripMenuItem.Size = new System.Drawing.Size(60, 21);
            this.关于AToolStripMenuItem.Text = "关于(A)";
            // 
            // 关于AToolStripMenuItem1
            // 
            this.关于AToolStripMenuItem1.Name = "关于AToolStripMenuItem1";
            this.关于AToolStripMenuItem1.Size = new System.Drawing.Size(116, 22);
            this.关于AToolStripMenuItem1.Text = "关于(A)";
            this.关于AToolStripMenuItem1.Click += new System.EventHandler(this.关于AToolStripMenuItem1_Click);
            // 
            // txtNote
            // 
            this.txtNote.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtNote.Location = new System.Drawing.Point(0, 28);
            this.txtNote.Name = "txtNote";
            this.txtNote.Size = new System.Drawing.Size(588, 429);
            this.txtNote.TabIndex = 1;
            this.txtNote.Text = "";
            this.txtNote.WordWrap = false;
            this.txtNote.TextChanged += new System.EventHandler(this.txtNote_TextChanged);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*";
            // 
            // MyText
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(588, 456);
            this.Controls.Add(this.txtNote);
            this.Controls.Add(this.menuStrip1);
            this.DoubleBuffered = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MyText";
            this.Text = "MyText";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormClose);
            this.Load += new System.EventHandler(this.MyText_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 文件FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 新建NToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开OToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 另存为OToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出EToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 查询CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 查找RToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 替换RToolStripMenuItem;
        private System.Windows.Forms.RichTextBox txtNote;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem 编辑EToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 撤回CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 字体WToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 修改字体ToolStripMenuItem;
        private System.Windows.Forms.FontDialog fontDialog1;
        private System.Windows.Forms.ToolStripMenuItem 关于AToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于AToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 恢复RToolStripMenuItem;
    }
}

