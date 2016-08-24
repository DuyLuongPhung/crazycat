using MapEditor.UserControlDesign;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor.UtilsForm
{
    public partial class AddNewItem : Form
    {
        public AddNewItem()
        {
            InitializeComponent();
        }
        private bool _isLoadImage;
        private bool _isAddItem;

        public bool IsAddItem
        {
            get { return _isAddItem; }
            set { _isAddItem = value; }
        }

        private string _imgPath;

        public string ImgPath
        {
            get { return _imgPath; }
            set { _imgPath = value; }
        }
        private Image _image;

        public Image Image
        {
            get { return _image; }
            set { _image = value; }
        }
        private bool _isMovable;

        public bool IsMovable
        {
            get { return _isMovable; }
            set { _isMovable = value; }
        }

        private int _countSprite;

        public int CountSprite
        {
            get { return _countSprite; }
            set { _countSprite = value; }
        }

        private int _spritePerRow;

        public int SpritePerRow
        {
            get { return _spritePerRow; }
            set { _spritePerRow = value; }
        }

        private int _tileWidth;

        public int TileWidth
        {
            get { return _tileWidth; }
            set { _tileWidth = value; }
        }
        private int _tileHeight;

        public int TileHeight
        {
            get { return _tileHeight; }
            set { _tileHeight = value; }
        }

        private Image _showImage;

        public Image ShowImage
        {
            get { return _showImage; }
            set { _showImage = value; }
        }

        private List<ComboboxItem> _allTypeStaticItem;
        private List<ComboboxItem> _allTypeMovableItem;

        private int _itemTypeId;

        public int ItemTypeId
        {
            get { return _itemTypeId; }
            set { _itemTypeId = value; }
        }


        private void txtBackground_Validated(object sender, EventArgs e)
        {
            string path = txtBackground.Text;
            if (File.Exists(path) && (path.EndsWith(".png")
                || path.EndsWith(".jpg") || path.EndsWith(".jpeg")
                || path.EndsWith(".bmp")))
            {
                FileStream streamImg = new FileStream(path, FileMode.Open);
                Bitmap bm = new Bitmap(Image.FromStream(streamImg));
                streamImg.Flush();
                streamImg.Close();
                pictureBox1.Size = new Size(bm.Width, bm.Height);
                pictureBox1.Image = bm;
                pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
                _isLoadImage = true;
                _image = bm;
                _imgPath = path;

                if(!_isMovable)
                {
                    _tileWidth = _image.Width;
                    _tileHeight = _image.Height;
                    txtTileWidth.Text = _tileWidth+"";
                    txtTileHeight.Text = _tileHeight+"";
                    _spritePerRow = -1;
                    _countSprite = -1;
                }

            }
            else
            {
                pictureBox1.Image = null;
                pictureBox1.Size = new Size(10, 10);
                _isLoadImage = false;
            }
        }

        private void btnBrowser_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "Select background image to item";
            ofd.Multiselect = false;
            ofd.Filter = "Image file |*.png;*.jpg;*.jpeg;*.bmp";
            if (DialogResult.OK == ofd.ShowDialog())
            {
                txtBackground.Text = ofd.FileName;
                txtBackground_Validated(sender, e);
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                if (!_isLoadImage)
                    throw new Exception("You have must select image before!");
                if (rdMovableObject.Checked)
                    _isMovable = true;
                else
                    _isMovable = false;
                _isAddItem = true;

                Bitmap image = new Bitmap(_image);
                Rectangle rect = new Rectangle(0,0,_tileWidth,_tileHeight);
                Bitmap img3 = image.Clone(rect, image.PixelFormat);
                _showImage = img3;
                _itemTypeId = (cbbTypeItem.SelectedItem as ComboboxItem).Id;
                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void AddNewItem_Load(object sender, EventArgs e)
        {
            _allTypeStaticItem = new List<ComboboxItem>();
            _allTypeMovableItem = new List<ComboboxItem>();

            _allTypeStaticItem.Add(new ComboboxItem(1, "1. Tường, đất - object tĩnh"));
            _allTypeStaticItem.Add(new ComboboxItem(2, "2. Hộp gỗ - bình thường"));
            _allTypeStaticItem.Add(new ComboboxItem(3, "3. Hộp gỗ - vàng"));
            _allTypeStaticItem.Add(new ComboboxItem(4, "4. Hộp gỗ - mạng chơi"));
            _allTypeStaticItem.Add(new ComboboxItem(5, "5. Hộp gỗ - thời gian chơi"));
            _allTypeStaticItem.Add(new ComboboxItem(6, "6. Hộp gỗ - tăng vận tốc"));
            _allTypeStaticItem.Add(new ComboboxItem(7, "7. Hộp gỗ - super bomb"));
            _allTypeStaticItem.Add(new ComboboxItem(12, "12. Hộp quà  - chìa khóa qua màn"));
            _allTypeStaticItem.Add(new ComboboxItem(14, "14. Của qua màn"));
            _allTypeStaticItem.Add(new ComboboxItem(25, "25. Con ma - ghost"));

            rdStaticObject.Checked = true;
            _isLoadImage = false;
            _isAddItem = false;
        }

        private void rdStaticObject_CheckedChanged(object sender, EventArgs e)
        {
            if (rdMovableObject.Checked)
            {
                txtSpritePerRow.Text = "1";
                txtCountSprite.Text = "1";
                txtCountSprite.Enabled = true;
                txtSpritePerRow.Enabled = true;
                cbbTypeItem.DataSource = _allTypeMovableItem;
                
            }
            else
            {
                txtSpritePerRow.Text = "";
                txtCountSprite.Text = "";
                txtCountSprite.Enabled = false;
                txtSpritePerRow.Enabled = false;
                _isMovable = false;
                cbbTypeItem.DataSource = _allTypeStaticItem;
            }
        }

        private void txtCountSprite_Validated(object sender, EventArgs e)
        {
            int countSprite;
            int.TryParse(txtCountSprite.Text, out countSprite);
            if(countSprite < 1)
            {
                MessageBox.Show("Count sprite least as 1");
                txtCountSprite.Focus();
                return;
            }

            int spritePerRow;
            int.TryParse(txtSpritePerRow.Text, out spritePerRow);
            if (spritePerRow < 1)
            {
                MessageBox.Show("Sprite per row least as 1");
                spritePerRow = 1;
            }

            if (spritePerRow > countSprite)
            {
                MessageBox.Show("Count sprite always greater or equal than sprite per row!");
                txtCountSprite.Focus();
                return;
            }
            if (!_isLoadImage)
                return;

            int row = (countSprite % spritePerRow == 0) ? (countSprite / spritePerRow) : (countSprite / spritePerRow + 1);
            int tileWidth = _image.Width / spritePerRow;
            int tileHeight = _image.Height / row;

            txtTileHeight.Text = tileHeight + "";
            txtTileWidth.Text = tileWidth + "";
            txtCountSprite.Text = countSprite + "";
            txtSpritePerRow.Text = spritePerRow + "";
            _countSprite = countSprite;
            _spritePerRow = spritePerRow;
            _tileWidth = tileWidth;
            _tileHeight = tileHeight;
        }

        private void txtSpritePerRow_Validated(object sender, EventArgs e)
        {
            int countSprite;
            int.TryParse(txtCountSprite.Text, out countSprite);
            if (countSprite < 1)
            {
                MessageBox.Show("Count sprite least as 1");
                countSprite = 1;
            }

            int spritePerRow;
            int.TryParse(txtSpritePerRow.Text, out spritePerRow);
            if (spritePerRow < 1)
            {
                MessageBox.Show("Sprite per row least as 1");
                txtSpritePerRow.Focus();
                return;
            }

            if (spritePerRow > countSprite)
            {
                MessageBox.Show("Sprite per row cannot greater Count sprite!");
                txtSpritePerRow.Focus();
                return;
            }

            if (!_isLoadImage)
                return;

            int row = (countSprite % spritePerRow == 0) ? (countSprite / spritePerRow) : (countSprite / spritePerRow + 1);
            int tileWidth = _image.Width / spritePerRow;
            int tileHeight = _image.Height / row;

            txtTileHeight.Text = tileHeight + "";
            txtTileWidth.Text = tileWidth + "";
            txtCountSprite.Text = countSprite + "";
            txtSpritePerRow.Text = spritePerRow + "";
            _countSprite = countSprite;
            _spritePerRow = spritePerRow;
            _tileWidth = tileWidth;
            _tileHeight = tileHeight;

        }

        private void txtCountSprite_GotFocus(object sender, EventArgs e)
        {
            if (!_isLoadImage)
            {
                txtBackground.Focus();
                MessageBox.Show("You have must select image before!");
                return;
            }
        }

        private void txtSpritePerRow_GotFocus(object sender, EventArgs e)
        {
            if (!_isLoadImage)
            {
                txtBackground.Focus();
                MessageBox.Show("You have must select image before!");
                return;
            }
        }

        private void txtCountSprite_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!((e.KeyChar == 8) || char.IsDigit(e.KeyChar)))
            {
                e.Handled = true;
            }
        }
    }
}
