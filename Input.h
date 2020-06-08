#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "Vector2.h"
#include <vector>

class Input {
public:
	//Input();
	//~Input();

	//An enum of every keycode (still not complete but more than enough for this game)
	enum KeyCode{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
					LeftArrow, RightArrow, UpArrow, DownArrow,
					Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
					Space, Enter, Escape,
					UNKNOWN};

	void BeginInput();							//Begin input detection
	void AddKeyPressed(SDL_Keycode key);		//Add the keys pressed this frame
	void AddKeyReleased(SDL_Keycode key);		//Add the keys released this frame
	void AddMouseButton(int button);			//Add the mouse button that was pressed this frame
	void RemoveMouseButton(int button);			//Remove the mouse button that was released this frame
	void SetMousePosition(Vector2 pos);			//Set the mouse position (in screen coordinates)

	static bool GetKey(KeyCode key);			//A key is held down
	static bool GetKeyDown(KeyCode key);		//A key was pressed this frame
	static bool GetKeyUp(KeyCode key);			//A key was released this frame
	static bool AnyKey();						//Any key is currently held down

	static bool GetMouseButton(int button);		//A mouse button is held down
	static bool GetMouseButtonDown(int button);	//A mouse button was pressed this frame
	static bool GetMouseButtonUp(int button);	//A mouse button was released this frame

	static Vector2 GetMousePosition();			//Get the position of the mouse on the screen

private:
	static std::vector<KeyCode> m_CurrentInput;				//All the keys that are currently held down
	static std::vector<KeyCode> m_KeysPressedThisFrame;		//All the keys that were pressed this frame
	static std::vector<KeyCode> m_KeysReleasedThisFrame;	//All the keys that were released this frame

	static bool m_MouseButtonsHeld[3];						//The mouse buttons currently held down
	static bool m_MouseButtonsPressedThisFrame[3];			//The mouse buttons pressed this frame
	static bool m_MouseButtonsReleasedThisFrame[3];			//The mouse buttons that were released this frame
	
	static KeyCode SDLToKeyCode(SDL_Keycode key);			//Convert an SDL_Keycode to this KeyCode
	static SDL_Keycode KeyCodeToSDL(KeyCode key);			//Convert KeyCode to SDL_Keycode

	static Vector2 m_MousePos;								//The position of the mouse (in screen coordinates)

	static int FoundKey(std::vector<KeyCode>* list, KeyCode key);	//Check if key is found in the vector list
	static bool CheckButton(bool arr[3], int button);				//Check a mouse button's state
};
#endif // !INPUT_H
