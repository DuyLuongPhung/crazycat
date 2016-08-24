using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace MapEditor.UserControlDesign
{
    public class ItemObject
    {
        public int ItemInfoIndex;
        public int ItemInfoID;
        public Rectangle ItemRectangle;
        public ItemObject(int itemInfoIndex, int itemInfoID, int x, int y, int width, int height)
        {
            this.ItemInfoIndex = itemInfoIndex;
            this.ItemInfoID = itemInfoID;
            ItemRectangle = new Rectangle(x, y, width, height);
        }
    }

    public class ItemInfo
    {
        public int Index;
        public string Path;
        public int TypeID;
        public Image ShowImage;
        public int MoveStatus;
        public bool IsMoveAble;
        public int CountSprite;
        public int SpritePerRow;
        public int ItemWidth;
        public int ItemHeight;
        public ItemInfo(int index, int typeId, Image showImg, string path, bool isMoveAble, int countSprite, int spritePerRow,
            int itemWidth, int itemHeight)
        {
            this.Index = index;
            this.TypeID = typeId;
            this.ShowImage = showImg;
            this.Path = path;
            this.IsMoveAble = isMoveAble;
            this.CountSprite = countSprite;
            this.SpritePerRow = spritePerRow;
            this.ItemWidth = itemWidth;
            this.ItemHeight = itemHeight;
            this.MoveStatus = (IsMoveAble == true) ? 1 : 0;
        }
    }

    public class ComboboxItem
    {
        public string Text;
        public int Id;
        public ComboboxItem(int id, string text)
        {
            Id = id;
            Text = text;
        }
        public override string ToString()
        {
            return Text;
        }
    }
}
