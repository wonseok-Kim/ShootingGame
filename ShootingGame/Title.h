#pragma once

struct Title {
	char screen[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};

void title_Input();

void title_Update();

void title_Render();