using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor.QuadTree
{
    class QuadTree
    {
        QuadNode _root;

        internal QuadNode Root
        {
            get { return _root; }
            set { _root = value; }
        }
    }
}
