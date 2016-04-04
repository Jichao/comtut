using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices.ComTypes;
using System.Runtime.InteropServices;
namespace DotNetClient
{
    class PolylineTest
    {
        private const string kFileName = "e:\\dotnet.bin";
        public int testCompoundFile()
        {
            return 0;
        }

        public int writePersistFile()
        {
            GraphicsLibrary.PolylineObjClass obj = new GraphicsLibrary.PolylineObjClass();
            GraphicsLibrary.PolyPoint pt = new GraphicsLibrary.PolyPoint();
            pt.x = 1;
            pt.y = 3;
            GraphicsLibrary.PolyPoint pt2 = new GraphicsLibrary.PolyPoint();
            pt2.x = 100;
            pt2.y = 300;
            GraphicsLibrary.PolyPoint[] pts = new GraphicsLibrary.PolyPoint[] { pt, pt2 };
            obj.Points = pts;
            foreach (GraphicsLibrary.PolyPoint ptt in pts)
            {
                Trace.WriteLine(String.Format("point ({0}, {1})", ptt.x, ptt.y));
            }
            IPersistFile pf = (IPersistFile)obj;
            pf.Save(kFileName, true);
            pf.SaveCompleted(kFileName);
            Marshal.ReleaseComObject(pf);
            Marshal.ReleaseComObject(obj);
            return 0;
        }
        public int readPersistFile()
        {
            GraphicsLibrary.PolylineObjClass obj = new GraphicsLibrary.PolylineObjClass();
            IPersistFile pf = (IPersistFile)obj;
            pf.Load(kFileName, 0);
            foreach (GraphicsLibrary.PolyPoint ptt in obj.Points)
            {
                Trace.WriteLine(String.Format("point ({0}, {1})", ptt.x, ptt.y));
            }
            Marshal.ReleaseComObject(pf);
            Marshal.ReleaseComObject(obj);
            return 0;
        }

        public int testFileMoniker()
        {
            IMoniker moniker;
            int hresult = NativeMethods.CreateFileMoniker(kFileName, out moniker);
            IBindCtx pbc;
            NativeMethods.CreateBindCtx(0, out pbc);
            Object obj;
            Guid guid = new Guid();
            guid = typeof(GraphicsLibrary.IPolyline).GUID;
            moniker.BindToObject(pbc, null, guid, out obj);
            GraphicsLibrary.IPolyline pl = (GraphicsLibrary.IPolyline)obj;
            foreach (GraphicsLibrary.PolyPoint ptt in pl.Points)
            {
                Trace.WriteLine(String.Format("point ({0}, {1})", ptt.x, ptt.y));
            }
            Guid clsid;
            moniker.GetClassID(out clsid);
            return 0;
        }

        private int writeCompoundFile()
        {

            return 0;
        }
        private int readCompoundFile()
        {
            return 0;
        }

    }


    internal class NativeMethods
    {
        [DllImport("ole32.dll")]
        public static extern int GetRunningObjectTable(int reserved, out IRunningObjectTable rot);
        [DllImport("ole32.dll")]
        public static extern int CreateFileMoniker([MarshalAs(UnmanagedType.LPWStr)] string lpszPathName, out IMoniker ppmk);
        [DllImport("ole32.dll")]
        public static extern int CreateBindCtx(int reserved, out IBindCtx ppbc);
        [Flags]
        public enum RotFlags : int
        {
            None = 0,
            RegistrationKeepsAlive = 1,
            /// <summary>
            /// In order to use this flag, the application must have its executable name in the AppID section
            /// of the registry. We probably don't need it, anyway, it seems like a remoting thing?
            /// </summary>
            AllowAnyClient = 2
        }


    }
}
