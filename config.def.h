/* See LICENSE file for copyright and license details. */

/* patches */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int swallowfloating         = 1;   /* 1 means swallow floating windows by default */
static const int splitstatus             = 1;        /* 1 for split status items */
static const char *splitdelim            = ";";       /* Character used for separating status */
static const unsigned int minwsz         = 20;       /* Minimal heigt of a client for smfact */
static const float smfact                = 0.00; /* factor of tiled clients [0.00..0.95] */


/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:10";
static const char col_gray1[]       = "#181818";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#f05577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                    instance        title                tags mask isfloating isterminal noswallow isfakefullscreen switchtotag monitor */
	{ "Gimp",                   NULL,           NULL,                 1 << 7,   1,         0,         0,        0,               1,            -1 },
	{ "St",                     NULL,           NULL,                 0,        0,         1,         1,        0,               1,            -1 },
	{ "org.gnome.Nautilus",     NULL,           NULL,                 1 << 1,   1,         0,         0,        0,               1,            -1 },
	{ "Subl4",                  NULL,           NULL,                 1 << 4,   1,         0,         0,        0,               1,            -1 },
	{ "iwgtk",                  NULL,           NULL,                 0,        1,         0,         0,        0,               1,            -1 },
	{ "Vlc",                    NULL,           NULL,                 0,        1,         0,         0,        1,               1,            -1 },
	{ "mpv",                    NULL,           NULL,                 0,        1,         0,         0,        1,               1,            -1 },
	{ "libreoffice-startcenter",NULL,           NULL,                 1 << 1,   1,         0,         0,        0,               1,            -1 },
	{ "jetbrains-pycharm-ce",   NULL,           NULL,                 1 << 7,   0,         0,         0,        0,               1,            -1 },
	{ "Matplotlib",             NULL,           NULL,                 0,        1,         0,         0,        0,               0,            -1 },
	{ "Cursor",                "cursor",        NULL,                 1 << 6,   0,         0,         0,        0,               1,            -1 },
	{ "Chromium",               NULL,           NULL,                 1 << 3,   0,         0,         0,        1,               1,            -1 },
	{ "Nm-connection-editor",   NULL,           NULL,                 0,        0,         0,         0,        1,               1,            -1 },
	{ "Brave-browser",         "brave-browser", NULL,                 1 << 3,   0,         0,         0,        1,               1,            -1 },
	{ "Firefox",               "Navigator",    "Mozilla Firefox",     1 << 3,   0,         0,         0,        1,               1,            -1 },
	{ "Firefox",               "Toolkit",      "Picture-in-Picture",  1 << 3,   1,         0,         0,        1,               1,            -1 },
	{ NULL,                     NULL,          "LibreOffice",         1 << 1,   0,         0,         0,        0,               1,            -1 },
	{ NULL,                     NULL,          "Event Tester",        0,        0,         0,         1,        0,               0,            -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, newterm,        {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },

	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setsmfact,      {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setsmfact,      {.f = -0.05} },

    	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
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
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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
