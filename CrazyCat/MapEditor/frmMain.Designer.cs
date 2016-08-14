
namespace MapEditor
{
    partial class frmMain
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.panel1 = new System.Windows.Forms.Panel();
            this.pnItem = new System.Windows.Forms.Panel();
            this.ptbRemoveItem = new System.Windows.Forms.PictureBox();
            this.ptbAddItem = new System.Windows.Forms.PictureBox();
            this.pnInformation = new System.Windows.Forms.Panel();
            this.label4 = new System.Windows.Forms.Label();
            this.txtTileHeight = new System.Windows.Forms.TextBox();
            this.txtColumns = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtRows = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtTileWidth = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.pnButton = new System.Windows.Forms.Panel();
            this.btnExit = new System.Windows.Forms.Button();
            this.btnOpenMap = new System.Windows.Forms.Button();
            this.btnSaveMap = new System.Windows.Forms.Button();
            this.btnNewMap = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.pnMapDraw = new MapEditor.UserControlDesign.MyPanel();
            this.imageListView1 = new MapEditor.UserControlDesign.ImageListView();
            this.panel1.SuspendLayout();
            this.pnItem.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ptbRemoveItem)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ptbAddItem)).BeginInit();
            this.pnInformation.SuspendLayout();
            this.pnButton.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.pnItem);
            this.panel1.Controls.Add(this.pnInformation);
            this.panel1.Controls.Add(this.pnButton);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(370, 412);
            this.panel1.TabIndex = 0;
            // 
            // pnItem
            // 
            this.pnItem.Controls.Add(this.imageListView1);
            this.pnItem.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnItem.Location = new System.Drawing.Point(0, 130);
            this.pnItem.Name = "pnItem";
            this.pnItem.Size = new System.Drawing.Size(370, 282);
            this.pnItem.TabIndex = 2;
            // 
            // ptbRemoveItem
            // 
            this.ptbRemoveItem.Cursor = System.Windows.Forms.Cursors.Default;
            this.ptbRemoveItem.Image = global::MapEditor.Properties.Resources.delete_icon;
            this.ptbRemoveItem.Location = new System.Drawing.Point(272, 11);
            this.ptbRemoveItem.Name = "ptbRemoveItem";
            this.ptbRemoveItem.Size = new System.Drawing.Size(34, 29);
            this.ptbRemoveItem.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.ptbRemoveItem.TabIndex = 0;
            this.ptbRemoveItem.TabStop = false;
            this.ptbRemoveItem.Click += new System.EventHandler(this.ptbRemoveItem_Click);
            this.ptbRemoveItem.MouseLeave += new System.EventHandler(this.btnNewMap_MouseLeave);
            this.ptbRemoveItem.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btnNewMap_MouseMove);
            // 
            // ptbAddItem
            // 
            this.ptbAddItem.Cursor = System.Windows.Forms.Cursors.Default;
            this.ptbAddItem.Image = global::MapEditor.Properties.Resources.add_icon;
            this.ptbAddItem.Location = new System.Drawing.Point(193, 11);
            this.ptbAddItem.Name = "ptbAddItem";
            this.ptbAddItem.Size = new System.Drawing.Size(35, 29);
            this.ptbAddItem.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.ptbAddItem.TabIndex = 1;
            this.ptbAddItem.TabStop = false;
            this.ptbAddItem.Click += new System.EventHandler(this.ptbAddItem_Click);
            this.ptbAddItem.MouseLeave += new System.EventHandler(this.btnNewMap_MouseLeave);
            this.ptbAddItem.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btnNewMap_MouseMove);
            // 
            // pnInformation
            // 
            this.pnInformation.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnInformation.Controls.Add(this.label4);
            this.pnInformation.Controls.Add(this.txtTileHeight);
            this.pnInformation.Controls.Add(this.txtColumns);
            this.pnInformation.Controls.Add(this.label3);
            this.pnInformation.Controls.Add(this.txtRows);
            this.pnInformation.Controls.Add(this.label2);
            this.pnInformation.Controls.Add(this.txtTileWidth);
            this.pnInformation.Controls.Add(this.label1);
            this.pnInformation.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnInformation.Location = new System.Drawing.Point(0, 64);
            this.pnInformation.Name = "pnInformation";
            this.pnInformation.Size = new System.Drawing.Size(370, 66);
            this.pnInformation.TabIndex = 1;
            this.pnInformation.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.pnInformation.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(122, 12);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(14, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "X";
            this.label4.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.label4.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // txtTileHeight
            // 
            this.txtTileHeight.Location = new System.Drawing.Point(162, 9);
            this.txtTileHeight.Name = "txtTileHeight";
            this.txtTileHeight.ReadOnly = true;
            this.txtTileHeight.Size = new System.Drawing.Size(49, 20);
            this.txtTileHeight.TabIndex = 6;
            this.txtTileHeight.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.txtTileHeight.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // txtColumns
            // 
            this.txtColumns.Location = new System.Drawing.Point(162, 35);
            this.txtColumns.Name = "txtColumns";
            this.txtColumns.ReadOnly = true;
            this.txtColumns.Size = new System.Drawing.Size(49, 20);
            this.txtColumns.TabIndex = 5;
            this.txtColumns.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.txtColumns.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(109, 38);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Columns";
            this.label3.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.label3.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // txtRows
            // 
            this.txtRows.Location = new System.Drawing.Point(54, 35);
            this.txtRows.Name = "txtRows";
            this.txtRows.ReadOnly = true;
            this.txtRows.Size = new System.Drawing.Size(49, 20);
            this.txtRows.TabIndex = 3;
            this.txtRows.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.txtRows.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Rows";
            this.label2.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.label2.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // txtTileWidth
            // 
            this.txtTileWidth.Location = new System.Drawing.Point(54, 9);
            this.txtTileWidth.Name = "txtTileWidth";
            this.txtTileWidth.ReadOnly = true;
            this.txtTileWidth.Size = new System.Drawing.Size(49, 20);
            this.txtTileWidth.TabIndex = 1;
            this.txtTileWidth.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.txtTileWidth.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Tile size";
            this.label1.MouseLeave += new System.EventHandler(this.pnInformation_MouseLeave);
            this.label1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnInformation_MouseMove);
            // 
            // pnButton
            // 
            this.pnButton.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnButton.Controls.Add(this.ptbRemoveItem);
            this.pnButton.Controls.Add(this.ptbAddItem);
            this.pnButton.Controls.Add(this.btnExit);
            this.pnButton.Controls.Add(this.btnOpenMap);
            this.pnButton.Controls.Add(this.btnSaveMap);
            this.pnButton.Controls.Add(this.btnNewMap);
            this.pnButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnButton.Location = new System.Drawing.Point(0, 0);
            this.pnButton.Name = "pnButton";
            this.pnButton.Size = new System.Drawing.Size(370, 64);
            this.pnButton.TabIndex = 0;
            this.pnButton.MouseLeave += new System.EventHandler(this.pnButton_MouseLeave);
            this.pnButton.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnButton_MouseMove);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(84, 32);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 23);
            this.btnExit.TabIndex = 3;
            this.btnExit.Text = "Close";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            this.btnExit.MouseLeave += new System.EventHandler(this.btnNewMap_MouseLeave);
            this.btnExit.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btnNewMap_MouseMove);
            // 
            // btnOpenMap
            // 
            this.btnOpenMap.Location = new System.Drawing.Point(3, 32);
            this.btnOpenMap.Name = "btnOpenMap";
            this.btnOpenMap.Size = new System.Drawing.Size(75, 23);
            this.btnOpenMap.TabIndex = 2;
            this.btnOpenMap.Text = "Open";
            this.btnOpenMap.UseVisualStyleBackColor = true;
            this.btnOpenMap.Click += new System.EventHandler(this.btnOpenMap_Click);
            this.btnOpenMap.MouseLeave += new System.EventHandler(this.btnNewMap_MouseLeave);
            this.btnOpenMap.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btnNewMap_MouseMove);
            // 
            // btnSaveMap
            // 
            this.btnSaveMap.Location = new System.Drawing.Point(84, 3);
            this.btnSaveMap.Name = "btnSaveMap";
            this.btnSaveMap.Size = new System.Drawing.Size(75, 23);
            this.btnSaveMap.TabIndex = 1;
            this.btnSaveMap.Text = "Save";
            this.btnSaveMap.UseVisualStyleBackColor = true;
            this.btnSaveMap.Click += new System.EventHandler(this.btnSaveMap_Click);
            this.btnSaveMap.MouseLeave += new System.EventHandler(this.btnNewMap_MouseLeave);
            this.btnSaveMap.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btnNewMap_MouseMove);
            // 
            // btnNewMap
            // 
            this.btnNewMap.Location = new System.Drawing.Point(3, 3);
            this.btnNewMap.Name = "btnNewMap";
            this.btnNewMap.Size = new System.Drawing.Size(75, 23);
            this.btnNewMap.TabIndex = 0;
            this.btnNewMap.Text = "New";
            this.btnNewMap.UseVisualStyleBackColor = true;
            this.btnNewMap.Click += new System.EventHandler(this.btnNewMap_Click);
            this.btnNewMap.MouseLeave += new System.EventHandler(this.btnNewMap_MouseLeave);
            this.btnNewMap.MouseMove += new System.Windows.Forms.MouseEventHandler(this.btnNewMap_MouseMove);
            // 
            // panel2
            // 
            this.panel2.AutoScroll = true;
            this.panel2.Controls.Add(this.pnMapDraw);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(370, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(514, 412);
            this.panel2.TabIndex = 2;
            // 
            // pnMapDraw
            // 
            this.pnMapDraw.AutoScroll = true;
            this.pnMapDraw.AutoScrollMargin = new System.Drawing.Size(10, 10);
            this.pnMapDraw.Location = new System.Drawing.Point(17, 12);
            this.pnMapDraw.Name = "pnMapDraw";
            this.pnMapDraw.Size = new System.Drawing.Size(485, 388);
            this.pnMapDraw.TabIndex = 1;
            this.pnMapDraw.Paint += new System.Windows.Forms.PaintEventHandler(this.pnMapDraw_Paint);
            this.pnMapDraw.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pnMapDraw_MouseClick);
            this.pnMapDraw.MouseLeave += new System.EventHandler(this.pnMapDraw_MouseLeave);
            this.pnMapDraw.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pnMapDraw_MouseMove);
            // 
            // imageListView1
            // 
            this.imageListView1.CurrentIndex = 0;
            this.imageListView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imageListView1.Location = new System.Drawing.Point(0, 0);
            this.imageListView1.Name = "imageListView1";
            this.imageListView1.SelectedImageName = null;
            this.imageListView1.Size = new System.Drawing.Size(370, 282);
            this.imageListView1.TabIndex = 0;
            this.imageListView1.ImageIndexChange += new System.EventHandler(this.imageListView1_ImageIndexChange);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(884, 412);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "frmMain";
            this.Text = "Map Editor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMainForm_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panel1.ResumeLayout(false);
            this.pnItem.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.ptbRemoveItem)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ptbAddItem)).EndInit();
            this.pnInformation.ResumeLayout(false);
            this.pnInformation.PerformLayout();
            this.pnButton.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private MapEditor.UserControlDesign.MyPanel pnMapDraw;
        private System.Windows.Forms.Panel pnItem;
        private System.Windows.Forms.Panel pnInformation;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtTileHeight;
        private System.Windows.Forms.TextBox txtColumns;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtRows;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtTileWidth;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel pnButton;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Button btnOpenMap;
        private System.Windows.Forms.Button btnSaveMap;
        private System.Windows.Forms.Button btnNewMap;
        private System.Windows.Forms.Panel panel2;
        private MapEditor.UserControlDesign.ImageListView imageListView1;
        private System.Windows.Forms.PictureBox ptbRemoveItem;
        private System.Windows.Forms.PictureBox ptbAddItem;
    }
}