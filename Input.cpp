#include "Input.h"
#include <iostream>

std::vector<Input::KeyCode> Input::m_CurrentInput;				//All the keys that are currently held down
std::vector<Input::KeyCode> Input::m_KeysPressedThisFrame;		//All the keys that were pressed this frame
std::vector<Input::KeyCode> Input::m_KeysReleasedThisFrame;		//All the keys that were released this frame

bool Input::m_MouseButtonsHeld[3] = { false, false, false };						//The mouse buttons currently held down
bool Input::m_MouseButtonsPressedThisFrame[3] = { false, false, false };			//The mouse buttons pressed this frame
bool Input::m_MouseButtonsReleasedThisFrame[3] = { false, false, false };			//The mouse buttons that were released this frame

Vector2 Input::m_MousePos = Vector2();	//The mouse position (in screen coordinates)

SDL_Keycode Input::KeyCodeToSDL(Input::KeyCode key) {
	switch (key) {
		case Num0: return SDLK_0;
		case Num1: return SDLK_1;
		case Num2: return SDLK_2;
		case Num3: return SDLK_3;
		case Num4: return SDLK_4;
		case Num5: return SDLK_5;
		case Num6: return SDLK_6;
		case Num7: return SDLK_7;
		case Num8: return SDLK_8;
		case Num9: return SDLK_9;
		case A: return SDLK_a;
		case B: return SDLK_b;
		case C: return SDLK_c;
		case D: return SDLK_d;
		case E: return SDLK_e;
		case F: return SDLK_f;
		case G: return SDLK_g;
		case H: return SDLK_h;
		case I: return SDLK_i;
		case J: return SDLK_j;
		case K: return SDLK_k;
		case L: return SDLK_l;
		case M: return SDLK_m;
		case N: return SDLK_n;
		case O: return SDLK_o;
		case P: return SDLK_p;
		case Q: return SDLK_q;
		case R: return SDLK_r;
		case S: return SDLK_s;
		case T: return SDLK_t;
		case U: return SDLK_u;
		case V: return SDLK_v;
		case W: return SDLK_w;
		case X: return SDLK_x;
		case Y: return SDLK_y;
		case Z: return SDLK_z;
		case UpArrow: return SDLK_UP;
		case DownArrow: return SDLK_DOWN;
		case LeftArrow: return SDLK_LEFT;
		case RightArrow: return SDLK_RIGHT;
		case Space: return SDLK_SPACE;
		case Enter: return SDLK_RETURN;
		case Escape: return SDLK_ESCAPE;
	}
	return SDLK_0;	//No key found (should change later to not return 0)
}

Input::KeyCode Input::SDLToKeyCode(SDL_Keycode key) {
	switch (key) {
		case SDLK_0: return Num0;
		case SDLK_1: return Num1;
		case SDLK_2: return Num2;
		case SDLK_3: return Num3;
		case SDLK_4: return Num4;
		case SDLK_5: return Num5;
		case SDLK_6: return Num6;
		case SDLK_7: return Num7;
		case SDLK_8: return Num8;
		case SDLK_9: return Num9;
		case SDLK_a: return A;
		case SDLK_b: return B;
		case SDLK_c: return C;
		case SDLK_d: return D;
		case SDLK_e: return E;
		case SDLK_f: return F;
		case SDLK_g: return G;
		case SDLK_h: return H;
		case SDLK_i: return I;
		case SDLK_j: return J;
		case SDLK_k: return K;
		case SDLK_l: return L;
		case SDLK_m: return M;
		case SDLK_n: return N;
		case SDLK_o: return O;
		case SDLK_p: return P;
		case SDLK_q: return Q;
		case SDLK_r: return R;
		case SDLK_s: return S;
		case SDLK_t: return T;
		case SDLK_u: return U;
		case SDLK_v: return V;
		case SDLK_w: return W;
		case SDLK_x: return X;
		case SDLK_y: return Y;
		case SDLK_z: return Z;
		case SDLK_UP: return UpArrow;
		case SDLK_DOWN: return DownArrow;
		case SDLK_LEFT: return LeftArrow;
		case SDLK_RIGHT: return RightArrow;
		case SDLK_SPACE: return Space;
		case SDLK_RETURN: return Enter;
		case SDLK_ESCAPE: return Escape;
	}
	return UNKNOWN;	//No key found
}

int Input::FoundKey(std::vector<Input::KeyCode>* list, Input::KeyCode key) {
	//std::cout << "List size: " << list->size() << '\n';
	for (int i = 0; i < list->size(); i++) {
		if (list->at(i) == key) return i;
	}
	return -1;
}

bool Input::CheckButton(bool arr[3], int button) {
	if (button < 0 || button >= 3) return false;
	return arr[button];
}

void Input::BeginInput() {
	m_KeysPressedThisFrame.clear();
	m_KeysReleasedThisFrame.clear();
	for (int i = 0; i < 3; i++) {
		m_MouseButtonsPressedThisFrame[i] = false;
		m_MouseButtonsReleasedThisFrame[i] = false;
	}
}

void Input::AddKeyPressed(SDL_Keycode key) {
	if (Input::FoundKey(&m_CurrentInput, Input::SDLToKeyCode(key)) == -1) {
		//std::cout << "Key pressed: " << Input::SDLToKeyCode(key) << '\n';
		m_KeysPressedThisFrame.push_back(Input::SDLToKeyCode(key));
		m_CurrentInput.push_back(Input::SDLToKeyCode(key));
	}
}

void Input::AddKeyReleased(SDL_Keycode key) {
	//std::cout << "Key released: " << Input::SDLToKeyCode(key) << '\n';
	m_KeysReleasedThisFrame.push_back(Input::SDLToKeyCode(key));
	int currentIndex = Input::FoundKey(&m_CurrentInput, Input::SDLToKeyCode(key));
	if (currentIndex != -1) m_CurrentInput.erase(m_CurrentInput.begin() + currentIndex);
}

void Input::AddMouseButton(int button) {
	button -= 1;
	if (button >= 0 && button < 3) {
		//std::cout << "Pressed mouse button " << button << '\n';
		m_MouseButtonsHeld[button] = true;
		m_MouseButtonsPressedThisFrame[button] = true;
	}
}

void Input::RemoveMouseButton(int button) {
	button -= 1;
	if (button >= 0 && button < 3) {
		//std::cout << "Released mouse button " << button << '\n';
		m_MouseButtonsReleasedThisFrame[button] = true;
		m_MouseButtonsHeld[button] = false;
	}
}

void Input::SetMousePosition(Vector2 pos) {
	m_MousePos = pos;
}

bool Input::GetKey(KeyCode key)
{
	return Input::FoundKey(&m_CurrentInput, key) != -1 ? true : false;
}

bool Input::GetKeyDown(KeyCode key)
{
	return Input::FoundKey(&m_KeysPressedThisFrame, key) != -1 ? true : false;
}

bool Input::GetKeyUp(KeyCode key)
{
	return Input::FoundKey(&m_KeysReleasedThisFrame, key) != -1 ? true : false;
}

bool Input::AnyKey()
{
	return m_CurrentInput.size() > 0;
}

bool Input::GetMouseButton(int button)
{
	return CheckButton(m_MouseButtonsHeld, button);
}

bool Input::GetMouseButtonDown(int button)
{
	return CheckButton(m_MouseButtonsPressedThisFrame, button);
}

bool Input::GetMouseButtonUp(int button)
{
	return CheckButton(m_MouseButtonsReleasedThisFrame, button);
}

Vector2 Input::GetMousePosition()
{
	return m_MousePos;
}
