using MapEditor.QuadTree;
using MapEditor.UserControlDesign;
using MapEditor.UtilsForm;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace MapEditor
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }
        List<ItemInfo> _listSourceItem;
        Bitmap cursorIcon;
        public static int _rows;
        public static int _columns;
        public static Image _background;
        public static int _tileWidth;
        public static int _tileHeight;
        public static int _screenWidth;
        public static int _screenHeight;
        public static bool _createdSuccessed;

        private int _margin;
        private bool _remove;
        private List<ItemObject> _allItemAdded;
        private int _index;
        private int _imageSaveInRow;
        private int _itemIndex;

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                DefaultValue();
                ToolTip addTooltip = new ToolTip();
                addTooltip.SetToolTip(ptbAddItem, "Add a item to use");
                addTooltip.SetToolTip(ptbRemoveItem, "Remove object from map");
                addTooltip.SetToolTip(btnNewMap, "Create new map");
                addTooltip.SetToolTip(btnSaveMap, "Save current map");
                addTooltip.SetToolTip(btnOpenMap, "Open exist map");
                addTooltip.SetToolTip(btnExit, "Close application");
                txtColumns.Text = _columns + "";
                txtRows.Text = _rows + "";
                txtTileHeight.Text = _tileHeight + "";
                txtTileWidth.Text = _tileWidth + "";
                pnMapDraw.BackColor = Color.White;

            }
            catch (IOException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void imageListView1_ImageIndexChange(object sender, EventArgs e)
        {
            _index = imageListView1.CurrentIndex;
            _remove = false;
            Bitmap bm = (Bitmap)_listSourceItem[_index].ShowImage;
            cursorIcon = bm;
            Graphics.FromImage(cursorIcon);
            IntPtr ptr = cursorIcon.GetHicon();
            Cursor c = new Cursor(ptr);
            this.Cursor = c;
        }

        private void ptbRemoveItem_Click(object sender, EventArgs e)
        {
            _remove = true;
            FileStream streamImg = new FileStream("Source\\Remove.png", FileMode.Open);
            Image bm = Image.FromStream(streamImg);
            streamImg.Flush();
            streamImg.Close();
            cursorIcon = new Bitmap(bm);
            Graphics.FromImage(cursorIcon);
            IntPtr ptr = cursorIcon.GetHicon();
            Cursor c = new Cursor(ptr);
            this.Cursor = c;
        }

        private void ptbAddItem_Click(object sender, EventArgs e)
        {
            try
            {
                AddNewItem frm = new AddNewItem();
                frm.ShowDialog();
                if (!frm.IsAddItem)
                    return;
                _listSourceItem.Add(new ItemInfo(_itemIndex++, frm.ItemTypeId,frm.ShowImage,frm.ImgPath,frm.IsMovable,frm.CountSprite,
                    frm.SpritePerRow,frm.TileWidth,frm.TileHeight));
                imageListView1.AddImageToList(frm.ShowImage);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void frmMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (_createdSuccessed)
                if (DialogResult.Yes != MessageBox.Show("If close application, current map data was lost. Are you exit?", "warning",
                    MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question))
                {
                    e.Cancel = true;
                }
        }

        private void DefaultValue()
        {
            _listSourceItem = new List<ItemInfo>();
            cursorIcon = null;
            _rows = 0;
            _columns = 0;
            _background = null;
            _tileWidth = 0;
            _tileHeight = 0;
            _screenHeight = 0;
            _screenWidth = 0;
            _createdSuccessed = false;
            _margin = 0;
            _remove = false;
            _allItemAdded = new List<ItemObject>();
            _index = -1;
            imageListView1.ClearItem();
            imageListView1.ClearSection();
            pnMapDraw.BackgroundImage = null;
            _imageSaveInRow = 10;
            _itemIndex = 0;
        }

        #region SetMouse

        private void pnButton_MouseLeave(object sender, EventArgs e)
        {
            if (cursorIcon == null)
            {
                return;
            }
            Graphics.FromImage(cursorIcon);
            IntPtr ptr = cursorIcon.GetHicon();
            Cursor c = new Cursor(ptr);
            this.Cursor = c;
        }

        private void pnButton_MouseMove(object sender, MouseEventArgs e)
        {
            this.Cursor = Cursors.Arrow;
        }

        private void pnInformation_MouseLeave(object sender, EventArgs e)
        {
            if (cursorIcon == null)
            {
                return;
            }
            Graphics.FromImage(cursorIcon);
            IntPtr ptr = cursorIcon.GetHicon();
            Cursor c = new Cursor(ptr);
            this.Cursor = c;
        }

        private void pnInformation_MouseMove(object sender, MouseEventArgs e)
        {
            this.Cursor = Cursors.Arrow;
        }

        private void btnNewMap_MouseLeave(object sender, EventArgs e)
        {
            if (cursorIcon == null)
            {
                return;
            }
            Graphics.FromImage(cursorIcon);
            IntPtr ptr = cursorIcon.GetHicon();
            Cursor c = new Cursor(ptr);
            this.Cursor = c;
        }

        private void btnNewMap_MouseMove(object sender, MouseEventArgs e)
        {
            this.Cursor = Cursors.Hand;
        }

        private void pnMapDraw_MouseLeave(object sender, EventArgs e)
        {
            this.Cursor = Cursors.Arrow;
        }
        private void pnMapDraw_MouseMove(object sender, MouseEventArgs e)
        {
            if (cursorIcon == null)
            {
                return;
            }
            //Graphics.FromImage(cursorIcon);
            //IntPtr ptr = cursorIcon.GetHicon();
            //Cursor c = new Cursor(ptr);
            //this.Cursor = c;
        }

        #endregion

        #region Button

        private void btnNewMap_Click(object sender, EventArgs e)
        {
            if (_createdSuccessed)
                if (DialogResult.Yes != MessageBox.Show("If create new map, current map data was lost. Are you exit?", "warning",
                    MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question))
                {
                    return;
                }
            try
            {
                AddNewMap frm = new AddNewMap();
                frm.ShowDialog();
                txtColumns.Text = _columns + "";
                txtRows.Text = _rows + "";
                txtTileHeight.Text = _tileHeight + "";
                txtTileWidth.Text = _tileWidth + "";
                _index = -1;
                cursorIcon = null;
                _remove = false;
                imageListView1.ClearSection();
                _allItemAdded = new List<ItemObject>();
                this.Cursor = Cursors.Arrow;
                if (_createdSuccessed)
                {
                    if (_background != null)
                        pnMapDraw.BackgroundImage = _background;
                    else
                        pnMapDraw.BackgroundImage = null;
                    pnMapDraw.Invalidate();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnSaveMap_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            try
            {
                this.Cursor = Cursors.WaitCursor;
                if (!_createdSuccessed)
                    throw new Exception("You must create map before save.");
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Title = "Select folder save this map";
                sfd.Filter = "Map file (*.svmap) |*.svmap";
                if (DialogResult.OK == sfd.ShowDialog())
                {
                    string folder = Path.GetDirectoryName(sfd.FileName);
                    string fileName = Path.GetFileNameWithoutExtension(sfd.FileName);
                    if (saveMapDraft(folder, fileName))
                        MessageBox.Show("Saved, Success!");
                    else
                        MessageBox.Show("Dont save, failed!");
                }

            }
            catch (Exception ex)
            {
                this.Cursor = Cursors.Default;
                MessageBox.Show(ex.Message);
            }
            this.Cursor = Cursors.Default;
                }
        private void btnExport_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            try
            {
                this.Cursor = Cursors.WaitCursor;
                if (!_createdSuccessed)
                    throw new Exception("You must create map before save.");
                SaveFileDialog sfd = new SaveFileDialog();
                sfd.Title = "Select folder save this map";
                sfd.Filter = "Map file (*.info, *.img, *.map) |*.info;*.img; *.map";
                if (DialogResult.OK == sfd.ShowDialog())
                {
                    string folder = Path.GetDirectoryName(sfd.FileName);
                    string file = Path.GetFileNameWithoutExtension(sfd.FileName);
                    save = true;
                    pnMapDraw.Invalidate();

                    using (Bitmap bitmap = new Bitmap(pnMapDraw.ClientSize.Width,
                                  pnMapDraw.ClientSize.Height))
                    {
                        pnMapDraw.DrawToBitmap(bitmap, pnMapDraw.ClientRectangle);
                        bitmap.Save(Path.Combine(folder,"fullImage.png"), System.Drawing.Imaging.ImageFormat.Png);
                    }

                    save = false;
                    ExportInformation(folder, file);
                    ExportMapFile(folder, file);
                    MessageBox.Show("Saved, Success!");
                }

            }
            catch (Exception ex)
            {
                this.Cursor = Cursors.Default;
                MessageBox.Show(ex.Message);
            }
            this.Cursor = Cursors.Default;
        }

        private void btnOpenMap_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            try
            {
                this.Cursor = Cursors.WaitCursor;
                if (DialogResult.Yes != MessageBox.Show("The current map will be lost. Are you continue?", "warning",
                MessageBoxButtons.YesNo, MessageBoxIcon.Question))
                {
                    this.Cursor = Cursors.Default;
                    return;
                }

                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Title = "Open folder exist map";
                ofd.Filter = "Map file (*.svmap) |*.svmap";
                if (DialogResult.OK == ofd.ShowDialog())
                {
                    string folder = Path.GetDirectoryName(ofd.FileName);
                    string file = Path.GetFileNameWithoutExtension(ofd.FileName);
                    OpenMap(folder, file);
                }
            }
            catch (Exception ex)
            {
                this.Cursor = Cursors.Default;
                MessageBox.Show(ex.Message);
            }
            this.Cursor = Cursors.Default;

        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        #endregion

        #region Draw

        bool save = false;

        private void pnMapDraw_Paint(object sender, PaintEventArgs e)
        {
            var p = sender as Panel;
            var g = e.Graphics;
            if(!save)
            DrawGridLine(g, p);
            DrawAllItem(g);
        }

        private void pnMapDraw_MouseClick(object sender, MouseEventArgs e)
        {
            int x = e.X;
            int y = e.Y;
            if (!_remove)
            {
                if (_listSourceItem.Count < 1 || _index < 0)
                    return;
                x -= _margin;
                int col = x / (_tileWidth);
                y -= _margin;
                int row = y / (_tileHeight);
                x = _margin + col * (_tileWidth);
                y = _margin + row * (_tileHeight);

                ItemObject item = new ItemObject(_listSourceItem[_index].Index, _listSourceItem[_index].TypeID, x, y, _listSourceItem[_index].ItemWidth, _listSourceItem[_index].ItemHeight);
                
                int search = _allItemAdded.FindIndex(it => (it.ItemRectangle.X == item.ItemRectangle.X && it.ItemRectangle.Y == item.ItemRectangle.Y
                    && it.ItemRectangle.Width == item.ItemRectangle.Width && item.ItemRectangle.Height == item.ItemRectangle.Height));
                if (search >= 0)
                    _allItemAdded.RemoveAt(search);
                _allItemAdded.Add(item);
            }
            else
            {
                for (int i = (_allItemAdded.Count - 1); i >= 0; i--)
                {
                    if ((x >= _allItemAdded[i].ItemRectangle.X && x < _allItemAdded[i].ItemRectangle.X + _allItemAdded[i].ItemRectangle.Width)
                        && (y >= _allItemAdded[i].ItemRectangle.Y && y < _allItemAdded[i].ItemRectangle.Y + _allItemAdded[i].ItemRectangle.Height))
                    {
                        _allItemAdded.RemoveAt(i);
                        break;
                    }
                }
            }
            pnMapDraw.Invalidate();
        }

        private void DrawGridLine(Graphics g, Panel p)
        {
            int width = _columns * _tileWidth + 1;
            int height = _rows * _tileHeight + 1;
            Pen pen = new Pen(Color.Red, 1);
            p.Size = new System.Drawing.Size(_margin * 2 + width, _margin * 2 + height);

            // draw row
            for (int i = 0; i <= _rows; i++)
            {
                int x1 = _margin;
                int x2 = x1 + width;
                int y1 = _margin + i * _tileHeight;
                int y2 = y1;

                g.DrawLine(pen, x1, y1, x2, y2);
            }

            // Draw col
            for (int i = 0; i <= _columns; i++)
            {
                int x1 = _margin + i * _tileWidth;
                int x2 = x1;
                int y1 = _margin;
                int y2 = y1 + height;
                g.DrawLine(pen, x1, y1, x2, y2);
            }
        }

        private void DrawAllItem(Graphics g)
        {
            foreach (ItemObject item in _allItemAdded)
            {
                DrawItem(g, item.ItemInfoIndex, item.ItemRectangle.X, item.ItemRectangle.Y);
            }
        }

        private void DrawItem(Graphics g, int itemInfoIndex, int x, int y)
        {
            foreach (ItemInfo item in _listSourceItem)
            {
                if (item.Index == itemInfoIndex)
                {
                    Bitmap bm = (Bitmap)item.ShowImage;
                    g.DrawImage(bm, x, y, bm.Width, bm.Height);
                    return;
                }
            }

        }

        #endregion

        #region Export

        private bool ExportInformation(string pathSave, string fileName)
        {
            try
            {
                string filePathInfo = Path.Combine(pathSave, fileName + ".info");
                if (!File.Exists(filePathInfo))
                    File.Create(filePathInfo).Dispose();

                StreamWriter strWriter = new StreamWriter(filePathInfo, true);
                strWriter.WriteLine();

                // basic information
                strWriter.WriteLine(
                    (_columns * _tileWidth) + " "       // map width
                    + (_rows * _tileHeight) + " "       // map height
                    + (_rows) + " "                     // rows
                    + (_columns) + " "                  // columns
                    + (_tileWidth) + " "                // tile width
                    + (_tileHeight) + " "               // tile height
                    + (_screenWidth) +" "               // screen width
                    + (_screenHeight) + " "             // screen height
                    );
                strWriter.WriteLine();

                List<int> allSaveItemedId = new List<int>();

                // item information
                for (int i = 0; i < _listSourceItem.Count; i++)
                {
                    int findIndex = allSaveItemedId.FindIndex(myId => (myId == _listSourceItem[i].Index));
                    if (findIndex >= 0)
                        continue;
                    allSaveItemedId.Add(_listSourceItem[i].Index);
                    FileStream streamImg = new FileStream(_listSourceItem[i].Path, FileMode.Open);
                    Image img = Image.FromStream(streamImg);
                    streamImg.Flush();
                    streamImg.Close();

                    string itemNameSave = Path.GetFileNameWithoutExtension(_listSourceItem[i].Path);
                    string pathImage = Path.Combine(pathSave, itemNameSave + ".png");
                    //if (_listSourceItem[i].ID > 5)      // các item động
                        img.Save(pathImage, ImageFormat.Png);
                    //else
                       // pathImage = "*";
                    strWriter.WriteLine("" 
                        + _listSourceItem[i].Index + " "               // item index
                        + _listSourceItem[i].TypeID + " "               // item type ID
                        + Path.GetFileName(pathImage) + " "               // item save name
                        + _listSourceItem[i].ItemWidth + " "        // item width
                        + _listSourceItem[i].ItemHeight + " "       // item height
                        + _listSourceItem[i].MoveStatus + " "       // is moveable: 0-none, 1-move
                        + +_listSourceItem[i].CountSprite + " "     // count sprite: if have else < 0
                        + _listSourceItem[i].SpritePerRow + " "     // sprite per row: if have else < 0
                        ); 
                }
                strWriter.WriteLine();

                QuadTree.QuadTreeManager manager = new QuadTree.QuadTreeManager(_screenWidth, _screenHeight);
                manager.SetAllData(_allItemAdded, new Rectangle(0, 0, (_columns * _tileWidth), (_rows * _tileHeight)));
                QuadNode root = manager.Tree.Root;

                // write node
                ExportQuadTreeNode(root, strWriter);
                strWriter.WriteLine();

                // write objects
                ExportQuadTreeObject(root, strWriter);
                strWriter.WriteLine();
                strWriter.Close();
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private bool ExportQuadTreeNode(QuadNode root, StreamWriter strWriter)
        {
            if (root == null)
                return false;

            //write node's information
            strWriter.WriteLine(""
                + root.Id + " "                 // root id
                + root.Partition.X + " "        // position X
                + root.Partition.Y + " "        // position Y
                + root.Partition.Width + " "    // partition width
                + root.Partition.Height + " "   // partition height
                );
            if (root.NodeLT != null)
                ExportQuadTreeNode(root.NodeLT, strWriter);       // save left-top node
            if (root.NodeLB != null)
                ExportQuadTreeNode(root.NodeLB, strWriter);       // save left-bottom node
            if (root.NodeRB != null)
                ExportQuadTreeNode(root.NodeRB, strWriter);       // save right-bottom node
            if (root.NodeRT != null)
                ExportQuadTreeNode(root.NodeRT, strWriter);       // save right-top node
            return true;
        }

        private bool ExportQuadTreeObject(QuadNode root, StreamWriter strWriter)
        {
            if (root == null)
                return false;
            //write object's information
            int mapHeight = _background.Height;

            List<ItemObject> allItem = root.GetAllObjects();
            for (int i = 0; i < allItem.Count; i++)
            {
                strWriter.WriteLine(""
                    + allItem[i].ItemInfoIndex + " "               // item index
                    + root.Id + " "                             // node id 
                    + allItem[i].ItemRectangle.X + " "          // position X
                    + (mapHeight - allItem[i].ItemRectangle.Y) + " "          // position Y
                    );
            }
            if (root.NodeLT != null)
                ExportQuadTreeObject(root.NodeLT, strWriter);     // save objects in left-top node
            if (root.NodeLB != null)
                ExportQuadTreeObject(root.NodeLB, strWriter);     // save objects in left-bottom node
            if (root.NodeRB != null)
                ExportQuadTreeObject(root.NodeRB, strWriter);     // save objects in right-bottom node
            if (root.NodeRT != null)
                ExportQuadTreeObject(root.NodeRT, strWriter);     // save objects in right-top node
            return true;
        }

        public bool ExportMapFile(string pathSave, string fileName)
        {
            try
            {
                string mapPathText = Path.Combine(pathSave, fileName + ".map");
                string mapPathImage = Path.Combine(pathSave, fileName + ".img");
                if (!File.Exists(mapPathText))
                    File.Create(mapPathText).Dispose();
                Bitmap backgroundMap = new Bitmap(_background);
                List<Bitmap> allBitmapRect = ToListSubImage(backgroundMap, _rows, _columns);
                int[] mapIndex = new int[allBitmapRect.Count];
                List<Bitmap> resultBitmap = new List<Bitmap>();
                for (int i = 0; i < mapIndex.Length; i++)
                    mapIndex[i] = -1;
                for (int i = 0; i < mapIndex.Length; i++)
                {
                    if (mapIndex[i] < 0 && allBitmapRect[i] != null)
                    {
                        resultBitmap.Add(allBitmapRect[i]);
                        int index = resultBitmap.Count - 1;
                        mapIndex[i] = index;
                        allBitmapRect[i] = null;
                        for (int j = i + 1; j < mapIndex.Length; j++)
                        {
                            if (mapIndex[j] < 0 && allBitmapRect[j] != null && CompareTwoImage(resultBitmap[index], allBitmapRect[j]))
                            {
                                mapIndex[j] = index;
                                allBitmapRect[j] = null;
                            }
                        }
                    }
                }

                // save text
                StreamWriter strWriter = new StreamWriter(mapPathText, true);
                strWriter.WriteLine();
                int imgHeight = (resultBitmap.Count / _imageSaveInRow + 1) * (resultBitmap[0].Height);
                int imgWidth = _imageSaveInRow * resultBitmap[0].Width;
                using (Bitmap bitmapSave = new Bitmap(imgWidth, imgHeight))
                {
                    using (Graphics g = Graphics.FromImage(bitmapSave))
                    {
                        for (int i = 0; i < resultBitmap.Count; i++)
                        {
                            int x = (i % _imageSaveInRow) * (resultBitmap[0].Width);
                            int y = (i / _imageSaveInRow) * (resultBitmap[0].Height);
                            g.DrawImage(resultBitmap[i], x, y, resultBitmap[i].Width, resultBitmap[i].Height);

                            strWriter.WriteLine(""
                                + i + " "                           // tile id
                                + x + " "                           // position X in saved image
                                + y + " "                           // position Y in saved image
                                );
                        }
                    }
                    bitmapSave.Save(mapPathImage, ImageFormat.Png);
                }
                for (int j = 0; j < mapIndex.Length; j++)
                {
                    if (j % _columns == 0)
                    {
                        strWriter.WriteLine();
                        strWriter.Write(" ");
                    }
                    strWriter.Write(mapIndex[j]+" ");
                }
                strWriter.WriteLine();
                strWriter.WriteLine();
                strWriter.Close();
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private bool CompareTwoImage(Bitmap bmp1, Bitmap bmp2)
        {
            if (bmp1.Size != bmp2.Size)
                return false;

            for (int x = 0; x < bmp1.Width; x++) 
            {
                for (int y = 0; y < bmp1.Height; y++)
                {
                    if (bmp1.GetPixel(x, y) != bmp2.GetPixel(x, y))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public List<Bitmap> ToListSubImage(Bitmap image, int rows, int columns)
        {
            List<Bitmap> ArrBm = new List<Bitmap>();
            int w = image.Width / columns;
            int h = image.Height / rows;

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    int x = w * j;
                    int y = h * i;
                    Rectangle rect = new Rectangle(x, y, w, h);
                    Bitmap img3 = image.Clone(rect, image.PixelFormat);
                    ArrBm.Add(img3);
                }
            }
            return ArrBm;
        }

        #endregion

        #region Save

        private bool saveMapDraft(string pathFolder, string fileName)
        {

            StreamWriter strWriter;
            string filePathInfo = Path.Combine(pathFolder, fileName + ".svmap");
            string filePathBackground = Path.Combine(pathFolder, fileName + ".bgimg");
            if (!File.Exists(filePathInfo))
                File.Create(filePathInfo).Dispose();
            strWriter = new StreamWriter(filePathInfo, true);
            try
            {


                // lưu ảnh back ground
                using (Bitmap bitmap = new Bitmap(_background))
                {
                    bitmap.Save(filePathBackground, System.Drawing.Imaging.ImageFormat.Png);
                }

                if (!Directory.Exists(Path.Combine(pathFolder, "Tiles")))
                {
                    Directory.CreateDirectory(Path.Combine(pathFolder, "Tiles"));
                }

                // lưu thông tin cơ bản của map
                strWriter.WriteLine();
                strWriter.WriteLine(String.Format("{0} {1} {2} {3} {4} {5} {6} {7}",
                    _background.Width, _background.Height, _rows, _columns, _tileWidth, _tileHeight, _screenWidth, _screenHeight));

                // lưu thông tin các item
                strWriter.WriteLine();
                List<int> allSaveItemedId = new List<int>();
                for (int i = 0; i < _listSourceItem.Count; i++)
                {
                    int findIndex = allSaveItemedId.FindIndex(myId => (myId == _listSourceItem[i].Index));
                    if (findIndex >= 0)
                        continue;
                    allSaveItemedId.Add(_listSourceItem[i].Index);

                    FileStream streamImg = new FileStream(_listSourceItem[i].Path, FileMode.Open);
                    Bitmap img = new Bitmap(Image.FromStream(streamImg));
                    streamImg.Flush();
                    streamImg.Close();
                    

                    string itemNameSave = Path.GetFileNameWithoutExtension(_listSourceItem[i].Path);
                    string pathImage = Path.Combine(pathFolder + "\\Tiles", _listSourceItem[i].Index + ".png");
                    Bitmap saveBitmap = new Bitmap(img);
                    saveBitmap.Save(pathImage, ImageFormat.Png);
                    
                    strWriter.WriteLine(""
                        + _listSourceItem[i].Index + " "               // item index
                        + _listSourceItem[i].TypeID + " "               // item type ID
                        + Path.GetFileName(pathImage) + " "               // item save name
                        + _listSourceItem[i].ItemWidth + " "        // item width
                        + _listSourceItem[i].ItemHeight + " "       // item height
                        + _listSourceItem[i].MoveStatus + " "       // is moveable: 0-none, 1-move
                        + +_listSourceItem[i].CountSprite + " "     // count sprite: if have else < 0
                        + _listSourceItem[i].SpritePerRow + " "     // sprite per row: if have else < 0
                        );
                }

                // lưu thông tin các objects đã add
                strWriter.WriteLine();
                foreach (var item in _allItemAdded)
                {
                    strWriter.WriteLine(""
                    + item.ItemInfoIndex + " "            // item index
                    + item.ItemRectangle.X + " "          // position X
                    + item.ItemRectangle.Y + " "          // position Y
                    );
                }

                strWriter.WriteLine();
                strWriter.Close();

                return true;
            }
            catch (Exception ex)
            {
                strWriter.Close();
                return false;
            }
        }

        #endregion

        #region Open

        private void OpenMap(string pathFolder, string fileName)
        {
            try
            {
                string filePathInfo = Path.Combine(pathFolder, fileName + ".svmap");
                string filePathBackground = Path.Combine(pathFolder, fileName + ".bgimg");
                if (!File.Exists(filePathInfo))
                    throw new Exception("Cannot find info file. Here, sure that info file is exist in this folder.");
                if (!File.Exists(filePathBackground))
                    throw new Exception("Cannot find background image file. Here, sure that image file is exist in this folder.");
              
                DefaultValue();

                #region Background

                using (FileStream fs = new FileStream(filePathBackground, FileMode.Open))
                {
                    _background = new Bitmap(Image.FromStream(fs));
                    fs.Flush();
                    fs.Close();
                }

                #endregion

                #region Read basic information


                string[] informationMap = File.ReadAllLines(filePathInfo);
                string infoLine = informationMap[1];
                List<string> itemInfoLines = new List<string>();
                List<string> objectListLines = new List<string>();

                List<int> allEndLine = new List<int>();

                for (int i = 0; i < informationMap.Length; i++)
                {
                    if (informationMap[i].Trim().Length < 1)
                        allEndLine.Add(i);
                }

                for (int i = allEndLine[1] + 1; i < allEndLine[2]; i++)
                {
                    itemInfoLines.Add(informationMap[i]);
                }
                for (int i = allEndLine[2] + 1; i < allEndLine[3]; i++)
                {
                    objectListLines.Add(informationMap[i]);
                }

                string[] allBasicInfo = infoLine.Split(' ');
                _rows = int.Parse(allBasicInfo[2]);
                _columns =  int.Parse(allBasicInfo[3]);
                _tileWidth =  int.Parse(allBasicInfo[4]);
                _tileHeight =  int.Parse(allBasicInfo[5]);
                _screenWidth = int.Parse(allBasicInfo[6]);
                _screenHeight = int.Parse(allBasicInfo[7]);

                #region Item

                for (int i = 0; i < itemInfoLines.Count; i++)
                {
                    string[] allContent = itemInfoLines[i].Split(' ');
                    int index = int.Parse(allContent[0]);
                    int id = int.Parse(allContent[1]);
                    string path = Path.Combine(pathFolder + "\\Tiles", allContent[2]);
                    int itemWidth = int.Parse(allContent[3]);
                    int itemHeight = int.Parse(allContent[4]);
                    int isMove = int.Parse(allContent[5]);
                    bool isMovable = (isMove > 0) ? true : false;
                    int countSprite = int.Parse(allContent[6]);
                    int spritePerRow = int.Parse(allContent[7]);
                    FileStream streamImg = new FileStream(path, FileMode.Open);
                    Image resourceImageImg = Image.FromStream(streamImg);
                    streamImg.Flush();
                    streamImg.Close();
                    
                    _listSourceItem.Add(new ItemInfo(index, id, resourceImageImg, path, isMovable, countSprite, spritePerRow, itemWidth, itemHeight));
                }

                #endregion

                #region Object

                for (int i = 0; i < objectListLines.Count; i++)
                {
                    string[] allContent = objectListLines[i].Split(' ');
                    int index = int.Parse(allContent[0]);
                    int x = int.Parse(allContent[1]);
                    int y = int.Parse(allContent[2]);
                    ItemInfo itemInfo = _listSourceItem.Find(item => (item.Index == index));

                    int width = itemInfo.ItemWidth;
                    int height = itemInfo.ItemHeight;
                    _allItemAdded.Add(new ItemObject(index, itemInfo.TypeID, x, y, width, height));
                }


                #endregion

                #endregion


                for (int i = 0; i < _listSourceItem.Count; i++)
                {
                    imageListView1.AddImageToList(_listSourceItem[i].ShowImage);
                    _itemIndex++;
                }
                txtColumns.Text = _columns + "";
                txtRows.Text = _rows + "";
                txtTileHeight.Text = _tileHeight + "";
                txtTileWidth.Text = _tileWidth + "";
                if (_background != null)
                    pnMapDraw.BackgroundImage = _background;
                else
                    pnMapDraw.BackgroundImage = null;
                _createdSuccessed = true;
                pnMapDraw.Invalidate();

            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        #endregion

    }
}
