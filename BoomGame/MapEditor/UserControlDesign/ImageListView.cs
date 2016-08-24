using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MapEditor.UserControlDesign
{
    public partial class ImageListView : UserControl
    {
        private int _currentIndex;

        public int CurrentIndex
        {
            get { return _currentIndex; }
            set { _currentIndex = value; }
        }
        private string _selectedImageName;

        public string SelectedImageName
        {
            get { return _selectedImageName; }
            set { _selectedImageName = value; }
        }
        public ImageListView()
        {
            InitializeComponent();
            ImageList largeList = new ImageList();
            largeList.ImageSize = new System.Drawing.Size(30, 30);
            listView1.LargeImageList = largeList;
        }
        public event EventHandler ImageIndexChange;

        public void AddImageToList(Image image)
        {
            listView1.LargeImageList.Images.Add(image);
            int index = listView1.LargeImageList.Images.Count - 1;
            ListViewItem item = new ListViewItem();
            item.ImageIndex = index;
            item.Tag = image.Tag;
            listView1.Items.Add(item);
            listView1.Refresh();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.listView1.SelectedItems.Count == 0)
                return;
            _currentIndex = listView1.SelectedIndices[0];
            _selectedImageName = listView1.SelectedItems[0].Tag + "";
            if (this.ImageIndexChange != null)
                this.ImageIndexChange(this, e);
        }

        public void ClearSection()
        {
            listView1.SelectedItems.Clear();
        }

        public void ClearItem()
        {
            listView1.Clear();
        }
    }
}
