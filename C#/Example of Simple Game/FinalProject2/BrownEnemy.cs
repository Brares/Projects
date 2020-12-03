using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalProject2
{
    class BrownEnemy : Enemy
    {
        int xStep, yStep;
        public BrownEnemy()
        {
            try
            {
                for (int i = 0; i < 6; i++)
                {
                    images.Add(new PictureBox());
                    images[i].Image = new Bitmap($"Brown_frame_{i}_delay-0.1s.png");
                }
            }
            catch
            {
                MessageBox.Show("Pictures must be in the same folder as .EXE");
            }

            mainImage.Image = images[0].Image;
            mainImage.SizeMode = PictureBoxSizeMode.AutoSize;

            hp = 900;
            yPosition = RND.Next(45, pForm.Height - mainImage.Height - 65);
            xStep = RND.Next(1, 11);
            yStep = RND.Next(-11, 11);
        }

        public override void Move()
        {
            if (++imagePnt > images.Count - 1)
            {
                imagePnt = 0;
            }
            mainImage.Image = images[imagePnt].Image;
            if (yPosition <= 45 || yPosition + mainImage.Height >= pForm.Height - 65)
                yStep *= -1;
            xPosition -= xStep;
            yPosition -= yStep;

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
