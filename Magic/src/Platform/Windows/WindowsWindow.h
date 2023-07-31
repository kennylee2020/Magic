#pragma once
#include "GLFW/glfw3.h"
#include "Magic/Core/Window.h"

namespace Magic {
	class WindowsWindow : public Window
	{
	public:
		struct WindowData{
			int width;
			int height;
			std::string title;
			WindowEventFunc windowEvent;
		};
	public:
		WindowsWindow(const WindowDesc& windowDesc);
		~WindowsWindow();

		virtual int GetWidth() const override { return m_Data.width;}
		virtual int GetHeight() const override {return m_Data.height;}
		virtual void OnUpdate() override;
		virtual void* GetNativeWindow() override;
		virtual void SetWindowEventCallback(const WindowEventFunc& callback) override;
	private:
		void init(const WindowData& windowData);
		void shutdow();
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}
