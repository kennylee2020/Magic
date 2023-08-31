using System;

namespace Magic
{
    public unsafe partial class Entity
    {
        public static Entity Create() {
            return new Entity();
        }

        public static Entity FindEntity(string name) {
            UInt32 entityID = nativeFindEntity(name);
            return new Entity(entityID);
        }

        public readonly UInt32 ID;

        protected Entity(){
            ID = nativeCreate();
        }

        protected Entity(UInt32 id){
            ID = id;
        }
        
        public bool HasComponent<T>() where T : Component{
            return nativeHasComponent(ID);
        }

        public T GetComponent<T>() where T : Component, new(){
            T component = new T();
            component.entity = this;
            component.Initialize();
            return component;
        }
    }
}
