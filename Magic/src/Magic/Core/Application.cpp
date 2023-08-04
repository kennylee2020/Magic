#include "magicpch.h"
#include "Magic/Event/Event.h"
#include "Magic/Core/Application.h"
#include "Magic/ImGui/ImGuiLayer.h"
#include "Magic/Graphics/Graphics.h"

namespace Magic {
	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationDesc desc)
	{
		MAG_CORE_INFO("Magic start!");
		s_Instance = this;
		m_IsRunning = true;
		m_Window = Window::Create(desc.windowDesc);
		m_Window->SetWindowEventCallback(BIND_EVENT_CALLBACK(Application::OnEvent));

		Graphics::Init();
		RendererCommand::SetViewPort(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

		PushLayer(new ImGuiLayer());
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	bool Application::OnEvent(Event& e) {
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled) break;
			(*it)->OnEvent(e);
		}

		EventDispatcher dispatcher(e);
		dispatcher.Dispath<WindowCloseEvent>(BIND_EVENT_CALLBACK(Application::onWindowCloseEvent));
		dispatcher.Dispath<WindowResizeEvent>(BIND_EVENT_CALLBACK(Application::onWindowResizeEvent));
		dispatcher.Dispath<WindowFocusEvent>(BIND_EVENT_CALLBACK(Application::onWindowFocusEvent));
		dispatcher.Dispath<WindowLostFocus>(BIND_EVENT_CALLBACK(Application::onWindowLostFocusEvent));

		dispatcher.Dispath<MouseButtonDownEvent>(BIND_EVENT_CALLBACK(Application::onMouseButtonDownEvent));
		dispatcher.Dispath<MouseButtonUpEvent>(BIND_EVENT_CALLBACK(Application::onMouseButtonUpEvent));
		dispatcher.Dispath<MouseScrollEvent>(BIND_EVENT_CALLBACK(Application::onMouseScrollEvent));
		dispatcher.Dispath<MouseMoveEvent>(BIND_EVENT_CALLBACK(Application::onMouseMoveEvent));

		dispatcher.Dispath<KeyDownEvent>(BIND_EVENT_CALLBACK(Application::onKeyDownEvent));
		dispatcher.Dispath<KeyUpEvent>(BIND_EVENT_CALLBACK(Application::onKeyUpEvent));
		dispatcher.Dispath<KeyTypedEvent>(BIND_EVENT_CALLBACK(Application::onKeyTypedEvent));
		return true;
	}

	bool Application::onWindowFocusEvent(WindowFocusEvent& e) {
		MAG_INFO("onWindowFocusEvent");
		return true;
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& e) {
		MAG_INFO("onWindowCloseEvent");
		m_IsRunning = false;
		return true;
	}

	bool Application::onWindowResizeEvent(WindowResizeEvent& e) {
		MAG_INFO("onWindowResizeEvent");
		Graphics::OnWindowResize(e.GetWidth(), e.GetHeight());
		return true;
	}

	bool Application::onWindowLostFocusEvent(WindowLostFocus& e) {
		MAG_INFO("onWindowLostFocusEvent");
		return true;
	}

	bool Application::onMouseButtonDownEvent(MouseButtonDownEvent& e)
	{
		MAG_INFO("onMouseButtonDownEvent");
		return true;
	}

	bool Application::onMouseButtonUpEvent(MouseButtonUpEvent& e)
	{
		MAG_INFO("onMouseButtonUpEvent");
		return true;
	}

	bool Application::onMouseMoveEvent(MouseMoveEvent& e)
	{
		//MAG_INFO("onMouseMoveEvent {0} {1}", event.getX(), event.getY());
		return true;
	}

	bool Application::onMouseScrollEvent(MouseScrollEvent& e)
	{
		//MAG_INFO("onMouseScrollEvent {0} {1}", event.getDeltaX(), event.getDeltaY());
		return true;
	}

	bool Application::onKeyDownEvent(KeyDownEvent& e)
	{
		MAG_INFO("onKeyDownEvent");
		return true;
	}

	bool Application::onKeyUpEvent(KeyUpEvent& e)
	{
		MAG_INFO("onKeyUpEvent");
		return true;
	}

	bool Application::onKeyTypedEvent(KeyTypedEvent& e)
	{
		MAG_INFO("onKeyTypedEvent {0}", e.GetKeycode());
		return true;
	}

	void Application::run()
	{
		while (m_IsRunning)
		{
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			ImGuiLayer::BeginImGui();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGui();
			}
			ImGuiLayer::EndImGui();
			
			m_Window->OnUpdate();
		}
	}
}