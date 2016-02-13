using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
namespace DotNetClient
{
    class Program
    {
        static void EarlyBindig()
        {
            StringLib.StringObjClass obj = new StringLib.StringObjClass();
            String result = obj.Concat("Hello", "World");
            System.Console.WriteLine(result);
        }
        static void LaterBinding()
        {
            //Type comType = Type.GetTypeFromCLSID(new Guid("B1D59117-CC63-483B-9A19-240A5A19ED67"));
            Type comType = Type.GetTypeFromProgID("DispTest.String.1");
            Object obj = Activator.CreateInstance(comType);
            Object[] args = {"Hello", "World"};
            Object result = comType.InvokeMember("Concat", BindingFlags.InvokeMethod, null, obj, args);
            System.Console.WriteLine(result);
        }
        static void Main(string[] args)
        {
            EarlyBindig();
            LaterBinding();
        }
    }
}
