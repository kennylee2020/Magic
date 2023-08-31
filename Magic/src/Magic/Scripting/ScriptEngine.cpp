#include "magicpch.h"
#include "ScriptEngine.h"
#include "ScriptGlue.h"

#include <coreclr/hostfxr.h>
#include <coreclr/coreclr_delegates.h>
#include <set>
#include <filesystem>

namespace Magic {

    using string_t = std::basic_string<char_t>;

    namespace
    {
        // Globals to hold hostfxr exports
        hostfxr_initialize_for_runtime_config_fn init_fptr;
        hostfxr_get_runtime_delegate_fn get_delegate_fptr;
        hostfxr_close_fn close_fptr;

        // Forward declarations
        bool load_hostfxr();
        load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* assembly);
    }

    namespace{
        #define HOSTFXR_VERSION "6.0.21"
        #define HOSTFXR_WINDOWS "hostfxr.dll"
        #define HOSTFXR_MAC "libhostfxr.dylib"
        #define HOSTFXR_LINUX "libhostfxr.so"

        #ifdef MAGIC_WINDOWS
        #define HOSTFXR_PATH "Runtime/Win64/host/fxr/" HOSTFXR_VERSION "/" HOSTFXR_WINDOWS
        #elif defined(MAGIC_MAC)
        #define HOSTFXR_PATH "Runtime/Mac/host/fxr/" HOSTFXR_VERSION "/" HOSTFXR_MAC
        #elif defined(MAGIC_LINUX)
        #define HOSTFXR_PATH "Runtime/Linux/host/fxr/" HOSTFXR_VERSION "/" HOSTFXR_LINUX
        #else
        #error "Unknown platform"
        #endif

        #define SDK_VERSION "net5.0"
        #define CLR_PATH SOLUTION_PATH "Magic/vendor/coreclr/" HOSTFXR_PATH
        #ifdef MAGIC_DEBUG
        #define DLL_PATH SOLUTION_PATH "Resources/Scripts/Debug/" SDK_VERSION "/"
        #else
        #define DLL_PATH SOLUTION_PATH "Resources/Scripts/Release/" SDK_VERSION "/"
        #endif
    }

    namespace {
        #define DOTNET_CONFIG DLL_PATH L"MagicCLR.runtimeconfig.json"
        #define DOTNET_LIB DLL_PATH L"MagicCLR.dll"
        #define DONET_TYPE L"Magic.InternalCalls, MagicCLR"
        #define DONET_TYPE_METHOD L"Init"
        typedef void (CORECLR_DELEGATE_CALLTYPE* entry_point_fn)(ScriptGlue::InitPayload payload);
    }

    namespace {
        // Forward declarations
        void* load_library(const char_t*);
        void* get_export(void*, const char*);

#ifdef MAGIC_WINDOWS
        void* load_library(const char_t* path)
        {
            HMODULE h = ::LoadLibraryW(path);
            assert(h != nullptr);
            return (void*)h;
        }
        void* get_export(void* h, const char* name)
        {
            void* f = ::GetProcAddress((HMODULE)h, name);
            assert(f != nullptr);
            return f;
        }
#else
        void* load_library(const char_t* path)
        {
            void* h = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
            assert(h != nullptr);
            return h;
        }
        void* get_export(void* h, const char* name)
        {
            void* f = dlsym(h, name);
            assert(f != nullptr);
            return f;
        }
#endif

        bool load_hostfxr() {
            std::wstringstream wss;
            wss << CLR_PATH;

            // Load hostfxr and get desired exports
            void* lib = load_library(wss.str().c_str());
            init_fptr = (hostfxr_initialize_for_runtime_config_fn)get_export(lib, "hostfxr_initialize_for_runtime_config");
            get_delegate_fptr = (hostfxr_get_runtime_delegate_fn)get_export(lib, "hostfxr_get_runtime_delegate");
            close_fptr = (hostfxr_close_fn)get_export(lib, "hostfxr_close");

            return (init_fptr && get_delegate_fptr && close_fptr);
        }

        // <SnippetInitialize>
        // Load and initialize .NET Core and get desired function pointer for scenario
        load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path)
        {
            // Load .NET Core
            void* load_assembly_and_get_function_pointer = nullptr;
            hostfxr_handle cxt = nullptr;
            int rc = init_fptr(config_path, nullptr, &cxt);
            if (rc != 0 || cxt == nullptr)
            {
                MAG_CORE_ERROR("Init failed: {0}", rc);
                close_fptr(cxt);
                return nullptr;
            }

            // Get the load assembly function pointer
            rc = get_delegate_fptr(
                cxt,
                hdt_load_assembly_and_get_function_pointer,
                &load_assembly_and_get_function_pointer);
            if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
                MAG_CORE_ERROR("Get delegate failed: {0}", rc);

            close_fptr(cxt);
            return (load_assembly_and_get_function_pointer_fn)load_assembly_and_get_function_pointer;
        }
    }

    Scene* ScriptEngine::m_Scene;
    ApplicationCallbacks ScriptEngine::m_ApplicationCallbacks;

	void ScriptEngine::Init()
	{
        if (!load_hostfxr())
        {
            MAG_CORE_CRITICAL("Failure: load_hostfxr()");
            return;
        }

        load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer = nullptr;
        load_assembly_and_get_function_pointer = get_dotnet_load_assembly(DOTNET_CONFIG);
        if (!load_assembly_and_get_function_pointer) {
            MAG_CORE_CRITICAL("Failure: get_dotnet_load_assembly()");
            return;
        }

        entry_point_fn Init = nullptr;
        int rc = load_assembly_and_get_function_pointer(
            DOTNET_LIB,
            DONET_TYPE,
            DONET_TYPE_METHOD,
            UNMANAGEDCALLERSONLY_METHOD,
            nullptr,
            (void**)&Init);

        if (rc != 0 || !Init) {
            MAG_CORE_CRITICAL("Failure: load_assembly_and_get_function_pointer()");
            return;
        }

        ScriptGlue::InitPayload playload;
        ScriptGlue::Register(playload);
        Init(playload);
	}

	void ScriptEngine::Shutdown()
	{
	}

    void ScriptEngine::OnRuntimeStart(Scene* scene)
    {
        m_Scene = scene;
        m_ApplicationCallbacks.Application_OnRuntimeStart();
    }

    void ScriptEngine::OnRuntimeUpdate()
    {
        auto view = m_Scene->m_Registry.view<ScriptComponent>();
        for (auto entity : view) {
            ScriptComponent& scriptComponent = view.get<ScriptComponent>(entity);
            scriptComponent.InvokeUpdate();
        }
        m_ApplicationCallbacks.Application_OnRuntimeUpdate();
    }

    void ScriptEngine::OnRuntimeStop() {
        m_ApplicationCallbacks.Application_OnRuntimeStop();
    }
}