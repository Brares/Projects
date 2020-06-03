using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalProject2
{
    class RedEnemy : Enemy
    {
        public RedEnemy()
        {
            try
            {
                for (int i = 0; i < 8; i++)
                {
                    images.Add(new PictureBox());
                    images[i].Image = new Bitmap($"frame_{i}_delay-0.1s.png");
                }
            }
            catch
            {
                MessageBox.Show("Pictures must be in the same folder as .EXE");
            }

            mainImage.Image = images[0].Image;
            mainImage.SizeMode = PictureBoxSizeMode.AutoSize;

            hp = 400;
            yPosition = RND.Next(45, pForm.Height - mainImage.Height - 65);
        }

        public override void Move()
        {
            if (++imagePnt > images.Count - 1)
            {
                imagePnt = 0;
            }
            mainImage.Image = images[imagePnt].Image;

            xPosition -= 10;

            if (xPosition < 50 && xPosition != 0 && Enemies.Count != 0)
            {
                Play("\\Explosion+5.wav");
                RemoveEnemy();
                Character.Characters[0].LifeDown(10);
            }               
        }

        public override void Draw(Graphics gr)
        {
            gr.DrawImage(mainImage.Image, new Point(xPosition, yPosition));
        }       
    }
}

