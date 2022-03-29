/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 9;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 25;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "FantasqueSansMono Nerd Font:size=13" };
static const char dmenufont[]       = "FantasqueSansMono Nerd Font:size=14";
static const char col_gray1[]       = "#0f0f17";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bfc9db";
static const char col_gray4[]       = "#0f0f17";
static const char col_cyan[]        = "#a1bdce";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	"xsetroot", "-cursor_name", "GoogleDot-Black", NULL,
	"flameshot", NULL,
	"nitrogen", "--restore", NULL,
	"picom", "--experimental-backends", "--config", "/home/katsuki/.config/picom.conf", NULL,
	"dunst", NULL,
	"xrdb", "/home/katsuki/.Xresources_dark", NULL,
	"lxappearance", NULL,
	"slstatus", NULL,
	"sh", "/home/katsuki/slstuff/dwm/kbsw", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       2,		    0,           -1 },
	{ "Lxappearance", NULL,	  NULL,		  1 << 7,			0,			 -1 },
	{ "Clementine", NULL,	  NULL,		  1 << 6,			0,			 -1 },
	{ "Nitrogen", NULL,		  NULL,		  1 << 7,		0,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
        { ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \
        { ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-x", "360", "-y", "352" , "-z", "1200", NULL };
static const char *termcmd[]  = { "st", NULL };

// static const char *rofiapps[] = { "sh", "/home/katsuki/scripts/rofi/launch.sh", "appmenu", NULL };

static const char *firefox[]  = { "firefox", NULL };
static const char *tg[]		  = { "telegram-desktop", NULL };
static const char *volup[]	  = { "sh", "/home/katsuki/scripts/misc/volume.sh", "up", NULL };
static const char *voldown[]  = { "sh", "/home/katsuki/scripts/misc/volume.sh", "down", NULL };
static const char *volmute[]  = { "sh", "/home/katsuki/scripts/misc/volume.sh", "mute", NULL };
static const char *pln[]	  = { "playerctl", "next", NULL };
static const char *plps[]	  = { "playerctl", "play-pause", NULL };
static const char *plp[]	  = { "playerctl", "prev", NULL };
static const char *scrnshtw[] = { "flameshot", "gui", NULL };
static const char *scrnshtf[] = { "flameshot", "full", "-p", "/home/katsuki/Pictures", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_n,      spawn,          {.v = dmenucmd} },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,						XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ ALTMOD,						XK_w,	   spawn,		   {.v = firefox } },
	{ ALTMOD,						XK_e,	   spawn,		   {.v = tg } },
	{ ALTMOD,						XK_a,	   spawn,		   {.v = voldown } },
	{ ALTMOD,						XK_s,	   spawn,		   {.v = volup } },
	{ ALTMOD,						XK_d,	   spawn,		   {.v = volmute } },
	{ ALTMOD,						XK_f,	   spawn,		   {.v = plp} },
	{ ALTMOD,						XK_g,	   spawn,		   {.v = plps} },
	{ ALTMOD,						XK_b,	   spawn,		   {.v = pln} },
	{ MODKEY|ControlMask,		    XK_p,	   spawn,		   {.v = scrnshtw} },
	{ MODKEY|ShiftMask,				XK_p,	   spawn,		   {.v = scrnshtf} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

