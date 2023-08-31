namespace Magic
{
    public static partial class Application
    {
        public static void OnRuntimeStart(){
            Debug.Log("Application::OnRuntimeStart");
            Entity entity = Entity.Create();
            TransformComponent transformComponent = entity.GetComponent<TransformComponent>();
            transformComponent.position = new Vector3(1f, 1f, 1f);
            Debug.Log($"New Position {entity.ID} :: {transformComponent.position.x}, {transformComponent.position.y} , {transformComponent.position.z}");
        }

        public static void OnRuntimeUpdate(){
        }

        public static void OnRuntimeStop(){
            Debug.Log("Application::OnRuntimeStop");
        }
    }
}
