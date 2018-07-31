/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

class LoaderScene final :
	public con::Scene
{
public:
	void onPush() override;

private:
	void validateSettings();
	void updateWindow();
	void loadTextures();
	void loadFont();
	void loadSound();
};