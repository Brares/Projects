using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalProject2
{
    public partial class FormHighScore : Form
    {
        public FormHighScore()
        {
            InitializeComponent();
            lblScore.Text = Character.Characters[0].score.score.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text=="")
            {
                MessageBox.Show("You need to enter your INITIALS");
                return;
            }
            Character.Characters[0].score.name = textBox1.Text;
            this.Close();
        }
    }
}
