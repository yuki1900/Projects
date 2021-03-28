using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NumberApplication
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
            parameter.SIZE = 3;
            comboBox2.SelectedIndex = 0;
            parameter.key = 1;
            groupBox1.Visible = true;
            groupBox2.Visible = true;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(comboBox1.SelectedIndex == 0)
            {
                parameter.SIZE = 3;
                groupBox1.Visible = true;
                groupBox2.Visible = true;
            }
            else if(comboBox1.SelectedIndex == 1)
            {
                parameter.SIZE = 4;
                groupBox1.Visible = true;
                groupBox2.Visible = false;
            }
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox2.SelectedIndex == 0)
            {
                parameter.key = 1;
            }
            else if (comboBox2.SelectedIndex == 1)
            {
                parameter.key = 2;
            }
            else if(comboBox2.SelectedIndex == 2)
            {
                parameter.key = 3;
            }
            else if (comboBox2.SelectedIndex == 3)
            {
                parameter.key = 4;
            }
        }
        
    }
}
