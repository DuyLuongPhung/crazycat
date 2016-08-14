using MapEditor.UserControlDesign;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor.QuadTree
{
    class QuadTreeManager
    {
        QuadTree _tree;

        internal QuadTree Tree
        {
            get { return _tree; }
            set { _tree = value; }
        }
        int _screenWidth, _screenHeight;

        public QuadTreeManager(int screenWidth, int screenHeight)
        {
            _screenWidth = screenWidth;
            _screenHeight = screenHeight;
            _tree = new QuadTree();
        }

        public void SetAllData(List<ItemObject> allObjects, Rectangle mapPartition)
        {
            if (allObjects == null)
                throw new Exception("List objects is null!");
            QuadNode root = new QuadNode(0, mapPartition);
            _tree.Root = root;
            SetQuadTree(allObjects, _tree.Root);
        }

        public void SetQuadTree(List<ItemObject> allObjects, QuadNode root)
        {
            int widthLeft, heightTop, widthRight, heightBottom;
            QuadNode nodeRT, nodeLT, nodeLB, nodeRB;
            if (root.Partition.Width > _screenWidth)
            {
                widthLeft = root.Partition.Width / 2;
                widthRight = root.Partition.Width - widthLeft;
            }
            else
            {
                widthLeft = root.Partition.Width;
                widthRight = 0;
            }
            if(root.Partition.Height > _screenHeight)
            {
                heightTop = root.Partition.Height / 2;
                heightBottom = root.Partition.Height - heightTop;
            }
            else
            {
                heightTop = root.Partition.Height;
                heightBottom = 0;
            }

            nodeLT = new QuadNode((root.Id * 4 + 2), new Rectangle(root.Partition.X, root.Partition.Y, widthLeft, heightTop));
            nodeLB = new QuadNode((root.Id * 4 + 3), new Rectangle(root.Partition.X, root.Partition.Y+heightTop, widthLeft, heightBottom));
            nodeRB = new QuadNode((root.Id * 4 + 4), new Rectangle(root.Partition.X+widthLeft, root.Partition.Y+heightTop, widthRight, heightBottom));
            nodeRT = new QuadNode((root.Id * 4 + 1), new Rectangle(root.Partition.X + widthLeft, root.Partition.Y, widthRight, heightTop));
            root.NodeLT = nodeLT;
            root.NodeLB = nodeLB;
            root.NodeRB = nodeRB;
            root.NodeRT = nodeRT;

            if(nodeLT.Partition.Width <= _screenWidth && nodeLT.Partition.Height <= _screenHeight)
            {
                for(int i=0;i<allObjects.Count;i++)
                {
                    if(allObjects[i].ItemRectangle.IntersectsWith(nodeLT.Partition))
                    {
                        nodeLT.AddObject(allObjects[i]);
                        allObjects.RemoveAt(i--);
                    }
                }
            }
            else
            {
                SetQuadTree(allObjects, nodeLT);
            }

            if (nodeLB.Partition.Width <= _screenWidth && nodeLB.Partition.Height <= _screenHeight)
            {
                for (int i = 0; i < allObjects.Count; i++)
                {
                    if (allObjects[i].ItemRectangle.IntersectsWith(nodeLB.Partition))
                    {
                        nodeLB.AddObject(allObjects[i]);
                        allObjects.RemoveAt(i--);
                    }
                }
            }
            else
            {
                SetQuadTree(allObjects, nodeLB);
            }
            if (nodeRB.Partition.Width <= _screenWidth && nodeRB.Partition.Height <= _screenHeight)
            {
                for (int i = 0; i < allObjects.Count; i++)
                {
                    if (allObjects[i].ItemRectangle.IntersectsWith(nodeRB.Partition))
                    {
                        nodeRB.AddObject(allObjects[i]);
                        allObjects.RemoveAt(i--);
                    }
                }
            }
            else
            {
                SetQuadTree(allObjects, nodeRB);
            }
            if (nodeRT.Partition.Width <= _screenWidth && nodeRT.Partition.Height <= _screenHeight)
            {
                for (int i = 0; i < allObjects.Count; i++)
                {
                    if (allObjects[i].ItemRectangle.IntersectsWith(nodeRT.Partition))
                    {
                        nodeRT.AddObject(allObjects[i]);
                        allObjects.RemoveAt(i--);
                    }
                }
            }
            else
            {
                SetQuadTree(allObjects, nodeRT);
            }
        }

    }
}
