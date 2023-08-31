using System;
using System.Reflection;
using System.Runtime.InteropServices;

namespace Magic
{
    public abstract class Component
    {
        public Entity entity { get; internal set; }
        internal abstract void Initialize();
    }

    public unsafe partial class NameComponent : Component{
        public string name{
            get{
                return nativeGetName(entity.ID);
            }
            set{
                nativeSetName(entity.ID, value);
            }
        }
    }

    public unsafe partial class TransformComponent : Component
    {
        public Vector3 position{ 
            get{
                return nativeGetPosition(entity.ID);
            }
            set{
                nativeSetPosition(entity.ID, value);
            }
        }

        public Vector3 eulerAngles {
            get {
                return nativeGetEulerAngles(entity.ID);
            }
            set {
                nativeSetEulerAngles(entity.ID, value);
            }
        }

        public Vector3 scale {
            get {
                return nativeGetScale(entity.ID);
            }
            set {
                nativeSetScale(entity.ID, value);
            }
        }
    }

    public unsafe partial class ScriptComponent : Component
    {
    }
}
