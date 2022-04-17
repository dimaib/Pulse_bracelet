using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using System.Data.Common;
using Tutorial.SqlConn;

namespace Body_client
{
    public partial class Form1 : Form
    {

        public static MySqlConnection conn;
        public static MySqlCommand command;
        public static MySqlDataReader reader;

        public static item[] read_item = new item[1000];            //массив элементов фрейма персонала


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            conn = DBUtils.GetDBConnection();
            try { conn.Open(); }                                                                    //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Application.Exit(); }   //обработка исключений

            command = new MySqlCommand("select * from application", conn);                          //объект для выполнения SQL-запроса
            reader = command.ExecuteReader();                                                       //объект для чтения ответа сервера
            string str = "";
            for (int i = 0; reader.Read(); i++)
            {
                read_item[i] = new item()
                {
                    Visible = true,
                    Top = (i == 0) ? 5 : read_item[i - 1].Top + read_item[i - 1].Height + 5,
                    Left = 5,
                    id = Convert.ToInt32(reader[0]),
                    uid0 = Convert.ToUInt32(reader[1]),
                    uid1 = Convert.ToUInt32(reader[2]),
                    uid2 = Convert.ToUInt32(reader[3]),
                    pacient_name = reader[4].ToString(),
                    puls = Convert.ToInt32(reader[6]),
                    sys = Convert.ToInt32(reader[7]),
                    dia = Convert.ToInt32(reader[8]),
                    index = i
                };
                this.Controls.Add(read_item[i]);
                read_item[i].Update();
                this.Height = read_item[i].Top + read_item[i].Height + button1.Height + 25 * 2;
            }
            
            this.Width = read_item[0].Width + 13 * 2;
            button1.Left = read_item[0].Left + read_item[0].Width - button1.Width;
            button1.Top = this.Height - button1.Height - 45;
            reader.Close();
            conn.Close(); conn.Dispose();                                                           //закрываем соединение с БД
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
