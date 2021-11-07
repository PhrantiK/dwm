/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 3;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int swallowfloating         = 1;   /* 1 means swallow floating windows by default */
static const unsigned int gappih         = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 20;  /* vert inner gap between windows */
static const unsigned int gappoh         = 20;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 20;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int usealtbar               = 0;        /* 1 means use non-dwm status bar */
static const char *altbarclass           = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd             = "$HOME/bar.sh"; /* Alternate bar launch command */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int vertpad                 = 20;  /* Padding above bar */
static const int sidepad                 = 20;  /* Padding sides bar */
static int floatposgrid_x                = 5;  /* float grid columns */
static int floatposgrid_y                = 5;  /* float grid rows */
static const char slopspawnstyle[]       = "-t 0 -c 0.92,0.85,0.69,0.3 -o"; /* do NOT define -f (format) here */
static const char slopresizestyle[]      = "-t 0 -c 0.92,0.85,0.69,0.3"; /* do NOT define -f (format) here */
static const int riodraw_borders         = 0;  /* 0 or 1, indicates whether the area drawn using slop includes the window borders */
static const int riodraw_matchpid        = 1;  /* 0 or 1, indicates whether to match the PID of the client that was spawned with riospawn */
static const int horizpadbar             = 5;   /* horizontal padding for statusbar */
static const int vertpadbar              = 15;   /* vertical padding for statusbar */
static const char buttonbar[]            = " ";
/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_PLUS_AND_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;

static int fakefsindicatortype           = INDICATOR_PLUS;
static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE;
static const char *fonts[]          = { "CatV_6x12_9 Nerd Font:style=Normal:size=12",
                                        /* "Material Icons:style=Regular:size=12", */
                                      };
static const char dmenufont[]            = "monospace:size=10";

static const int tagschemes[] = {
        SchemeTag1, SchemeTag2, SchemeTag3,
        SchemeTag4, SchemeTag5, SchemeTag6,
        SchemeTag7, SchemeTag8, SchemeTag9,
        SchemeTag10
};

static char col_bg[]               = "#111111";
static char col_bg2[]              = "#24283b";
static char col_gray2[]            = "#414868";
static char col_gray3[]            = "#565f89";
static char col_fg[]               = "#c0caf5";
static char col_magenta[]          = "#bb9af7";
static char col_red[]              = "#f7768e";
static char col_green[]            = "#73daca";
static char col_blue[]             = "#7aa2f7";
static char col_yellow[]           = "#e0af68";
static char col_cyan[]             = "#7dcfff";

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3] = {
	/*                       fg      bg        border     */
	[SchemeNorm]         = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]          = { OPAQUE, baralpha, borderalpha },
};

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { col_fg,        col_bg,      col_gray3,      col_gray3 },
	[SchemeSel]          = { col_fg,       col_bg2,       col_cyan,       col_cyan },
	[SchemeScratchNorm]  = { col_gray2,       col_bg,       col_cyan,       col_cyan },
	[SchemeScratchSel]   = { col_gray2,       col_bg,       col_magenta,       col_magenta },
	[SchemeTag1]         = { col_magenta,    col_bg,  col_bg,  col_gray3 },
	[SchemeTag2]         = { col_green,    col_bg,  col_gray3,  col_gray3 },
	[SchemeTag3]         = { col_blue,    col_bg,  col_gray3,  col_gray3 },
	[SchemeTag4]         = { col_cyan,    col_bg,  col_gray3,  col_gray3 },
	[SchemeTag5]         = { col_yellow,    col_bg,  col_gray3,  col_gray3 },
	[SchemeTag6]         = { col_magenta,  col_bg,  col_gray3,  col_gray3 },
	[SchemeTag7]         = { col_green,    col_bg,  col_gray3,  col_gray3 },
	[SchemeTag8]         = { col_blue,     col_bg,  col_gray3,  col_gray3 },
	[SchemeTag9]         = { col_cyan,     col_bg,  col_gray3,  col_gray3 },
	[SchemeTag10]        = { col_yellow,   col_bg,  col_gray3,  col_gray3 },
	[SchemeUrg]          = { col_fg,       col_bg,       col_red,       col_magenta },
};


static const char *layoutmenu_cmd = "layoutmenu.sh";

static const char *const autostart[] = {
	"dwmblocks", NULL,
	"pulse_daemon.sh", NULL,
	"picom", NULL,
	NULL /* terminate */
};

static char *tagicons[][NUMTAGS*2] = {
	[DEFAULT_TAGS]        = { "", "", "ﱦ", "", "", "廓", "喝", "", "", "" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)

	{.class = "kitty", .isterminal = 1},
	{.class = "Xephyr", .noswallow = 1},

        // Scratchpads
	{.title = "Scratchpad [a]", .isterminal = 1, .isfloating = 1, .floatpos = "50% 50% 50% 65%", .scratchkey = 'a'},
	{.title = "Scratchpad [s]", .isterminal = 1, .isfloating = 1, .floatpos = "22% 77% 40% 40%", .scratchkey = 's'},
	{.title = "Scratchpad [d]", .isterminal = 1, .isfloating = 1, .floatpos = "50% 50% 75% 85%", .scratchkey = 'd'},
};

static const MonitorRule monrules[] = {
	/* monitor  tag   layout  mfact  nmaster  showbar  topbar */
	{  1,       -1,   2,      -1,    -1,      -1,      -1     }, // use a different layout for the second monitor
	{  -1,      -1,   0,      -1,    -1,      -1,      -1     }, // default
};


/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor  bar    alignment         widthfunc                drawfunc                clickfunc                name */
	{ -1,       0,     BAR_ALIGN_LEFT,   width_stbutton,          draw_stbutton,          click_stbutton,          "statusbutton" },
	{ -1,       0,     BAR_ALIGN_LEFT,   width_tags,              draw_tags,              click_tags,              "tags" },
	{ -1,       0,     BAR_ALIGN_LEFT,   width_ltsymbol,          draw_ltsymbol,          click_ltsymbol,          "layout" },
	{ 'A',      0,     BAR_ALIGN_RIGHT,  width_status2d,          draw_status2d,          click_statuscmd,         "status2d" },
	{ -1,       0,     BAR_ALIGN_NONE,   width_wintitle,          draw_wintitle,          click_wintitle,          "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */


/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */
/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ "|||",      col },
	{ "[D]",      deck },
	{ "[\\]",     dwindle },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};


/* key definitions */
#define MODKEY Mod3Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ControlMask,  KEY,      tagprevmon,     {.ui = 1 << TAG} },


#define SCRATCHKEYS(KEY,CMD) \
	{ MODKEY,                      KEY,      togglescratch,     {.v = CMD } }, \
	{ MODKEY|ControlMask,                 KEY,      setscratch,        {.v = CMD } }, \
	{ MODKEY|ControlMask|ShiftMask,           KEY,      removescratch,     {.v = CMD } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_red, "-sf", col_bg, NULL };
static const char *roficmd[] = {
	"rofi",
	"-show",
	"drun",
	NULL
};
static const char *termcmd[]  = { "kitty", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchcmd1[] = {"a", "kitty", "--title", "Scratchpad [a]", NULL};
static const char *scratchcmd2[] = {"s", "kitty", "--title", "Scratchpad [s]", NULL};
static const char *scratchcmd3[] = {"d", "kitty", "--title", "Scratchpad [d]", NULL};

/* This defines the name of the executable that handles the bar (used for signalling purposes) */
#define STATUSBAR "dwmblocks"


static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_space,      spawn,                  {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_space,      spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_p,          spawn,                  SHCMD("prompt.sh") },
	{ MODKEY|ControlMask,           XK_p,          riospawnsync,           {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_Return,     riospawn,               {.v = termcmd } },
	/* { MODKEY,                       XK_s,          rioresize,              {0} }, */
        SCRATCHKEYS(                    XK_a,                                  scratchcmd1)
        SCRATCHKEYS(                    XK_s,                                  scratchcmd2)
        SCRATCHKEYS(                    XK_d,                                  scratchcmd3)
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_Left,       focusdir,               {.i = 0 } }, // left
	{ MODKEY,                       XK_Right,      focusdir,               {.i = 1 } }, // right
	{ MODKEY,                       XK_Up,         focusdir,               {.i = 2 } }, // up
	{ MODKEY,                       XK_Down,       focusdir,               {.i = 3 } }, // down
	{ MODKEY,                       XK_s,          swapfocus,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_j,          rotatestack,            {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_k,          rotatestack,            {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_j,          inplacerotate,          {.i = +2 } }, // same as rotatestack
	{ MODKEY|Mod1Mask,              XK_k,          inplacerotate,          {.i = -2 } }, // same as reotatestack
	{ MODKEY|Mod1Mask|ShiftMask,    XK_j,          inplacerotate,          {.i = +1} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_k,          inplacerotate,          {.i = -1} },
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	/* { MODKEY,                       XK_d,          incnmaster,             {.i = -1 } }, */
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,          setcfact,               {0} },
	{ MODKEY|Mod1Mask,              XK_Down,       moveresize,             {.v = "0x 25y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_Up,         moveresize,             {.v = "0x -25y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_Right,      moveresize,             {.v = "25x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_Left,       moveresize,             {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_Down,       moveresize,             {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_Up,         moveresize,             {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_Right,      moveresize,             {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_Left,       moveresize,             {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_u,          incrgaps,               {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,          incrigaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,          incrogaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,             {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY|Mod1Mask,              XK_Tab,        shiftviewclients,       { .i = -1 } },
	{ MODKEY|Mod1Mask,              XK_backslash,  shiftviewclients,       { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_c,          killclient,             {0} },
	{ MODKEY,                       XK_r,          self_restart,           {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {1} },
	{ MODKEY|ShiftMask,             XK_F5,         xrdb,                   {.v = NULL } },
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,          setlayout,              {.v = &layouts[3]} },
	{ MODKEY,                       XK_p,          setlayout,              {0} },
	{ MODKEY|ControlMask,           XK_f,          togglefloating,         {0} },
	{ MODKEY,                       XK_y,          togglefullscreen,       {0} },
	{ MODKEY|ShiftMask,             XK_y,          togglefakefullscreen,   {0} },
	{ MODKEY|ShiftMask,             XK_f,          fullscreen,             {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,           {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	{ MODKEY,                       XK_n,          togglealttag,           {0} },
        { MODKEY|ShiftMask,             XK_m,          spawn,                  SHCMD("~/.config/rofi/scripts/layout_switcher.sh")},
	/* Note that due to key limitations the below example kybindings are defined with a Mod3Mask,
	 * which is not always readily available. Refer to the patch wiki for more details. */
	/* Client position is limited to monitor window area */
	/* { Mod3Mask,                     XK_u,            floatpos,               {.v = "-26x -26y" } }, // ↖ */
	/* { Mod3Mask,                     XK_i,            floatpos,               {.v = "  0x -26y" } }, // ↑ */
	/* { Mod3Mask,                     XK_o,            floatpos,               {.v = " 26x -26y" } }, // ↗ */
	/* { Mod3Mask,                     XK_j,            floatpos,               {.v = "-26x   0y" } }, // ← */
	/* { Mod3Mask,                     XK_l,            floatpos,               {.v = " 26x   0y" } }, // → */
	/* { Mod3Mask,                     XK_m,            floatpos,               {.v = "-26x  26y" } }, // ↙ */
	/* { Mod3Mask,                     XK_comma,        floatpos,               {.v = "  0x  26y" } }, // ↓ */
	/* { Mod3Mask,                     XK_period,       floatpos,               {.v = " 26x  26y" } }, // ↘ */
	/* Absolute positioning (allows moving windows between monitors) */
	/* { Mod3Mask|ControlMask,         XK_u,            floatpos,               {.v = "-26a -26a" } }, // ↖ */
	/* { Mod3Mask|ControlMask,         XK_i,            floatpos,               {.v = "  0a -26a" } }, // ↑ */
	/* { Mod3Mask|ControlMask,         XK_o,            floatpos,               {.v = " 26a -26a" } }, // ↗ */
	/* { Mod3Mask|ControlMask,         XK_j,            floatpos,               {.v = "-26a   0a" } }, // ← */
	/* { Mod3Mask|ControlMask,         XK_l,            floatpos,               {.v = " 26a   0a" } }, // → */
	/* { Mod3Mask|ControlMask,         XK_m,            floatpos,               {.v = "-26a  26a" } }, // ↙ */
	/* { Mod3Mask|ControlMask,         XK_comma,        floatpos,               {.v = "  0a  26a" } }, // ↓ */
	/* { Mod3Mask|ControlMask,         XK_period,       floatpos,               {.v = " 26a  26a" } }, // ↘ */
	/* Resize client, client center position is fixed which means that client expands in all directions */
	/* { Mod3Mask|ShiftMask,           XK_u,            floatpos,               {.v = "-26w -26h" } }, // ↖ */
	/* { Mod3Mask|ShiftMask,           XK_i,            floatpos,               {.v = "  0w -26h" } }, // ↑ */
	/* { Mod3Mask|ShiftMask,           XK_o,            floatpos,               {.v = " 26w -26h" } }, // ↗ */
	/* { Mod3Mask|ShiftMask,           XK_j,            floatpos,               {.v = "-26w   0h" } }, // ← */
	/* { Mod3Mask|ShiftMask,           XK_k,            floatpos,               {.v = "800W 800H" } }, // · */
	/* { Mod3Mask|ShiftMask,           XK_l,            floatpos,               {.v = " 26w   0h" } }, // → */
	/* { Mod3Mask|ShiftMask,           XK_m,            floatpos,               {.v = "-26w  26h" } }, // ↙ */
	/* { Mod3Mask|ShiftMask,           XK_comma,        floatpos,               {.v = "  0w  26h" } }, // ↓ */
	/* { Mod3Mask|ShiftMask,           XK_period,       floatpos,               {.v = " 26w  26h" } }, // ↘ */
	/* Client is positioned in a floating grid, movement is relative to client's current position */
	/* { Mod3Mask|Mod1Mask,            XK_u,            floatpos,               {.v = "-1p -1p" } }, // ↖ */
	/* { Mod3Mask|Mod1Mask,            XK_i,            floatpos,               {.v = " 0p -1p" } }, // ↑ */
	/* { Mod3Mask|Mod1Mask,            XK_o,            floatpos,               {.v = " 1p -1p" } }, // ↗ */
	/* { Mod3Mask|Mod1Mask,            XK_j,            floatpos,               {.v = "-1p  0p" } }, // ← */
	/* { Mod3Mask|Mod1Mask,            XK_k,            floatpos,               {.v = " 0p  0p" } }, // · */
	/* { Mod3Mask|Mod1Mask,            XK_l,            floatpos,               {.v = " 1p  0p" } }, // → */
	/* { Mod3Mask|Mod1Mask,            XK_m,            floatpos,               {.v = "-1p  1p" } }, // ↙ */
	/* { Mod3Mask|Mod1Mask,            XK_comma,        floatpos,               {.v = " 0p  1p" } }, // ↓ */
	/* { Mod3Mask|Mod1Mask,            XK_period,       floatpos,               {.v = " 1p  1p" } }, // ↘ */
	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     cyclelayout,            {.i = +1 } },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkButton,            0,                   Button1,        spawn,          {.v = dmenucmd } },
	{ ClkButton,            0,                   Button2,        self_restart,           {0} },
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	/* { ClkLtSymbol,          0,                   Button3,        layoutmenu,     {0} }, */
	{ ClkLtSymbol,          0,                   Button3,        spawn,          SHCMD("layoutmenu.sh") },
	{ ClkWinTitle,          0,                   Button3,        spawn,          SHCMD("clientmenu.sh") },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigstatusbar,   {.i = 1 } },
	{ ClkStatusText,        0,                   Button2,        sigstatusbar,   {.i = 2 } },
	{ ClkStatusText,        0,                   Button3,        sigstatusbar,   {.i = 3 } },
        { ClkRootWin,           0,                   Button3,        spawn,          SHCMD("rootmenu.sh") },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,              Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,              Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,              Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,              Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,              Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button3,        dragcfact,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button1,        dragmfact,      {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};


static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
	IPCCOMMAND( focusmon, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( focusstack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incnmaster, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( killclient, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( quit, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setlayoutsafe, 1, {ARG_TYPE_PTR} ),
        IPCCOMMAND( setlayoutex, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( setmfact, 1, {ARG_TYPE_FLOAT} ),
	IPCCOMMAND( setstatus, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( tag, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( tagmon, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( togglebar, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( togglefloating, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( toggletag, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( toggleview, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( view, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( zoom, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( togglealttag, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setcfact, 1, {ARG_TYPE_FLOAT} ),
	IPCCOMMAND( cyclelayout, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglefakefullscreen, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( floatpos, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( fullscreen, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( inplacerotate, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( moveresize, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( rioresize, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( rotatestack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( self_restart, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( shiftviewclients, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglesticky, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( swapfocus, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( tagnextmonex, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( tagprevmonex, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( togglefullscreen, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( incrgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrigaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrogaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrihgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrivgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrohgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrovgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglegaps, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( defaultgaps, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setgapsex, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( xrdb, 1, {ARG_TYPE_NONE} ),
};

