using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Media;

namespace ElevatorProgram
{
    class Elevator
    {
        static public Form pForm;
        static public List<Elevator> Eleveators = new List<Elevator>();

        private const int LOWERY = 795;
        private const int UPPERY = 315;
        private const int FLOORHEIGHT = 65;
        private int EV_Y = LOWERY;
        private int EV_New_Y;
        private int EV_Floor = 0;
        private int EV_New_Floor;


        private enum ElevState { waiting, prep_closing, closing, prep_moving, moving, prep_opening, opening };
        private ElevState EVState;

        private static List<PictureBox> images = new List<PictureBox>();
        private static Hashtable replaceValues = new Hashtable();

        private PictureBox mainImage = new PictureBox();
        private int imagePnt;
        private ComboBox floor;
        private Label lblfloor;
        private SoundPlayer player;


        private static Timer myTimer = new Timer();

        static Elevator()
        {
            try
            {
                for (int i = 0; i < 83; i++)
                {
                    images.Add(new PictureBox());
                    images[i].Image = new Bitmap($"frame_{i}_delay-0.04s.gif");
                }
            }
            catch
            {
                MessageBox.Show("Pictures must be in the same folder as .EXE");
            }
            replaceValues.Add("0", 795);
            replaceValues.Add("1", 731);
            replaceValues.Add("2", 674);
            replaceValues.Add("3", 624);
            replaceValues.Add("4", 575);
            replaceValues.Add("5", 526);
            replaceValues.Add("6", 478);
            replaceValues.Add("7", 426);
            replaceValues.Add("8", 374);
            replaceValues.Add("9", 321);
            replaceValues.Add("10", 300);

            myTimer.Interval = 100;
            myTimer.Enabled = true;

           
        }

        public Elevator(int x, int y)
        {
            mainImage.Image = images[40].Image;
            mainImage.SizeMode = PictureBoxSizeMode.AutoSize;
            mainImage.Left = x;
            mainImage.Top = y;

            floor = new ComboBox();
            floor.Left = x;
            floor.Top = y + mainImage.Height;
            floor.Width = mainImage.Width+ 10;
            floor.Height = mainImage.Height;
            floor.BackColor = System.Drawing.Color.Orange;
            floor.ForeColor = System.Drawing.Color.Black;

            lblfloor = new Label();
            lblfloor.Text = "Lobby";
            lblfloor.BackColor = Color.White;
            lblfloor.Width = mainImage.Width + 8;
            lblfloor.Left = x;
            lblfloor.Top = y - lblfloor.Height;
            

            floor.Items.Add("Lobby");
            floor.Items.Add("Floor 2");
            floor.Items.Add("Floor 3");
            floor.Items.Add("Floor 4");
            floor.Items.Add("Floor 5");
            floor.Items.Add("Floor 6");
            floor.Items.Add("Floor 7");
            floor.Items.Add("Floor 8");
            floor.Items.Add("Floor 9");
            floor.Items.Add("Floor 10");

            pForm.Controls.Add(floor);
            pForm.Controls.Add(lblfloor);

            player = new SoundPlayer();
            player.SoundLocation = AppDomain.CurrentDomain.BaseDirectory + "\\Elevator-music.wav";

            EVState = ElevState.waiting;

            myTimer.Tick += MyTimer_Tick;
        }

        private void MyTimer_Tick(object sender, EventArgs e)
        {
            switch (EVState)
            {
                case ElevState.waiting:
                    imagePnt = 40;
                    floor.SelectedIndexChanged += new System.EventHandler(floor_SelectedIndexChanged);
                    
                    break;
                case ElevState.prep_closing:
                    imagePnt = 40;
                    
                    EVState = ElevState.closing;
                    
                    break;
                case ElevState.closing:

                    Closing();

                    break;
                case ElevState.prep_moving:
                    EV_New_Floor = floor.SelectedIndex;
                    imagePnt = 0;

                    if (EV_New_Floor != EV_Floor)
                    {
                        EV_New_Y = (int)replaceValues[EV_New_Floor.ToString()];
                        player.PlayLooping();
                        EVState = ElevState.moving;
                    }
                    else
                    {
                        
                        EVState = ElevState.prep_opening;
                    }
                        
                                       
                    break;
                case ElevState.moving:

                    
                    Moving();
                   
                    break;
                case ElevState.prep_opening:

                    imagePnt= 0;
                    EVState = ElevState.opening;
                   
                    break;
                case ElevState.opening:

                    Opening();
                   
                    break;

            }
        }

        public void Draw(Graphics gr)
        {
            gr.DrawImage(mainImage.Image, new Point(mainImage.Left, mainImage.Top));

            floor.Location = new Point(mainImage.Left, mainImage.Top + mainImage.Height + 10);
            lblfloor.Location = new Point(mainImage.Left, mainImage.Top - lblfloor.Height - 10);

        }

        public void Closing()
        {
            if (++imagePnt <= (images.Count) -1)
            {
                mainImage.Image = images[imagePnt].Image;
            }
            else
            {
                EVState = ElevState.prep_moving;
            }
        }

        public void Opening()
        {
            if (++imagePnt <= ((images.Count) - 1) / 2)
            {
                mainImage.Image = images[imagePnt].Image;
            }
            else
            {
                EV_Floor = EV_New_Floor;
                EVState = ElevState.waiting;
            }
        }

        public void Moving ()
        {
            if (mainImage.Top > EV_New_Y)
            {
                EV_Y--;
                mainImage.Top--;
                lblfloor.Text = ReturnFloor();
                
            }
            else if (mainImage.Top < EV_New_Y)
            {
                EV_Y++;
                mainImage.Top++;
                lblfloor.Text = ReturnFloor();

            }
            else
            {
                player.Stop();
                EVState = ElevState.prep_opening;
            }
        }

        public string ReturnFloor()
        {
            if (mainImage.Top == (int)replaceValues["0"])
            {
                return "Lobby";
            }

            else if (mainImage.Top < (int)replaceValues["0"] && mainImage.Top >= (int)replaceValues["1"])
            {
                return "Floor 2";
            }
            else if (mainImage.Top < (int)replaceValues["1"] && mainImage.Top >= (int)replaceValues["2"])
            {
                return "Floor 3";
            }
            else if (mainImage.Top < (int)replaceValues["2"] && mainImage.Top >= (int)replaceValues["3"])
            {
                return "Floor 4";
            }
            else if (mainImage.Top < (int)replaceValues["3"] && mainImage.Top >= (int)replaceValues["4"])
            {
                return "Floor 5";
            }
            else if (mainImage.Top < (int)replaceValues["4"] && mainImage.Top >= (int)replaceValues["5"])
            {
                return "Floor 6";
            }
            else if (mainImage.Top < (int)replaceValues["5"] && mainImage.Top >= (int)replaceValues["6"])
            {
                return "Floor 7";
            }
            else if (mainImage.Top < (int)replaceValues["6"] && mainImage.Top >= (int)replaceValues["7"])
            {
                return "Floor 8";
            }
            else if (mainImage.Top < (int)replaceValues["7"] && mainImage.Top >= (int)replaceValues["8"])
            {
                return "Floor 9";
            }
            else if (mainImage.Top < (int)replaceValues["8"] && mainImage.Top >= (int)replaceValues["9"])
            {
                return "Floor 10";
            }
            return "";
        }

        private void floor_SelectedIndexChanged(object sender, EventArgs e)
        {
            
            EVState = ElevState.prep_closing;
        }

    }
}
