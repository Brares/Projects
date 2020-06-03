using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinalProject2
{
    class Missile
    {
        static public List<Missile> Missiles = new List<Missile>();

        protected int xPosition;
        protected int yPosition;
        protected Rectangle myRectangle;

        public Missile(int x, int y)
        {
            myRectangle = new Rectangle();
            myRectangle.X = x;
            myRectangle.Y = y;
            myRectangle.Width = 5;
            myRectangle.Height = 6;
            

            xPosition = x;
            yPosition = y;
        }

        public void Move()
        {
            myRectangle.X += 10;
        }

        public void Collision()
        {

            Missiles.Remove(this);
           
        }

        public Rectangle GetMissile()
        {
            return myRectangle;
        }
    }
}
