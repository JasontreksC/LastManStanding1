#pragma once
#include "BaseObject.h"

class UI : public BaseObject
{
public:
	UI* parentUI;
	vector<pair<wstring, UI*>> childUI;

	void AddChild(wstring _uiName, UI& newChild);
	void FollowParent();

	bool isCursorOn(HWND _hWnd);
	void SetChildsVertical();
	void MakeLonger();
};

