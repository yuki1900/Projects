namespace TEXT
{
    partial class fatherForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新建NToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.退出EToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于AToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.子窗口排列CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.水平并排HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.垂直并排ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.层叠排列ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关闭所有子窗口CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关闭CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件FToolStripMenuItem,
            this.关于AToolStripMenuItem,
            this.子窗口排列CToolStripMenuItem,
            this.关闭所有子窗口CToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(849, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件FToolStripMenuItem
            // 
            this.文件FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新建NToolStripMenuItem,
            this.打开OToolStripMenuItem,
            this.toolStripSeparator1,
            this.退出EToolStripMenuItem});
            this.文件FToolStripMenuItem.Name = "文件FToolStripMenuItem";
            this.文件FToolStripMenuItem.Size = new System.Drawing.Size(58, 21);
            this.文件FToolStripMenuItem.Text = "文件(F)";
            // 
            // 新建NToolStripMenuItem
            // 
            this.新建NToolStripMenuItem.Name = "新建NToolStripMenuItem";
            this.新建NToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.新建NToolStripMenuItem.Text = "新建(N)";
            this.新建NToolStripMenuItem.Click += new System.EventHandler(this.新建NToolStripMenuItem_Click);
            // 
            // 打开OToolStripMenuItem
            // 
            this.打开OToolStripMenuItem.Name = "打开OToolStripMenuItem";
            this.打开OToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.打开OToolStripMenuItem.Text = "打开(O)";
            this.打开OToolStripMenuItem.Click += new System.EventHandler(this.打开OToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(127, 6);
            // 
            // 退出EToolStripMenuItem
            // 
            this.退出EToolStripMenuItem.Name = "退出EToolStripMenuItem";
            this.退出EToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.退出EToolStripMenuItem.Text = "退出(E)";
            this.退出EToolStripMenuItem.Click += new System.EventHandler(this.退出EToolStripMenuItem_Click);
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
            this.关于AToolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.关于AToolStripMenuItem1.Text = "关于(A)";
            this.关于AToolStripMenuItem1.Click += new System.EventHandler(this.关于AToolStripMenuItem1_Click);
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
            // 子窗口排列CToolStripMenuItem
            // 
            this.子窗口排列CToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.水平并排HToolStripMenuItem,
            this.垂直并排ToolStripMenuItem,
            this.层叠排列ToolStripMenuItem});
            this.子窗口排列CToolStripMenuItem.Name = "子窗口排列CToolStripMenuItem";
            this.子窗口排列CToolStripMenuItem.Size = new System.Drawing.Size(95, 21);
            this.子窗口排列CToolStripMenuItem.Text = "子窗口排列(S)";
            // 
            // 水平并排HToolStripMenuItem
            // 
            this.水平并排HToolStripMenuItem.Name = "水平并排HToolStripMenuItem";
            this.水平并排HToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.水平并排HToolStripMenuItem.Text = "水平并排(H)";
            this.水平并排HToolStripMenuItem.Click += new System.EventHandler(this.水平并排HToolStripMenuItem_Click);
            // 
            // 垂直并排ToolStripMenuItem
            // 
            this.垂直并排ToolStripMenuItem.Name = "垂直并排ToolStripMenuItem";
            this.垂直并排ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.垂直并排ToolStripMenuItem.Text = "垂直并排(P)";
            this.垂直并排ToolStripMenuItem.Click += new System.EventHandler(this.垂直并排ToolStripMenuItem_Click);
            // 
            // 层叠排列ToolStripMenuItem
            // 
            this.层叠排列ToolStripMenuItem.Name = "层叠排列ToolStripMenuItem";
            this.层叠排列ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.层叠排列ToolStripMenuItem.Text = "层叠排列(S)";
            this.层叠排列ToolStripMenuItem.Click += new System.EventHandler(this.层叠排列ToolStripMenuItem_Click);
            // 
            // 关闭所有子窗口CToolStripMenuItem
            // 
            this.关闭所有子窗口CToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.关闭CToolStripMenuItem});
            this.关闭所有子窗口CToolStripMenuItem.Name = "关闭所有子窗口CToolStripMenuItem";
            this.关闭所有子窗口CToolStripMenuItem.Size = new System.Drawing.Size(120, 21);
            this.关闭所有子窗口CToolStripMenuItem.Text = "关闭所有子窗口(C)";
            // 
            // 关闭CToolStripMenuItem
            // 
            this.关闭CToolStripMenuItem.Name = "关闭CToolStripMenuItem";
            this.关闭CToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.关闭CToolStripMenuItem.Text = "关闭(C)";
            this.关闭CToolStripMenuItem.Click += new System.EventHandler(this.关闭CToolStripMenuItem_Click);
            // 
            // fatherForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(849, 597);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.Name = "fatherForm";
            this.Text = "Notepad";
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
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem 退出EToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于AToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于AToolStripMenuItem1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem 子窗口排列CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 水平并排HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 垂直并排ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 层叠排列ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关闭所有子窗口CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关闭CToolStripMenuItem;
    }
}