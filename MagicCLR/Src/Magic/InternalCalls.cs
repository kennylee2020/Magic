using System;
using System.Reflection;
using System.Runtime.InteropServices;

namespace Magic
{
    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct InitPayload
    {
        //Application
        public delegate* unmanaged<Application.ApplicationCallbacks, void> Application_RegisterCallbacks;
        //Debug
        public delegate* unmanaged<string, void> Debug_Log;
        public delegate* unmanaged<string, void> Debug_Warn;
        public delegate* unmanaged<string, void> Debug_Error;
        public delegate* unmanaged<string, void> Debug_Critical;
        //Entity
        public delegate* unmanaged<UInt64> Entity_Create;
        public delegate* unmanaged<string, UInt64> Entity_FindEntity;
        public delegate* unmanaged<UInt64, bool> Entity_HasComponent;
        //NameComponent
        public delegate* unmanaged<UInt64, void> NameComponent_Create;
        public delegate* unmanaged<UInt64, string, void> NameComponent_SetName;
        public delegate* unmanaged<UInt64, string> NameComponent_GetName;
        //ScriptComponent
        public delegate* unmanaged<UInt64, ScriptComponent.LifeCycleCallbacks, void> ScriptComponent_Create;
        //TransformComponent
        public delegate* unmanaged<UInt64, void> TransformComponent_Create;
        public delegate* unmanaged<UInt64, Vector3, void> TransformComponent_SetPosition;
        public delegate* unmanaged<UInt64, Vector3> TransformComponent_GetPosition;
        public delegate* unmanaged<UInt64, Vector3, void> TransformComponent_SetEulerAngles;
        public delegate* unmanaged<UInt64, Vector3> TransformComponent_GetEulerAngles;
        public delegate* unmanaged<UInt64, Vector3, void> TransformComponent_SetScale;
        public delegate* unmanaged<UInt64, Vector3> TransformComponent_GetScale;
    }

    internal static class InternalCalls
    {
        private static void Main(string[] args) {}

        [UnmanagedCallersOnly]
        public static void Init(InitPayload payload) {
            unsafe
            {
                Application.nativeRegisterApplicationCallbacks = payload.Application_RegisterCallbacks;
            }

            unsafe 
            {
                Debug.nativeLog = payload.Debug_Log;
                Debug.nativeWarn = payload.Debug_Warn;
                Debug.nativeError = payload.Debug_Error;
                Debug.nativeCritical = payload.Debug_Critical;
            }

            unsafe
            {
                Entity.nativeCreate = payload.Entity_Create;
                Entity.nativeFindEntity = payload.Entity_FindEntity;
                Entity.nativeHasComponent = payload.Entity_HasComponent;
            }

            unsafe
            {
                NameComponent.nativeCreate = payload.NameComponent_Create;
                NameComponent.nativeSetName = payload.NameComponent_SetName;
                NameComponent.nativeGetName = payload.NameComponent_GetName;
            }

            unsafe
            {
                ScriptComponent.nativeCreate = payload.ScriptComponent_Create;
            }

            unsafe 
            {
                TransformComponent.nativeCreate = payload.TransformComponent_Create;
                TransformComponent.nativeSetPosition = payload.TransformComponent_SetPosition;
                TransformComponent.nativeGetPosition = payload.TransformComponent_GetPosition;
                TransformComponent.nativeSetEulerAngles = payload.TransformComponent_SetEulerAngles;
                TransformComponent.nativeGetEulerAngles = payload.TransformComponent_GetEulerAngles;
                TransformComponent.nativeSetScale = payload.TransformComponent_SetScale;
                TransformComponent.nativeGetScale = payload.TransformComponent_GetScale;
            }

            Application.Initialize();

            Debug.Log("Hello awesome magic dotnet!");
        }
    }

    public static unsafe partial class Application
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct ApplicationCallbacks{
            public delegate* unmanaged<void> OnRuntimeStart;
            public delegate* unmanaged<void> OnRuntimeUpdate;
            public delegate* unmanaged<void> OnRuntimeStop;
        }
        internal static delegate* unmanaged<ApplicationCallbacks, void> nativeRegisterApplicationCallbacks;
        internal static void Initialize(){
            ApplicationCallbacks callbacks = new ApplicationCallbacks();
            callbacks.OnRuntimeStart =  (delegate* unmanaged<void>)Marshal.GetFunctionPointerForDelegate<Action>(OnRuntimeStart);
            callbacks.OnRuntimeUpdate = (delegate* unmanaged<void>)Marshal.GetFunctionPointerForDelegate<Action>(OnRuntimeUpdate);
            callbacks.OnRuntimeStop =   (delegate* unmanaged<void>)Marshal.GetFunctionPointerForDelegate<Action>(OnRuntimeStop);
            nativeRegisterApplicationCallbacks(callbacks);
        }
    }

    public static unsafe partial class Debug
    {
        internal static delegate* unmanaged<string, void> nativeLog;
        internal static delegate* unmanaged<string, void> nativeWarn;
        internal static delegate* unmanaged<string, void> nativeError;
        internal static delegate* unmanaged<string, void> nativeCritical;
    }

    public unsafe partial class Entity{
        internal static delegate* unmanaged<UInt64> nativeCreate;
        internal static delegate* unmanaged<string, UInt64> nativeFindEntity;
        internal static delegate* unmanaged<UInt64, bool> nativeHasComponent;
    }

    public unsafe partial class NameComponent
    {
        internal static delegate* unmanaged<UInt64, void> nativeCreate;
        internal static delegate* unmanaged<UInt64, string, void> nativeSetName;
        internal static delegate* unmanaged<UInt64, string> nativeGetName;
        internal override void Initialize() {
            nativeCreate(entity.ID);
        }
    }

    public unsafe partial class ScriptComponent
    {
        [StructLayout(LayoutKind.Sequential)]
        internal struct LifeCycleCallbacks
        {
            public delegate* unmanaged<void> OnCreate;
            public delegate* unmanaged<void> OnUpdate;
            public delegate* unmanaged<void> OnDestroy;
        }

        internal static delegate* unmanaged<UInt64, LifeCycleCallbacks, void> nativeCreate;

        internal override void Initialize() {
            LifeCycleCallbacks lifeCycleMethod = new LifeCycleCallbacks();
            MethodInfo method = GetType().GetMethod("OnCreate", BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);
            if (method != null) {
                lifeCycleMethod.OnCreate = (delegate* unmanaged<void>)Marshal.GetFunctionPointerForDelegate(method.CreateDelegate<Action>(this));
            }

            method = GetType().GetMethod("OnUpdate", BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);
            if (method != null) {
                lifeCycleMethod.OnUpdate = (delegate* unmanaged<void>)Marshal.GetFunctionPointerForDelegate(method.CreateDelegate<Action>(this));
            }

            method = GetType().GetMethod("OnDestroy", BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);
            if (method != null) {
                lifeCycleMethod.OnDestroy = (delegate* unmanaged<void>)Marshal.GetFunctionPointerForDelegate(method.CreateDelegate<Action>(this));
            }
            nativeCreate(entity.ID, lifeCycleMethod);
        }
    }

    public unsafe partial class TransformComponent{
        internal static delegate* unmanaged<UInt64, void> nativeCreate;
        internal static delegate* unmanaged<UInt64, Vector3, void> nativeSetPosition;
        internal static delegate* unmanaged<UInt64, Vector3> nativeGetPosition;
        internal static delegate* unmanaged<UInt64, Vector3, void> nativeSetEulerAngles;
        internal static delegate* unmanaged<UInt64, Vector3> nativeGetEulerAngles;
        internal static delegate* unmanaged<UInt64, Vector3, void> nativeSetScale;
        internal static delegate* unmanaged<UInt64, Vector3> nativeGetScale;
        internal override void Initialize() {
            nativeCreate(entity.ID);
        }
    }
}
