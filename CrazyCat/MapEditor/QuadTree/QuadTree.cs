using MapEditor.UserControlDesign;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor.QuadTree
{
    class QuadTree
    {
        QuadNode _root;
        int maxLevel = 3;
        internal QuadNode Root
        {
            get { return _root; }
            set { _root = value; }
        }

        public void SetAllData(List<ItemObject> allObjects, Rectangle mapPartition)
        {
            if (allObjects == null)
                throw new Exception("List objects is null!");
            QuadNode root = new QuadNode(0,0, mapPartition);
            _root = root;
            SetQuadTree(allObjects, _root);
        }

        private void SetQuadTree(List<MapEditor.UserControlDesign.ItemObject> allObjects, QuadNode root)
        {
            if (root.level >= maxLevel)  // ko chia them nua
            {
                foreach (ItemObject obj in allObjects)
                {
                    if (root.Partition.IntersectsWith(obj.ItemRectangle))
                    {
                        root._objects.Add(obj);
                    }
                }
                return;
            }

            int cLevel = root.level;

            root.NodeRT = new QuadNode(cLevel + 1, (root.Id * 4 + 1), new Rectangle(root.Partition.X + root.Partition.Width/2,
                root.Partition.Y, root.Partition.Width / 2, root.Partition.Height / 2));
            root.NodeLT = new QuadNode(cLevel + 1, (root.Id * 4 + 2), new Rectangle(root.Partition.X,
                root.Partition.Y, root.Partition.Width / 2, root.Partition.Height / 2));
            root.NodeLB = new QuadNode(cLevel + 1, (root.Id * 4 + 3), new Rectangle(root.Partition.X,
                root.Partition.Y - root.Partition.Height / 2, root.Partition.Width / 2, root.Partition.Height / 2));
            root.NodeRB = new QuadNode(cLevel + 1, (root.Id * 4 + 4), new Rectangle(root.Partition.X + root.Partition.Width/2,
                root.Partition.Y - root.Partition.Height / 2, root.Partition.Width / 2, root.Partition.Height / 2));

            SetQuadTree(allObjects, root.NodeRT);
            SetQuadTree(allObjects, root.NodeLT);
            SetQuadTree(allObjects, root.NodeLB);
            SetQuadTree(allObjects, root.NodeRB);
        }

    }
}
