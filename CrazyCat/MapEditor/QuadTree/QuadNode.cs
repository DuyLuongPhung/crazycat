using MapEditor.UserControlDesign;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor.QuadTree
{
    class QuadNode
    {
        QuadNode _nodeLT;

        internal QuadNode NodeLT
        {
            get { return _nodeLT; }
            set { _nodeLT = value; }
        }
        QuadNode _nodeRT;

        internal QuadNode NodeRT
        {
            get { return _nodeRT; }
            set { _nodeRT = value; }
        }
        QuadNode _nodeLB;

        internal QuadNode NodeLB
        {
            get { return _nodeLB; }
            set { _nodeLB = value; }
        }
        QuadNode _nodeRB;

        internal QuadNode NodeRB
        {
            get { return _nodeRB; }
            set { _nodeRB = value; }
        }

        List<ItemObject> _objects;
        int _id;

        public int Id
        {
            get { return _id; }
            set { _id = value; }
        }
        Rectangle _partition;

        public Rectangle Partition
        {
            get { return _partition; }
            set { _partition = value; }
        }

        public QuadNode(int id, Rectangle partition)
        {
            _id = id;
            _partition = partition;
            _nodeLT = null;
            _nodeRT = null;
            _nodeLB = null;
            _nodeRB = null;
            _objects = new List<ItemObject>();
        }

        public void AddNode(QuadNode node)
        {
            if (_id * 4 + 1 == node._id)
            {
                _nodeRT = node;
                return;
            }
            if (_id * 4 + 2 == node._id)
            {
                _nodeLT = node;
                return;
            }
            if (_id * 4 + 3 == node._id)
            {
                _nodeLB = node;
                return;
            }
            if (_id * 4 + 4 == node._id)
            {
                _nodeRB = node;
                return;
            }
            if (_nodeRT != null)
                _nodeRT.AddNode(node);

            if (_nodeRT != null)
                _nodeLT.AddNode(node);

            if (_nodeRB != null)
                _nodeRB.AddNode(node);

            if (_nodeLB != null)
                _nodeLB.AddNode(node);
        }
        public bool AddObject(ItemObject objects)
        {
            _objects.Add(objects);
            return true;
        }
        public List<ItemObject> GetAllObjects()
        {
            return _objects;
        }
        
    }
}
