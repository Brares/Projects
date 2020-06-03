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
using System.Media;

namespace FinalProject2
{
    public partial class Form1 : Form
    {
        //The delegate
        public delegate void MyDelegate();
        MyDelegate MyD1;

        Random RND = new Random();
        int probabilityEnemy=60;
        int ticks;
        int seconds;
        PictureBox back1 = new PictureBox();
        PictureBox back2 = new PictureBox();
        int pback1 = 0; 
        int pback2 =0;
        WMPLib.WindowsMediaPlayer player1 = new WMPLib.WindowsMediaPlayer();
        public Form1()
        {
            InitializeComponent();
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            Character.pForm = this;
            Enemy.pForm = this;

            back1.Image = new Bitmap("Background.png");
            pback2 = back1.Image.Width;

            Character.Characters.Add(new Character());
            MyD1 = Character.Characters[0].ResetCharacter;


        }
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawImage(back1.Image, new PointF(pback1, 0));
            e.Graphics.DrawImage(back1.Image, new PointF(pback2, 0));
            foreach (Character tmp in Character.Characters)
                tmp.Draw(e.Graphics);
            foreach (Enemy tmp in Enemy.Enemies)
                tmp.Draw(e.Graphics);
           
        }

        private void newGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Play("\\Background_Music.wav");
            ShowLabels();
            timer1.Stop();
            Enemy.myTimer.Stop();
            Enemy.myTimer.Enabled = false;
            Character.myTimer.Stop();
            Character.myTimer.Enabled = false;
            timer1.Enabled = false;
            barLife.Value = 100;
            Enemy.ResetEnemies();
            MyD1();
            Missile.Missiles.Clear();
            Character.Characters.Clear();
            
            Enemy.Enemies.Clear();
            
            Character.Characters.Add(new Character());
            MyD1 = Character.Characters[0].ResetCharacter;
            Enemy.Enemies.Add(new RedEnemy());

            seconds = 0;
            ticks = 0;
            probabilityEnemy = 60;

            timer1.Enabled = true;
            timer1.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                this.Invalidate(false);
                if (RND.Next(0, probabilityEnemy) == 1)
                {
                    if (RND.Next(0, 3) == 1)
                        Enemy.Enemies.Add(new BrownEnemy());
                    else
                        Enemy.Enemies.Add(new RedEnemy());
                }

                if (barLife.Value <= 0)
                    GameOver();
                else
                    barLife.Value = Character.Characters[0].GetLife();
                ticks++;
                if (ticks == 10)
                {
                    seconds++;
                    if (seconds == 10)
                        probabilityEnemy -= 10;
                    else if (seconds == 20)
                        probabilityEnemy -= 10;
                    else if (seconds == 30)
                        probabilityEnemy -= 10;
                    else if (seconds == 40)
                        probabilityEnemy -= 10;
                    else if (seconds == 50)
                        probabilityEnemy -= 10;
                    else if (seconds == 120)
                        probabilityEnemy -= 5;
                    ticks = 0;
                }

                if (-pback1 >= back1.Image.Width)
                {
                    pback1 = back1.Image.Width;
                }
                if (-pback2 >= back1.Image.Width)
                {
                    pback2 = back1.Image.Width;
                }
                pback1--;
                pback2--;

                lblScore.Text = Character.Characters[0].score.score.ToString();
                lblSeconds.Visible = true;
                lblSeconds.Text = seconds.ToString();
                lblSeconds.Visible = true;
            }

            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
           
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (Character.Characters.Count == 0)
                return true;
            if (keyData == Keys.A) Character.Characters[0].MoveUp();
            if (keyData == Keys.Z) Character.Characters[0].MoveDown();
            if (keyData == Keys.Up) Character.Characters[0].MoveUp();
            if (keyData == Keys.Down) Character.Characters[0].MoveDown();

            return true;
        }

        private void ShowLabels()
        {
            lblLife.Visible = true;
            barLife.Visible = true;
            lblScore.Visible = true;
            lblTime.Visible = true;
        }

        private void GameOver()
        {
            timer1.Stop();
            timer1.Enabled = false;
            player1.controls.stop();
            Enemy.myTimer.Enabled = false;
            Character.myTimer.Enabled = false;
            FormGameOver gameover = new FormGameOver();
            gameover.ShowDialog();
        }

        public void Play(string file)
        {
            player1.controls.stop();
            player1.URL = AppDomain.CurrentDomain.BaseDirectory + file;
            (this.player1.settings as WMPLib.IWMPSettings).setMode("loop", true);
            player1.controls.play();
        }
    }
}
