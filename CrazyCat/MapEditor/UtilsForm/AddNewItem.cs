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

            _allTypeStaticItem.Add(new ComboboxItem(1, "1. Stone: Đất - đá(phần dưới đáy)"));
            _allTypeStaticItem.Add(new ComboboxItem(2, "2. Chimney_T01: ống khói không chui vào được"));
            _allTypeStaticItem.Add(new ComboboxItem(3, "3. Chimney_T02: ống khói chui vào được"));
            _allTypeStaticItem.Add(new ComboboxItem(4, "4. Wall: những khối tường dựng đứng"));
            _allTypeStaticItem.Add(new ComboboxItem(5, "5. Wood: gỗ"));

            _allTypeMovableItem.Add(new ComboboxItem(6, "6. Coin: đồng tiền"));
            _allTypeMovableItem.Add(new ComboboxItem(7, "7. 1 up MushRoom: nấm xanh thêm 1 mạng"));
            _allTypeMovableItem.Add(new ComboboxItem(8, "8. Brick: gạch"));
            _allTypeMovableItem.Add(new ComboboxItem(9, "9. Switch Block: item để dổi các ô gạch ra tiền"));
            _allTypeMovableItem.Add(new ComboboxItem(10, "10. Cards: item để qua màn"));
            _allTypeMovableItem.Add(new ComboboxItem(11, "11. QuestionBlock: hộp có dấu hỏi để ăn item và sau khi ăn item"));
            _allTypeMovableItem.Add(new ComboboxItem(12, "12. Goomba: con goomba bình thường"));
            _allTypeMovableItem.Add(new ComboboxItem(13, "13. Vernus fire trap green: con quái hoa bắn đạn"));
            _allTypeMovableItem.Add(new ComboboxItem(14, "14. Koopa troopa green: con rùa không nhảy đc màu xanh"));
            _allTypeMovableItem.Add(new ComboboxItem(15, "15. Koopa troopa red: con rùa ko nhảy đc màu đỏ"));
            _allTypeMovableItem.Add(new ComboboxItem(16, "16. Koopa paratroopa green: con rùa nhảy đc màu xanh"));
            _allTypeMovableItem.Add(new ComboboxItem(17, "17. Para - goomba : con goomba nhảy đc"));
            _allTypeMovableItem.Add(new ComboboxItem(18, "18. Piranha plant: con quái hoa ăn thịt ko bắn đạn"));
            _allTypeMovableItem.Add(new ComboboxItem(19, "19. Leaf- Mushroom: có thể là lá hoặc nấm"));
            _allTypeMovableItem.Add(new ComboboxItem(20, "20. vernus fire trap red: con quái hoa bắn đạn màu đỏ"));

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
