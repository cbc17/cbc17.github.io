using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;

namespace _154Finalv2
{
    class ShoppingList
    {
        private Node firstItem;

        public ShoppingList()
        {
            firstItem = null;
        }
        public int DisplayMenu()
        {
            int i;
            WriteLine("*******************************************************************************************\n");
            WriteLine("1. Add an item to the list\n" +
                "2. Remove an item from the list\n" +
                "3. Search the list for an item by name\n" +
                "4. Display the list\n" +
                "5. Sort the list by amount\n" +
                "6. Sort the list by color\n" +
                "7. Sort the list by name\n" +
                "8. Filter the list by color\n" +
                "9. View the list in reverse order\n" +
                "10. Exit the app\n");
            i = Convert.ToInt32(ReadLine());
            WriteLine("*******************************************************************************************\n");
            return i;
        }
        public void DisplayList()
        {
            Node item;
            WriteLine("******************************************************************************************************\n");
            WriteLine("List is :   ");
            item = firstItem;
            while (item != null)
            {
                WriteLine(item.name + "  " + item.color + "  " + item.amount);
                item = item.next;
            }
            WriteLine("******************************************************************************************************\n");
        }
        public void AddItem(string n, string c, int v)
        {
            Node temp = new Node(n, c, v);
            temp.next = firstItem;
            firstItem = temp;
        }
        public string EnterName()
        {
            string n;
            WriteLine("Enter Item Name: ");
            n = ReadLine();
            return n;
        }
        public string EnterColor()
        {
            string c;
            WriteLine("Enter Item Color: ");
            c = ReadLine();
            return c;
        }
        public int EnterAmount()
        {
            int v;
            WriteLine("Enter Item Amount: ");
            v = Convert.ToInt32(ReadLine());
            return v;
        }
        public void DeleteItem()
        {
            Node a = firstItem;
            string n = ItemByName();
            if (firstItem == null)
            {
                Console.WriteLine("Nothing to Delete\n");
                return;
            }
            if (firstItem.name == n)
            {
                firstItem = firstItem.next;
                return;
            }
            while (a.next != null)
            {
                if (a.next.name == n)
                    break;
                a = a.next;
            }
            if (a.next == null)
                Console.WriteLine("Element " + n + " not in list");
            else
                a.next = a.next.next;
        }
        public void SearchByName()
        {
            int position = 1;
            string searchTerm = ItemByName();
            Node a = firstItem;
            while (a != null)
            {
                if (a.name == searchTerm)
                    break;
                position++;
                a = a.next;
            }
            if (a == null)
            {
                WriteLine("Item not found in list");
            }
            else
            {
                WriteLine(searchTerm + " is at position " + position);
            }
        }
        public string ItemByName()
        {
            WriteLine("*******************************************************************************************\n");
            WriteLine("Please enter the name of the item you would like to find:");
            string n = ReadLine();
            WriteLine("*******************************************************************************************\n");
            return n;
        }
        public void ReverseList()
        {
            Node previous, a, next;

            previous = null;
            a = firstItem;
            while (a != null)
            {
                next = a.next;
                a.next = previous;
                previous = a;
                a = next;
            }
            firstItem = previous;
        }
        public void FilterColor()
        {
            string filterColor;
            Node item = firstItem;
            ShoppingList c = new ShoppingList();
            WriteLine("\nEnter the color you wish to filter the list by: ");
            filterColor = ReadLine();
            while (item != null)
            {
                if(item.color == filterColor)
                {
                    c.AddItem(item.name,item.color,item.amount);
                }
                item = item.next;
            }
            c.DisplayList();
            WriteLine("Choose an option for sorting the filtered list: ");
            int filterSelection;
            WriteLine("1. sort by amount\n" +
                "2. sort by color\n" +
                "3. sort by name\n" +
                "4. reverse the list\n" +
                "5. main menu");

            filterSelection = Convert.ToInt32(ReadLine());
            while(filterSelection != 5) {
                switch (filterSelection)
                {
                    case 1:
                        c.BubbleSortAmount();
                        c.DisplayList();
                        break;
                    case 2:
                        c.BubbleSortColor();
                        c.DisplayList();
                        break;
                    case 3:
                        c.BubbleSortName();
                        c.DisplayList();
                        break;
                    case 4:
                        c.ReverseList();
                        c.DisplayList();
                        break;
                }
                WriteLine("1. sort by amount\n" +
                "2.sort by color\n" +
                "3. sort by name\n" +
                "4. reverse the list\n" +
                "5. main menu");

                filterSelection = Convert.ToInt32(ReadLine());
            }
            
        }
        
        public void BubbleSortAmount()
        {
            Node a;
            Node b;
            Node tail;

            for (tail = null; tail != firstItem; tail = a)
            {
                for (a = firstItem; a.next != tail; a = a.next)
                {
                    b = a.next;
                    if (a.amount > b.amount)
                    {
                        string placeholder1 = a.name;
                        string placeholder2 = a.color;
                        int placeholder3 = a.amount;

                        a.name = b.name;
                        a.color = b.color;
                        a.amount = b.amount;

                        b.name = placeholder1;
                        b.color = placeholder2;
                        b.amount = placeholder3;

                    }
                }
            }
        }
        public void BubbleSortColor()
        {
            Node a;
            Node b;
            Node tail;

            for (tail = null; tail != firstItem; tail = a)
            {
                for (a = firstItem; a.next != tail; a = a.next)
                {
                    b = a.next;
                    if (string.Compare(a.color, b.color) == 1)
                    {
                        string placeholder1 = a.name;
                        string placeholder2 = a.color;
                        int placeholder3 = a.amount;

                        a.name = b.name;
                        a.color = b.color;
                        a.amount = b.amount;

                        b.name = placeholder1;
                        b.color = placeholder2;
                        b.amount = placeholder3;
                      }
                }
            }
        }
        public void BubbleSortName()
        {
            Node a;
            Node b;
            Node tail;

            for (tail = null; tail != firstItem; tail = a)
            {
                for (a = firstItem; a.next != tail; a = a.next)
                {
                    b = a.next;
                    if (string.Compare(a.name, b.name) == 1)
                    {
                        string placeholder1 = a.name;
                        string placeholder2 = a.color;
                        int placeholder3 = a.amount;
                        //Node placeholder4 = a.next;
                        a.name = b.name;
                        a.color = b.color;
                        a.amount = b.amount;
                        //a.next = b.next;
                        b.name = placeholder1;
                        b.color = placeholder2;
                        b.amount = placeholder3;
                        //b.next = placeholder4;
                    }
                }
            }
        }
    }
}
