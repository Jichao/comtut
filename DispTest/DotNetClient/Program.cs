using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace DotNetClient
{
    class Program
    {
        static void Main(string[] args)
        {
            StringLib.StringObjClass obj = new StringLib.StringObjClass();
            String result = obj.Concat("haha", "keke");
            System.Console.Write(result);
        }
    }
}
