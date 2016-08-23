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

        public void SetAllData(List<ObjectSave> allObjects, Rectangle mapPartition)
        {
            if (allObjects == null)
                throw new Exception("List objects is null!");
            QuadNode root = new QuadNode(0,0, mapPartition);
            _root = root;
            SetQuadTree(allObjects, _root);
        }

        private void SetQuadTree(List<ObjectSave> allObjects, QuadNode root)
        {
            if (root.level >= maxLevel)  // ko chia them nua
            {
                foreach (ObjectSave obj in allObjects)
                {
                    if (root.Partition.IntersectsWith(obj.partionRect))
                    {
                        root._objects.Add(obj);
                    }
                }
                return;
            }

            int cLevel = root.level;
            int width = root.Partition.Width / 2;
            int height = root.Partition.Height / 2;
            int x = root.Partition.X;
            int y = root.Partition.Y;
            int x1 = x + width;
            int y1 = y - height;

            root.NodeRT = new QuadNode(cLevel + 1, (root.Id * 4 + 1), new Rectangle(x1,y,width,height));
            root.NodeLT = new QuadNode(cLevel + 1, (root.Id * 4 + 2), new Rectangle(x,y,width,height));
            root.NodeLB = new QuadNode(cLevel + 1, (root.Id * 4 + 3), new Rectangle(x,y1,width,height));
            root.NodeRB = new QuadNode(cLevel + 1, (root.Id * 4 + 4), new Rectangle(x1,y1,width,height));

            SetQuadTree(allObjects, root.NodeRT);
            SetQuadTree(allObjects, root.NodeLT);
            SetQuadTree(allObjects, root.NodeLB);
            SetQuadTree(allObjects, root.NodeRB);
        }

    }
}
