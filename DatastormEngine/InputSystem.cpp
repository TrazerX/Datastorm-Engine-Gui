#include "InputSystem.h"
#include <Windows.h>

#include "imgui/imgui.h"
InputSystem* InputSystem::m_system = nullptr;

inline ImGuiKey ConvertToImGuiKey(int key)
{
	static std::unordered_map<int, ImGuiKey> keyMap = {
		// ASCII characters
		{'A', ImGuiKey_A},
		{'B', ImGuiKey_B},
		{'C', ImGuiKey_C},
		{'D', ImGuiKey_D},
		{'E', ImGuiKey_E},
		{'F', ImGuiKey_F},
		{'G', ImGuiKey_G},
		{'H', ImGuiKey_H},
		{'I', ImGuiKey_I},
		{'J', ImGuiKey_J},
		{'K', ImGuiKey_K},
		{'L', ImGuiKey_L},
		{'M', ImGuiKey_M},
		{'N', ImGuiKey_N},
		{'O', ImGuiKey_O},
		{'P', ImGuiKey_P},
		{'Q', ImGuiKey_Q},
		{'R', ImGuiKey_R},
		{'S', ImGuiKey_S},
		{'T', ImGuiKey_T},
		{'U', ImGuiKey_U},
		{'V', ImGuiKey_V},
		{'W', ImGuiKey_W},
		{'X', ImGuiKey_X},
		{'Y', ImGuiKey_Y},
		{'Z', ImGuiKey_Z},
		// Digits
		{'0', ImGuiKey_0},
		{'1', ImGuiKey_1},
		{'2', ImGuiKey_2},
		{'3', ImGuiKey_3},
		{'4', ImGuiKey_4},
		{'5', ImGuiKey_5},
		{'6', ImGuiKey_6},
		{'7', ImGuiKey_7},
		{'8', ImGuiKey_8},
		{'9', ImGuiKey_9},
		// Special keys
	};

	auto it = keyMap.find(key);
	if (it != keyMap.end())
		return it->second;

	return ImGuiKey_None;  // Default return value if key is not found
}

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
	InputSystem::m_system = nullptr;
}

void InputSystem::update()
{
	auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
		return;
	}
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		//THERE IS MOUSE MOVE EVENT
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);



	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			ImGuiKey imguiKey = ConvertToImGuiKey(i);
			// KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				if (imguiKey != ImGuiKey_None) {
					io.AddKeyEvent(imguiKey, true);
				}
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else
						(*it)->onKeyDown(i);

					++it;
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					if (m_keys_state[i] != m_old_keys_state[i])
					{
						if (imguiKey != ImGuiKey_None) {
							io.AddKeyEvent(imguiKey, false);
						}
					}
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						if (i == VK_LBUTTON)
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else if (i == VK_RBUTTON)
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else
							(*it)->onKeyUp(i);

						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

InputSystem* InputSystem::get()
{
	return m_system;
}

void InputSystem::create()
{
	if (InputSystem::m_system) throw std::exception("InputSystem already created");
	InputSystem::m_system = new InputSystem();
}

void InputSystem::release()
{
	if (!InputSystem::m_system) return;
	delete InputSystem::m_system;
}