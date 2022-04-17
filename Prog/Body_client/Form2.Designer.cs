namespace Body_client
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.title = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.t_name = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.t_puls = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.t_sys = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.t_dia = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.BackColor = System.Drawing.Color.Gray;
            this.listBox1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(12, 30);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(558, 563);
            this.listBox1.TabIndex = 0;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.ListBox1_SelectedIndexChanged);
            // 
            // title
            // 
            this.title.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.title.AutoSize = true;
            this.title.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.title.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.title.Location = new System.Drawing.Point(12, 0);
            this.title.Name = "title";
            this.title.Size = new System.Drawing.Size(298, 18);
            this.title.TabIndex = 1;
            this.title.Text = "Уникальный номер устройства: ";
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.Gray;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Location = new System.Drawing.Point(503, 610);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(67, 26);
            this.button1.TabIndex = 2;
            this.button1.Text = "Закрыть";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // t_name
            // 
            this.t_name.Location = new System.Drawing.Point(12, 616);
            this.t_name.Name = "t_name";
            this.t_name.Size = new System.Drawing.Size(158, 20);
            this.t_name.TabIndex = 3;
            this.t_name.Leave += new System.EventHandler(this.T_name_Leave);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label1.Location = new System.Drawing.Point(9, 600);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Имя";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label2.Location = new System.Drawing.Point(173, 600);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Пульс";
            // 
            // t_puls
            // 
            this.t_puls.Location = new System.Drawing.Point(176, 616);
            this.t_puls.MaxLength = 3;
            this.t_puls.Name = "t_puls";
            this.t_puls.Size = new System.Drawing.Size(44, 20);
            this.t_puls.TabIndex = 5;
            this.t_puls.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.t_puls.TextChanged += new System.EventHandler(this.TextBox2_TextChanged);
            this.t_puls.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox2_KeyPress);
            this.t_puls.Leave += new System.EventHandler(this.T_puls_Leave);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label3.Location = new System.Drawing.Point(223, 600);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "SYS АД";
            // 
            // t_sys
            // 
            this.t_sys.Location = new System.Drawing.Point(226, 616);
            this.t_sys.MaxLength = 3;
            this.t_sys.Name = "t_sys";
            this.t_sys.Size = new System.Drawing.Size(44, 20);
            this.t_sys.TabIndex = 7;
            this.t_sys.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.t_sys.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox3_KeyPress);
            this.t_sys.Leave += new System.EventHandler(this.T_sys_Leave);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label4.Location = new System.Drawing.Point(273, 600);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "DIA АД";
            // 
            // t_dia
            // 
            this.t_dia.Location = new System.Drawing.Point(276, 616);
            this.t_dia.MaxLength = 3;
            this.t_dia.Name = "t_dia";
            this.t_dia.Size = new System.Drawing.Size(41, 20);
            this.t_dia.TabIndex = 9;
            this.t_dia.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.t_dia.TextChanged += new System.EventHandler(this.T_dia_TextChanged);
            this.t_dia.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox4_KeyPress);
            this.t_dia.Leave += new System.EventHandler(this.T_dia_Leave);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DimGray;
            this.ClientSize = new System.Drawing.Size(582, 647);
            this.ControlBox = false;
            this.Controls.Add(this.label4);
            this.Controls.Add(this.t_dia);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.t_sys);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.t_puls);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.t_name);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.title);
            this.Controls.Add(this.listBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form2";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Данные поциента";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        public System.Windows.Forms.Label title;
        public System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox t_name;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox t_puls;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox t_sys;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox t_dia;
    }
}