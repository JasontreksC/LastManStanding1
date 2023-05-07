#include "pch.h"
#include "UI.h"

void UI::AddChild(wstring _uiName,UI& newChild)
{
	childUI.push_back(make_pair(_uiName, &newChild));
	newChild.parentUI = this;
}

void UI::FollowParent()
{
	if (parentUI != nullptr)
	{
		for (int i = 0; i < 6; ++i)
		{
			this->vertexList[i].p.v[0] = parentUI->vertexList[i].p.v[0];
		}
	}
}

bool UI::isCursorOn(HWND _hWnd)
{
	RECT wndRect;
	GetClientRect(_hWnd, &wndRect);

	POINT cursorPos;
	float NDCcursorX;
	float NDCcursorY;
	GetCursorPos(&cursorPos);

	ScreenToClient(_hWnd, &cursorPos);

	NDCcursorX = ((float)cursorPos.x - (wndRect.right / 2)) / (wndRect.right / 2) * 1.0f;
	NDCcursorY = ((float)cursorPos.y - (wndRect.bottom / 2)) / (wndRect.bottom / 2) * -1.0f;


	if (this->GetLeftPosX() < NDCcursorX && NDCcursorX < this->GetRightPosX())
		if (this->GetBottomPosY() < NDCcursorY && NDCcursorY < this->GetTopPosY())
			return true;
	

	return false;
}

void UI::SetChildsVertical()
{
	for (auto iter = childUI.begin(); iter != childUI.end(); ++iter)
	{
		if (iter == childUI.begin())
		{
			while (iter->second->GetTopPosY() < 1.0f)
			{
				for (int i = 0; i < 6; ++i)
				{
					iter->second->vertexList[i].p.v[1] += 0.033f;
				}
			}

		}
		else
		{
			if (iter->second->GetTopPosY() < (iter - 1)->second->GetBottomPosY())
			{
				while (iter->second->GetTopPosY() < (iter - 1)->second->GetBottomPosY())
				{
					for (int i = 0; i < 6; ++i)
						iter->second->vertexList[i].p.v[1] += 0.033f;
				}
			}
			else if (iter->second->GetTopPosY() > (iter - 1)->second->GetBottomPosY())
			{
				while (iter->second->GetTopPosY() > (iter - 1)->second->GetBottomPosY())
				{
					for (int i = 0; i < 6; ++i)
						iter->second->vertexList[i].p.v[1] -= 0.033f;
				}
			}
			
		}
		iter->second->FollowParent();

		if (iter == childUI.end())
			break;
	}
}

void UI::MakeLonger()
{
	this->vertexList[0].p.v[1] += 0.5f;
	this->vertexList[1].p.v[1] += 0.5f;
	this->vertexList[2].p.v[1] -= 0.5f;
	this->vertexList[3].p.v[1] -= 0.5f;
	this->vertexList[4].p.v[1] += 0.5f;
	this->vertexList[5].p.v[1] -= 0.5f;
}
