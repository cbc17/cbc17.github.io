using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;

namespace _154Finalv2
{
    class Program
    {
        
        static void Main(string[] args)
        {
            int selection;

            ShoppingList sl = new ShoppingList();

            sl.AddItem(sl.EnterName(), sl.EnterColor(), sl.EnterAmount());
            selection = sl.DisplayMenu();
            while (selection < 10)
            {               
                switch (selection)
                {
                    case 1:
                        sl.AddItem(sl.EnterName(), sl.EnterColor(), sl.EnterAmount());
                        break;
                    case 2:
                        sl.DeleteItem();
                        break;
                    case 3:
                        sl.SearchByName();
                        break;
                    case 4:
                        sl.DisplayList();
                        break;
                    case 5:
                        sl.BubbleSortAmount();
                        sl.DisplayList();
                        break;
                    case 6:
                        sl.BubbleSortColor();
                        sl.DisplayList();
                        break;
                    case 7:
                        sl.BubbleSortName();
                        sl.DisplayList();
                        break;
                    case 8:
                        sl.FilterColor();
                        break;
                    case 9:
                        sl.ReverseList();
                        sl.DisplayList();
                        break;
                }
                selection = sl.DisplayMenu();
            }
        }       
    }
}
