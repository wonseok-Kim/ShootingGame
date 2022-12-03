#pragma once

struct Title {
	char screen[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
};

void title_Input();

void title_Update(bool* out_bGameLoop);

void title_Render();