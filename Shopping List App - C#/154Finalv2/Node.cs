using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _154Finalv2
{
    class Node
    {
        public Node next;
        public String name;
        public String color;
        public int amount;

        public Node(string n, string c, int v)
        {
            name = n;
            color = c;
            amount = v;
            next = null;
        }
    }
}
