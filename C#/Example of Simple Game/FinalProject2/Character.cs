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
    
    class Character
    {
        static public Form pForm;
        static public List<Character> Characters = new List<Character>();

        private PictureBox mainImage = new PictureBox();
        private int newX =0;
        private int newY = 250;
        private int life = 100;

        public Scores score;

        public static Timer myTimer = new Timer();

        public  Character()
        {
            mainImage.Image = new Bitmap("character shooting.png");
            mainImage.Location = new Point(newX, newY);
            mainImage.SizeMode = PictureBoxSizeMode.AutoSize;

            score = new Scores();

            myTimer.Interval = 100;
            myTimer.Enabled = true;
            myTimer.Tick += MyTimer_Tick;
        }

        protected void MyTimer_Tick(object sender, EventArgs e)
        {
            Missile.Missiles.Add(new Missile(newX + mainImage.Width + 14, newY + (mainImage.Height / 2) - 9));
            for (int i = 0; i < Missile.Missiles.Count; i++)
            {
                if (Missile.Missiles[i].GetMissile().Left + Missile.Missiles[i].GetMissile().Width >= pForm.Width -50)
                {
                    Missile.Missiles[i].Collision();
                }
                else
                {
                    Missile.Missiles[i].Move();
                }  
            }         
        }

        public void MoveUp()
        {
            if (newY < 40)
                return;
            else
                newY -= 10;
        }
        public void MoveDown()
        {
            if (newY > pForm.Height - (mainImage.Height*2) + 40)
                return;
            else
                newY += 10;
        }

        public void LifeDown(int damage)
        {
            life = life - damage;
        }

        public int GetLife()
        {
            return life;
        }

        public void ResetCharacter()
        {
            for (int i = 0; i < Characters.Count; i++)
                Characters[i].StopTimer();

        }

        public void StopTimer()
        {
            myTimer.Tick -= MyTimer_Tick;
        }

        public void Draw(Graphics gr)
        {
            gr.DrawImage(mainImage.Image, new Point(newX, newY));
            foreach(Missile tmp in Missile.Missiles)
            {
                gr.FillRectangle(new SolidBrush(Color.Red), tmp.GetMissile());
                gr.DrawRectangle(new Pen(Color.Red), tmp.GetMissile());
            }
            
        }
    }
}
