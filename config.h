/* border */
static const unsigned int borderpx  = 3;                 /* border pixel of windows */
static const unsigned int snap      = 10;                /* snap pixel */

/* system tray */
static const unsigned int systraypinning = 0;            /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const int          systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int          showsystray = 1;               /* 0 means no systray */

/* gaps */
static const unsigned int gappih = 5;                    /* horiz inner gap between windows */
static const unsigned int gappiv = 5;                    /* vert inner gap between windows */
static const unsigned int gappoh = 5;                    /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 5;                    /* vert outer gap between windows and screen edge */
static       int          smartgaps = 1;                 /* 1 means no outer gap when there is only one window */

/* bar */
static const int          showbar = 1;                   /* 0 means no bar */
static const int          topbar = 1;                    /* 0 means bottom bar */

/* fonts */
static const char        *fonts[]     = { "JetBrainsMono Nerd Font:size=10:style=Bold" };

/* colors */ 
static const char accent[]          = "#758c9f";
static const char text[]            = "#b6b6b6";
static const char unf[]             = "#212121";
static const char base[]            = "#141414";

static const char green[]           = "#b6bc7a";
static const char red[]             = "#de4c4c";
static const char blue[]            = "#8ca7bd";
static const char yellow[]          = "#f3ce86";

/* color schemes */
enum { SchemeNorm, SchemeSel, Red, Green, Blue, Yellow };

static const char *colors[][3]      = {
	/*               fg       bg        border   */
	[SchemeNorm] = { text,    base,     unf     },
	[SchemeSel]  = { base, 	  accent,   accent  },	
	[Red]        = { red,     base },
	[Green]      = { green,   base },
	[Blue]       = { blue,    base },
	[Yellow]     = { yellow,  base },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int taglayouts[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance                    title		tags mask     isfloating   monitor	isgame */
	{ "steam_app",         NULL,                       NULL,		1 << 1,       0,           -1,		1 },
	{ "cs2",               NULL,                       NULL,		1 << 1,       0,           -1,		1 },
	{ "Minecraft 1.8.9",   NULL,                       NULL,		1 << 1,       0,           -1 },
	{ "tf_linux64",        NULL,                       NULL,		1 << 1,       0,           -1 },
	{ "hl2_linux",         NULL,                       NULL,		1 << 1,       0,           -1 },
	{ "Unturned.x86_64",   NULL,                       NULL,		1 << 1,       0,           -1 },
	{ "Lutris",            NULL,                       NULL,		1 << 2,       0,           -1 },
	{ "melonDS",           NULL,                       NULL,		1 << 2,       0,           -1 },
	{ NULL,                "steamwebhelper",           NULL,		1 << 3,       0,           -1 },
	{ NULL,                NULL,                      "cmus",	    1 << 4,       0,           -1 },
	{ "discord",           NULL,                       NULL,		1 << 3,       0,           -1 },
	{ "Signal",            "signal",                   NULL,		1 << 3,       0,           -1 },
};

/* layout(s) */
#define DEFAULT_MFACT 0.50
static const float mfact = DEFAULT_MFACT;                /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;                            /* number of clients in master area */
static const int resizehints = 0;                        /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;                     /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;                      /* refresh rate (per second) for client move/resize */

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                                /* first entry is default */
	{ "[M]",      monocle },
	{ ":::",      gaplessgrid },
	{ "###",      nrowgrid },
	{ "|M|",      centeredmaster },
	{ "><>",      NULL },                                /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]   = { "st", NULL };
static const char *lockcmd[]   = { "slock", NULL };
static const char *forcekillcmd[] = { "xdotool", "getwindowfocus", "windowkill", NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"

static const Key keys[] = {
	/* modifier                     key                        function        argument */

	/* app binds */
	{ MODKEY,                       XK_F1,                     spawn,          SHCMD("firefox") },
	{ MODKEY,                       XK_F2,                     spawn,          SHCMD("torbrowser-launcher") },
	{ MODKEY,                       XK_F3,                     spawn,          SHCMD("st -e yazi") },
	{ MODKEY,                       XK_F4,                     spawn,          SHCMD("keepassxc") },
	{ MODKEY,                       XK_F5,                     spawn,          SHCMD("st -e cmus") },
	{ MODKEY,                       XK_F6,                     spawn,          SHCMD("st -e btop") },
	{ MODKEY,                       XK_F7,                     spawn,          SHCMD("st -e htop") },

	/* rofi & dmenu binds */
	{ MODKEY,                       XK_c,                      spawn,          SHCMD("rofi -show drun -config ~/.config/rofi/drun.rasi") },
	{ MODKEY|ShiftMask,             XK_c,                      spawn,          SHCMD("rofi -show window -config ~/.config/rofi/window.rasi") },
	{ MODKEY|ShiftMask,             XK_e,                      spawn,          SHCMD("~/.config/scripts/powermenu") },
	{ MODKEY|ControlMask,           XK_c,                      spawn,          SHCMD("rofi -modi emoji -show emoji -emoji-format '{emoji} {name}' -config ~/.config/rofi/emoji.rasi") },

	/* volume binds */
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5% ; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5% ; kill -36 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioMute,          spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle ; kill -36 $(pidof dwmblocks)") },

	/* brightness binds */
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          SHCMD("xbacklight -inc 10") },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          SHCMD("xbacklight -dec 10") },
	
	/* player ctl binds */
	{ MODKEY|ControlMask,           XK_space,                  spawn,          SHCMD("playerctl --player=cmus play-pause") },
	{ MODKEY|ControlMask,           XK_a,                      spawn,          SHCMD("playerctl --player=cmus previous") },
	{ MODKEY|ControlMask,           XK_d,                      spawn,          SHCMD("playerctl --player=cmus next") },
	{ MODKEY|ControlMask,           XK_w,                      spawn,          SHCMD("playerctl --player=cmus volume 0.1+") },
	{ MODKEY|ControlMask,           XK_s,                      spawn,          SHCMD("playerctl --player=cmus volume 0.1-") },

	{ 0,                            XF86XK_AudioPlay,          spawn,          SHCMD("playerctl  play-pause") },
	{ 0,                            XF86XK_AudioPrev,          spawn,          SHCMD("playerctl  previous") },
	{ 0,                            XF86XK_AudioNext,          spawn,          SHCMD("playerctl  next") },

	/* screenshot binds */
	{ MODKEY,                       XK_Print,                  spawn,          SHCMD("~/.config/scripts/ss-full-clip") },
	{ MODKEY|ShiftMask,             XK_Print,                  spawn,          SHCMD("~/.config/scripts/ss-crop-drive") },
	{ MODKEY|ControlMask|ShiftMask, XK_Print,                  spawn,          SHCMD("~/.config/scripts/ss-full-drive") },
	{ 0,                            XK_Print,                  spawn,          SHCMD("~/.config/scripts/ss-crop-clip") },

	/* switch keyboard */
	{ MODKEY2,                      XK_Shift_L,                spawn,          SHCMD("~/.config/scripts/kbswitch") },

	/* command spawning */
	{ MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,                  spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_l,                      spawn,          {.v = lockcmd } },

	/* toggle bar &/ border */
	{ MODKEY,                       XK_b,                      togglebar,      {0} },

	/* layout focus */
	{ MODKEY,                       XK_s,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_w,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Tab,                    focusmaster,    {0} },

	/* layout movement */
	{ MODKEY|ShiftMask,             XK_Return,                 zoom,           {0} },
	{ MODKEY,                       XK_d,                      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_a,                      movestack,      {.i = -1 } },

	/* nmaster +/- 1 */
	{ MODKEY,                       XK_z,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_x,                      incnmaster,     {.i = -1 } },

	/* reset nmaster to default */
	{ MODKEY|ShiftMask,             XK_x,                      resetnmaster,   {0} },

	/* resize windows horizontally */
	{ MODKEY|ShiftMask,             XK_d,                      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_a,                      setmfact,       {.f = -0.05} },

	/* resize windows vertically */
	{ MODKEY|ShiftMask,             XK_w,                      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_s,                      setcfact,       {.f = -0.25} },

	/* reset window size */
	{ MODKEY|ShiftMask,             XK_f,                      setmfact,       {.f = -1.00} },
	{ MODKEY|ShiftMask,             XK_g,                      setcfact,       {.f =  0.00} },

	/*gap management */
	{ MODKEY,                       XK_bracketright,           incrgaps,       {.i = +5 } },
	{ MODKEY,                       XK_bracketleft,            incrgaps,       {.i = -5 } },
	{ MODKEY|ControlMask,           XK_bracketright,           incrigaps,      {.i = +5 } },
	{ MODKEY|ControlMask,           XK_bracketleft,            incrigaps,      {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_bracketright,           incrogaps,      {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,            incrogaps,      {.i = -5 } },
	{ MODKEY|ControlMask,           XK_KP_Down,                incrihgaps,     {.i = -5 } },
	{ MODKEY|ControlMask,           XK_KP_Up,                  incrihgaps,     {.i = +5 } },
	{ MODKEY|ControlMask,           XK_KP_Right,               incrivgaps,     {.i = +5 } },
	{ MODKEY|ControlMask,           XK_KP_Left,                incrivgaps,     {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_KP_Up,                  incrohgaps,     {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_KP_Down,                incrohgaps,     {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_KP_Right,               incrovgaps,     {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_KP_Left,                incrovgaps,     {.i = -5 } },
	{ MODKEY,                       XK_g,                      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,                      defaultgaps,    {0} },

	/* restartsig bind */
	{ MODKEY|ShiftMask,             XK_r,                      quit,           {1} }, 

	/* client killing */
	{ MODKEY|ShiftMask,             XK_q,                      killclient,     {0} },
	{ MODKEY2,                      XK_F4,                     spawn,          {.v = forcekillcmd } },
	{ MODKEY|ControlMask,           XK_q,                      killclient,     {.ui = 1} },  // kill unselected
	{ MODKEY|ShiftMask|ControlMask, XK_q,                      killclient,     {.ui = 2} },  // killall

	/* kill dwm */
	{ MODKEY|ShiftMask,             XK_p,                      quit,           {0} },

	/* layout management */
	{ MODKEY,                       XK_q,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_y,                      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_u,                      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_minus,                  cyclelayout,    {.i = -1 } },
	{ MODKEY,                       XK_equal,                  cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_f,                      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_space,                  movecenter,     {0} },
	{ MODKEY|ShiftMask,             XK_t,                      togglealwaysontop, {0} },

	/* move and resize floating windows with arrow keys */
	{ MODKEY,                       XK_Down,                   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,                     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,                  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,                   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,                   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,                     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,                  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,                   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,                     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,                   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,                   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,                  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,                     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,                   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,                   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,                  moveresizeedge, {.v = "R"} },

	/* sticky window */
	{ MODKEY|ControlMask,           XK_0,                      togglesticky,   {0} },

	/* tag management */
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_r,                      quit,           {1} },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[5]} },
	{ ClkLtSymbol,          0,              Button4,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,    {.i = +1 } },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = -1 } },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = +1 } },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
