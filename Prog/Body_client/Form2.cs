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
using Body_client;

namespace Body_client
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private int id_;
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

        public int id
        {
            set
            {
                id_ = value;
            }
        }

        public string puls
        {
            set
            {
                t_puls.Text = value;
            }
        }
        public string sys
        {
            set
            {
                t_sys.Text = value;
            }
        }

        public string dia
        {
            set
            {
                t_dia.Text = value;
            }
        }

        public string NAME
        {
            set
            {
                t_name.Text = value;
            }
        }

        private void TableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show(listBox1.Items.Count.ToString());
        }

        private void TextBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void TextBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
        }

        private void TextBox3_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
        }

        private void TextBox4_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
        }

        private void T_puls_Leave(object sender, EventArgs e)
        {
            if (t_puls.Text == ""|| t_puls.Text == ".") t_puls.Text = "0";
            string sql = "UPDATE `body_2.0`.`application` SET `K_Puls` = '" + t_puls.Text + "' WHERE (`id` = '" + id_.ToString() + "');";
            Form1.conn = DBUtils.GetDBConnection();
            try { Form1.conn.Open(); }                                                          //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Close(); }  //обработка исключений
            Form1.command = new MySqlCommand(sql, Form1.conn);
            Form1.command.ExecuteNonQuery();
            Form1.conn.Close();
            Form1.read_item[index_].puls = Convert.ToInt32(t_puls.Text);
        }

        private void T_name_Leave(object sender, EventArgs e)
        {
            if (t_puls.Text == "" || t_puls.Text == ".") t_puls.Text = "0";
            string sql = "UPDATE `body_2.0`.`application` SET `patient` = '" + t_name.Text + "' WHERE (`id` = '" + id_.ToString() + "');";
            Form1.conn = DBUtils.GetDBConnection();
            try { Form1.conn.Open(); }                                                          //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Close(); }  //обработка исключений
            Form1.command = new MySqlCommand(sql, Form1.conn);
            Form1.command.ExecuteNonQuery();
            Form1.conn.Close();
            Form1.read_item[index_].pacient_name = t_name.Text;
        }

        private void T_sys_Leave(object sender, EventArgs e)
        {
            if (t_puls.Text == "" || t_puls.Text == ".") t_puls.Text = "0";
            string sql = "UPDATE `body_2.0`.`application` SET `K_PUp` = '" + t_sys.Text + "' WHERE (`id` = '" + id_.ToString() + "');";
            Form1.conn = DBUtils.GetDBConnection();
            try { Form1.conn.Open(); }                                                          //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Close(); }  //обработка исключений
            Form1.command = new MySqlCommand(sql, Form1.conn);
            Form1.command.ExecuteNonQuery();
            Form1.conn.Close();
            Form1.read_item[index_].sys = Convert.ToInt32(t_sys.Text);
        }

        private void T_dia_Leave(object sender, EventArgs e)
        {
            if (t_puls.Text == "" || t_puls.Text == ".") t_puls.Text = "0";
            string sql = "UPDATE `body_2.0`.`application` SET `K_PDown` = '" + t_dia.Text + "' WHERE (`id` = '" + id_.ToString() + "');";
            Form1.conn = DBUtils.GetDBConnection();
            try { Form1.conn.Open(); }                                                          //обработка исключений
            catch (Exception e_) { MessageBox.Show("Error: " + e_.Message); Close(); }  //обработка исключений
            Form1.command = new MySqlCommand(sql, Form1.conn);
            Form1.command.ExecuteNonQuery();
            Form1.conn.Close();
            Form1.read_item[index_].dia = Convert.ToInt32(t_dia.Text);
        }

        private void T_dia_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
