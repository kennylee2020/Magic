#pragma once
#include "Magic/Core/Window.h"
#include "GLFW/glfw3.h"

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

		virtual int getWidth() const override { return m_Data.width;}
		virtual int getHeight() const override {return m_Data.height;}
		virtual void onUpdate() override;
		virtual void* getNativeWindow() override;
		virtual void setWindowEventCallback(const WindowEventFunc& callback) override;
	private:
		void init(const WindowData& windowData);
		void shutdow();
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}
