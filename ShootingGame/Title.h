#pragma once

struct Title {
	char screen[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];
	int nMenus;
	COORD* pMenuCoordList;
};
