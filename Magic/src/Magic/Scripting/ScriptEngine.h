#pragma once

/// <summary>
/// https://github.com/dotnet/runtime/blob/main/docs/design/features/native-hosting.md
/// https://learn.microsoft.com/en-us/dotnet/core/tutorials/netcore-hosting
/// https://learn.microsoft.com/en-us/dotnet/standard/native-interop/type-marshalling
/// https://www.mono-project.com/docs/advanced/embedding/#how-embedding-works
/// https://www.mono-project.com/docs/advanced/embedding/#invoking-methods-in-the-cil-universe
/// https://www.mono-project.com/docs/advanced/pinvoke/
/// https://github.com/Cutano/CoreCLREmbedTest/tree/master/ManagedLib
/// https://github.com/nxrighthere/UnrealCLR/blob/master/Source/Native/Source/UnrealCLR/Public/UnrealCLR.h
/// https://dev.to/tvinko/control-net-runtime-from-native-code-473f
/// </summary>

#include "Magic/Scene/Entity.h"
#include "Magic/Scene/Scene.h";
#include "Magic/Scripting/ScriptGlue.h"

namespace Magic {
	class ScriptEngine {
	public:
		static void Init();
		static void Shutdown();
		static void OnRuntimeStart(Scene* scene);
		static void OnRuntimeUpdate();
		static void OnRuntimeStop();
		static Scene* GetSceneContext(){ return m_Scene; }
		static void RegisterApplicationCallbacks(const ApplicationCallbacks& applicationCallbacks){ m_ApplicationCallbacks = applicationCallbacks;}
	private:
		static Scene* m_Scene;
		static ApplicationCallbacks m_ApplicationCallbacks;
	private:
		friend ScriptGlue;
	};
}