namespace MapEditor.UtilsForm
{
    partial class AddNewItem
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AddNewItem));
            this.label1 = new System.Windows.Forms.Label();
            this.txtTileWidth = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtTileHeight = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtBackground = new System.Windows.Forms.TextBox();
            this.btnBrowser = new System.Windows.Forms.Button();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.txtSpritePerRow = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtCountSprite = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.rdMovableObject = new System.Windows.Forms.RadioButton();
            this.rdStaticObject = new System.Windows.Forms.RadioButton();
            this.panel2 = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.cbbTypeItem = new System.Windows.Forms.ComboBox();
            this.Type = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 63);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Tile Width";
            // 
            // txtTileWidth
            // 
            this.txtTileWidth.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtTileWidth.Location = new System.Drawing.Point(81, 60);
            this.txtTileWidth.Name = "txtTileWidth";
            this.txtTileWidth.ReadOnly = true;
            this.txtTileWidth.Size = new System.Drawing.Size(49, 20);
            this.txtTileWidth.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 88);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Tile Height";
            // 
            // txtTileHeight
            // 
            this.txtTileHeight.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtTileHeight.Location = new System.Drawing.Point(81, 86);
            this.txtTileHeight.Name = "txtTileHeight";
            this.txtTileHeight.ReadOnly = true;
            this.txtTileHeight.Size = new System.Drawing.Size(49, 20);
            this.txtTileHeight.TabIndex = 4;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(3, 37);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Item Image";
            // 
            // txtBackground
            // 
            this.txtBackground.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtBackground.Location = new System.Drawing.Point(81, 34);
            this.txtBackground.Name = "txtBackground";
            this.txtBackground.Size = new System.Drawing.Size(304, 20);
            this.txtBackground.TabIndex = 5;
            this.txtBackground.Validated += new System.EventHandler(this.txtBackground_Validated);
            // 
            // btnBrowser
            // 
            this.btnBrowser.Location = new System.Drawing.Point(403, 32);
            this.btnBrowser.Name = "btnBrowser";
            this.btnBrowser.Size = new System.Drawing.Size(24, 23);
            this.btnBrowser.TabIndex = 6;
            this.btnBrowser.Text = "...";
            this.btnBrowser.UseVisualStyleBackColor = true;
            this.btnBrowser.Click += new System.EventHandler(this.btnBrowser_Click);
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(81, 139);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(75, 28);
            this.btnAdd.TabIndex = 7;
            this.btnAdd.Text = "Add";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(188, 139);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 28);
            this.btnCancel.TabIndex = 8;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(136, 63);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(34, 13);
            this.label10.TabIndex = 21;
            this.label10.Text = "Pixels";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(136, 88);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(34, 13);
            this.label11.TabIndex = 22;
            this.label11.Text = "Pixels";
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.Type);
            this.panel1.Controls.Add(this.cbbTypeItem);
            this.panel1.Controls.Add(this.txtSpritePerRow);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.txtCountSprite);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.rdMovableObject);
            this.panel1.Controls.Add(this.rdStaticObject);
            this.panel1.Controls.Add(this.label11);
            this.panel1.Controls.Add(this.label10);
            this.panel1.Controls.Add(this.btnCancel);
            this.panel1.Controls.Add(this.btnAdd);
            this.panel1.Controls.Add(this.btnBrowser);
            this.panel1.Controls.Add(this.txtBackground);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.txtTileHeight);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.txtTileWidth);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(476, 181);
            this.panel1.TabIndex = 1;
            // 
            // txtSpritePerRow
            // 
            this.txtSpritePerRow.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtSpritePerRow.Location = new System.Drawing.Point(327, 86);
            this.txtSpritePerRow.Name = "txtSpritePerRow";
            this.txtSpritePerRow.Size = new System.Drawing.Size(58, 20);
            this.txtSpritePerRow.TabIndex = 27;
            this.txtSpritePerRow.GotFocus += new System.EventHandler(this.txtSpritePerRow_GotFocus);
            this.txtSpritePerRow.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtCountSprite_KeyPress);
            this.txtSpritePerRow.Validated += new System.EventHandler(this.txtSpritePerRow_Validated);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(243, 88);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(78, 13);
            this.label4.TabIndex = 28;
            this.label4.Text = "Sprite Per Row";
            // 
            // txtCountSprite
            // 
            this.txtCountSprite.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtCountSprite.Location = new System.Drawing.Point(327, 60);
            this.txtCountSprite.Name = "txtCountSprite";
            this.txtCountSprite.Size = new System.Drawing.Size(58, 20);
            this.txtCountSprite.TabIndex = 25;
            this.txtCountSprite.GotFocus += new System.EventHandler(this.txtCountSprite_GotFocus);
            this.txtCountSprite.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtCountSprite_KeyPress);
            this.txtCountSprite.Validated += new System.EventHandler(this.txtCountSprite_Validated);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(243, 63);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 13);
            this.label3.TabIndex = 26;
            this.label3.Text = "Count Sprite";
            // 
            // rdMovableObject
            // 
            this.rdMovableObject.AutoSize = true;
            this.rdMovableObject.Location = new System.Drawing.Point(188, 11);
            this.rdMovableObject.Name = "rdMovableObject";
            this.rdMovableObject.Size = new System.Drawing.Size(98, 17);
            this.rdMovableObject.TabIndex = 24;
            this.rdMovableObject.TabStop = true;
            this.rdMovableObject.Text = "Movable object";
            this.rdMovableObject.UseVisualStyleBackColor = true;
            // 
            // rdStaticObject
            // 
            this.rdStaticObject.AutoSize = true;
            this.rdStaticObject.Location = new System.Drawing.Point(81, 11);
            this.rdStaticObject.Name = "rdStaticObject";
            this.rdStaticObject.Size = new System.Drawing.Size(84, 17);
            this.rdStaticObject.TabIndex = 23;
            this.rdStaticObject.TabStop = true;
            this.rdStaticObject.Text = "Static object";
            this.rdStaticObject.UseVisualStyleBackColor = true;
            this.rdStaticObject.CheckedChanged += new System.EventHandler(this.rdStaticObject_CheckedChanged);
            // 
            // panel2
            // 
            this.panel2.AutoScroll = true;
            this.panel2.Controls.Add(this.pictureBox1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 181);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(476, 155);
            this.panel2.TabIndex = 2;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(12, 6);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(452, 137);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // cbbTypeItem
            // 
            this.cbbTypeItem.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbTypeItem.FormattingEnabled = true;
            this.cbbTypeItem.Location = new System.Drawing.Point(81, 115);
            this.cbbTypeItem.Name = "cbbTypeItem";
            this.cbbTypeItem.Size = new System.Drawing.Size(304, 21);
            this.cbbTypeItem.TabIndex = 29;
            // 
            // Type
            // 
            this.Type.AutoSize = true;
            this.Type.Location = new System.Drawing.Point(3, 115);
            this.Type.Name = "Type";
            this.Type.Size = new System.Drawing.Size(54, 13);
            this.Type.TabIndex = 30;
            this.Type.Text = "Type Item";
            // 
            // AddNewItem
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(476, 336);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddNewItem";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Add New Item";
            this.Load += new System.EventHandler(this.AddNewItem_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtTileWidth;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtTileHeight;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtBackground;
        private System.Windows.Forms.Button btnBrowser;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.RadioButton rdMovableObject;
        private System.Windows.Forms.RadioButton rdStaticObject;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox txtCountSprite;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtSpritePerRow;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label Type;
        private System.Windows.Forms.ComboBox cbbTypeItem;
    }
}