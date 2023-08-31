using System.Runtime.InteropServices;

namespace Magic
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public static Vector3 zero = new Vector3(0,0,0);

        public float x,y,z;
        public Vector3(float x, float y, float z){
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }
}
