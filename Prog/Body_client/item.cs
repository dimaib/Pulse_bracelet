using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using System.Data.Common;
using Tutorial.SqlConn;

namespace Body_client
{
    public partial class item : UserControl
    {
        private float temperature_;
        private string time_;
        private int SpO2_;
        private int puls_;
        private int Pup_;
        private int Pdown_;
        private UInt32 uid0_;
        private UInt32 uid1_;
        private UInt32 uid2_;
        private string pacient_name_;
        private int id_;
        private int sys_;
        private int dia_;
        private object it_;
        private int index_;

        public int index
        {
            set
            {
                index_ = value;
            }
            get
            {
                return index_;
            }
        }

        public int sys
        {
            set
            {
                sys_ = value;
            }
            get
            {
                return sys_;
            }
        }

        public int dia
        {
            set
            {
                dia_ = value;
            }
            get
            {
                return dia_;
            }
        }

        public int id
        {
            set
            {
                id_ = value;
            }
            get
            {
                return id_;
            }
        }

        public string pacient_name
        {
            set
            {
                pacient_name_ = value;
                lname.Text = "Имя поциента: " + pacient_name_;
            }
            get
            {
                return pacient_name_;
            }
        }


        public UInt32 uid0
        {
            set
            {
                uid0_ = value;
                luid.Text = "Уникальный номер устройства: " + uid0_.ToString() + "_" + uid1_.ToString() + "_" + uid2_.ToString();
            }
            get
            {
                return uid0_;
            }
        }
        public UInt32 uid1
        {
            set
            {
                uid1_ = value;
                luid.Text = "Уникальный номер устройства: " + uid0_.ToString() + "_" + uid1_.ToString() + "_" + uid2_.ToString();
            }
            get
            {
                return uid1_;
            }
        }
        public UInt32 uid2
        {
            set
            {
                uid2_ = value;
                luid.Text = "Уникальный номер устройства: " + uid0_.ToString() + "_" + uid1_.ToString() + "_" + uid2_.ToString();
            }
            get
            {
                return uid2_;
            }
        }



        public float temperature
        {
            set
            {
                temperature_ = value;
         
            }
            get
            {
                return temperature_;
            }
        }
        public string time
        {
            set
            {
                time_ = value;
                luid.Text = "Время записи: " + value.ToString();
            }

            get
            {
                return time_;
            }
        }

        public int SpO2
        {
            set
            {
                SpO2_ = value;
            }
            get
            {
                return SpO2_;
            }
        }

        public int puls
        {
            set
            {
                puls_ = value;
            }
            get
            {
                return puls_;
            }
        }

        public int Pup
        {
            set
            {
                Pup_ = value;
            }
            get
            {
                return Pup_;
            }
        }

        public int Pdown
        {
            set
            {
                Pdown_ = value;
            }
            get
            {
                return Pdown_;
            }
        }
        private static LinkLabel[] labellk = new LinkLabel[32];            //массив элементов фрейма персонала


        private void labellk_Click(object sender, EventArgs e)
        {
            Body_client.Form1.conn = DBUtils.GetDBConnection();
            try { Body_client.Form1.conn.Open(); }                                                                      //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Application.Exit(); }                       //обработка исключений
            string query_str = "SELECT * FROM application WHERE id=" + id_.ToString() + ";";
            Body_client.Form1.command = new MySqlCommand(query_str, Body_client.Form1.conn);                            //объект для выполнения SQL-запроса
            Body_client.Form1.reader = Body_client.Form1.command.ExecuteReader();                                       //объект для чтения ответа сервера
            UInt32 commands_flag = 0;
            for (int i = 0; Body_client.Form1.reader.Read(); i++) commands_flag = (UInt32)Convert.ToInt32(Body_client.Form1.reader[5]);
            Body_client.Form1.conn.Close();

            Body_client.Form1.conn = DBUtils.GetDBConnection();
            try { Body_client.Form1.conn.Open(); }                                                                      //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Application.Exit(); }                       //обработка исключений
            commands_flag |= (UInt32)(1 << Convert.ToInt32((sender as LinkLabel).Text));
            query_str = "UPDATE application SET commands = " + commands_flag.ToString() + " WHERE (id = " + id_.ToString() + ");";
            Body_client.Form1.command = new MySqlCommand(query_str, Body_client.Form1.conn);
            Body_client.Form1.command.ExecuteNonQuery();
            Body_client.Form1.conn.Close();
        }

        private void load_link_commands()
        {
            for (byte i = 0; i < 32; i++) {
                labellk[i] = new LinkLabel()
                {
                    Visible = true,
                    AutoSize = true,
                    BorderStyle = BorderStyle.FixedSingle,
                    Text = i > 9 ? i.ToString() : "0" + i.ToString(),
                    Left = i != 0 ? labellk[i - 1].Left + labellk[i - 1].Width-1:pictureBox1.Left+pictureBox1.Width+5,
                    Top=pictureBox1.Top+pictureBox1.Height-20,
            };
                this.Controls.Add(labellk[i]);
                labellk[i].Click += new System.EventHandler(labellk_Click);
            }
        }

        public item()
        {
            InitializeComponent();
        }

        private void Item_Load(object sender, EventArgs e)
        {
            load_link_commands();
        }

        private void PictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void Item_DoubleClick(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.title.Text = "Пациент: " + pacient_name_;
            form2.listBox1.Items.Clear();
            Body_client.Form1.conn = DBUtils.GetDBConnection();
            try { Body_client.Form1.conn.Open(); }                                                                      //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Application.Exit(); }                       //обработка исключений
            string query_str = "SELECT * FROM telemetry WHERE uid0=" + uid0_.ToString() + " AND uid1=" + uid1_.ToString() + " AND uid2=" + uid2_.ToString() + ";";
            Body_client.Form1.command = new MySqlCommand(query_str, Body_client.Form1.conn);            //объект для выполнения SQL-запроса
            Body_client.Form1.reader = Body_client.Form1.command.ExecuteReader();                                       //объект для чтения ответа сервера
            for (int i = 0; Body_client.Form1.reader.Read(); i++)
            {
                form2.listBox1.Items.Add(Body_client.Form1.reader[1]+"     Температура: "+ Body_client.Form1.reader[5] +"\tКислород: "+ 
                    Body_client.Form1.reader[6]+"%"+"\tПульс: "+ Body_client.Form1.reader[7]+"уд/мин."+ "\tДавление: "+ Body_client.Form1.reader[8]+"/"+
                    Body_client.Form1.reader[9]);
                form2.listBox1.SetSelected(i, true);
            }
            form2.id = id_;
            form2.NAME = pacient_name_;
            form2.puls = puls_.ToString();
            form2.sys = sys_.ToString();
            form2.dia = dia_.ToString();
            form2.index = index_;

            form2.Show();
        }


    }
}
