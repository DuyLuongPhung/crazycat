using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MapEditor.UtilsForm
{
    public partial class AddNewMap : Form
    {
        public AddNewMap()
        {
            InitializeComponent();
        }
        private bool _IsLoadImage;

        #region Logic

        private void txtRows_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!((e.KeyChar == 8) || char.IsDigit(e.KeyChar)))
            {
                e.Handled = true;
            }
        }

        private void txtColumns_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!((e.KeyChar == 8) || char.IsDigit(e.KeyChar)))
            {
                e.Handled = true;
            }
        }

        private void txtColumns_Validated(object sender, EventArgs e)
        {
            string r = txtRows.Text;
            string c = txtColumns.Text;
            if (c.Length < 1)
                return;
            if (r.Length < 1)
                return;
            int row, col;
            int.TryParse(c, out col);
            int.TryParse(r, out row);

            txtColumns.Text = col + "";
            txtRows.Text = row + "";
            txtTiles.Text = (row * col) + "";
        }

        private void txtRows_Validated(object sender, EventArgs e)
        {
            string r = txtRows.Text;
            string c = txtColumns.Text;
            if (c.Length < 1)
                return;
            if (r.Length < 1)
                return;
            int row, col;
            int.TryParse(c, out col);
            int.TryParse(r, out row);

            txtColumns.Text = col + "";
            txtRows.Text = row + "";
            txtTiles.Text = (row * col) + "";
        }

        private void txtTileWidth_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!_IsLoadImage)
            {
                MessageBox.Show("You have must select map image before!");
                e.Handled = true;
            }
            if (!((e.KeyChar == 8) || char.IsDigit(e.KeyChar)))
            {
                e.Handled = true;
            }
        }

        private void txtTileHeight_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!_IsLoadImage)
            {
                MessageBox.Show("You have must select map image before!");
                e.Handled = true;
            }
            if (!((e.KeyChar == 8) || char.IsDigit(e.KeyChar)))
            {
                e.Handled = true;
            }
        }

        private void txtTileWidth_Validated(object sender, EventArgs e)
        {
            string w = txtTileWidth.Text;
            string h = txtTileHeight.Text;
            if (w.Length < 1)
                return;
            if (h.Length < 1)
                return;
            int width, height;
            int.TryParse(w, out width);
            int.TryParse(h, out height);

            txtTileWidth.Text = width + "";
            txtTileHeight.Text = height + "";
            txtMapSize.Text = (pictureBox1.Width) + "-" + (pictureBox1.Height);

            int row, col;
            row = pictureBox1.Height / height;
            col = pictureBox1.Width / width;
            txtRows.Text = row + "";
            txtColumns.Text = col + "";
            txtTiles.Text = (row * col) + "";

        }

        private void txtTileHeight_Validated(object sender, EventArgs e)
        {
            string w = txtTileWidth.Text;
            string h = txtTileHeight.Text;
            if (w.Length < 1)
                return;
            if (h.Length < 1)
                return;
            int width, height;
            int.TryParse(w, out width);
            int.TryParse(h, out height);

            txtTileWidth.Text = width + "";
            txtTileHeight.Text = height + "";
            txtMapSize.Text = (pictureBox1.Width) + "-" + (pictureBox1.Height);

            int row, col;
            row = pictureBox1.Height / height;
            col = pictureBox1.Width / width;
            txtRows.Text = row + "";
            txtColumns.Text = col + "";
            txtTiles.Text = (row * col) + "";
        }

        private void txtBackground_Validated(object sender, EventArgs e)
        {
            string path = txtBackground.Text;
            if (File.Exists(path) && (path.EndsWith(".png")
                || path.EndsWith(".jpg") || path.EndsWith(".jpeg")
                || path.EndsWith(".bmp")))
            {
                Image im = Image.FromFile(path);
                pictureBox1.Size = new Size(im.Width, im.Height);
                pictureBox1.Image = im;
                pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
                _IsLoadImage = true;
            }
            else
            {
                pictureBox1.Image = null;
                pictureBox1.Size = new Size(10, 10);
                _IsLoadImage = false;
            }
        }

        private void txtScreenWidth_Validated(object sender, EventArgs e)
        {
            int w;
            int.TryParse(txtScreenWidth.Text.Trim(), out w);
            txtScreenWidth.Text = w + "";
        }

        private void txtScreenHeight_Validated(object sender, EventArgs e)
        {
            int h;
            int.TryParse(txtScreenHeight.Text.Trim(), out h);
            txtScreenHeight.Text = h + "";
        }

        #endregion

        #region Button

        private void btnBrowser_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "Select background image to map";
            ofd.Multiselect = false;
            ofd.Filter = "Image file |*.png;*.jpg;*.jpeg;*.bmp";
            if (DialogResult.OK == ofd.ShowDialog())
            {
                txtBackground.Text = ofd.FileName;
                txtBackground_Validated(sender, e);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            frmMain._createdSuccessed = false;
            this.Close();
        }

        private void btnCreate_Click(object sender, EventArgs e)
        {
            try
            {
                if (!_IsLoadImage)
                    throw new Exception("You have must select map image before!");
                string strRow = txtRows.Text;
                string strColumn = txtColumns.Text;
                string strTileWidth = txtTileWidth.Text;
                string strTileHeight = txtTileHeight.Text;
                string strScreenWidth = txtScreenWidth.Text;
                string strScreenHeight = txtScreenHeight.Text;

                int row, column,tileWidth, tileHeight,screenWidth, screenHeight;
                int.TryParse(strColumn, out column);
                int.TryParse(strRow, out row);
                int.TryParse(strTileWidth, out tileWidth);
                int.TryParse(strTileHeight, out tileHeight);
                int.TryParse(strScreenWidth, out screenWidth);
                int.TryParse(strScreenHeight, out screenHeight);

                if (row < 1)
                    throw new Exception("Rows is smaller 1");
                if (column < 1)
                    throw new Exception("Colomuns is smaller 1");
                if (tileWidth < 1)
                    throw new Exception("Tile width is smaller 1");
                if (tileHeight < 1)
                    throw new Exception("Tile height is smaller 1");
                if (screenWidth < 1)
                    throw new Exception("Screen's width is smaller 1");
                if (screenHeight < 1)
                    throw new Exception("Screen 's height is smaller 1");

                frmMain._columns = column;
                frmMain._rows = row;
                frmMain._tileHeight = tileHeight;
                frmMain._tileWidth = tileWidth;
                frmMain._screenWidth = screenWidth;
                frmMain._screenHeight = screenHeight;
                frmMain._background = Image.FromFile(txtBackground.Text);
                frmMain._createdSuccessed = true;
                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        #endregion

        private void AddNewMap_Load(object sender, EventArgs e)
        {
            _IsLoadImage = false;
        }

       

    }
}
