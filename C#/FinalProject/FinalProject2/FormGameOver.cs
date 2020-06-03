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
using System.Runtime.Serialization.Formatters.Binary;

namespace FinalProject2
{
    public partial class FormGameOver : Form
    {
        List<Scores> highScores = new List<Scores>();
        List<Label> customLabels = new List<Label>();

        public FormGameOver()
        {
            InitializeComponent();
            try
            {
                using (Stream strm = File.Open("HighScores.bin", FileMode.Open))
                {
                    BinaryFormatter bf = new BinaryFormatter();
                    highScores = (List<Scores>)bf.Deserialize(strm);
                }
            }
            catch (IOException ex)
            {
                MessageBox.Show("Failed to read file, " + ex.Message);
            }

            if (highScores.Count < 5)
            {
                FormHighScore displayForm = new FormHighScore();
                displayForm.ShowDialog();
                highScores.Add(Character.Characters[0].score);
            }
                
            else
            {
                for (int i = 0; i < 5; i++)
                {
                    if (Character.Characters[0].score.score > highScores[i].score)
                    {
                        FormHighScore displayForm = new FormHighScore();
                        displayForm.ShowDialog();
                        highScores.Insert(i, Character.Characters[0].score);
                        break;
                    }
                }
            }
            highScores.RemoveRange(5, (highScores.Count-5));
            try
            {
                using (Stream strm = File.Open("HighScores.bin", FileMode.Create))
                {
                    BinaryFormatter bf = new BinaryFormatter();
                    bf.Serialize(strm, highScores);
                }
            }
            catch (IOException)
            {
                MessageBox.Show("Error while writing");
            }

            for(int i =0; i < 5; i++)
            {
                Label test = new Label();
                test.Location = new Point(lblHighScores.Location.X - 10, lblHighScores.Location.Y + lblHighScores.Height + 10 + (i * 30));
                test.ForeColor = Color.White;
                test.Font = new Font("Arial", 16);
                test.AutoSize = true;
                test.Text = highScores[i].name.ToString() + " - " + highScores[i].score.ToString();
                customLabels.Add(test);
                this.Controls.Add(test);
            }
        }
    }
}
