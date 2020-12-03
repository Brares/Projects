using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ElevatorProgram
{
    public partial class Form1 : Form
    {
        public delegate string MyDelegate();
        MyDelegate MyD1, MyD2, MyD3;

        public Form1()
        {
            InitializeComponent();

            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.SetStyle(ControlStyles.UserPaint, true);

            Elevator.pForm = this;
            Elevator.Eleveators.Add( new Elevator(219, 795));
            MyD1 = Elevator.Eleveators[0].ReturnFloor;
            Elevator.Eleveators.Add(new Elevator(393, 795));
            MyD2 = Elevator.Eleveators[1].ReturnFloor;
            Elevator.Eleveators.Add(new Elevator(655, 795));
            MyD3 = Elevator.Eleveators[2].ReturnFloor;

            timer1.Enabled = true;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            foreach (Elevator tmp in Elevator.Eleveators)
                tmp.Draw(e.Graphics);               
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Invalidate(false);
            lblElevator1.Text = MyD1();
            lblElevator2.Text = MyD2();
            lblElevator3.Text = MyD3();
        }
    }
}