using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Media;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalProject2
{
    class Enemy
    {

        static public Form pForm;
        static public List<Enemy> Enemies = new List<Enemy>();

        protected int hp;
        protected int id;
        protected static int count;
        protected Random RND = new Random();
        protected List<PictureBox> images = new List<PictureBox>();
        protected PictureBox mainImage;
        protected int imagePnt = 0;
        protected int xPosition = pForm.Size.Width;
        protected int yPosition;
        protected SoundPlayer player = new SoundPlayer();


        public static Timer myTimer = new Timer();

        static Enemy()
        {
            myTimer.Interval = 100;
            myTimer.Enabled = true;
        }
        public Enemy()
        {
            mainImage = new PictureBox();
            hp = 100;
            id = count;
            count += 1;
            myTimer.Enabled = true;
            myTimer.Tick += MyTimer_Tick;
        }

        protected void MyTimer_Tick(object sender, EventArgs e)
        {
            Move();
            CheckForColission();
        }

        public void CheckForColission()
        {
            for(int i =0; i < Missile.Missiles.Count; i++)
            {
                if (CrashTest(mainImage, Missile.Missiles[i].GetMissile()))
                {
                    Collision();
                    Missile.Missiles[i].Collision();
                }
            }

        }

        public virtual void Collision()
        {
            hp -= 50;
            if (hp <= 0)
            {
                hp = 0;
                Play("\\PUNCH.wav");
                RemoveEnemy();
                Character.Characters[0].score.score += 300;
            }
        }

        public bool CrashTest(PictureBox One, Rectangle Two)
        {
            if (xPosition + One.Width < Two.X)
                return false;
            if (Two.X + Two.Width < xPosition)
                return false;
            if (yPosition + One.Height < Two.Y)
                return false;
            if (Two.Y + Two.Height < yPosition)
                return false;
            return true;
        }

        public virtual void Move()
        {
            if (++imagePnt > images.Count - 1)
            {
                imagePnt = 0;
            }
            mainImage.Image = images[imagePnt].Image;

            xPosition -= 1;
                
        }

        public void RemoveEnemy()
        {
            mainImage.Top = -100;
            myTimer.Tick -= MyTimer_Tick;
            Enemies.Remove(this);
        }
        public void StopTimer()
        {
            myTimer.Tick -= MyTimer_Tick;
        }

        public void ModifiedID(int index)
        {
            for (int i = index; i < Enemies.Count ; i++)
            {
                Enemies[i].id -= 1;
                
            }
            count -= 1;
        }

        public static void ResetEnemies()
        {            
            for (int i = 0; i < Enemies.Count; i++)
                Enemies[i].StopTimer();
            count = 0;
        }
        public virtual void Draw(Graphics gr)
        {
            
        }

        public void Play(string file)
        {
            player.Stop();
            player.SoundLocation = AppDomain.CurrentDomain.BaseDirectory + file;
            player.Play();
        }
    }
}
