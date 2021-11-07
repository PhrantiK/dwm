//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	/* {"", "dwm_network",					5,		1}, */
	{"", "dwm_cpu_temp",				        5,		8},
	/* {"", "dwm_traffic",					4,		2}, */
	/* {"", "dwm_updates",					300,		3}, */
	{"", "dwm_volume",					0,		4},
	{"", "dwm_memory",					5,		5},
	{"", "dwm_date",					60,		6},
	{"", "dwm_clock",					60,		7},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "  ";
static unsigned int delimLen = 5;
